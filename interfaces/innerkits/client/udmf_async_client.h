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

#ifndef UDMF_ASYNC_CLIENT_H
#define UDMF_ASYNC_CLIENT_H

#include "async_task_params.h"

namespace OHOS::UDMF {
class UdmfAsyncClient {
public:
    friend class UdmfCopyFile;
    static UdmfAsyncClient API_EXPORT &GetInstance();
    Status API_EXPORT StartAsyncDataRetrieval(const GetDataParams &params);
    Status API_EXPORT Cancel(std::string businessUdKey);
    Status CancelOnSingleTask();
private:
    UdmfAsyncClient();
    ~UdmfAsyncClient() = default;
    UdmfAsyncClient(const UdmfAsyncClient &obj) = delete;
    UdmfAsyncClient &operator = (const UdmfAsyncClient &obj) = delete;

    Status ProgressTask(const std::string &businessUdKey);
    Status GetDataTask(const QueryOption &query);
    Status InvokeHapTask(const std::string &businessUdKey);

    Status RegisterAsyncHelper(const GetDataParams &params);
    Status CheckSync(std::unique_ptr<AsyncHelper> &asyncHelper, const QueryOption &query);
    Status GetDataFromDB(std::unique_ptr<AsyncHelper> &asyncHelper, const QueryOption &query);
    Status GetDataFromCache(std::unique_ptr<AsyncHelper> &asyncHelper, const QueryOption &query);
    Status SetProgressData(const std::string &businessUdKey);
    Status SetCancelData(const std::string &businessUdKey);
    Status UpdateProgressData(const std::string &progressUdKey, const ProgressInfo &progressInfo);
    Status CopyFile(std::unique_ptr<AsyncHelper> &asyncHelper);
    void CallProgress(std::unique_ptr<AsyncHelper> &asyncHelper, ProgressInfo &progressInfo,
        std::shared_ptr<UnifiedData> data);
    Status Clear(const std::string &businessUdKey);
    Status ProcessUnifiedData(std::unique_ptr<AsyncHelper> &asyncHelper);
    bool IsParamValid(const GetDataParams &params);

#ifndef IOS_PLATFORM
    ExecutorPool executor_;
#endif
    std::unordered_map<std::string, std::unique_ptr<AsyncHelper>> asyncHelperMap_;
    std::mutex mutex_;
};
} // namespace
#endif // UDMF_ASYNC_CLIENT_H
