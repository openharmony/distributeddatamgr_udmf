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

#include "type_descriptor.h"
#include <string>
#include <vector>
#include <set>

namespace OHOS {
namespace UDMF {

void TypeDescriptor::SetTypeId(const std::string &typeId)
{
    typeId_ = typeId;
}

void TypeDescriptor::SetBelongingToTypes(const std::vector<std::string> &belongingToTypes)
{
    belongingToTypes_ = belongingToTypes;
}

void TypeDescriptor::SetFilenameExtensions(const std::vector<std::string> &filenameExtensions)
{
    filenameExtensions_ = filenameExtensions;
}

void TypeDescriptor::SetMimeTypes(const std::vector<std::string> &mimeTypes)
{
    mimeTypes_ = mimeTypes;
}

void TypeDescriptor::SetDescription(const std::string &description)
{
    description_ = description;
}

void TypeDescriptor::SetReferenceURL(const std::string &referenceURL)
{
    referenceURL_ = referenceURL;
}

void TypeDescriptor::SetIconFile(const std::string &iconFile)
{
    iconFile_ = iconFile;
}

} // namespace UDMF
} // namespace OHOS