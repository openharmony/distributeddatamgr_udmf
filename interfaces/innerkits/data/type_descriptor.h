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
namespace OHOS {
namespace UDMF {
class TypeDescriptor {
public:
    TypeDescriptor(const std::string &typeId, const std::set<std::string> &belongingToTypes,
                   const std::vector<std::string> &filenameExtensions, const std::vector<std::string> &mimeTypes,
                   const std::string &description, const std::string &referenceURL, const std::string &iconFile);
    TypeDescriptor(const TypeDescriptorCfg& typeDescriptorCfg);
    ~TypeDescriptor();
    Status BelongsTo(const std::string &typeId, bool &checkResult);
    Status IsLowerLevelType(const std::string &typeId, bool &checkResult);
    Status IsHigherLevelType(const std::string &typeId, bool &checkResult);

    bool Equals(std::shared_ptr<TypeDescriptor> descriptor);
    const std::string& GetTypeId() const;
    std::set<std::string> GetBelongingToTypes();
    std::string GetIconFile();
    std::string GetDescription();
    std::string GetReferenceURL();
    std::vector<std::string> GetFilenameExtensions();
    std::vector<std::string> GetMimeTypes();

private:
    bool CmpFlexibleTypeLevel(const std::string higherLevelTypeId, bool isFlexibleType);

    std::string typeId_;
    std::set<std::string> belongingToTypes_;
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
