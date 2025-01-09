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

#ifndef UDMF_COPY_FILE_H
#define UDMF_COPY_FILE_H

#include <string>
#include <vector>

#include "unified_data.h"
#include "async_task_params.h"

namespace OHOS {
namespace UDMF {

class UdmfCopyFile {
public:
    static UdmfCopyFile &GetInstance();
    Status Copy(std::unique_ptr<AsyncHelper> &asyncHelper);

private:
    UdmfCopyFile() = default;
    ~UdmfCopyFile() = default;
    int64_t GetTotalSize(const std::vector<std::string> &uris);
    bool IsDirectory(const std::string &path);
    std::string GetFileName(const std::string &path);
    std::string GetRealPath(const std::string& path);
    bool IsRemote(const std::string &uri);
    bool IsFile(const std::string &path);
    bool IsMediaUri(const std::string &uriPath);
    bool IsNormalUri(const std::string &path);

    // temp
    uint64_t GetFileSize(const std::string &path);
};

} // namespace UDMF
} // namespace OHOS
#endif /* UDMF_COPY_FILE_H */