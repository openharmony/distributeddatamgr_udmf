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

#define LOG_TAG "UdmfCopyFileMock"
#include "copy/file_copy_manager.h"

#include <cstring>
#include <dirent.h>
#include <fcntl.h>
#include <filesystem>
#include <limits>
#include <memory>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "logger.h"

namespace OHOS {
namespace Storage {
namespace DistributedFile {

FileCopyManager &FileCopyManager::GetInstance()
{
    static FileCopyManager instance;
    return instance;
}

int32_t FileCopyManager::Copy(const std::string &srcUri, const std::string &destUri, ProcessCallback &processCallback)
{
    return 0;
}

int32_t FileCopyManager::ExecRemote(std::shared_ptr<FileInfos> infos, ProcessCallback &processCallback)
{
    return 0;
}

int32_t FileCopyManager::Cancel(const bool isKeepFiles)
{
    return 0;
}

int32_t FileCopyManager::Cancel(const std::string &srcUri, const std::string &destUri, const bool isKeepFiles)
{
    return 0;
}

void FileCopyManager::DeleteResFile(std::shared_ptr<FileInfos> infos)
{
}

int32_t FileCopyManager::ExecLocal(std::shared_ptr<FileInfos> infos)
{
    return 0;
}

int32_t FileCopyManager::CopyFile(const std::string &src, const std::string &dest, std::shared_ptr<FileInfos> infos)
{
    return 0;
}

void fs_req_cleanup(uv_fs_t* req)
{
}

int32_t FileCopyManager::SendFileCore(std::shared_ptr<FDGuard> srcFdg,
    std::shared_ptr<FDGuard> destFdg, std::shared_ptr<FileInfos> infos)
{
    return 0;
}

int32_t FileCopyManager::CopyDirFunc(const std::string &src, const std::string &dest, std::shared_ptr<FileInfos> infos)
{
    return 0;
}

int32_t FileCopyManager::CopySubDir(const std::string &srcPath,
    const std::string &destPath, std::shared_ptr<FileInfos> infos)
{
    return 0;
}

int32_t FileCopyManager::RecurCopyDir(const std::string &srcPath,
    const std::string &destPath, std::shared_ptr<FileInfos> infos)
{
    return 0;
}

void FileCopyManager::AddFileInfos(std::shared_ptr<FileInfos> infos)
{
}

void FileCopyManager::RemoveFileInfos(std::shared_ptr<FileInfos> infos)
{
}

int32_t FileCopyManager::CreateFileInfos(const std::string &srcUri,
    const std::string &destUri, std::shared_ptr<FileInfos> &infos)
{
    return 0;
}
 
std::string GetModeFromFlags(unsigned int flags)
{
    return 0;
}
 
int32_t FileCopyManager::OpenSrcFile(const std::string &srcPth, std::shared_ptr<FileInfos> infos, int32_t &srcFd)
{
    return 0;
}
 
int FileCopyManager::MakeDir(const std::string &path)
{
    return 0;
}
 
bool FileCopyManager::IsRemoteUri(const std::string &uri)
{
    return true;
}

bool FileCopyManager::IsMediaUri(const std::string &uriPath)
{
    return true;
}
 
int32_t FileCopyManager::CheckOrCreatePath(const std::string &destPath)
{
    return 0;
}
} // namespace DistributedFile
} // namespace Storage
} // namespace OHOS