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

#ifndef UDMF_TYPE_DESCRIPTOR_H
#define UDMF_TYPE_DESCRIPTOR_H

#include <string>
#include <set>
#include <vector>
#include <map>
#include "error_code.h"
#include "utd_common.h"
#include "visibility.h"
namespace OHOS {
namespace UDMF {
class TypeDescriptor {
public:
    API_EXPORT TypeDescriptor(const std::string &typeId, const std::vector<std::string> &belongingToTypes,
                   const std::vector<std::string> &filenameExtensions, const std::vector<std::string> &mimeTypes,
                   const std::string &description, const std::string &referenceURL, const std::string &iconFile);
    API_EXPORT TypeDescriptor(const TypeDescriptorCfg& typeDescriptorCfg);
    API_EXPORT ~TypeDescriptor();
    Status API_EXPORT BelongsTo(const std::string &typeId, bool &checkResult);
    Status API_EXPORT IsLowerLevelType(const std::string &typeId, bool &checkResult);
    Status API_EXPORT IsHigherLevelType(const std::string &typeId, bool &checkResult);

    bool API_EXPORT Equals(std::shared_ptr<TypeDescriptor> descriptor);
    const std::string& API_EXPORT GetTypeId() const;
    std::vector<std::string> API_EXPORT GetBelongingToTypes();
    std::string API_EXPORT GetIconFile();
    std::string API_EXPORT GetDescription();
    std::string API_EXPORT GetReferenceURL();
    std::vector<std::string> API_EXPORT GetFilenameExtensions();
    std::vector<std::string> API_EXPORT GetMimeTypes();

private:
    bool CmpFlexibleTypeLevel(const std::string higherLevelTypeId, bool isFlexibleType);

    std::string typeId_;
    std::vector<std::string> belongingToTypes_;
    std::vector<std::string> filenameExtensions_;
    std::vector<std::string> mimeTypes_;
    std::string description_;
    std::string referenceURL_;
    std::string iconFile_;
    bool isFlexibleType_ = false;
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_TYPE_DESCRIPTOR_H
