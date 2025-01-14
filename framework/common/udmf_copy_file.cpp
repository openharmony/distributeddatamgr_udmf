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
static constexpr char* NETWORK_PARA = "?networkid=";
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
    if (asyncHelper->progressQueue.IsCancel()) {
        LOG_INFO(UDMF_CLIENT, "Copy file cancel");
        return E_COPY_CANCELED;
    }
    if (!IsDirectory(asyncHelper->destUri, false)) {
        LOG_ERROR(UDMF_CLIENT, "DestUri is not directory.");
        return E_FS_ERROR;
    }
    auto uris = asyncHelper->data->GetFileUris();
    LOG_INFO(UDMF_CLIENT, "Uris size=%{public}zu", uris.size());
    uint64_t finishSize = 0;
    uint64_t totalSize = GetTotalSize(uris);
    
    Status status = E_OK;
    for (size_t i = 0; i < uris.size(); i++) {
        std::string srcUri = uris[i];
        if (IsDirectory(srcUri, true)) {
            LOG_ERROR(UDMF_CLIENT, "Source cannot be directory.");
            status = E_COPY_FILE_FAILED;
            continue;
        }
        std::string fileName = GetFileName(srcUri);
        std::string destFileUri = asyncHelper->destUri;
        if (destFileUri.back() != '/') {
            destFileUri += '/';
        }
        destFileUri += fileName;

        if (asyncHelper->fileConflictOptions == FileConflictOptions::SKIP && IsFile(destFileUri, false)) {
            LOG_INFO(UDMF_CLIENT, "File has existed, skip.");
            continue;
        }

        uint64_t fileSize = 0;
        using ProcessCallBack = std::function<void(uint64_t processSize, uint64_t totalFileSize)>;   
        ProcessCallBack listener = [&] (uint64_t processSize, uint64_t totalFileSize) {
            if (asyncHelper->progressQueue.IsCancel()) {
                LOG_INFO(UDMF_CLIENT, "Cancel copy.");
                std::thread([&]() {
                    auto ret = Storage::DistributedFile::FileCopyManager::GetInstance()->Cancel(srcUri, destFileUri);
                    if (ret != E_OK) {
                        LOG_ERROR(UDMF_CLIENT, "Cancel failed. errno=%{public}d", ret);
                        status = E_COPY_FILE_FAILED;
                    }
                }).detach();
            }
            fileSize = totalFileSize;
            auto processNum = std::min(PROGRESS_COPY_START + int32_t((finishSize + processSize) * PROGRESS_INCRE / totalSize), MAX_PROGRESS);
            ProgressInfo progressInfo = { .progress = processNum, .errorCode = E_OK };
            UdmfAsyncClient::GetInstance().CallProgress(asyncHelper, progressInfo, nullptr);
        };
        auto ret = Storage::DistributedFile::FileCopyManager::GetInstance()->Copy(srcUri, destFileUri, listener);
        if (ret == DFS_CANCEL_STATUS) {
            status = E_COPY_CANCELED;
            break;
        } else if (ret != E_OK) {
            LOG_ERROR(UDMF_CLIENT, "Copy failed. errno=%{public}d", ret);
            status = E_COPY_FILE_FAILED;
            continue;
        }
        finishSize += fileSize;
    }
    LOG_INFO(UDMF_CLIENT, "Copy end.");
    return status;
}

int64_t UdmfCopyFile::GetTotalSize(const std::vector<std::string> &uris)
{
    int64_t g_totalSize = 0;
    std::string srcUri;
    for (const auto &srcUri : uris) {
        if (IsFile(srcUri, true)) {
            g_totalSize += GetFileSize(srcUri, true);
        }
    }
    return g_totalSize;
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