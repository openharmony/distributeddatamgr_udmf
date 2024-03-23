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
#ifndef UDMF_UTD_FLEXIBLE_TYPE
#define UDMF_UTD_FLEXIBLE_TYPE
#include <string>
#include <set>
#include <vector>
#include "error_code.h"
#include "utd_common.h"
namespace OHOS {
namespace UDMF {
constexpr const char* FLEXIBLE_TYPE_FLAG = "flex.z";
enum FlexibleTypeAttr : int32_t {
    BELONGINGTO_TYPE = 0,
    MIMETYPE,
    FILE_EXTENTSION,
    INVALID_BUT
};
class FlexibleType {
public:
    static std::string EscapeStr(const std::string &chs);
    static bool ParseFlexibleUtd(const std::string &typeId, TypeDescriptorCfg &flexibleTypeDescriptorCfg);
    static std::string GenFlexibleUtd(const std::string &mimeType, const std::string &fileExtension,
                                     const std::string &belongsTo);
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_UTD_FLEXIBLE_TYPE
