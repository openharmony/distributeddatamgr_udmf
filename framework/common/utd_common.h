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
#ifndef UDMF_UTD_TYPE
#define UDMF_UTD_TYPE
#include <string>
#include <set>
#include <vector>
#include "error_code.h"

namespace OHOS {
namespace UDMF {
struct TypeDescriptorCfg;
using CustomUtdCfgs = std::pair<std::vector<TypeDescriptorCfg>, std::vector<TypeDescriptorCfg>>;
struct TypeDescriptorCfg {
    std::string typeId;
    std::set<std::string> belongingToTypes;
    std::vector<std::string> filenameExtensions;
    std::vector<std::string> mimeTypes;
    std::string description;
    std::string referenceURL;
    std::string iconFile;
    std::string ownerBundle;
    std::set<std::string> installerBundles;

    bool operator==(const TypeDescriptorCfg &typeDescriptor) const
    {
        return typeDescriptor.typeId == typeId;
    }
};

// UTD data category
constexpr const char* UTD_CUSTOM_DECLAEEARION = "UniformDataTypeDeclarations";
constexpr const char* UTD_CUSTOM_REFERENCE = "ReferenceUniformDataTypeDeclarations";

constexpr const char* UTD_CUSTOM = "CustomUTDs";

constexpr const char* DEFAULT_TYPE_ID = "#default";
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_UTD_TYPE
