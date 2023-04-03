/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
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

#ifndef UNIFIED_META_H
#define UNIFIED_META_H

#include <array>
#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#include "string_ex.h"

namespace OHOS {
namespace UDMF {
enum UDType : int32_t {
    TEXT = 0,
    PLAIN_TEXT,
    STYLED_TEXT,
    HYPER_LINK,
    HTML,
    FILE,
    FOLDER,
    MEDIA,
    IMAGE,
    VIDEO,
    AUDIO,
    OFFICE,
    EBOOK,
    COMPRESSION,
    GENERAL,
    SYSTEM_DEFINED_FORM,
    SYSTEM_DEFINED_RECORD,
    SYSTEM_DEFINED_APP_ITEM,
    SYSTEM_DEFINED_PIXEL_MAP,
    UD_BUTT
};

static const std::unordered_map<int32_t, std::string> UD_TYPE_MAP{
    { TEXT, "Text" },
    { PLAIN_TEXT, "Text.PlainText" },
    { STYLED_TEXT, "Text.StyledText" },
    { HYPER_LINK, "Text.HyperLink" },
    { HTML, "Text.HTML" },
    { FILE, "File" },
    { FOLDER, "File.Folder" },
    { MEDIA, "File.Media" },
    { OFFICE, "File.Office" },
    { EBOOK, "File.Ebook" },
    { COMPRESSION, "File.Compression" },
    { GENERAL, "File.General" },
    { IMAGE, "File.Media.Image" },
    { VIDEO, "File.Media.Video" },
    { AUDIO, "File.Media.Audio" },
    { SYSTEM_DEFINED_RECORD, "SystemDefinedType" },
    { SYSTEM_DEFINED_FORM, "SystemDefinedType.Form" },
    { SYSTEM_DEFINED_APP_ITEM, "SystemDefinedType.AppItem" },
    { SYSTEM_DEFINED_PIXEL_MAP, "SystemDefinedType.PixelMap" },
    { UD_BUTT, "INVALID" }
};

static const std::unordered_map<int32_t, std::string> JS_UD_TYPE_NAME_MAP{
    { TEXT, "TEXT" },
    { PLAIN_TEXT, "PLAIN_TEXT" },
    { HYPER_LINK, "HYPER_LINK" },
    { HTML, "HTML" },
    { IMAGE, "IMAGE" },
    { VIDEO, "VIDEO" },
    { SYSTEM_DEFINED_RECORD, "SYSTEM_DEFINED_RECORD" },
    { SYSTEM_DEFINED_FORM, "SYSTEM_DEFINED_FORM" },
    { SYSTEM_DEFINED_APP_ITEM, "SYSTEM_DEFINED_APP_ITEM" },
    { SYSTEM_DEFINED_PIXEL_MAP, "SYSTEM_DEFINED_PIXEL_MAP" },
};

/*
 * UnifiedData variant definitions.
 */
using UDVariant = std::variant<int32_t, int64_t, bool, double, std::string, std::vector<uint8_t>>;
using UDDetails = std::map<std::string, UDVariant>;

/*
 * UnifiedData Intention.
 */
enum Intention : int32_t {
    UD_INTENTION_DRAG = 0,
    UD_INTENTION_SYS,
    UD_INTENTION_SHARE,
    UD_INTENTION_BUTT,
};

static const std::unordered_map<int32_t, std::string> UD_INTENTION_MAP {
    {UD_INTENTION_DRAG, "drag"}
};

class UnifiedDataUtils {
public:
    static bool IsValidType(int32_t value);
    static bool IsValidIntention(int32_t value);
    static size_t GetVariantSize(UDVariant &variant);
    static size_t GetDetailsSize(UDDetails &details);
};
} // namespace UDMF
} // namespace OHOS
#endif //UNIFIED_META_H