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
#include "visibility.h"
#include "string_ex.h"

namespace OHOS {
namespace UDMF {
enum UDType : int32_t {
    ENTITY = 0,
    OBJECT,
    COMPOSITE_OBJECT,
    TEXT,
    PLAIN_TEXT,
    HTML,
    HYPERLINK,
    XML,
    SOURCE_CODE,
    SCRIPT,
    SHELL_SCRIPT,
    CSH_SCRIPT,
    PERL_SCRIPT,
    PHP_SCRIPT,
    PYTHON_SCRIPT,
    RUBY_SCRIPT,
    TYPE_SCRIPT,
    JAVA_SCRIPT,
    C_HEADER,
    C_SOURCE,
    C_PLUS_PLUS_HEADER,
    C_PLUS_PLUS_SOURCE,
    JAVA_SOURCE,
    EBOOK,
    EPUB,
    AZW,
    AZW3,
    KFX,
    MOBI,
    MEDIA,
    IMAGE,
    JPEG,
    PNG,
    RAW_IMAGE,
    TIFF,
    BMP,
    ICO,
    PHOTOSHOP_IMAGE,
    AI_IMAGE,
    WORD_DOC,
    EXCEL,
    PPT,
    PDF,
    POSTSCRIPT,
    ENCAPSULATED_POSTSCRIPT,
    VIDEO,
    AVI,
    MPEG,
    MPEG4,
    VIDEO_3GPP,
    VIDEO_3GPP2,
    WINDOWS_MEDIA_WM,
    WINDOWS_MEDIA_WMV,
    WINDOWS_MEDIA_WMP,
    AUDIO,
    AAC,
    AIFF,
    ALAC,
    FLAC,
    MP3,
    OGG,
    PCM,
    WINDOWS_MEDIA_WMA,
    WAVEFORM_AUDIO,
    WINDOWS_MEDIA_WMX,
    WINDOWS_MEDIA_WVX,
    WINDOWS_MEDIA_WAX,
    FILE,
    DIRECTORY,
    FOLDER,
    SYMLINK,
    ARCHIVE,
    BZ2_ARCHIVE,
    DISK_IMAGE,
    TAR_ARCHIVE,
    ZIP_ARCHIVE,
    JAVA_ARCHIVE,
    GNU_TAR_ARCHIVE,
    GNU_ZIP_ARCHIVE,
    GNU_ZIP_TAR_ARCHIVE,
    CALENDAR,
    CONTACT,
    DATABASE,
    MESSAGE,
    VCARD,
    NAVIGATION,
    LOCATION,
    SYSTEM_DEFINED_FORM,
    SYSTEM_DEFINED_RECORD,
    SYSTEM_DEFINED_APP_ITEM,
    SYSTEM_DEFINED_PIXEL_MAP,
    OPENHARMONY_ATOMIC_SERVICE,
    APPLICATION_DEFINED_RECORD,
    OPENHARMONY_PACKAGE,
    OPENHARMONY_HAP,
    SMIL,
    MARKDOWN,
    FAX,
    JFX_FAX,
    EFX_FAX,
    XBITMAP_IMAGE,
    TGA_IMAGE,
    SGI_IMAGE,
    OPENEXR_IMAGE,
    FLASHPIX_IMAGE,
    REALMEDIA,
    AU_AUDIO,
    AIFC_AUDIO,
    SD2_AUDIO,
    REALAUDIO,
    OPENXML,
    WORDPROCESSINGML_DOCUMENT,
    SPREADSHEETML_SHEET,
    PRESENTATIONML_PRESENTATION,
    OPENDOCUMENT,
    OPENDOCUMENT_TEXT,
    OPENDOCUMENT_SPREADSHEET,
    OPENDOCUMENT_PRESENTATION,
    OPENDOCUMENT_GRAPHICS,
    OPENDOCUMENT_FORMULA,
    STUFFIT_ARCHIVE,
    VCS,
    ICS,
    EXECUTABLE,
    PORTABLE_EXECUTABLE,
    SUN_JAVA_CLASS,
    FONT,
    TRUETYPE_FONT,
    TRUETYPE_COLLECTION_FONT,
    OPENTYPE_FONT,
    POSTSCRIPT_FONT,
    POSTSCRIPT_PFB_FONT,
    POSTSCRIPT_PFA_FONT,
    OPENHARMONY_HDOC,
    OPENHARMONY_HINOTE,
    OPENHARMONY_STYLED_STRING,
    OPENHARMONY_WANT,
    UD_BUTT
};

struct UtdType {
    int32_t UtdEnum;
    const char *UtdEnumName;
    const char *UtdId;
};

namespace UtdUtils {
    bool API_EXPORT IsValidUtdId(const std::string &utdId);
    int32_t API_EXPORT GetUtdEnumFromUtdId(const std::string &utdId);
    std::string API_EXPORT GetUtdIdFromUtdEnum(int32_t utdType);
    std::vector<UtdType> API_EXPORT GetUtdTypes();
} // namespace UtdUtils

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

static const std::unordered_map<int32_t, std::string> UD_SYSTEM_INTENTION_MAP {
    { UD_INTENTION_DRAG, "Drag" },
};

static const std::unordered_map<int32_t, std::string> JS_UD_INTENTION_NAME_MAP {
    { UD_INTENTION_DATA_HUB, "DATA_HUB" },
    { UD_INTENTION_DRAG, "DRAG" },
};

enum ShareOptions : int32_t {
    IN_APP,
    CROSS_APP,
    SHARE_OPTIONS_BUTT,
};

struct AppShareOption {
    int32_t enumNum;
    const char *enumStr;
};

namespace ShareOptionsUtil {
    bool API_EXPORT IsValid(int32_t shareOption);
    int32_t API_EXPORT GetEnumNum(const std::string &shareOption);
    std::string API_EXPORT GetEnumStr(int32_t shareOption);
} // namespace ShareOptionsUtil

class API_EXPORT UnifiedDataUtils {
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
