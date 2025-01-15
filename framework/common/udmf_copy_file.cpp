/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#define LOG_TAG "UdmfCopyFile"

#include "udmf_copy_file.h"

#include <filesystem>
#include <sys/stat.h>
#include <unistd.h>
#include "copy/file_copy_manager.h"
#include "copy/file_size_utils.h"
#include "file_uri.h"
#include "logger.h"
#include "udmf_async_client.h"

namespace OHOS {
namespace UDMF {
static constexpr const char* NETWORK_PARA = "?networkid=";
static constexpr int32_t PROGRESS_COPY_START = 20;
static constexpr int32_t PROGRESS_INCRE = 80;
static constexpr int32_t MAX_PROGRESS = 99;
static constexpr int32_t DFS_CANCEL_STATUS = 204;

UdmfCopyFile &UdmfCopyFile::GetInstance()
{
    static UdmfCopyFile udmfCopyFile;
    return udmfCopyFile;
}

Status UdmfCopyFile::Copy(std::unique_ptr<AsyncHelper> &asyncHelper)
{
    CopyContext context(asyncHelper);

    if (context.asyncHelper->progressQueue.IsCancel()) {
        LOG_INFO(UDMF_CLIENT, "Copy file cancel");
        return E_COPY_CANCELED;
    }

    if (!IsDirectory(context.asyncHelper->destUri, false)) {
        LOG_ERROR(UDMF_CLIENT, "DestUri is not directory.");
        return E_FS_ERROR;
    }

    for (const auto &record : context.asyncHelper->data->GetRecords()) {
        if (!HandleRecord(record, context)) {
            break;
        }
    }

    context.asyncHelper->data = context.processedData;
    LOG_INFO(UDMF_CLIENT, "Copy end.");
    return context.status;
}

bool UdmfCopyFile::HandleRecord(const std::shared_ptr<UnifiedRecord> &record, CopyContext &context)
{
    std::string srcUri;
    if (!record->HasFileType(srcUri)) {
        context.processedData->AddRecord(record);
        return true;
    }

    if (IsDirectory(srcUri, true)) {
        LOG_ERROR(UDMF_CLIENT, "Source cannot be directory.");
        context.status = E_COPY_FILE_FAILED;
        return true;
    }

    std::string destFileUri = ConstructDestUri(context.asyncHelper->destUri, srcUri);

    if (context.asyncHelper->fileConflictOptions == FileConflictOptions::SKIP && IsFile(destFileUri, false)) {
        LOG_INFO(UDMF_CLIENT, "File has existed, skip.");
        return true;
    }

    return CopyFile(srcUri, destFileUri, record, context);
}

bool UdmfCopyFile::CopyFile(const std::string &srcUri, const std::string &destFileUri,
                            const std::shared_ptr<UnifiedRecord> &record, CopyContext &context)
{
    uint64_t fileSize = 0;
    using ProcessCallBack = std::function<void(uint64_t processSize, uint64_t totalFileSize)>;

    ProcessCallBack listener = [&](uint64_t processSize, uint64_t totalFileSize) {
        fileSize = totalFileSize;
        HandleProgress(srcUri, destFileUri, context, processSize);
    };

    auto ret = Storage::DistributedFile::FileCopyManager::GetInstance()->Copy(srcUri, destFileUri, listener);

    if (ret == DFS_CANCEL_STATUS) {
        context.status = E_COPY_CANCELED;
        return false;
    } else if (ret != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "Copy failed. errno=%{public}d", ret);
        context.status = E_COPY_FILE_FAILED;
        return true;
    }

    context.finishSize += fileSize;
    record->SetFileUri(destFileUri);
    context.processedData->AddRecord(record);
    return true;
}

void UdmfCopyFile::HandleProgress(const std::string &srcUri, const std::string &destFileUri, CopyContext &context, uint64_t processSize)
{
    if (context.asyncHelper->progressQueue.IsCancel()) {
        LOG_INFO(UDMF_CLIENT, "Cancel copy.");
        std::thread([&]() {
            auto ret = Storage::DistributedFile::FileCopyManager::GetInstance()->Cancel(srcUri, destFileUri);
            if (ret != E_OK) {
                LOG_ERROR(UDMF_CLIENT, "Cancel failed. errno=%{public}d", ret);
                context.status = E_COPY_FILE_FAILED;
            }
        }).detach();
        return;
    }

    context.totalSize = std::max(context.totalSize, uint64_t(1));
    auto processNum = std::min(PROGRESS_COPY_START +
        int32_t((context.finishSize + processSize) * PROGRESS_INCRE / context.totalSize), MAX_PROGRESS);
    ProgressInfo progressInfo = { .progress = processNum, .errorCode = E_OK };
    UdmfAsyncClient::GetInstance().CallProgress(context.asyncHelper, progressInfo, nullptr);
}

std::string UdmfCopyFile::ConstructDestUri(const std::string &destUri, const std::string &srcUri)
{
    std::string destFileUri = destUri;
    if (destFileUri.back() != '/') {
        destFileUri += '/';
    }
    destFileUri += GetFileName(srcUri);
    return destFileUri;
}

int64_t UdmfCopyFile::GetTotalSize(const std::vector<std::string> &uris)
{
    int64_t totalSize = 0;
    std::string srcUri;
    for (const auto &srcUri : uris) {
        if (IsFile(srcUri, true)) {
            totalSize += GetFileSize(srcUri, true);
        }
    }
    return totalSize;
}

bool UdmfCopyFile::IsDirectory(const std::string &uri, bool isSource)
{
    bool isDir = false;
    auto ret = Storage::DistributedFile::FileSizeUtils::IsDirectory(uri, isSource, isDir);
    if (ret != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "Is dir failed. errno=%{public}d", ret);
        return false;
    }
    return isDir;
}

bool UdmfCopyFile::IsRemote(const std::string &uri)
{
    return uri.find(NETWORK_PARA) != uri.npos;
}

std::string UdmfCopyFile::GetFileName(const std::string &path)
{
    std::string realSrc = path;
    if (IsRemote(path)) {
        int index = path.rfind("?", 0);
        realSrc = path.substr(0, index);
    }
    std::filesystem::path filePath(realSrc);
    return filePath.filename();
}

bool UdmfCopyFile::IsFile(const std::string &uri, bool isSource)
{
    bool isDir = false;
    auto ret = Storage::DistributedFile::FileSizeUtils::IsDirectory(uri, isSource, isDir);
    if (ret != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "Is dir failed. errno=%{public}d", ret);
        return false;
    }
    return !isDir;
}

uint64_t UdmfCopyFile::GetFileSize(const std::string &uri, bool isSource)
{
    uint64_t size = 0;
    auto ret = Storage::DistributedFile::FileSizeUtils::GetSize(uri, isSource, size);
    if (ret != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "Get size failed. errno=%{public}d", ret);
        return 0;
    }
    return size;
}
} // namespace UDMF
} // namespace OHOS