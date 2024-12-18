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
#include "pixel_map.h"
#include "string_ex.h"
#include "want.h"

namespace OHOS {
namespace UDMF {
constexpr const char* UNIFORM_DATA_TYPE = "uniformDataType";
constexpr const char* CONTENT = "textContent";
constexpr const char* ABSTRACT = "abstract";
constexpr const char* URL = "url";
constexpr const char* DESCRIPTION = "description";
constexpr const char* HTML_CONTENT = "htmlContent";
constexpr const char* PLAIN_CONTENT = "plainContent";
constexpr const char* APP_ID = "appId";
constexpr const char* APP_NAME = "appName";
constexpr const char* APP_ICON_ID = "appIconId";
constexpr const char* APP_LABEL_ID = "appLabelId";
constexpr const char* BUNDLE_NAME = "bundleName";
constexpr const char* ABILITY_NAME = "abilityName";
constexpr const char* FILE_URI_PARAM = "oriUri";
constexpr const char* FILE_TYPE = "fileType";
constexpr const char* PIXEL_MAP = "pixelMap";
constexpr const char* ARRAY_BUFFER = "arrayBuffer";
constexpr const char* ARRAY_BUFFER_LENGTH = "arrayBufferLen";
constexpr const char *FORMID = "formId";
constexpr const char *FORMNAME = "formName";
constexpr const char *MODULE = "module";
constexpr const char *ORI_URI = "oriUri";
constexpr const char *REMOTE_URI = "remoteUri";
constexpr const char *DETAILS = "details";
constexpr const char *VALUE_TYPE = "VALUE_TYPE";
constexpr const char *THUMB_DATA = "thumbData";
constexpr const char *THUMB_DATA_LENGTH = "thumbDataLen";
constexpr const char *TITLE = "title";
constexpr const char* APP_ICON = "appIcon";
constexpr const char* APP_ICON_LENGTH = "appIconLen";
constexpr const char* LINK_URL = "linkUrl";

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
    OFD,
    OPG,
    TEX,
    CSS,
    VOB,
    DIF_VIDEO,
    DV_VIDEO,
    FLC_ANIMATION,
    MNG,
    MPEGURL_VIDEO,
    TS,
    AMR,
    AMR_WB,
    GMS,
    IMY,
    KAR,
    MPEGURL_AUDIO,
    MPEG_4_AUDIO,
    MIDI_AUDIO,
    MP2,
    MPEG_AUDIO,
    MXMF,
    OTA,
    PLS,
    RTTTL,
    PSID,
    ULAW_AUDIO,
    XMF,
    GIF,
    DJVU_IMAGE,
    JNG_IMAGE,
    PCX_IMAGE,
    PBM_IMAGE,
    PGM_IMAGE,
    PNM_IMAGE,
    PPM_IMAGE,
    RGB_IMAGE,
    SVG_IMAGE,
    WBMP_IMAGE,
    XPIXMP_IMAGE,
    XWINDOWDUMP_IMAGE,
    HEIF,
    HEIC,
    VIRTUAL_CD,
    BOO_SOURCE,
    D_SOURCE,
    HTML_COMPONENT,
    PASCAL_SOURCE,
    HASKELL_SCRIPT,
    LITERATE_HASKELL_SCRIPT,
    TCL_SCRIPT,
    ASC_TEXT,
    PORTABLE_OBJECT,
    RICH_TEXT,
    DELIMITED_VALUES_TEXT,
    COMMA_SEPARATED_VALUES_TEXT,
    DIFF,
    SETEXT,
    GCD,
    TAB_SEPARATED_VALUES_TEXT,
    P7R,
    PEM,
    CHESS_PGN,
    LHA_ARCHIVE,
    LZH_ARCHIVE,
    LZX_ARCHIVE,
    TAZ_ARCHIVE,
    SHAR_ARCHIVE,
    CPIO_ARCHIVE,
    WEB_ARCHIVE,
    USTAR,
    MATHML,
    XHTML,
    RSS,
    RDF,
    IGES,
    CAD,
    OCTET_STREAM,
    ISO,
    MESH_MODEL,
    CERTIFICATE,
    C_OBJECT,
    DVI,
    CER_CERTIFICATE,
    CRT_CERTIFICATE,
    CRL_CERTIFICATE,
    PRN,
    OPENDOCUMENT_CHART,
    OPENDOCUMENT_TEXT_MASTER,
    OPENDOCUMENT_TEXT_WEB,
    OPENDOCUMENT_DATABASE,
    OPENDOCUMENT_IMAGE,
    OPENDOCUMENT_FORMULA_TEMPLATE,
    OPENDOCUMENT_CHART_TEMPLATE,
    OPENDOCUMENT_PRESENTATION_TEMPLATE,
    OPENDOCUMENT_IMAGE_TEMPLATE,
    OPENDOCUMENT_GRAPHICS_TEMPLATE,
    OPENDOCUMENT_SPREADSHEET_TEMPLATE,
    OPENDOCUMENT_TEXT_TEMPLATE,
    WORD_DOT,
    POWERPOINT_PPS,
    POWERPOINT_POT,
    EXCEL_XLT,
    VISIO_VSD,
    DRAWINGML_VISIO,
    DRAWINGML_TEMPLATE,
    DRAWINGML_VISIO_MACROENABLED,
    DRAWINGML_TEMPLATE_MACROENABLED,
    WORDPROCESSINGML_TEMPLATE,
    PRESENTATIONML_TEMPLATE,
    PRESENTATIONML_SLIDESHOW,
    SPREADSHEETML_TEMPLATE,
    WORDPROCESSINGML_DOCUMENT_MACROENABLED,
    WORDPROCESSINGML_TEMPLATE_MACROENABLED,
    SPREADSHEETML_TEMPLATE_MACROENABLED,
    SPREADSHEETML_ADDIN_MACROENABLED,
    SPREADSHEETML_BINARY_MACROENABLED,
    SPREADSHEETML_SHEET_MACROENABLED,
    PRESENTATIONALML_ADDIN_MACROENABLED,
    PRESENTATIONALML_PRESENTATION_MACROENABLED,
    PRESENTATIONALML_SLIDESHOW_MACROENABLED,
    PRESENTATIONALML_TEMPLATE_MACROENABLED,
    OPENOFFICE,
    OPENOFFICE_CALC,
    OPENOFFICE_DRAW,
    OPENOFFICE_WRITER_GLOBAL,
    OPENOFFICE_IMPRESS,
    OPENOFFICE_MATH,
    OPENOFFICE_WRITER,
    OPENOFFICE_CALC_TEMPLATE,
    OPENOFFICE_DRAW_TEMPLATE,
    OPENOFFICE_IMPRESS_TEMPLATE,
    OPENOFFICE_WRITER_TEMPLATE,
    STAROFFICE,
    STAROFFICE_DRAW,
    STAROFFICE_CALC,
    STAROFFICE_IMPRESS,
    STAROFFICE_WRITER,
    STAROFFICE_CHART,
    STAROFFICE_MAIL,
    STAROFFICE_WRITER_GLOBAL,
    STAROFFICE_MATH,
    STAROFFICE_TEMPLATE,
    TUG_BIB,
    TUG_CLS,
    TUG_STY,
    TUG_TEX,
    LATEX,
    ADVANCED_SYSTEMS_FORMAT,
    ADVANCED_STREAM_REDIRECTOR,
    MATROSKA_VIDEO,
    MATROSKA_AUDIO,
    SGI_MOVIE,
    APPLE_M4V,
    WEBM,
    QUICKTIME_MOVIE,
    CORELDRAW_CDR,
    CORELDRAW_CDT,
    CORELDRAW_CPT,
    CORELDRAW_PAT,
    MICROSOFT_CUR,
    SUN_RASTER,
    GOOGLE_WEBP,
    KOAN_AUDIO,
    QT_MOC,
    GHOSTSCRIPT_FONT,
    X_PCF_FONT,
    WINDOWS_MEDIA_WMD,
    WINDOWS_MEDIA_WMZ,
    WINDOWS_INSTALLER,
    PUBLISHER_PUB,
    WINDOWS_MEDIA_PLAYLIST,
    ACCESS_MDB,
    STEREOLITHOGRAPHY,
    APPLE_MEDIA_PLAYLIST,
    ABISOURCE_WORD,
    ADOBE_FRAMEMAKER,
    WOLFRAM_CDF,
    CINDERELLA_CDY,
    ADOBE_DCR,
    ADOBE_DIR,
    ADOBE_DXR,
    GNUMERIC_SPREADSHEET,
    HDFGROUP_HDF,
    BINHEX_ARCHIVE,
    MICROSOFT_HTA,
    INTERNET_INS,
    INTERNET_ISP,
    TROFF,
    ADOBE_MIF,
    FREEMIND,
    YAMAHA_SMAF,
    MATHEMATICA_NOTEBOOK,
    XIPH_OGG,
    PROXY_AUTOCONFIG,
    PKCS_12,
    PGP_SIGNATURE,
    QUICKTIME_LINK,
    RAR_ARCHIVE,
    SEVEN_ZIP_ARCHIVE,
    RED_BEAN_SGF,
    SIT_ARCHIVE,
    FUTURESPLASH,
    FLASH,
    TEXINFO,
    TORRENT,
    DOOM,
    APPLE_WEBARCHIVE,
    ANDROID_WEBARCHIVE,
    GIMP_XCF,
    EDRWMAX,
    EDRWMIND,
    CNKI_CAJ,
    DBASE_DBF,
    AUTODESK_DWG,
    AUTODESK_DXF,
    AUTODESK_DWS,
    AUTODESK_DWT,
    AUTODESK_DWF,
    AUTODESK_DWFX,
    AUTODESK_SHP,
    AUTODESK_SHX,
    AUTODESK_SLIDE_LIB,
    AUTODESK_LINE,
    AUTODESK_PLOTTER,
    HP_GRAPHICS_LANG,
    MICROSOFT_METAFILE,
    ACIS_SAT,
    AVIF_IMAGE,
    MICROSOFT_DDS,
    IFF_ILBM,
    CR2_RAW_IMAGE,
    CR3_RAW_IMAGE,
    CRW_RAW_IMAGE,
    DNG_RAW_IMAGE,
    ARW_RAW_IMAGE,
    NEF_RAW_IMAGE,
    MINDMANAGER_MMAP,
    MICROSOFT_EMAIL,
    MICROSOFT_MESSAGE,
    MICROSOFT_PST,
    KINGSOFT_OFFICE,
    KINGSOFT_WRITER_WPS,
    KINGSOFT_WRITER_WPT,
    KINGSOFT_PRESENTATION_DPS,
    KINGSOFT_PRESENTATION_TEMPLATE,
    KINGSOFT_SPREADSHEETS_ET,
    KINGSOFT_SPREADSHEETS_TEMPLATE,
    MICROSOFT_INI,
    JSON,
    YAML,
    LOG,
    URI,
    FILE_URI,
    TEXT_LST,
    ANDROID_APK,
    BZ_ARCHIVE,
    TBZ_ARCHIVE,
    TBZ2_ARCHIVE,
    XZ_ARCHIVE,
    TXZ_ARCHIVE,
    XAR_ARCHIVE,
    CAB_ARCHIVE,
    RPM_ARCHIVE,
    TPZ_ARCHIVE,
    LZA_ARCHIVE,
    ARJ_ARCHIVE,
    ZIPX_ARCHIVE,
    LZMA_ARCHIVE,
    LZMA86_ARCHIVE,
    XPI_ARCHIVE,
    HFS_DISK_IMAGE,
    IMG_DISK_IMAGE,
    ISZ_DISK_IMAGE,
    WIM_DISK_IMAGE,
    SWM_DISK_IMAGE,
    KINGSOFT_SPREADSHEETS_ETX,
    KINGSOFT_SPREADSHEETS_ETTX,
    EXCEL_DIF,
    OPENHARMONY_APP,
    HMOS_WIFI,
    TEL,
    ETS,
    JSON5,
    APE_AUDIO,
    OPUS_AUDIO,
    CONF,
    MICROSOFT_DOS_BATCH,
    MICROSOFT_VBSCRIPT,
    ION,
    MICROSOFT_REGISTRY,
    MICROSOFT_CATALOG,
    MICROSOFT_POWERSHELL_SCRIPT,
    W3_WOFF,
    SQLITE_DATABASE,
    MICROSOFT_SYS,
    MICROSOFT_INF,
    MICROSOFT_PDB,
    MICROSOFT_TLB,
    MICROSOFT_SCCD,
    ADOBE_F4V,
    MP2T,
    YOUTUBE_VIDEO,
    WEBEX_VIDEO,
    MPEG2,
    MPEG1,
    REALMEDIA_VBR,
    REAL_REALVIDEO,
    DIVX_VIDEO,
    CSIRO_ANNODEX,
    OGV,
    LSF_VIDEO,
    H264_VIDEO,
    JPEG2000,
    RAF_RAW_IMAGE,
    NRW_RAW_IMAGE,
    RW2_RAW_IMAGE,
    PEF_RAW_IMAGE,
    SRW_RAW_IMAGE,
    ERF_RAW_IMAGE,
    ORF_RAW_IMAGE,
    IEF_IMAGE,
    ART_IMAGE,
    CONTENT_FORM,
    M4P_AUDIO,
    AC3_AUDIO,
    OPENHARMONY_HSP,
    OPENHARMONY_HAR,
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
    CROSS_DEVICE,
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

struct Object;
using ValueType = std::variant<std::monostate, int32_t, int64_t, double, bool, std::string, std::vector<uint8_t>,
    std::shared_ptr<OHOS::AAFwk::Want>, std::shared_ptr<OHOS::Media::PixelMap>, std::shared_ptr<Object>, nullptr_t>;

struct API_EXPORT Object {
    template<typename T>
    bool GetValue(const std::string &key, T &value)
    {
        auto it = value_.find(key);
        if (it != value_.end() && std::holds_alternative<T>(it->second)) {
            value = std::get<T>(it->second);
            return true;
        }
        return false;
    }

    std::map<std::string, ValueType> value_;
};

namespace ObjectUtils {
    std::shared_ptr<Object> API_EXPORT ConvertToObject(UDDetails &details);
    UDDetails API_EXPORT ConvertToUDDetails(std::shared_ptr<Object> object);

    int64_t GetValueSize(const ValueType &value, bool isCalValueType);
    int64_t GetObjectValueSize(const std::shared_ptr<Object> object, bool isCalValueType);
    int64_t GetAllObjectSize(const std::shared_ptr<Object> object);

    template<typename T, typename... Types>
    bool ConvertVariant(T &&input, std::variant<Types...> &output)
    {
        bool converted = false;
        std::visit(
            [&output, &converted](auto &&val) {
              using BasicType = std::decay_t<decltype(val)>;
              if constexpr ((std::is_same_v<BasicType, Types> || ...)) {
                output = std::variant<Types...>(std::move(val));
                converted = true;
              }
            },
            input);
        return converted;
    }
} // namespace ObjectUtils
} // namespace UDMF
} // namespace OHOS
#endif // UNIFIED_META_H
