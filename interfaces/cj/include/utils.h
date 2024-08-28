/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef OHOS_UDMF_UTILS_H
#define OHOS_UDMF_UTILS_H

#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include "cj_common_ffi.h"

#define FFI_EXPORT __attribute__((visibility("default")))

class FFI_EXPORT Utils {
    public:
        static char *MallocCString(const std::string &origin);
        static CArrString StringVectorToArray(std::vector<std::string> vector);
 
};
#endif // OHOS_UDMF_UTILS_H