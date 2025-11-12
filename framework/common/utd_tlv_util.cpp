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
#include "utd_tlv_util.h"
namespace OHOS::ITypesUtil {
template<>
bool Marshalling(const UDMF::TypeDescriptorCfg &input, MessageParcel &data)
{
    return Marshal(data,
        input.typeId,
        input.belongingToTypes,
        input.filenameExtensions,
        input.mimeTypes,
        input.description,
        input.referenceURL,
        input.iconFile);
}

template<>
bool Unmarshalling(UDMF::TypeDescriptorCfg &output, MessageParcel &data)
{
    if (!Unmarshal(data,
        output.typeId,
        output.belongingToTypes,
        output.filenameExtensions,
        output.mimeTypes,
        output.description,
        output.referenceURL,
        output.iconFile)) {
        return false;
    }
    return true;
}
} // namespace ITypesUtil