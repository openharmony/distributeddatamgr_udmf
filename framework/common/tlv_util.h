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
#include "visibility.h"
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
bool API_EXPORT CountBufferSize(const T &input, TLVObject &data);

template<>
bool API_EXPORT CountBufferSize(const std::shared_ptr<UnifiedRecord> &input, TLVObject &data);

template<>
bool API_EXPORT CountBufferSize(const Runtime &input, TLVObject &data);

template<>
bool API_EXPORT CountBufferSize(const UnifiedData &input, TLVObject &data);

template<>
bool API_EXPORT CountBufferSize(const std::vector<UnifiedData> &input, TLVObject &data);

template<typename T>
bool API_EXPORT Writing(const T &input, TLVObject &data);
template<typename T>
bool API_EXPORT Reading(T &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const int32_t &input, TLVObject &data);
template<>
bool API_EXPORT Reading(int32_t &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const int64_t &input, TLVObject &data);
template<>
bool API_EXPORT Reading(int64_t &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const bool &input, TLVObject &data);
template<>
bool API_EXPORT Reading(bool &output, TLVObject &data);

template<>
bool API_EXPORT Reading(uint32_t &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const uint32_t &input, TLVObject &data);

template<>
bool API_EXPORT Reading(uint64_t &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const uint64_t &input, TLVObject &data);

template<>
bool API_EXPORT Writing(const std::string &input, TLVObject &data);
template<>
bool API_EXPORT Reading(std::string &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const std::vector<uint8_t> &input, TLVObject &data);
template<>
bool API_EXPORT Reading(std::vector<uint8_t> &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const UDVariant &input, TLVObject &data);
template<>
bool API_EXPORT Reading(UDVariant &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const UDDetails &input, TLVObject &data);
template<>
bool API_EXPORT Reading(UDDetails &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const UDType &input, TLVObject &data);
template<>
bool API_EXPORT Reading(UDType &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const Text &input, TLVObject &data);
template<>
bool API_EXPORT Reading(Text &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const PlainText &input, TLVObject &data);
template<>
bool API_EXPORT Reading(PlainText &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const Html &input, TLVObject &data);
template<>
bool API_EXPORT Reading(Html &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const Link &input, TLVObject &data);
template<>
bool API_EXPORT Reading(Link &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const File &input, TLVObject &data);
template<>
bool API_EXPORT Reading(File &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const Image &input, TLVObject &data);
template<>
bool API_EXPORT Reading(Image &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const Video &input, TLVObject &data);
template<>
bool API_EXPORT Reading(Video &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const Audio &input, TLVObject &data);
template<>
bool API_EXPORT Reading(Audio &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const Folder &input, TLVObject &data);
template<>
bool API_EXPORT Reading(Folder &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const SystemDefinedRecord &input, TLVObject &data);
template<>
bool API_EXPORT Reading(SystemDefinedRecord &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const SystemDefinedForm &input, TLVObject &data);
template<>
bool API_EXPORT Reading(SystemDefinedForm &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const SystemDefinedAppItem &input, TLVObject &data);
template<>
bool API_EXPORT Reading(SystemDefinedAppItem &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const SystemDefinedPixelMap &input, TLVObject &data);
template<>
bool API_EXPORT Reading(SystemDefinedPixelMap &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const ApplicationDefinedRecord &input, TLVObject &data);
template<>
bool API_EXPORT Reading(ApplicationDefinedRecord &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const std::shared_ptr<UnifiedRecord> &input, TLVObject &data);
template<>
bool API_EXPORT Reading(std::shared_ptr<UnifiedRecord> &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const UnifiedData &input, TLVObject &data);
template<>
bool API_EXPORT Reading(UnifiedData &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const std::vector<UnifiedData> &input, TLVObject &data);
template<>
bool API_EXPORT Reading(std::vector<UnifiedData> &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const UnifiedKey &input, TLVObject &data);
template<>
bool API_EXPORT Reading(UnifiedKey &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const Privilege &input, TLVObject &data);
template<>
bool API_EXPORT Reading(Privilege &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const DataStatus &input, TLVObject &data);
template<>
bool API_EXPORT Reading(DataStatus &output, TLVObject &data);

template<>
bool API_EXPORT Writing(const Runtime &input, TLVObject &data);
template<>
bool API_EXPORT Reading(Runtime &output, TLVObject &data);
} // namespace TLVUtil
} // namespace OHOS
#endif // UDMF_TLV_UTIL_H