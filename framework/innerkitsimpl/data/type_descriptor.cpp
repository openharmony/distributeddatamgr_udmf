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

namespace OHOS {
namespace UDMF {
TypeDescriptor::TypeDescriptor(const std::string &typeId) : typeId_(typeId)
{
}

TypeDescriptor::~TypeDescriptor()
{
}

bool TypeDescriptor::Equals(std::shared_ptr<TypeDescriptor> descriptor)
{
    return  descriptor->GetTypeId() == typeId_;
}

std::string TypeDescriptor::GetTypeId()
{
    return typeId_;
}

void TypeDescriptor::SetBelongingToTypes(const std::set<std::string> &belongingToTypes)
{
    belongingToTypes_ = belongingToTypes;
}

std::set<std::string> TypeDescriptor::GetBelongingToTypes()
{
    return belongingToTypes_;
}

void TypeDescriptor::SetIconFile(const std::string &iconFile)
{
    iconFile_ = iconFile;
}

std::string TypeDescriptor::GetIconFile()
{
    return iconFile_;
}

void TypeDescriptor::SetDescription(std::string description)
{
    description_ = description;
}

std::string TypeDescriptor::GetDescription()
{
    return description_;
}

void TypeDescriptor::SetReferenceURL(std::string referenceURL)
{
    referenceURL_ = referenceURL;
}

std::string TypeDescriptor::GetReferenceURL()
{
    return referenceURL_;
}

void TypeDescriptor::SetFilenameExtensions(const std::vector<std::string> &filenameExtensions)
{
    filenameExtensions_ = filenameExtensions;
}

std::vector<std::string> TypeDescriptor::GetFilenameExtensions()
{
    return filenameExtensions_;
}

void TypeDescriptor::SetMimeTypes(const std::vector<std::string> &mimeTypes)
{
    mimeTypes_ = mimeTypes;
}

std::vector<std::string> TypeDescriptor::GetMimeTypes()
{
    return mimeTypes_;
}
} // namespace UDMF
} // namespace OHOS