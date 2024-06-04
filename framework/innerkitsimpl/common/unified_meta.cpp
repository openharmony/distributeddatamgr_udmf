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

#include "unified_meta.h"

#include "unified_key.h"

namespace OHOS {
namespace UDMF {
static constexpr UtdType UTD_TYPES[] = {
    { ENTITY, "ENTITY", "general.entity" },
    { OBJECT, "OBJECT", "general.object" },
    { COMPOSITE_OBJECT, "COMPOSITE_OBJECT", "general.composite-object" },
    { TEXT, "TEXT", "general.text" },
    { PLAIN_TEXT, "PLAIN_TEXT", "general.plain-text" },
    { HTML, "HTML", "general.html" },
    { HYPERLINK, "HYPERLINK", "general.hyperlink" },
    { XML, "XML", "general.xml" },
    { SOURCE_CODE, "SOURCE_CODE", "general.source-code" },
    { SCRIPT, "SCRIPT", "general.script" },
    { SHELL_SCRIPT, "SHELL_SCRIPT", "general.shell-script" },
    { CSH_SCRIPT, "CSH_SCRIPT", "general.csh-script" },
    { PERL_SCRIPT, "PERL_SCRIPT", "general.perl-script" },
    { PHP_SCRIPT, "PHP_SCRIPT", "general.php-script" },
    { PYTHON_SCRIPT, "PYTHON_SCRIPT", "general.python-script" },
    { RUBY_SCRIPT, "RUBY_SCRIPT", "general.ruby-script" },
    { TYPE_SCRIPT, "TYPE_SCRIPT", "general.type-script" },
    { JAVA_SCRIPT, "JAVA_SCRIPT", "general.java-script" },
    { C_HEADER, "C_HEADER", "general.c-header" },
    { C_SOURCE, "C_SOURCE", "general.c-source" },
    { C_PLUS_PLUS_HEADER, "C_PLUS_PLUS_HEADER", "general.c-plus-plus-header" },
    { C_PLUS_PLUS_SOURCE, "C_PLUS_PLUS_SOURCE", "general.c-plus-plus-source" },
    { JAVA_SOURCE, "JAVA_SOURCE", "general.java-source" },
    { EBOOK, "EBOOK", "general.ebook" },
    { EPUB, "EPUB", "general.epub" },
    { AZW, "AZW", "com.amazon.azw" },
    { AZW3, "AZW3", "com.amazon.azw3" },
    { KFX, "KFX", "com.amazon.kfx" },
    { MOBI, "MOBI", "com.amazon.mobi" },
    { MEDIA, "MEDIA", "general.media" },
    { IMAGE, "IMAGE", "general.image" },
    { JPEG, "JPEG", "general.jpeg" },
    { PNG, "PNG", "general.png" },
    { RAW_IMAGE, "RAW_IMAGE", "general.raw-image" },
    { TIFF, "TIFF", "general.tiff" },
    { BMP, "BMP", "com.microsoft.bmp" },
    { ICO, "ICO", "com.microsoft.ico" },
    { PHOTOSHOP_IMAGE, "PHOTOSHOP_IMAGE", "com.adobe.photoshop-image" },
    { AI_IMAGE, "AI_IMAGE", "com.adobe.illustrator.ai-image" },
    { WORD_DOC, "WORD_DOC", "com.microsoft.word.doc" },
    { EXCEL, "EXCEL", "com.microsoft.excel.xls" },
    { PPT, "PPT", "com.microsoft.powerpoint.ppt" },
    { PDF, "PDF", "com.adobe.pdf" },
    { POSTSCRIPT, "POSTSCRIPT", "com.adobe.postscript" },
    { ENCAPSULATED_POSTSCRIPT, "ENCAPSULATED_POSTSCRIPT", "com.adobe.encapsulated-postscript" },
    { VIDEO, "VIDEO", "general.video" },
    { AVI, "AVI", "general.avi" },
    { MPEG, "MPEG", "general.mpeg" },
    { MPEG4, "MPEG4", "general.mpeg-4" },
    { VIDEO_3GPP, "VIDEO_3GPP", "general.3gpp" },
    { VIDEO_3GPP2, "VIDEO_3GPP2", "general.3gpp2" },
    { WINDOWS_MEDIA_WM, "WINDOWS_MEDIA_WM", "com.microsoft.windows-media-wm" },
    { WINDOWS_MEDIA_WMV, "WINDOWS_MEDIA_WMV", "com.microsoft.windows-media-wmv" },
    { WINDOWS_MEDIA_WMP, "WINDOWS_MEDIA_WMP", "com.microsoft.windows-media-wmp" },
    { AUDIO, "AUDIO", "general.audio" },
    { AAC, "AAC", "general.aac" },
    { AIFF, "AIFF", "general.aiff" },
    { ALAC, "ALAC", "general.alac" },
    { FLAC, "FLAC", "general.flac" },
    { MP3, "MP3", "general.mp3" },
    { OGG, "OGG", "general.ogg" },
    { PCM, "PCM", "general.pcm" },
    { WINDOWS_MEDIA_WMA, "WINDOWS_MEDIA_WMA", "com.microsoft.windows-media-wma" },
    { WAVEFORM_AUDIO, "WAVEFORM_AUDIO", "com.microsoft.waveform-audio" },
    { WINDOWS_MEDIA_WMX, "WINDOWS_MEDIA_WMX", "com.microsoft.windows-media-wmx" },
    { WINDOWS_MEDIA_WVX, "WINDOWS_MEDIA_WVX", "com.microsoft.windows-media-wvx" },
    { WINDOWS_MEDIA_WAX, "WINDOWS_MEDIA_WAX", "com.microsoft.windows-media-wax" },
    { FILE, "FILE", "general.file" },
    { DIRECTORY, "DIRECTORY", "general.directory" },
    { FOLDER, "FOLDER", "general.folder" },
    { SYMLINK, "SYMLINK", "general.symlink" },
    { ARCHIVE, "ARCHIVE", "general.archive" },
    { BZ2_ARCHIVE, "BZ2_ARCHIVE", "general.bz2-archive" },
    { DISK_IMAGE, "DISK_IMAGE", "general.disk-image" },
    { TAR_ARCHIVE, "TAR_ARCHIVE", "general.tar-archive" },
    { ZIP_ARCHIVE, "ZIP_ARCHIVE", "general.zip-archive" },
    { JAVA_ARCHIVE, "JAVA_ARCHIVE", "com.sun.java-archive" },
    { GNU_TAR_ARCHIVE, "GNU_TAR_ARCHIVE", "org.gnu.gnu-tar-archive" },
    { GNU_ZIP_ARCHIVE, "GNU_ZIP_ARCHIVE", "org.gnu.gnu-zip-archive" },
    { GNU_ZIP_TAR_ARCHIVE, "GNU_ZIP_TAR_ARCHIVE", "org.gnu.gnu-zip-tar-archive" },
    { CALENDAR, "CALENDAR", "general.calendar" },
    { CONTACT, "CONTACT", "general.contact" },
    { DATABASE, "DATABASE", "general.database" },
    { MESSAGE, "MESSAGE", "general.message" },
    { VCARD, "VCARD", "general.vcard" },
    { NAVIGATION, "NAVIGATION", "general.navigation" },
    { LOCATION, "LOCATION", "general.location" },
    { SYSTEM_DEFINED_RECORD, "SYSTEM_DEFINED_RECORD", "SystemDefinedType" },
    { SYSTEM_DEFINED_FORM, "OPENHARMONY_FORM", "openharmony.form" },
    { SYSTEM_DEFINED_APP_ITEM, "OPENHARMONY_APP_ITEM", "openharmony.app-item" },
    { SYSTEM_DEFINED_PIXEL_MAP, "OPENHARMONY_PIXEL_MAP", "openharmony.pixel-map" },
    { OPENHARMONY_ATOMIC_SERVICE, "OPENHARMONY_ATOMIC_SERVICE", "openharmony.atomic-service" },
    { APPLICATION_DEFINED_RECORD, "APPLICATION_DEFINED_RECORD", "ApplicationDefinedType" },
    { OPENHARMONY_PACKAGE, "OPENHARMONY_PACKAGE", "openharmony.package" },
    { OPENHARMONY_HAP, "OPENHARMONY_HAP", "openharmony.hap" },
    { SMIL, "SMIL", "com.real.smil" },
    { MARKDOWN, "MARKDOWN", "general.markdown" },
    { FAX, "FAX", "general.fax" },
    { JFX_FAX, "JFX_FAX", "com.j2.jfx-fax" },
    { EFX_FAX, "EFX_FAX", "com.js.efx-fax" },
    { XBITMAP_IMAGE, "XBITMAP_IMAGE", "general.xbitmap-image" },
    { TGA_IMAGE, "TGA_IMAGE", "com.truevision.tga-image" },
    { SGI_IMAGE, "SGI_IMAGE", "com.sgi.sgi-image" },
    { OPENEXR_IMAGE, "OPENEXR_IMAGE", "com.ilm.openexr-image" },
    { FLASHPIX_IMAGE, "FLASHPIX_IMAGE", "com.kodak.flashpix.image" },
    { REALMEDIA, "REALMEDIA", "com.real.realmedia" },
    { AU_AUDIO, "AU_AUDIO", "general.au-audio" },
    { AIFC_AUDIO, "AIFC_AUDIO", "general.aifc-audio" },
    { SD2_AUDIO, "SD2_AUDIO", "com.digidesign.sd2-audio" },
    { REALAUDIO, "REALAUDIO", "com.real.realaudio" },
    { OPENXML, "OPENXML", "org.openxmlformats.openxml" },
    { WORDPROCESSINGML_DOCUMENT, "WORDPROCESSINGML_DOCUMENT",
      "org.openxmlformats.wordprocessingml.document" },
    { SPREADSHEETML_SHEET, "SPREADSHEETML_SHEET", "org.openxmlformats.spreadsheetml.sheet" },
    { PRESENTATIONML_PRESENTATION, "PRESENTATIONML_PRESENTATION",
      "org.openxmlformats.presentationml.presentation" },
    { OPENDOCUMENT, "OPENDOCUMENT", "org.oasis.opendocument" },
    { OPENDOCUMENT_TEXT, "OPENDOCUMENT_TEXT", "org.oasis.opendocument.text" },
    { OPENDOCUMENT_SPREADSHEET, "OPENDOCUMENT_SPREADSHEET", "org.oasis.opendocument.spreadsheet" },
    { OPENDOCUMENT_PRESENTATION, "OPENDOCUMENT_PRESENTATION", "org.oasis.opendocument.presentation" },
    { OPENDOCUMENT_GRAPHICS, "OPENDOCUMENT_GRAPHICS", "org.oasis.opendocument.graphics" },
    { OPENDOCUMENT_FORMULA, "OPENDOCUMENT_FORMULA", "org.oasis.opendocument.formula" },
    { STUFFIT_ARCHIVE, "STUFFIT_ARCHIVE", "com.allume.stuffit-archive" },
    { VCS, "VCS", "general.vcs" },
    { ICS, "ICS", "general.ics" },
    { EXECUTABLE, "EXECUTABLE", "general.executable" },
    { PORTABLE_EXECUTABLE, "PORTABLE_EXECUTABLE", "com.microsoft.portable-executable" },
    { SUN_JAVA_CLASS, "SUN_JAVA_CLASS", "com.sun.java-class" },
    { FONT, "FONT", "general.font" },
    { TRUETYPE_FONT, "TRUETYPE_FONT", "general.truetype-font" },
    { TRUETYPE_COLLECTION_FONT, "TRUETYPE_COLLECTION_FONT", "general.truetype-collection-font" },
    { OPENTYPE_FONT, "OPENTYPE_FONT", "general.opentype-font" },
    { POSTSCRIPT_FONT, "POSTSCRIPT_FONT", "com.adobe.postscript-font" },
    { POSTSCRIPT_PFB_FONT, "POSTSCRIPT_PFB_FONT", "com.adobe.postscript-pfb-font" },
    { POSTSCRIPT_PFA_FONT, "POSTSCRIPT_PFA_FONT", "com.adobe.postscript-pfa-font" },
    { OPENHARMONY_HDOC, "OPENHARMONY_HDOC", "openharmony.hdoc" },
    { OPENHARMONY_HINOTE, "OPENHARMONY_HINOTE", "openharmony.hinote" },
    { OPENHARMONY_STYLED_STRING, "OPENHARMONY_STYLED_STRING", "openharmony.styled-string" },
    { OPENHARMONY_WANT, "OPENHARMONY_WANT", "openharmony.want" },
};

namespace UtdUtils {
bool IsValidUtdId(const std::string &utdId)
{
    for (const auto &item : UTD_TYPES) {
        if (item.UtdId == utdId) {
            return true;
        }
    }
    return false;
}

int32_t GetUtdEnumFromUtdId(const std::string &utdId)
{
    for (const auto &item : UTD_TYPES) {
        if (item.UtdId == utdId) {
            return item.UtdEnum;
        }
    }
    return UD_BUTT;
}

std::string GetUtdIdFromUtdEnum(int32_t utdType)
{
    for (const auto &item : UTD_TYPES) {
        if (item.UtdEnum == utdType) {
            return item.UtdId;
        }
    }
    return "";
}

std::vector<UtdType> GetUtdTypes()
{
    std::vector<UtdType> utdTypes(UTD_TYPES, UTD_TYPES + sizeof(UTD_TYPES) / sizeof(UtdType));
    return utdTypes;
}
} // namespace UtdUtils

bool UnifiedDataUtils::IsValidType(int32_t value)
{
    return value >= ENTITY && value < UD_BUTT;
}

bool UnifiedDataUtils::IsValidIntention(int32_t value)
{
    return value > UD_INTENTION_BASE && value < UD_INTENTION_BUTT;
}

static constexpr AppShareOption APP_SHARE_OPTIONS[] = {
    { IN_APP, "IN_APP"},
    { CROSS_APP, "CROSS_APP"},
};

bool ShareOptionsUtil::IsValid(int32_t shareOption)
{
    if (shareOption < 0 || shareOption >= SHARE_OPTIONS_BUTT) {
        return false;
    }
    return true;
}

int32_t ShareOptionsUtil::GetEnumNum(const std::string &shareOption)
{
    for (const auto &item : APP_SHARE_OPTIONS) {
        if (item.enumStr == shareOption) {
            return item.enumNum;
        }
    }
    return SHARE_OPTIONS_BUTT;
}

std::string ShareOptionsUtil::GetEnumStr(int32_t shareOption)
{
    for (const auto &item : APP_SHARE_OPTIONS) {
        if (item.enumNum == shareOption) {
            return item.enumStr;
        }
    }
    return "";
}

size_t UnifiedDataUtils::GetVariantSize(UDVariant &variant)
{
    auto int32Value = std::get_if<int32_t>(&variant);
    if (int32Value != nullptr) {
        return sizeof(std::get<int32_t>(variant));
    }
    auto int64Value = std::get_if<int64_t>(&variant);
    if (int64Value != nullptr) {
        return sizeof(std::get<int64_t>(variant));
    }
    auto boolValue = std::get_if<bool>(&variant);
    if (boolValue != nullptr) {
        return sizeof(std::get<bool>(variant));
    }
    auto doubleValue = std::get_if<double>(&variant);
    if (doubleValue != nullptr) {
        return sizeof(std::get<double>(variant));
    }
    auto strValue = std::get_if<std::string>(&variant);
    if (strValue != nullptr) {
        return std::get<std::string>(variant).size();
    }
    auto vecValue = std::get_if<std::vector<uint8_t>>(&variant);
    if (vecValue != nullptr) {
        return std::get<std::vector<uint8_t>>(variant).size();
    }
    return 0;
}

size_t UnifiedDataUtils::GetDetailsSize(UDDetails &details)
{
    size_t total = 0;
    for (std::pair<std::string, UDVariant> prop : details) {
        total += prop.first.size();
        total += GetVariantSize(prop.second);
    }
    return total;
}

bool UnifiedDataUtils::IsPersist(const Intention &intention)
{
    return intention >= UD_INTENTION_DATA_HUB && intention < UD_INTENTION_BUTT;
}

bool UnifiedDataUtils::IsPersist(const std::string &intention)
{
    return IsPersist(GetIntentionByString(intention));
}

Intention UnifiedDataUtils::GetIntentionByString(const std::string &intention)
{
    for (const auto &it : UD_INTENTION_MAP) {
        if (it.second == intention) {
            return static_cast<Intention>(it.first);
        }
    }
    return UD_INTENTION_BUTT;
}

bool UnifiedDataUtils::IsValidOptions(const std::string &key, std::string &intention)
{
    UnifiedKey unifiedKey(key);
    auto isValidKey = unifiedKey.IsValid();
    if (key.empty() && IsPersist(intention)) {
        return true;
    }
    if (intention.empty() && isValidKey && IsPersist(unifiedKey.intention)) {
        return true;
    }
    if (isValidKey && unifiedKey.intention == intention && IsPersist(intention)) {
        intention = "";
        return true;
    }
    return false;
}
} // namespace UDMF
} // namespace OHOS