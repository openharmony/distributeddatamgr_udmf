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

#include "type_descriptor.h"
#include "logger.h"
#include "utd_graph.h"

namespace OHOS {
namespace UDMF {
TypeDescriptor::TypeDescriptor(const std::string &typeId, const std::set<std::string> &belongingToTypes,
    const std::vector<std::string> &filenameExtensions, const std::vector<std::string> &mimeTypes,
    const std::string &description, const std::string &referenceURL, const std::string &iconFile) : typeId_(typeId),
    belongingToTypes_(belongingToTypes), filenameExtensions_(filenameExtensions), mimeTypes_(mimeTypes),
    description_(description), referenceURL_(referenceURL), iconFile_(iconFile)
{
}

TypeDescriptor::~TypeDescriptor()
{
}

Status TypeDescriptor::BelongsTo(const std::string &typeId, bool &checkResult)
{
    checkResult = false;
    if (UtdGraph::GetInstance().IsInvalidType(typeId)) {
        checkResult = false;
        LOG_ERROR(UDMF_CLIENT, "invalid para. %{public}s,", typeId.c_str());
        return Status::E_INVALID_PARAMETERS;
    }
    if (typeId_ == typeId) {
        checkResult = true;
        return Status::E_OK;
    };
    checkResult = UtdGraph::GetInstance().IsRelatedOrNot(typeId, typeId_);
    return Status::E_OK;
}

Status TypeDescriptor::IsLowerLevelType(const std::string &typeId, bool &checkResult)
{
    if (UtdGraph::GetInstance().IsInvalidType(typeId)) {
        checkResult = false;
        LOG_ERROR(UDMF_CLIENT, "invalid para. %{public}s,", typeId.c_str());
        return Status::E_INVALID_PARAMETERS;
    }
    if (typeId_ == typeId) {
        checkResult = false;
        return Status::E_OK;
    };
    checkResult = UtdGraph::GetInstance().IsRelatedOrNot(typeId, typeId_);
    return Status::E_OK;
}

Status TypeDescriptor::IsHigherLevelType(const std::string &typeId, bool &checkResult)
{
    if (UtdGraph::GetInstance().IsInvalidType(typeId)) {
        checkResult = false;
        LOG_ERROR(UDMF_CLIENT, "invalid para. %{public}s,", typeId.c_str());
        return Status::E_INVALID_PARAMETERS;
    }
    if (typeId_ == typeId) {
        checkResult = false;
        return Status::E_OK;
    };
    checkResult = UtdGraph::GetInstance().IsRelatedOrNot(typeId_, typeId);
    return Status::E_OK;
}

bool TypeDescriptor::Equals(std::shared_ptr<TypeDescriptor> descriptor)
{
    return  descriptor->GetTypeId() == this->GetTypeId();
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