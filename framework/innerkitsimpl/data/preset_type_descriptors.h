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
#ifndef UDMF_PRESET_TYPE_DESCRIPTORS
#define UDMF_PRESET_TYPE_DESCRIPTORS
#include <string>
#include "error_code.h"
#include "utd_common.h"

namespace OHOS {
namespace UDMF {
class PresetTypeDescriptors {
public:
    static PresetTypeDescriptors &GetInstance();
    std::vector<TypeDescriptorCfg> &GetPresetTypes();
private:
    PresetTypeDescriptors();
    ~PresetTypeDescriptors();
    PresetTypeDescriptors(const PresetTypeDescriptors &obj) = delete;
    PresetTypeDescriptors &operator=(const PresetTypeDescriptors &obj) = delete;

    void InitDescriptors();
    std::vector<TypeDescriptorCfg> typeDescriptors_;
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_PRESET_TYPE_DESCRIPTORS