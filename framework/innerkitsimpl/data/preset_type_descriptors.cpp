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
#define LOG_TAG "PresetTypeDescriptors"

#include "preset_type_descriptors.h"
#include <sstream>
#include <fstream>
#include "cJSON.h"
#include "custom_utd_json_parser.h"
#include "logger.h"

namespace OHOS {
namespace UDMF {
static constexpr const char *UTD_CONF_PATH = "/system/etc/utd/conf/";
static constexpr const char *UNIFORM_DATA_TYPES_JSON_PATH = "uniform_data_types.json";

PresetTypeDescriptors::PresetTypeDescriptors()
{
    InitDescriptors();
}

PresetTypeDescriptors::~PresetTypeDescriptors()
{
}

PresetTypeDescriptors &PresetTypeDescriptors::GetInstance()
{
    static auto instance = new PresetTypeDescriptors();
    return *instance;
}

std::vector<TypeDescriptorCfg> &PresetTypeDescriptors::GetPresetTypes()
{
    return typeDescriptors_;
}

void PresetTypeDescriptors::InitDescriptors()
{
    std::ifstream fin(std::string(UTD_CONF_PATH) + std::string(UNIFORM_DATA_TYPES_JSON_PATH));
    if (!fin.good()) {
        LOG_ERROR(UDMF_CLIENT, "Failed to open uniform data types json file");
        return;
    }
    std::ostringstream oss;
    std::string line;
    while (std::getline(fin, line)) {
        oss << line;
    }
    CustomUtdJsonParser utdJsonParser;
    cJSON* jsonRoot = cJSON_Parse(oss.str().c_str());
    if (jsonRoot != NULL && cJSON_IsObject(jsonRoot)) {
        std::lock_guard<std::recursive_mutex> lock(mutex_);
        utdJsonParser.GetTypeDescriptors(*jsonRoot, UTD_CUSTOM_DECLAEEARION, typeDescriptors_);
    }
    cJSON_Delete(jsonRoot);
    LOG_DEBUG(UDMF_CLIENT, "Preset type descriptors init success, utd size is %{public}lu", typeDescriptors_.size());
};
} // namespace UDMF
} // namespace OHOS
