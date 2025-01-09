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
#include "file_uri.h"
#include "logger.h"
#include "udmf_async_client.h"

namespace OHOS {
namespace UDMF {
constexpr const char* NETWORK_PARA = "?networkid=";
constexpr const char* MEDIA_BUNDLE = "media";
static constexpr int32_t PROGRESS_GET_DATA_FINISHED = 20;

UdmfCopyFile &UdmfCopyFile::GetInstance()
{
    static UdmfCopyFile pasteBoardCopyFile;
    return pasteBoardCopyFile;
}

int32_t UdmfCopyFile::CopyPasteData(const std::vector<std::string> &uris, std::unique_ptr<AsyncHelper> &asyncHelper)
{
    if (!IsDirectory(asyncHelper->destUri)) {
        LOG_ERROR(UDMF_CLIENT, "DestUri is not directory.");
        return E_FS_ERROR;
    }
    uint64_t finishSize = 0;
    uint64_t totalSize = GetTotalSize(uris);
    
    Status status = E_OK;
    for (size_t i = 0; i < uris.size(); i++) {
        if (asyncHelper->progressQueue.IsCancel()) {
            status = E_COPY_FILE_FAILED;
            break;
        }
        std::string srcUri = uris[i];
        if (IsDirectory(srcUri)) {
            LOG_ERROR(UDMF_CLIENT, "Source cannot be directory.");
            status = E_COPY_FILE_FAILED;
            continue;
        }
        std::string fileName = GetFileName(srcUri);
        std::string destFileUri = asyncHelper->destUri;
        if (destFileUri.back() != '/') {
            destFileUri += '/';
        }
        destFileUri = asyncHelper->destUri + fileName;
        std::error_code errCode;
        if (std::filesystem::exists(destFileUri, errCode)
            && errCode.value() == E_OK
            && asyncHelper->fileConflictOptions == SKIP) {
            LOG_INFO(UDMF_CLIENT, "File has existed, skip.");
            continue;
        }
        let listener = [&] (uint64_t processSize, uint64_t totalSize) {
            auto status = E_OK;
            if (asyncHelper->progressQueue.IsCancel()) {
                status = E_COPY_FILE_FAILED;
                // cancel();
            }
            finishSize += processSize;
            auto processNum = PROGRESS_GET_DATA_FINISHED + finishSize / totalSize * 80 - 1;
            ProgressInfo progressInfo = { .progress = processNum, .errorCode = status };
            UdmfAsyncClient::GetInstance().CallProgress(asyncHelper, progressInfo, nullptr);
        }
        // copy(srcUri, destFileUri, listener);
    }
    return status;
}

int32_t UdmfCopyFile::GetTotalSize(const std::vector<std::string> &uris)
{
    int32_t g_totalSize = 0;
    std::string srcUri;
    std::string srcPath;
    bool isFile;
    for (const auto &srcUri : uris) {
        AppFileService::ModuleFileUri::FileUri srcFileUri(srcUri);
        srcPath = srcFileUri.GetRealPath();
        srcPath = GetRealPath(srcPath);
        isFile = IsFile(srcPath);
        if (isFile) {
            g_totalSize += GetFileSize(srcPath);
        }
    }
    return g_totalSize;
}

std::string UdmfCopyFile::GetRealPath(const std::string& path)
{
    std::filesystem::path tempPath(path);
    std::filesystem::path realPath{};
    for (const auto& component : tempPath) {
        if (component == ".") {
            continue;
        } else if (component == "..") {
            realPath = realPath.parent_path();
        } else {
            realPath /= component;
        }
    }
    return realPath.string();
}

bool UdmfCopyFile::IsDirectory(const std::string &path)
{
    struct stat buf {};
    int ret = stat(path.c_str(), &buf);
    if (ret == -1) {
        LOG_ERROR(UDMF_CLIENT, "Stat failed. errno=%{public}d", errno);
        return false;
    }
    return (buf.st_mode & S_IFMT) == S_IFDIR;
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

bool UdmfCopyFile::IsFile(const std::string &path)
{
    return IsNormalUri(path) || IsNormalUri(path);
}

bool UdmfCopyFile::IsNormalUri(const std::string &path)
{
    struct stat buf {};
    int ret = stat(path.c_str(), &buf);
    if (ret == -1) {
        LOG_ERROR(UDMF_CLIENT, "Stat failed. errno=%{public}d", errno);
        return false;
    }
    return (buf.st_mode & S_IFMT) == S_IFREG;
}

bool UdmfCopyFile::IsMediaUri(const std::string &uriPath)
{
    Uri uri(uriPath);
    std::string bundleName = uri.GetAuthority();
    return bundleName == MEDIA_BUNDLE;
}

uint64_t UdmfCopyFile::GetFileSize(const std::string &path)
{
    return 100;
}
} // namespace UDMF
} // namespace OHOS