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

#include "itypes_util.h"

#include "application_defined_record.h"
#include "audio.h"
#include "file.h"
#include "folder.h"
#include "html.h"
#include "image.h"
#include "link.h"
#include "plain_text.h"
#include "system_defined_appitem.h"
#include "system_defined_form.h"
#include "system_defined_pixelmap.h"
#include "system_defined_record.h"
#include "text.h"
#include "unified_data.h"
#include "unified_meta.h"
#include "unified_record.h"
#include "unified_types.h"
#include "video.h"

namespace OHOS {
namespace ITypesUtil {
using UnifiedRecord = UDMF::UnifiedRecord;
using UnifiedData = UDMF::UnifiedData;
using Summary = UDMF::Summary;
using Privilege = UDMF::Privilege;
using CustomOption = UDMF::CustomOption;
using QueryOption = UDMF::QueryOption;
using Text = UDMF::Text;
using PlainText = UDMF::PlainText;
using Html = UDMF::Html;
using Link = UDMF::Link;
using File = UDMF::File;
using Folder = UDMF::Folder;
using Image = UDMF::Image;
using Video = UDMF::Video;
using Audio = UDMF::Audio;
using SystemDefinedRecord = UDMF::SystemDefinedRecord;
using SystemDefinedForm = UDMF::SystemDefinedForm;
using SystemDefinedAppItem = UDMF::SystemDefinedAppItem;
using SystemDefinedPixelMap = UDMF::SystemDefinedPixelMap;
using ApplicationDefinedRecord = UDMF::ApplicationDefinedRecord;
using UDType = UDMF::UDType;
using Intention = UDMF::Intention;

template<> bool Marshalling(const std::shared_ptr<UnifiedRecord> &input, MessageParcel &parcel);
template<> bool Unmarshalling(std::shared_ptr<UnifiedRecord> &output, MessageParcel &parcel);

template<> bool Marshalling(const UnifiedData &input, MessageParcel &parcel);
template<> bool Unmarshalling(UnifiedData &output, MessageParcel &parcel);

template<> bool Marshalling(const Summary &input, MessageParcel &parcel);
template<> bool Unmarshalling(Summary &output, MessageParcel &parcel);

template<> bool Marshalling(const Privilege &input, MessageParcel &parcel);
template<> bool Unmarshalling(Privilege &output, MessageParcel &parcel);

template<> bool Marshalling(const CustomOption &input, MessageParcel &parcel);
template<> bool Unmarshalling(CustomOption &output, MessageParcel &parcel);

template<> bool Marshalling(const QueryOption &input, MessageParcel &parcel);
template<> bool Unmarshalling(QueryOption &output, MessageParcel &parcel);

template<> bool Marshalling(const Text &input, MessageParcel &parcel);
template<> bool Unmarshalling(Text &output, MessageParcel &parcel);

template<> bool Marshalling(const PlainText &input, MessageParcel &parcel);
template<> bool Unmarshalling(PlainText &output, MessageParcel &parcel);

template<> bool Marshalling(const Html &input, MessageParcel &parcel);
template<> bool Unmarshalling(Html &output, MessageParcel &parcel);

template<> bool Marshalling(const Link &input, MessageParcel &parcel);
template<> bool Unmarshalling(Link &output, MessageParcel &parcel);

template<> bool Marshalling(const File &input, MessageParcel &parcel);
template<> bool Unmarshalling(File &output, MessageParcel &parcel);

template<> bool Marshalling(const Image &input, MessageParcel &parcel);
template<> bool Unmarshalling(Image &output, MessageParcel &parcel);

template<> bool Marshalling(const Video &input, MessageParcel &parcel);
template<> bool Unmarshalling(Video &output, MessageParcel &parcel);

template<> bool Marshalling(const Audio &input, MessageParcel &parcel);
template<> bool Unmarshalling(Audio &output, MessageParcel &parcel);

template<> bool Marshalling(const Folder &input, MessageParcel &parcel);
template<> bool Unmarshalling(Folder &output, MessageParcel &parcel);

template<> bool Marshalling(const SystemDefinedRecord &input, MessageParcel &parcel);
template<> bool Unmarshalling(SystemDefinedRecord &output, MessageParcel &parcel);

template<> bool Marshalling(const SystemDefinedForm &input, MessageParcel &parcel);
template<> bool Unmarshalling(SystemDefinedForm &output, MessageParcel &parcel);

template<> bool Marshalling(const SystemDefinedAppItem &input, MessageParcel &parcel);
template<> bool Unmarshalling(SystemDefinedAppItem &output, MessageParcel &parcel);

template<> bool Marshalling(const SystemDefinedPixelMap &input, MessageParcel &parcel);
template<> bool Unmarshalling(SystemDefinedPixelMap &output, MessageParcel &parcel);

template<> bool Marshalling(const ApplicationDefinedRecord &input, MessageParcel &parcel);
template<> bool Unmarshalling(ApplicationDefinedRecord &output, MessageParcel &parcel);

template<> bool Marshalling(const UDType &input, MessageParcel &parcel);
template<> bool Unmarshalling(UDType &output, MessageParcel &parcel);

template<> bool Marshalling(const Intention &input, MessageParcel &parcel);
template<> bool Unmarshalling(Intention &output, MessageParcel &parcel);
} // namespace ITypesUtil
} // namespace OHOS

#endif // UDMF_TYPES_UTIL_H
