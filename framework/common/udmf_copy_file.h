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
    struct CopyContext {
        std::unique_ptr<AsyncHelper> &asyncHelper;
        uint64_t finishSize = 0;
        uint64_t totalSize = 0;
        Status status = E_OK;
        std::shared_ptr<UnifiedData> processedData;

        CopyContext(std::unique_ptr<AsyncHelper> &helper)
            : asyncHelper(helper),
            totalSize(UdmfCopyFile::GetInstance().GetTotalSize(helper->data->GetFileUris())),
            processedData(std::make_shared<UnifiedData>()) {}
    };

    UdmfCopyFile() = default;
    ~UdmfCopyFile() = default;

    bool HandleRecord(const std::shared_ptr<UnifiedRecord> &record, CopyContext &context);
    bool CopyFile(const std::string &srcUri, const std::string &destFileUri,
        const std::shared_ptr<UnifiedRecord> &record, CopyContext &context);
    void HandleProgress(const std::string &srcUri, const std::string &destFileUri,
        CopyContext &context, uint64_t processSize);
    std::string ConstructDestUri(const std::string &destUri, const std::string &srcUri);
    int64_t GetTotalSize(const std::vector<std::string> &uris);
    bool IsDirectory(const std::string &uri, bool isSource);
    std::string GetFileName(const std::string &path);
    bool IsRemote(const std::string &uri);
    bool IsFile(const std::string &uri, bool isSource);
    uint64_t GetFileSize(const std::string &uri, bool isSource);
};
 
} // namespace UDMF
} // namespace OHOS
#endif /* UDMF_COPY_FILE_H */