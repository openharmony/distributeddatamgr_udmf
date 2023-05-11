/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "uri_permission_manager.h"

#include "want.h"
#include "uri.h"

#include "logger.h"

namespace OHOS {
namespace UDMF {
UriPermissionManager &UriPermissionManager::GetInstance()
{
    static UriPermissionManager instance;
    return instance;
}

Status UriPermissionManager::GrantUriPermission(const std::string &path, const std::string &bundleName)
{
    if (uriPermissionManager_ == nullptr) {
        uriPermissionManager_ = AAFwk::UriPermissionManagerClient::GetInstance();
    }
    Uri uri(path);
    int autoRemove = 1;
    auto status = uriPermissionManager_->GrantUriPermission(uri, AAFwk::Want::FLAG_AUTH_READ_URI_PERMISSION,
                                                            bundleName, autoRemove);
    if (status != ERR_OK) {
        LOG_ERROR(UDMF_FRAMEWORK, "GrantUriPermission failed, %{public}d", status);
        return E_ERROR;
    }
    return E_OK;
}
} // namespace UDMF
} // namespace OHOS
