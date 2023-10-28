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

bool TypeDescriptor::BelongsTo(const std::string &typeId)
{
    if (typeId_ == typeId) {
        return true;
    };
    return UtdGraph::GetInstance().IsRelatedOrNot(typeId, typeId_);
}

bool TypeDescriptor::IsLowerLevelType(const std::string &typeId)
{
    return UtdGraph::GetInstance().IsRelatedOrNot(typeId, typeId_);
}

bool TypeDescriptor::IsHigherLevelType(const std::string &typeId)
{
    return UtdGraph::GetInstance().IsRelatedOrNot(typeId_, typeId);
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