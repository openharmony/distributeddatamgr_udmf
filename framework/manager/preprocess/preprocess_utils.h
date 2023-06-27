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
#ifndef UDMF_PREPROCESS_UTILS_H
#define UDMF_PREPROCESS_UTILS_H

#include <bitset>
#include <random>
#include <string>
#include <vector>

#include "logger.h"
#include "unified_data.h"
#include "unified_meta.h"

namespace OHOS {
namespace UDMF {
class PreProcessUtils {
public:
    static PreProcessUtils &GetInstance();
    /*
     * Data Imputation
     */
    bool RuntimeDataImputation(UnifiedData &data, CustomOption &option);
    std::string IdGenerator();
    time_t GetTimeStamp();
    bool GetHapBundleNameByToken(uint32_t  tokenId, std::string &bundleName);
    bool GetNativeProcessNameByToken(uint32_t  tokenId, std::string &processName);
    std::string errorStr;
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_PREPROCESS_UTILS_H
