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

#ifndef UTD_TLV_UTIL_H
#define UTD_TLV_UTIL_H

#include "itypes_util.h"
#include "utd_common.h"
#include "visibility.h"
namespace OHOS::ITypesUtil {
using TypeDescriptorCfg = UDMF::TypeDescriptorCfg;
template<>
bool API_EXPORT Marshalling(const TypeDescriptorCfg &input, MessageParcel &data);

template<>
bool API_EXPORT Unmarshalling(TypeDescriptorCfg &output, MessageParcel &data);
} // namespace ITypesUtil
#endif // UTD_TLV_UTIL_H
