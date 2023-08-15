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
    HYPERLINK,
    HTML,
    FILE,
    FOLDER,
    IMAGE,
    VIDEO,
    AUDIO,
    SYSTEM_DEFINED_FORM,
    SYSTEM_DEFINED_RECORD,
    SYSTEM_DEFINED_APP_ITEM,
    SYSTEM_DEFINED_PIXEL_MAP,
    APPLICATION_DEFINED_RECORD,
    UD_BUTT
};

static const std::unordered_map<int32_t, std::string> UD_TYPE_MAP {
    { TEXT, "general.text" },
    { PLAIN_TEXT, "general.plain-text" },
    { HYPERLINK, "general.hyperlink" },
    { HTML, "general.html" },
    { FILE, "general.file" },
    { FOLDER, "general.folder" },
    { IMAGE, "general.image" },
    { VIDEO, "general.video" },
    { AUDIO, "general.audio" },
    { SYSTEM_DEFINED_RECORD, "SystemDefinedType" },
    { SYSTEM_DEFINED_FORM, "openharmony.form" },
    { SYSTEM_DEFINED_APP_ITEM, "openharmony.app-item" },
    { SYSTEM_DEFINED_PIXEL_MAP, "openharmony.pixel-map" },
    { APPLICATION_DEFINED_RECORD, "ApplicationDefinedType" },
    { UD_BUTT, "INVALID" }
};

static const std::unordered_map<int32_t, std::string> JS_UD_TYPE_NAME_MAP {
    { TEXT, "TEXT" },
    { PLAIN_TEXT, "PLAIN_TEXT" },
    { HYPERLINK, "HYPERLINK" },
    { HTML, "HTML" },
    { FILE, "FILE" },
    { IMAGE, "IMAGE" },
    { VIDEO, "VIDEO" },
    { AUDIO, "AUDIO" },
    { FOLDER, "FOLDER" },
    { SYSTEM_DEFINED_RECORD, "SYSTEM_DEFINED_RECORD" },
    { SYSTEM_DEFINED_FORM, "OPENHARMONY_FORM" },
    { SYSTEM_DEFINED_APP_ITEM, "OPENHARMONY_APP_ITEM" },
    { SYSTEM_DEFINED_PIXEL_MAP, "OPENHARMONY_PIXEL_MAP" },
    { APPLICATION_DEFINED_RECORD, "APPLICATION_DEFINED_RECORD" },
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
    UD_INTENTION_BASE = 0,
    UD_INTENTION_DRAG,
    UD_INTENTION_DATA_HUB,
    UD_INTENTION_BUTT,
};

static const std::unordered_map<int32_t, std::string> UD_INTENTION_MAP {
    { UD_INTENTION_DRAG, "drag" },
    { UD_INTENTION_DATA_HUB, "DataHub" },
};

static const std::unordered_map<int32_t, std::string> JS_UD_INTENTION_NAME_MAP {
    { UD_INTENTION_DATA_HUB, "DATA_HUB" },
};

class UnifiedDataUtils {
public:
    static bool IsValidType(int32_t value);
    static bool IsValidIntention(int32_t value);
    static size_t GetVariantSize(UDVariant &variant);
    static size_t GetDetailsSize(UDDetails &details);
    static bool IsPersist(const Intention &intention);
    static bool IsPersist(const std::string &intention);
    static Intention GetIntentionByString(const std::string &intention);
    static bool IsValidOptions(const std::string &key, std::string &intention);
};
} // namespace UDMF
} // namespace OHOS
#endif // UNIFIED_META_H