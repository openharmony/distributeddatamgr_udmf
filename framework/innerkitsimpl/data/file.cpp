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
#include "file.h"

namespace OHOS {
namespace UDMF {
namespace {
void UpdateUriAuthorizationPolicies(const std::shared_ptr<Object> &object,
    const std::vector<UriPermission> &uriAuthorizationPolicies)
{
    if (object == nullptr) {
        return;
    }
    if (uriAuthorizationPolicies.empty()) {
        object->value_.erase(URI_AUTHORIZATION_POLICIES);
        return;
    }
    uint32_t permissionMask = UriPermissionUtil::ToMask(uriAuthorizationPolicies);
    object->value_[URI_AUTHORIZATION_POLICIES] = static_cast<int32_t>(permissionMask);
}
} // namespace

File::File() : UnifiedRecord(FILE)
{
    SetType(FILE);
    utdId2_ = GENERAL_FILE_URI;
}

File::File(const std::string &uri) : UnifiedRecord(FILE)
{
    SetType(FILE);
    this->oriUri_ = uri;
    utdId2_ = GENERAL_FILE_URI;
}

File::File(UDType type, ValueType value) : UnifiedRecord(type, value)
{
    SetType(FILE);
    utdId2_ = GENERAL_FILE_URI;
    if (std::holds_alternative<std::string>(value)) {
        oriUri_ = std::get<std::string>(value);
    } else if (std::holds_alternative<std::shared_ptr<Object>>(value)) {
        auto object = std::get<std::shared_ptr<Object>>(value);
        object->GetValue(ORI_URI, oriUri_);
        object->GetValue(REMOTE_URI, remoteUri_);
        object->GetValue(FILE_TYPE, fileType_);
        int32_t permissionMask = 0;
        if (object->GetValue(URI_AUTHORIZATION_POLICIES, permissionMask) && permissionMask >= 0) {
            uriAuthorizationPolicies_ = UriPermissionUtil::FromMask(static_cast<uint32_t>(permissionMask));
        }
        std::shared_ptr<Object> detailObj = nullptr;
        if (object->GetValue(DETAILS, detailObj)) {
            details_ = ObjectUtils::ConvertToUDDetails(detailObj);
        }
    }
}

int64_t File::GetSize()
{
    return static_cast<int64_t>(this->oriUri_.size() + this->remoteUri_.size() +
        UnifiedDataUtils::GetDetailsSize(this->details_)) + GetInnerEntriesSize();
}

std::string File::GetUri() const
{
    return this->oriUri_;
}

void File::SetUri(const std::string &uri)
{
    this->oriUri_ = uri;
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        auto object = std::get<std::shared_ptr<Object>>(value_);
        object->value_[ORI_URI] = oriUri_;
    }
}

std::string File::GetRemoteUri() const
{
    return this->remoteUri_;
}

void File::SetRemoteUri(const std::string &uri)
{
    this->remoteUri_ = uri;
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        auto object = std::get<std::shared_ptr<Object>>(value_);
        object->value_[REMOTE_URI] = remoteUri_;
    }
}

void File::SetDetails(UDDetails &variantMap)
{
    this->details_ = variantMap;
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        auto object = std::get<std::shared_ptr<Object>>(value_);
        object->value_[DETAILS] = ObjectUtils::ConvertToObject(details_);
    }
}

UDDetails File::GetDetails() const
{
    return this->details_;
}

void File::InitObject()
{
    if (!std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        auto value = value_;
        value_ = std::make_shared<Object>();
        auto object = std::get<std::shared_ptr<Object>>(value_);
        object->value_[UNIFORM_DATA_TYPE] = GENERAL_FILE_URI;
        object->value_[ORI_URI] = oriUri_;
        object->value_[REMOTE_URI] = remoteUri_;
        if (!fileType_.empty()) {
            object->value_[FILE_TYPE] = fileType_;
        } else {
            object->value_[FILE_TYPE] = "general.file";
        }
        object->value_[DETAILS] = ObjectUtils::ConvertToObject(details_);
        UpdateUriAuthorizationPolicies(object, uriAuthorizationPolicies_);
        object->value_.insert_or_assign(VALUE_TYPE, std::move(value));
    }
}

std::vector<UriPermission> File::GetUriAuthorizationPolicies() const
{
    return uriAuthorizationPolicies_;
}

void File::SetUriAuthorizationPolicies(const std::vector<UriPermission> &uriAuthorizationPolicies)
{
    uriAuthorizationPolicies_ = uriAuthorizationPolicies;
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        auto object = std::get<std::shared_ptr<Object>>(value_);
        UpdateUriAuthorizationPolicies(object, uriAuthorizationPolicies_);
    }
}

} // namespace UDMF
} // namespace OHOS
