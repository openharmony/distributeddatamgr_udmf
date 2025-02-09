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

#ifndef ASYNC_TASK_PARAMS_H
#define ASYNC_TASK_PARAMS_H

#include <map>
#include <mutex>
#include <string>

#ifndef IOS_PLATFORM
#include "executor_pool.h"
#endif
#include "progress_queue.h"
#include "unified_types.h"
#include "unified_data.h"

namespace OHOS::UDMF {
enum class FileConflictOptions: uint32_t {
    OVERWRITE = 0,
    SKIP = 1
};

enum class ProgressIndicator: uint32_t {
    NONE = 0,
    DEFAULT = 1
};

using ProgressListener = std::function<void(ProgressInfo progressInfo, std::shared_ptr<UnifiedData> data)>;

struct GetDataParams {
public:
    FileConflictOptions fileConflictOptions;
    ProgressIndicator progressIndicator;
    ProgressListener progressListener;
    std::string destUri;
    QueryOption query;
};

struct AsyncHelper {
    uint32_t sycnRetryTime = 0;
    int32_t lastProgress = 0;
    ProgressIndicator progressIndicator;
    ExecutorPool::TaskId invokeHapTask = ExecutorPool::INVALID_TASK_ID;
    ExecutorPool::TaskId getDataTask = ExecutorPool::INVALID_TASK_ID;
    ExecutorPool::TaskId progressTask = ExecutorPool::INVALID_TASK_ID;
    ProgressListener progressListener;
    FileConflictOptions fileConflictOptions;
    std::string businessUdKey;
    std::string processKey;
    std::string cancelKey;
    std::string destUri;
    std::shared_ptr<UnifiedData> data = std::make_shared<UnifiedData>();
    ProgressQueue progressQueue;
};

enum ListenerStatus: int32_t {
    FINISHED = 0,
    PROCESSING,
    CANCEL,
    INNER_ERROR = 200,
    INVALID_PARAMETERS,
    DATA_NOT_FOUND,
    SYNC_FAILED,
    COPY_FILE_FAILED,
};

enum ProgressStatus {
    NORMAL_PASTE = 0,
    CANCEL_PASTE = 1,
    PASTE_TIME_OUT = 2,
};

} // namespace OHOS::UDMF
#endif // ASYNC_TASK_PARAMS_H