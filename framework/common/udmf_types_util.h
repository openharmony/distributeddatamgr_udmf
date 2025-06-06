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

#ifndef UDMF_TYPES_UTIL_H
#define UDMF_TYPES_UTIL_H
#include "visibility.h"
#include "itypes_util.h"

#include "unified_data.h"
#include "unified_meta.h"
#include "unified_types.h"
#include "async_task_params.h"

namespace OHOS {
namespace ITypesUtil {
using UnifiedData = UDMF::UnifiedData;
using Summary = UDMF::Summary;
using Privilege = UDMF::Privilege;
using CustomOption = UDMF::CustomOption;
using QueryOption = UDMF::QueryOption;
using UDType = UDMF::UDType;
using Intention = UDMF::Intention;
using Visibility = UDMF::Visibility;
using AsyncProcessInfo = UDMF::AsyncProcessInfo;
using DataLoadInfo = UDMF::DataLoadInfo;

template<>
bool API_EXPORT Marshalling(const UnifiedData &input, MessageParcel &parcel);
template<>
bool API_EXPORT Unmarshalling(UnifiedData &output, MessageParcel &parcel);

template<>
bool API_EXPORT Marshalling(const std::vector<UnifiedData> &input, MessageParcel &parcel);
template<>
bool API_EXPORT Unmarshalling(std::vector<UnifiedData> &output, MessageParcel &parcel);

template<>
bool API_EXPORT Marshalling(const Summary &input, MessageParcel &parcel);
template<>
bool API_EXPORT Unmarshalling(Summary &output, MessageParcel &parcel);

template<>
bool API_EXPORT Marshalling(const Privilege &input, MessageParcel &parcel);
template<>
bool API_EXPORT Unmarshalling(Privilege &output, MessageParcel &parcel);

template<>
bool API_EXPORT Marshalling(const CustomOption &input, MessageParcel &parcel);
template<>
bool API_EXPORT Unmarshalling(CustomOption &output, MessageParcel &parcel);

template<>
bool API_EXPORT Marshalling(const QueryOption &input, MessageParcel &parcel);
template<>
bool API_EXPORT Unmarshalling(QueryOption &output, MessageParcel &parcel);

template<>
bool API_EXPORT Marshalling(const UDType &input, MessageParcel &parcel);
template<>
bool API_EXPORT Unmarshalling(UDType &output, MessageParcel &parcel);

template<>
bool API_EXPORT Marshalling(const Intention &input, MessageParcel &parcel);
template<>
bool API_EXPORT Unmarshalling(Intention &output, MessageParcel &parcel);

template<>
bool API_EXPORT Marshalling(const Visibility &input, MessageParcel &parcel);
template<>
bool API_EXPORT Unmarshalling(Visibility &output, MessageParcel &parcel);

template<>
bool API_EXPORT Marshalling(const AsyncProcessInfo &input, MessageParcel &parcel);
template<>
bool API_EXPORT Unmarshalling(AsyncProcessInfo &output, MessageParcel &parcel);

template<>
bool API_EXPORT Marshalling(const DataLoadInfo &input, MessageParcel &parcel);
template<>
bool API_EXPORT Unmarshalling(DataLoadInfo &output, MessageParcel &parcel);
} // namespace ITypesUtil
} // namespace OHOS
#endif // UDMF_TYPES_UTIL_H