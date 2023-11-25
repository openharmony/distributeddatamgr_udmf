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

#ifndef UDMF_UTD_CUSTOM_PERSISTENCE_H
#define UDMF_UTD_CUSTOM_PERSISTENCE_H
#include <string>
#include <vector>
#include <set>
#include <map>
#include <cstdint>
#include "visibility.h"
#include "utd_common.h"
#include "utd_json_parse.h"
namespace OHOS {
namespace UDMF {
class UtdCustomPersistence {
public:
    static UtdCustomPersistence &GetInstance();
    std::vector<TypeDescriptorCfg> GetCustomTypesFromCfg(const std::string &cfgFilePath);
    int32_t PersistingCustomUtdData(std::vector<TypeDescriptorCfg> &customUtdTypes,
                                    const std::string &cfgFilePath);

private:
    UtdCustomPersistence();
    ~UtdCustomPersistence();
    int32_t UpdateTypesCfgFile(const std::string &jsonData, const std::string cfgFilePath);
    bool CreateDirectory(const std::string &path) const;

    UtdJsonParse utdJsonParse_;
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_UTD_CUSTOM_PERSISTENCE_H