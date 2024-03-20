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
#define LOG_TAG "TypeDescriptor"
#include "type_descriptor.h"
#include "logger.h"
#include "utd_graph.h"
#include "flexible_type.h"
namespace OHOS {
namespace UDMF {
TypeDescriptor::TypeDescriptor(const std::string &typeId, const std::set<std::string> &belongingToTypes,
    const std::vector<std::string> &filenameExtensions, const std::vector<std::string> &mimeTypes,
    const std::string &description, const std::string &referenceURL, const std::string &iconFile) : typeId_(typeId),
    belongingToTypes_(belongingToTypes), filenameExtensions_(filenameExtensions), mimeTypes_(mimeTypes),
    description_(description), referenceURL_(referenceURL), iconFile_(iconFile)
{
}

TypeDescriptor::TypeDescriptor(const TypeDescriptorCfg& typeDescriptorCfg)
{
    typeId_ = typeDescriptorCfg.typeId;
    belongingToTypes_ = typeDescriptorCfg.belongingToTypes;
    filenameExtensions_ = typeDescriptorCfg.filenameExtensions;
    mimeTypes_ = typeDescriptorCfg.mimeTypes;
    description_ = typeDescriptorCfg.description;
    referenceURL_ = typeDescriptorCfg.referenceURL;
    iconFile_ = typeDescriptorCfg.iconFile;
    isFlexibleType_ = (typeId_.find(FLEXIBLE_TYPE_FLAG) != typeId_.npos);
}

TypeDescriptor::~TypeDescriptor()
{
}

bool TypeDescriptor::CmpFlexibleTypeLevel(const std::string higherLevelTypeId, bool isFlexibleType)
{
    if (belongingToTypes_.empty()) {
        LOG_WARN(UDMF_CLIENT, "The current utd belongings is empty. %{public}s,", typeId_.c_str());
        return false;
    }
    if (std::find(belongingToTypes_.begin(), belongingToTypes_.end(), higherLevelTypeId) != belongingToTypes_.end()) {
        return true;
    }
    if (!isFlexibleType) {
        for (auto belong : belongingToTypes_) {
            if (UtdGraph::GetInstance().IsLowerLevelType(higherLevelTypeId, belong)) {
                return true;
            }
        }
    }
    LOG_INFO(UDMF_CLIENT, "The current utd[%{public}s] belongings is not belong[] %{public}s,",
             typeId_.c_str(), higherLevelTypeId.c_str());
    return false;
}

Status TypeDescriptor::BelongsTo(const std::string &typeId, bool &checkResult)
{
    checkResult = false;
    bool isFlexibleType = typeId.find(FLEXIBLE_TYPE_FLAG) != typeId_.npos;
    if (!UtdGraph::GetInstance().IsValidType(typeId) && !isFlexibleType) {
        LOG_ERROR(UDMF_CLIENT, "invalid para. %{public}s,", typeId.c_str());
        return Status::E_INVALID_PARAMETERS;
    }

    if (isFlexibleType_) {
        if (typeId_ == typeId) {
            checkResult = true;
            return Status::E_OK;
        };
        checkResult = CmpFlexibleTypeLevel(typeId, isFlexibleType);
        return Status::E_OK;
    }

    if (typeId_ == typeId) {
        checkResult = true;
        return Status::E_OK;
    };
    checkResult = UtdGraph::GetInstance().IsLowerLevelType(typeId, typeId_);
    return Status::E_OK;
}

Status TypeDescriptor::IsLowerLevelType(const std::string &typeId, bool &checkResult)
{
    checkResult = false;
    bool isFlexibleType = typeId.find(FLEXIBLE_TYPE_FLAG) != typeId_.npos;
    if (!UtdGraph::GetInstance().IsValidType(typeId) && !isFlexibleType) {
        LOG_ERROR(UDMF_CLIENT, "invalid para. %{public}s,", typeId.c_str());
        return Status::E_INVALID_PARAMETERS;
    }
    if (isFlexibleType_) {
        checkResult = CmpFlexibleTypeLevel(typeId, isFlexibleType);
        return Status::E_OK;
    }

    if (typeId_ == typeId) {
        return Status::E_OK;
    };
    checkResult = UtdGraph::GetInstance().IsLowerLevelType(typeId, typeId_);
    return Status::E_OK;
}

Status TypeDescriptor::IsHigherLevelType(const std::string &typeId, bool &checkResult)
{
    checkResult = false;
    bool isFlexibleType = typeId.find(FLEXIBLE_TYPE_FLAG) != typeId_.npos;
    if (!UtdGraph::GetInstance().IsValidType(typeId) && !isFlexibleType) {
        LOG_ERROR(UDMF_CLIENT, "invalid para. %{public}s,", typeId.c_str());
        return Status::E_INVALID_PARAMETERS;
    }
    if (isFlexibleType_) {  // flexibleType cannot be other type height level.
        return Status::E_OK;
    }
    if (typeId_ == typeId) {
        return Status::E_OK;
    };
    checkResult = UtdGraph::GetInstance().IsLowerLevelType(typeId_, typeId);
    return Status::E_OK;
}

bool TypeDescriptor::Equals(std::shared_ptr<TypeDescriptor> descriptor)
{
    return descriptor->GetTypeId() == this->GetTypeId();
}

const std::string& TypeDescriptor::GetTypeId() const
{
    return typeId_;
}

std::set<std::string> TypeDescriptor::GetBelongingToTypes()
{
    return belongingToTypes_;
}

std::string TypeDescriptor::GetIconFile()
{
    return iconFile_;
}

std::string TypeDescriptor::GetDescription()
{
    return description_;
}

std::string TypeDescriptor::GetReferenceURL()
{
    return referenceURL_;
}

std::vector<std::string> TypeDescriptor::GetFilenameExtensions()
{
    return filenameExtensions_;
}

std::vector<std::string> TypeDescriptor::GetMimeTypes()
{
    return mimeTypes_;
}
} // namespace UDMF
} // namespace OHOS