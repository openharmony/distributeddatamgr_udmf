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

#ifndef UDMF_TLV_UTIL_H
#define UDMF_TLV_UTIL_H

#include <type_traits>

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
#include "tlv_object.h"
#include "unified_data.h"
#include "unified_key.h"
#include "unified_meta.h"
#include "unified_record.h"
#include "unified_types.h"
#include "video.h"

namespace OHOS {
namespace TLVUtil {
using namespace OHOS::UDMF;
template<typename T>
bool CountBufferSize(const T &input, TLVObject &data);

template<>
bool CountBufferSize(const std::shared_ptr<UnifiedRecord> &input, TLVObject &data);

template<>
bool CountBufferSize(const Runtime &input, TLVObject &data);

template<>
bool CountBufferSize(const UnifiedData &input, TLVObject &data);

template<>
bool CountBufferSize(const std::vector<UnifiedData> &input, TLVObject &data);

template<typename T>
bool Writing(const T &input, TLVObject &data);
template<typename T>
bool Reading(T &output, TLVObject &data);

template<>
bool Writing(const int32_t &input, TLVObject &data);
template<>
bool Reading(int32_t &output, TLVObject &data);

template<>
bool Writing(const int64_t &input, TLVObject &data);
template<>
bool Reading(int64_t &output, TLVObject &data);

template<>
bool Writing(const bool &input, TLVObject &data);
template<>
bool Reading(bool &output, TLVObject &data);

template<>
bool Reading(uint32_t &output, TLVObject &data);

template<>
bool Writing(const uint32_t &input, TLVObject &data);

template<>
bool Reading(uint64_t &output, TLVObject &data);

template<>
bool Writing(const uint64_t &input, TLVObject &data);

template<>
bool Writing(const std::string &input, TLVObject &data);
template<>
bool Reading(std::string &output, TLVObject &data);

template<>
bool Writing(const std::vector<uint8_t> &input, TLVObject &data);
template<>
bool Reading(std::vector<uint8_t> &output, TLVObject &data);

template<>
bool Writing(const UDVariant &input, TLVObject &data);
template<>
bool Reading(UDVariant &output, TLVObject &data);

template<>
bool Writing(const UDDetails &input, TLVObject &data);
template<>
bool Reading(UDDetails &output, TLVObject &data);

template<>
bool Writing(const UDType &input, TLVObject &data);
template<>
bool Reading(UDType &output, TLVObject &data);

template<>
bool Writing(const Text &input, TLVObject &data);
template<>
bool Reading(Text &output, TLVObject &data);

template<>
bool Writing(const PlainText &input, TLVObject &data);
template<>
bool Reading(PlainText &output, TLVObject &data);

template<>
bool Writing(const Html &input, TLVObject &data);
template<>
bool Reading(Html &output, TLVObject &data);

template<>
bool Writing(const Link &input, TLVObject &data);
template<>
bool Reading(Link &output, TLVObject &data);

template<>
bool Writing(const File &input, TLVObject &data);
template<>
bool Reading(File &output, TLVObject &data);

template<>
bool Writing(const Image &input, TLVObject &data);
template<>
bool Reading(Image &output, TLVObject &data);

template<>
bool Writing(const Video &input, TLVObject &data);
template<>
bool Reading(Video &output, TLVObject &data);

template<>
bool Writing(const Audio &input, TLVObject &data);
template<>
bool Reading(Audio &output, TLVObject &data);

template<>
bool Writing(const Folder &input, TLVObject &data);
template<>
bool Reading(Folder &output, TLVObject &data);

template<>
bool Writing(const SystemDefinedRecord &input, TLVObject &data);
template<>
bool Reading(SystemDefinedRecord &output, TLVObject &data);

template<>
bool Writing(const SystemDefinedForm &input, TLVObject &data);
template<>
bool Reading(SystemDefinedForm &output, TLVObject &data);

template<>
bool Writing(const SystemDefinedAppItem &input, TLVObject &data);
template<>
bool Reading(SystemDefinedAppItem &output, TLVObject &data);

template<>
bool Writing(const SystemDefinedPixelMap &input, TLVObject &data);
template<>
bool Reading(SystemDefinedPixelMap &output, TLVObject &data);

template<>
bool Writing(const ApplicationDefinedRecord &input, TLVObject &data);
template<>
bool Reading(ApplicationDefinedRecord &output, TLVObject &data);

template<>
bool Writing(const std::shared_ptr<UnifiedRecord> &input, TLVObject &data);
template<>
bool Reading(std::shared_ptr<UnifiedRecord> &output, TLVObject &data);

template<>
bool Writing(const UnifiedData &input, TLVObject &data);
template<>
bool Reading(UnifiedData &output, TLVObject &data);

template<>
bool Writing(const std::vector<UnifiedData> &input, TLVObject &data);
template<>
bool Reading(std::vector<UnifiedData> &output, TLVObject &data);

template<>
bool Writing(const UnifiedKey &input, TLVObject &data);
template<>
bool Reading(UnifiedKey &output, TLVObject &data);

template<>
bool Writing(const Privilege &input, TLVObject &data);
template<>
bool Reading(Privilege &output, TLVObject &data);

template<>
bool Writing(const DataStatus &input, TLVObject &data);
template<>
bool Reading(DataStatus &output, TLVObject &data);

template<>
bool Writing(const Runtime &input, TLVObject &data);
template<>
bool Reading(Runtime &output, TLVObject &data);
} // namespace TLVUtil
} // namespace OHOS
#endif // UDMF_TLV_UTIL_H