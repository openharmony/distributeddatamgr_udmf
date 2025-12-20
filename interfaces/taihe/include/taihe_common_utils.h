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

#ifndef UDMF_TAIHE_COMMON_UTILS_H
#define UDMF_TAIHE_COMMON_UTILS_H

#include "ani.h"
#include "ohos.data.unifiedDataChannel.proj.hpp"
#include "ohos.data.unifiedDataChannel.impl.hpp"
#include "unified_meta.h"
#include "taihe/runtime.hpp"
#include "logger.h"
#include "unified_record_taihe.h"
#include "unified_data_properties.h"

namespace taiheChannel = ohos::data::unifiedDataChannel;

namespace OHOS {
namespace UDMF {
static constexpr int PARAMETERSERROR = 401;
static const std::string NEW_INSTANCE_LIB = "libudmf_data_napi.z.so";
static constexpr int NOPERMISSION = 201;
static constexpr int ESETTINGSEXISTED = 20400001;
Intention ConvertIntention(::ohos::data::unifiedDataChannel::Intention value);
::taihe::array<::taihe::string> ConvertStringVectorToTaiheArray(const std::vector<std::string>& stringVector);
ValueType ConvertValueType(ani_env *env, const ::taihe::string_view &type,
    ::ohos::data::unifiedDataChannel::ValueType const& value);
::ohos::data::unifiedDataChannel::ValueType ConvertValueType(const ValueType &value);
UDDetails ConvertUDDetails(const ::taihe::map_view<::taihe::string, ::taihe::string> &details);
::taihe::map<::taihe::string, ::taihe::string> ConvertUDDetailsToString(const UDDetails &details);
::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> ConvertUDDetailsToUnion(
    const UDDetails &details);
::taihe::map<::taihe::string, ::ohos::data::uniformDataStruct::DetailsValue> ConvertUDSUDDetailsToUnion(
    const UDDetails &details);
UDDetails ConvertUDDetailsToUnion(
    const ::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> &details);
ShareOptions ConvertShareOptions(::ohos::data::unifiedDataChannel::ShareOptions value);
Visibility ConvertVisibility(::ohos::data::unifiedDataChannel::Visibility value);
::taihe::array<::taihe::string> ConvertStringVectorToTaiheArray(const std::vector<std::string>& stringVector);
::ohos::data::unifiedDataChannel::ShareOptions ConvertShareOptions(OHOS::UDMF::ShareOptions value);
ValueType ConvertRecordData(ani_env *env, ::ohos::data::unifiedDataChannel::RecordData const& value, int depth);
::ohos::data::unifiedDataChannel::RecordData ConvertRecordData(std::shared_ptr<Object> object, int depth);
::ohos::data::unifiedDataChannel::ValueType ConvertPlainText(std::shared_ptr<Object> udsObj);
::ohos::data::unifiedDataChannel::ValueType ConvertHyperlink(std::shared_ptr<Object> udsObj);
::ohos::data::unifiedDataChannel::ValueType ConvertHTML(std::shared_ptr<Object> udsObj);
::ohos::data::unifiedDataChannel::ValueType ConvertOpenHarmonyAppItem(std::shared_ptr<Object> udsObj);
::ohos::data::unifiedDataChannel::ValueType ConvertContentForm(std::shared_ptr<Object> udsObj);
::ohos::data::unifiedDataChannel::ValueType ConvertForm(std::shared_ptr<Object> udsObj);
::ohos::data::unifiedDataChannel::ValueType ConvertFileUri(std::shared_ptr<Object> udsObj);
::ohos::data::unifiedDataChannel::ValueType ConvertPixelMap(std::shared_ptr<Object> udsObj);
OHOS::UDMF::UnifiedDataProperties ConvertUnifiedDataProperties(const ::taiheChannel::UnifiedDataProperties &value);
::taiheChannel::UnifiedDataProperties ConvertUnifiedDataProperties(OHOS::UDMF::UnifiedDataProperties &value);

} // namespace UDMF
} // namespace OHOS
#endif // UDMF_TAIHE_COMMON_UTILS_H