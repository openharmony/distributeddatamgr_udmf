/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#define LOG_TAG "UdmfAsyncClient"

#include "udmf_async_client.h"

#include "logger.h"
#include "plain_text.h"
#include "udmf_client.h"
#include "udmf_copy_file.h"
#include "udmf_service_client.h"

namespace OHOS::UDMF {
static constexpr size_t MAX_THREADS = 10;
static constexpr size_t MIN_THREADS = 0;

static constexpr int32_t START_ABILITY_INTERVAL = 500;
static constexpr int32_t READ_PROGRESS_INTERVAL = 100;
static constexpr int32_t SYNC_INTERVAL = 200;
static constexpr int32_t MAX_SYNC_TIMES = 14;

static std::unordered_map<Status, int32_t> STATUS_MAP = {
    { E_INVALID_PARAMETERS, ListenerStatus::INVALID_PARAMETERS },
    { E_NOT_FOUND, ListenerStatus::DATA_NOT_FOUND },
    { E_SYNC_FAILED, ListenerStatus::SYNC_FAILED },
    { E_COPY_FILE_FAILED, ListenerStatus::COPY_FILE_FAILED }
};

static constexpr int32_t PROGRESS_ERROR = -1;
static constexpr int32_t PROGRESS_INIT = 0;
static constexpr int32_t PROGRESS_SYNC_FINSHED = 10;
static constexpr int32_t PROGRESS_GET_DATA_FINISHED = 20;
static constexpr int32_t PROGRESS_ALL_FINISHED = 100;

UdmfAsyncClient::UdmfAsyncClient() : executor_(MAX_THREADS, MIN_THREADS) {}

UdmfAsyncClient &UdmfAsyncClient::GetInstance()
{
    static UdmfAsyncClient instance;
    return instance;
}

Status UdmfAsyncClient::StartAsyncDataRetireval(const GetDataParams &params)
{
    if (!IsParamValid(params)) {
        return E_INVALID_PARAMETERS;
    }
    auto status = RegisterAsyncHelper(params);
    if (status != E_OK) {
        return status;
    }
    auto &asyncHelper = asyncHelperMap_.at(params.query.key);
    if (params.progressIndicator == ProgressIndicator::DEFAULT) {
        asyncHelper->progressQueue.SetClearable(false);
        asyncHelper->invokeHapTask = executor_.Schedule(std::chrono::milliseconds(START_ABILITY_INTERVAL),
            (std::bind(&UdmfAsyncClient::InvokeHapTask, this, params.query.key)));
    }
    asyncHelper->getDataTask = executor_.Execute(std::bind(&UdmfAsyncClient::GetDataTask, this, params.query));
    asyncHelper->progressTask = executor_.Execute(std::bind(&UdmfAsyncClient::ProgressTask, this, params.query.key));
    return E_OK;
}

Status UdmfAsyncClient::Cancel(std::string businessUdKey)
{
    std::lock_guard<std::mutex> lockMap(mutex_);
    if (asyncHelperMap_.find(businessUdKey) == asyncHelperMap_.end()) {
        LOG_ERROR(UDMF_CLIENT, "No task can Cancel, key=%{public}s", businessUdKey.c_str());
        return E_ERROR;
    }
    auto &asyncHelper = asyncHelperMap_.at(businessUdKey);
    asyncHelper->progressQueue.Cancel();
    return E_OK;
}

Status UdmfAsyncClient::ProgressTask(const std::string &businessUdKey)
{
    auto &asyncHelper = asyncHelperMap_.at(businessUdKey);
    if (asyncHelper->progressIndicator == ProgressIndicator::DEFAULT) {
        auto status = SetProgressData(businessUdKey);
        if (status != E_OK) {
            Clear(businessUdKey);
            return status;
        }
        status = SetCancelData(businessUdKey);
        if (status != E_OK) {
            Clear(businessUdKey);
            return status;
        }
    }
    while (asyncHelper->lastProgress >= PROGRESS_INIT && asyncHelper->lastProgress < PROGRESS_ALL_FINISHED) {
        HandleCancelStatus(asyncHelper);
        if (asyncHelper->progressQueue.IsCancel()) {
            break;
        }
        auto pair = asyncHelper->progressQueue.Poll();
        if (!pair.first) {
            std::this_thread::sleep_for(std::chrono::milliseconds(READ_PROGRESS_INTERVAL));
            continue;
        }
        auto progressInfo = pair.second;
        if (progressInfo->progress >= PROGRESS_INIT && progressInfo->progress <= asyncHelper->lastProgress) {
            continue;
        }
        asyncHelper->lastProgress = progressInfo->progress;
        if (asyncHelper->progressIndicator == ProgressIndicator::DEFAULT) {
            UpdateProgressData(asyncHelper->processKey, *progressInfo);
        }
    }
    Clear(businessUdKey);
    return E_OK;
}

Status UdmfAsyncClient::GetDataTask(const QueryOption &query)
{
    auto &asyncHelper = asyncHelperMap_.at(query.key);
    if (GetDataFromCache(asyncHelper, query) == E_OK) {
        ProcessUnifiedData(asyncHelper);
        return E_OK;
    }
    return CheckSync(asyncHelper, query);
}

Status UdmfAsyncClient::InvokeHapTask(const std::string &businessUdKey)
{
    LOG_INFO(UDMF_CLIENT, "InvokeHap start!");
    auto &asyncHelper = asyncHelperMap_.at(businessUdKey);
    if (asyncHelper->progressQueue.IsCancel()) {
        LOG_INFO(UDMF_CLIENT, "Finished, not invoke hap.");
        return E_OK;
    }
    if (asyncHelper->processKey.empty() || asyncHelper->cancelKey.empty()) {
        LOG_ERROR(UDMF_CLIENT, "Get key failed, not invoke hap.");
        return E_ERROR;
    }
    auto status = UdmfServiceClient::GetInstance()->InvokeHap(asyncHelper->processKey, asyncHelper->cancelKey);
    if (status != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "Invoke hap failed, status=%{public}d", status);
        return E_ERROR;
    }
    return E_OK;
}

Status UdmfAsyncClient::RegisterAsyncHelper(const GetDataParams &params)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (asyncHelperMap_.find(params.query.key) != asyncHelperMap_.end()) {
        LOG_ERROR(UDMF_CLIENT, "The same task is running, key = %{public}s", params.query.key.c_str());
        return E_IDEMPOTENT_ERROR;
    }
    auto asyncHelper = std::make_unique<AsyncHelper>();
    asyncHelper->businessUdKey = params.query.key;
    asyncHelper->progressListener = params.progressListener;
    asyncHelper->progressIndicator = params.progressIndicator;
    asyncHelper->fileConflictOptions = params.fileConflictOptions;
    asyncHelper->destUri = params.destUri;
    asyncHelperMap_.insert_or_assign(params.query.key, std::move(asyncHelper));
    return E_OK;
}

Status UdmfAsyncClient::CheckSync(std::unique_ptr<AsyncHelper> &asyncHelper, const QueryOption &query)
{
    AsyncProcessInfo processInfo = {
        .businessUdKey = query.key
    };
    auto serviceClient = UdmfServiceClient::GetInstance();
    if (serviceClient == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "UdmfServiceClient GetInstance failed");
        return E_IPC;
    }
    auto status = serviceClient->ObtainAsynProcess(processInfo);
    if (status != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "Sync error status = %{public}d!", status);
        ProgressInfo progressInfo = { .progress = PROGRESS_ERROR, .errorCode = E_ERROR };
        CallProgress(asyncHelper, progressInfo, nullptr);
        return static_cast<Status>(status);
    }
    if (processInfo.syncStatus == AsyncTaskStatus::ASYNC_FAILURE) {
        LOG_ERROR(UDMF_CLIENT, "Sync failed!");
        ProgressInfo progressInfo = { .progress = PROGRESS_ERROR, .errorCode = E_SYNC_FAILED };
        CallProgress(asyncHelper, progressInfo, nullptr);
        return E_ERROR;
    }
    if (processInfo.syncStatus == AsyncTaskStatus::ASYNC_SUCCESS) {
        ProgressInfo progressInfo = { .progress = PROGRESS_SYNC_FINSHED, .errorCode = E_OK };
        CallProgress(asyncHelper, progressInfo, nullptr);
        return GetDataFromDB(asyncHelper, query);
    }
    if (asyncHelper->sycnRetryTime > MAX_SYNC_TIMES) {
        LOG_ERROR(UDMF_CLIENT, "Sync retry timeout!");
        ProgressInfo progressInfo = { .progress = PROGRESS_ERROR, .errorCode = E_SYNC_FAILED };
        CallProgress(asyncHelper, progressInfo, nullptr);
        return E_SYNC_FAILED;
    }
    (asyncHelper->sycnRetryTime)++;
    asyncHelper->getDataTask = executor_.Schedule(std::chrono::milliseconds(SYNC_INTERVAL),
        std::bind(&UdmfAsyncClient::GetDataTask, this, query));
    return E_OK;
}

Status UdmfAsyncClient::GetDataFromDB(std::unique_ptr<AsyncHelper> &asyncHelper, const QueryOption &query)
{
    auto &data = *(asyncHelper->data);
    auto status = static_cast<Status>(UdmfServiceClient::GetInstance()->GetData(query, data));
    if (status != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "GetData error, status = %{public}d", status);
        ProgressInfo progressInfo = {
            .progress = PROGRESS_ERROR,
            .errorCode = status
        };
        CallProgress(asyncHelper, progressInfo, nullptr);
        return status;
    }
    return ProcessUnifiedData(asyncHelper);
}

Status UdmfAsyncClient::GetDataFromCache(std::unique_ptr<AsyncHelper> &asyncHelper, const QueryOption &query)
{
    return UdmfClient::GetInstance().GetDataFromCache(query, *(asyncHelper->data));
}

Status UdmfAsyncClient::SetProgressData(const std::string &businessUdKey)
{
    auto serviceClient = UdmfServiceClient::GetInstance();
    if (serviceClient == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "UdmfServiceClient GetInstance failed");
        return E_IPC;
    }
    std::string progressKey;
    CustomOption cusomOption = {
        .intention = Intention::UD_INTENTION_DATA_HUB
    };
    auto obj = std::make_shared<Object>();
    auto progressRecord = std::make_shared<PlainText>(UDType::PLAIN_TEXT, obj);
    progressRecord->SetContent(std::to_string(PROGRESS_INIT));
    UnifiedData progressData;
    progressData.AddRecord(progressRecord);
    auto status = serviceClient->SetData(cusomOption, progressData, progressKey);
    if (status != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "Set progress data error, status = %{public}d", status);
        return static_cast<Status>(status);
    }
    auto &asyncHelper = asyncHelperMap_.at(businessUdKey);
    asyncHelper->processKey = progressKey;
    return E_OK;
}

Status UdmfAsyncClient::SetCancelData(const std::string &businessUdKey)
{
    auto serviceClient = UdmfServiceClient::GetInstance();
    if (serviceClient == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "UdmfServiceClient GetInstance failed");
        return E_IPC;
    }
    std::string cancelKey;
    CustomOption cusomOption = {
        .intention = Intention::UD_INTENTION_DATA_HUB
    };
    auto obj = std::make_shared<Object>();
    auto progressRecord = std::make_shared<PlainText>(UDType::PLAIN_TEXT, obj);
    progressRecord->SetContent(std::to_string(PROGRESS_INIT));
    UnifiedData cancelData;
    cancelData.AddRecord(progressRecord);
    auto status = serviceClient->SetData(cusomOption, cancelData, cancelKey);
    if (status != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "Set cancel data error, status = %{public}d", status);
        return static_cast<Status>(status);
    }
    auto &asyncHelper = asyncHelperMap_.at(businessUdKey);
    asyncHelper->cancelKey = cancelKey;
    return E_OK;
}

Status UdmfAsyncClient::UpdateProgressData(const std::string &progressUdKey, const ProgressInfo &progressInfo)
{
    auto serviceClient = UdmfServiceClient::GetInstance();
    if (serviceClient == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "UdmfServiceClient GetInstance failed");
        return E_IPC;
    }
    QueryOption queryOption = {
        .key = progressUdKey,
        .intention = Intention::UD_INTENTION_DATA_HUB
    };
    auto obj = std::make_shared<Object>();
    auto progressRecord = std::make_shared<PlainText>(UDType::PLAIN_TEXT, obj);
    progressRecord->SetContent(std::to_string(progressInfo.progress));
    UnifiedData progressData;
    progressData.AddRecord(progressRecord);
    auto status = serviceClient->UpdateData(queryOption, progressData);
    if (status != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "Update progress data error, status = %{public}d", status);
        return static_cast<Status>(status);
    }
    return E_OK;
}

Status UdmfAsyncClient::CopyFile(std::unique_ptr<AsyncHelper> &asyncHelper)
{
    if (asyncHelper->destUri.empty()) {
        LOG_ERROR(UDMF_CLIENT, "No dest path, no copy.");
        return E_ERROR;
    }
    auto status = UdmfCopyFile::GetInstance().Copy(asyncHelper);
    ProgressInfo progressInfo = {
        .progress = PROGRESS_ALL_FINISHED,
        .errorCode = status
    };
    CallProgress(asyncHelper, progressInfo, asyncHelper->data);
    return E_OK;
}

void UdmfAsyncClient::CallProgress(std::unique_ptr<AsyncHelper> &asyncHelper, ProgressInfo &progressInfo,
    std::shared_ptr<UnifiedData> data)
{
    LOG_ERROR(UDMF_CLIENT, "progressInfo.errorCode = %{public}d", progressInfo.errorCode);
    if (progressInfo.errorCode == E_OK) {
        if (progressInfo.progress == PROGRESS_ALL_FINISHED) {
            progressInfo.progressStatus = ListenerStatus::FINISHED;
        } else {
            progressInfo.progressStatus = ListenerStatus::PROCESSING;
        }
    } else {
        auto it = STATUS_MAP.find(progressInfo.errorCode);
        if (it == STATUS_MAP.end()) {
            progressInfo.progressStatus = ListenerStatus::INNER_ERROR;
        } else {
            progressInfo.progressStatus = it->second;
        }
    }

    asyncHelper->progressListener(progressInfo, data);
    asyncHelper->progressQueue.PushBack(progressInfo);
}

Status UdmfAsyncClient::Clear(const std::string &businessUdKey)
{
    std::lock_guard<std::mutex> lockMap(mutex_);
    if (asyncHelperMap_.find(businessUdKey) == asyncHelperMap_.end()) {
        LOG_ERROR(UDMF_CLIENT, "No task can Clear, key=%{public}s", businessUdKey.c_str());
        return E_ERROR;
    }
    auto &asyncHelper = asyncHelperMap_.at(businessUdKey);
    if (!asyncHelper->progressQueue.Clear()) {
        return E_OK;
    }
    if (asyncHelper->invokeHapTask != ExecutorPool::INVALID_TASK_ID) {
        executor_.Remove(asyncHelper->invokeHapTask);
    }
    executor_.Remove(asyncHelper->getDataTask);
    executor_.Remove(asyncHelper->progressTask);
    asyncHelperMap_.erase(businessUdKey);
    UdmfServiceClient::GetInstance()->ClearAsynProcessByKey(businessUdKey);
    LOG_INFO(UDMF_CLIENT, "Clear task success, key = %{public}s", businessUdKey.c_str());
    return E_OK;
}

Status UdmfAsyncClient::ProcessUnifiedData(std::unique_ptr<AsyncHelper> &asyncHelper)
{
    if (!asyncHelper->data->HasFileType()) {
        ProgressInfo progressInfo = {
            .progress = PROGRESS_ALL_FINISHED,
            .errorCode = E_OK
        };
        CallProgress(asyncHelper, progressInfo, asyncHelper->data);
        return E_OK;
    }
    ProgressInfo progressInfo = {
        .progress = PROGRESS_GET_DATA_FINISHED,
        .errorCode = E_OK
    };
    CallProgress(asyncHelper, progressInfo, nullptr);
    return CopyFile(asyncHelper);
}

bool UdmfAsyncClient::IsParamValid(const GetDataParams &params)
{
    auto query = params.query;
    if (query.key.empty() || query.intention != Intention::UD_INTENTION_DRAG) {
        LOG_ERROR(UDMF_CLIENT, "Params query invalid. query.key=%{public}s, intention=%{public}d", query.key.c_str(),
            query.intention);
        return false;
    }
    if (params.progressListener == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Params progressListener not null.");
        return false;
    }
    return true;
}

Status UdmfAsyncClient::GetCancelStatus(const std::string &cancelKey, std::string &value)
{
    QueryOption option = { .key = cancelKey };
    std::vector<UnifiedData> data;
    UdmfServiceClient::GetInstance()->GetBatchData(option, data);
    if (data.empty()) {
        LOG_INFO(UDMF_CLIENT, "data is empty");
        return E_INVALID_PARAMETERS;
    }
    if (data[0].GetRecords().empty()) {
        LOG_INFO(UDMF_CLIENT, "Getrecords is empty");
        return E_INVALID_PARAMETERS;
    }
    auto outputRecord = data[0].GetRecordAt(0);
    if (outputRecord == nullptr) {
        LOG_INFO(UDMF_CLIENT, "outputRecord is nullptr");
        return E_INVALID_PARAMETERS;
    }
    auto plainText = outputRecord->GetValue();
    auto object = std::get<std::shared_ptr<Object>>(plainText);
    if (object == nullptr) {
        LOG_INFO(UDMF_CLIENT, "object is nullptr");
        return E_INVALID_PARAMETERS;
    }
    object->GetValue(UDMF::CONTENT, value);
    return E_OK;
}

void UdmfAsyncClient::HandleCancelStatus(std::unique_ptr<AsyncHelper> &asyncHelper)
{
    std::string defaultCancel = "0";
    int32_t cancelStatus = 0;
    auto ret = GetCancelStatus(asyncHelper->cancelKey, defaultCancel);
    if (ret != E_OK) {
        LOG_WARN(UDMF_CLIENT, "GetCancelStatus failed, status=%{public}d", ret);
        return;
    }
    try {
        cancelStatus = std::stoi(defaultCancel);
    } catch (const std::exception& e) {
        LOG_ERROR(UDMF_CLIENT, "cancelStatus error, cancelStatus=%{public}s", defaultCancel.c_str());
        return;
    }
    switch (cancelStatus) {
        case NORMAL_PASTE:
            break;
        case CANCEL_PASTE:
            LOG_INFO(UDMF_CLIENT, "Progress cancel paste");
            asyncHelper->progressQueue.Cancel();
            break;
        case PASTE_TIME_OUT:
            LOG_ERROR(UDMF_CLIENT, "Progress timed out");
            break;
        default:
            LOG_ERROR(UDMF_CLIENT, "status error, status=%{public}d", cancelStatus);
            break;
    }
}
} // namespace OHOS::UDMF
