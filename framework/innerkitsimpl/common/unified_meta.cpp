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

#define LOG_TAG "UnifiedMeta"
#include "unified_meta.h"

#include "logger.h"
#include "unified_key.h"
#include "utd_client.h"

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
    { OFD, "OFD", "general.ofd" },
    { OPG, "OPG", "general.opg" },
    { TEX, "TEX", "general.tex" },
    { CSS, "CSS", "general.css" },
    { VOB, "VOB", "general.vob" },
    { DIF_VIDEO, "DIF_VIDEO", "general.dif-video" },
    { DV_VIDEO, "DV_VIDEO", "general.dv-video" },
    { FLC_ANIMATION, "FLC_ANIMATION", "general.flc-animation" },
    { MNG, "MNG", "general.mng" },
    { MPEGURL_VIDEO, "MPEGURL_VIDEO", "general.mpegurl-video" },
    { TS, "TS", "general.ts" },
    { AMR, "AMR", "general.amr" },
    { AMR_WB, "AMR_WB", "general.amr-wb" },
    { GMS, "GSM", "general.gsm" },
    { IMY, "IMY", "general.imy" },
    { KAR, "KAR", "general.kar" },
    { MPEGURL_AUDIO, "MPEGURL_AUDIO", "general.mpegurl-audio" },
    { MPEG_4_AUDIO, "MPEG_4_AUDIO", "general.mpeg-4-audio" },
    { MIDI_AUDIO, "MIDI_AUDIO", "general.midi-audio" },
    { MP2, "MP2", "general.mp2" },
    { MPEG_AUDIO, "MPEG_AUDIO", "general.mpeg-audio" },
    { MXMF, "MXMF", "general.mxmf" },
    { OTA, "OTA", "general.ota" },
    { PLS, "PLS", "general.pls" },
    { RTTTL, "RTTTL", "general.rtttl" },
    { PSID, "PSID", "general.psid" },
    { ULAW_AUDIO, "ULAW_AUDIO", "general.ulaw-audio" },
    { XMF, "XMF", "general.xmf" },
    { GIF, "GIF", "general.gif" },
    { DJVU_IMAGE, "DJVU_IMAGE", "general.djvu-image" },
    { JNG_IMAGE, "JNG_IMAGE", "general.jng-image" },
    { PCX_IMAGE, "PCX_IMAGE", "general.pcx-image" },
    { PBM_IMAGE, "PBM_IMAGE", "general.pbm-image" },
    { PGM_IMAGE, "PGM_IMAGE", "general.pgm-image" },
    { PNM_IMAGE, "PNM_IMAGE", "general.pnm-image" },
    { PPM_IMAGE, "PPM_IMAGE", "general.ppm-image" },
    { RGB_IMAGE, "RGB_IMAGE", "general.rgb-image" },
    { SVG_IMAGE, "SVG_IMAGE", "general.svg-image" },
    { WBMP_IMAGE, "WBMP_IMAGE", "general.wbmp-image" },
    { XPIXMP_IMAGE, "XPIXMAP_IMAGE", "general.xpixmap-image" },
    { XWINDOWDUMP_IMAGE, "XWINDOWDUMP_IMAGE", "general.xwindowdump-image" },
    { HEIF, "HEIF", "general.heif" },
    { HEIC, "HEIC", "general.heic" },
    { VIRTUAL_CD, "VIRTUAL_CD", "general.virtual-cd" },
    { BOO_SOURCE, "BOO_SOURCE", "general.boo-source" },
    { D_SOURCE, "D_SOURCE", "general.d-source" },
    { HTML_COMPONENT, "HTML_COMPONENT", "general.html-component" },
    { PASCAL_SOURCE, "PASCAL_SOURCE", "general.pascal-source" },
    { HASKELL_SCRIPT, "HASKELL_SCRIPT", "general.haskell-script" },
    { LITERATE_HASKELL_SCRIPT, "LITERATE_HASKELL_SCRIPT", "general.literate-haskell-script" },
    { TCL_SCRIPT, "TCL_SCRIPT", "general.tcl-script" },
    { ASC_TEXT, "ASC_TEXT", "general.asc-text" },
    { PORTABLE_OBJECT, "PORTABLE_OBJECT", "general.portable-object" },
    { RICH_TEXT, "RICH_TEXT", "general.rich-text" },
    { DELIMITED_VALUES_TEXT, "DELIMITED_VALUES_TEXT", "general.delimited-values-text" },
    { COMMA_SEPARATED_VALUES_TEXT, "COMMA_SEPARATED_VALUES_TEXT", "general.comma-separated-values-text" },
    { DIFF, "DIFF", "general.diff" },
    { SETEXT, "SETEXT", "general.setext" },
    { GCD, "GCD", "general.gcd" },
    { TAB_SEPARATED_VALUES_TEXT, "TAB_SEPARATED_VALUES_TEXT", "general.tab-separated-values-text" },
    { P7R, "P7R", "general.p7r" },
    { PEM, "PEM", "general.pem" },
    { CHESS_PGN, "CHESS_PGN", "general.chess-pgn" },
    { LHA_ARCHIVE, "LHA_ARCHIVE", "general.lha-archive" },
    { LZH_ARCHIVE, "LZH_ARCHIVE", "general.lzh-archive" },
    { LZX_ARCHIVE, "LZX_ARCHIVE", "general.lzx-archive" },
    { TAZ_ARCHIVE, "TAZ_ARCHIVE", "general.taz-archive" },
    { SHAR_ARCHIVE, "SHAR_ARCHIVE", "general.shar-archive" },
    { CPIO_ARCHIVE, "CPIO_ARCHIVE", "general.cpio-archive" },
    { WEB_ARCHIVE, "WEB_ARCHIVE", "general.web-archive" },
    { USTAR, "USTAR", "general.ustar" },
    { MATHML, "MATHML", "general.mathml" },
    { XHTML, "XHTML", "general.xhtml" },
    { RSS, "RSS", "general.rss" },
    { RDF, "RDF", "general.rdf" },
    { IGES, "IGES", "general.iges" },
    { CAD, "CAD", "general.cad" },
    { OCTET_STREAM, "OCTET_STREAM", "general.octet-stream" },
    { ISO, "ISO", "general.iso" },
    { MESH_MODEL, "MESH_MODEL", "general.mesh-model" },
    { CERTIFICATE, "CERTIFICATE", "general.certificate" },
    { C_OBJECT, "C_OBJECT", "general.c-object" },
    { DVI, "DVI", "general.dvi" },
    { CER_CERTIFICATE, "CER_CERTIFICATE", "general.cer-certificate" },
    { CRT_CERTIFICATE, "CRT_CERTIFICATE", "general.crt-certificate" },
    { CRL_CERTIFICATE, "CRL_CERTIFICATE", "general.crl-certificate" },
    { PRN, "PRN", "general.prn" },
    { OPENDOCUMENT_CHART, "OPENDOCUMENT_CHART", "org.oasis-open.opendocument.chart" },
    { OPENDOCUMENT_TEXT_MASTER, "OPENDOCUMENT_TEXT_MASTER", "org.oasis-open.opendocument.text-master" },
    { OPENDOCUMENT_TEXT_WEB, "OPENDOCUMENT_TEXT_WEB", "org.oasis-open.opendocument.text-web" },
    { OPENDOCUMENT_DATABASE, "OPENDOCUMENT_DATABASE", "org.oasis-open.opendocument.database" },
    { OPENDOCUMENT_IMAGE, "OPENDOCUMENT_IMAGE", "org.oasis-open.opendocument.image" },
    { OPENDOCUMENT_FORMULA_TEMPLATE, "OPENDOCUMENT_FORMULA_TEMPLATE",  "org.oasis-open.opendocument.formula-template" },
    { OPENDOCUMENT_CHART_TEMPLATE, "OPENDOCUMENT_CHART_TEMPLATE", "org.oasis-open.opendocument.chart-template" },
    { OPENDOCUMENT_PRESENTATION_TEMPLATE, "OPENDOCUMENT_PRESENTATION_TEMPLATE",
      "org.oasis-open.opendocument.presentation-template" },
    { OPENDOCUMENT_IMAGE_TEMPLATE, "OPENDOCUMENT_IMAGE_TEMPLATE", "org.oasis-open.opendocument.image-template" },
    { OPENDOCUMENT_GRAPHICS_TEMPLATE, "OPENDOCUMENT_GRAPHICS_TEMPLATE",
      "org.oasis-open.opendocument.graphics-template" },
    { OPENDOCUMENT_SPREADSHEET_TEMPLATE, "OPENDOCUMENT_SPREADSHEET_TEMPLATE",
      "org.oasis-open.opendocument.spreadsheet-template" },
    { OPENDOCUMENT_TEXT_TEMPLATE, "OPENDOCUMENT_TEXT_TEMPLATE", "org.oasis-open.opendocument.text-template" },
    { WORD_DOT, "WORD_DOT", "com.microsoft.word.dot" },
    { POWERPOINT_PPS, "POWERPOINT_PPS", "com.microsoft.powerpoint.pps" },
    { POWERPOINT_POT, "POWERPOINT_POT", "com.microsoft.powerpoint.pot" },
    { EXCEL_XLT, "EXCEL_XLT", "com.microsoft.excel.xlt" },
    { VISIO_VSD, "VISIO_VSD", "com.microsoft.visio.vsd" },
    { DRAWINGML_VISIO, "DRAWINGML_VISIO", "org.openxmlformats.drawingml.visio" },
    { DRAWINGML_TEMPLATE, "DRAWINGML_TEMPLATE", "org.openxmlformats.drawingml.template" },
    { DRAWINGML_VISIO_MACROENABLED, "DRAWINGML_VISIO_MACROENABLED", "org.openxmlformats.drawingml.visio.macroenabled" },
    { DRAWINGML_TEMPLATE_MACROENABLED, "DRAWINGML_TEMPLATE_MACROENABLED",
      "org.openxmlformats.drawingml.template.macroenabled" },
    { WORDPROCESSINGML_TEMPLATE, "WORDPROCESSINGML_TEMPLATE", "org.openxmlformats.wordprocessingml.template" },
    { PRESENTATIONML_TEMPLATE, "PRESENTATIONML_TEMPLATE", "org.openxmlformats.presentationml.template" },
    { PRESENTATIONML_SLIDESHOW, "PRESENTATIONML_SLIDESHOW", "org.openxmlformats.presentationml.slideshow" },
    { SPREADSHEETML_TEMPLATE, "SPREADSHEETML_TEMPLATE", "org.openxmlformats.spreadsheetml.template" },
    { WORDPROCESSINGML_DOCUMENT_MACROENABLED, "WORDPROCESSINGML_DOCUMENT_MACROENABLED",
      "org.openxmlformats.wordprocessingml.document.macroenabled" },
    { WORDPROCESSINGML_TEMPLATE_MACROENABLED, "WORDPROCESSINGML_TEMPLATE_MACROENABLED",
      "org.openxmlformats.wordprocessingml.template.macroenabled" },
    { SPREADSHEETML_TEMPLATE_MACROENABLED, "SPREADSHEETML_TEMPLATE_MACROENABLED",
      "org.openxmlformats.spreadsheetml.template.macroenabled" },
    { SPREADSHEETML_ADDIN_MACROENABLED, "SPREADSHEETML_ADDIN_MACROENABLED",
      "org.openxmlformats.spreadsheetml.addin.macroenabled" },
    { SPREADSHEETML_BINARY_MACROENABLED, "SPREADSHEETML_BINARY_MACROENABLED",
      "org.openxmlformats.spreadsheetml.binary.macroenabled" },
    { SPREADSHEETML_SHEET_MACROENABLED, "SPREADSHEETML_SHEET_MACROENABLED",
      "org.openxmlformats.spreadsheetml.sheet.macroenabled" },
    { PRESENTATIONALML_ADDIN_MACROENABLED, "PRESENTATIONALML_ADDIN_MACROENABLED",
      "org.openxmlformats.presentationml.addin.macroenabled" },
    { PRESENTATIONALML_PRESENTATION_MACROENABLED, "PRESENTATIONALML_PRESENTATION_MACROENABLED",
      "org.openxmlformats.presentationml.presentation.macroenabled" },
    { PRESENTATIONALML_SLIDESHOW_MACROENABLED, "PRESENTATIONALML_SLIDESHOW_MACROENABLED",
      "org.openxmlformats.presentationml.slideshow.macroenabled" },
    { PRESENTATIONALML_TEMPLATE_MACROENABLED, "PRESENTATIONALML_TEMPLATE_MACROENABLED",
      "org.openxmlformats.presentationml.template.macroenabled" },
    { OPENOFFICE, "OPENOFFICE", "org.openoffice" },
    { OPENOFFICE_CALC, "OPENOFFICE_CALC", "org.openoffice.calc" },
    { OPENOFFICE_DRAW, "OPENOFFICE_DRAW", "org.openoffice.draw" },
    { OPENOFFICE_WRITER_GLOBAL, "OPENOFFICE_WRITER_GLOBAL", "org.openoffice.writer-global" },
    { OPENOFFICE_IMPRESS, "OPENOFFICE_IMPRESS", "org.openoffice.impress" },
    { OPENOFFICE_MATH, "OPENOFFICE_MATH", "org.openoffice.math" },
    { OPENOFFICE_WRITER, "OPENOFFICE_WRITER", "org.openoffice.writer" },
    { OPENOFFICE_CALC_TEMPLATE, "OPENOFFICE_CALC_TEMPLATE", "org.openoffice.calc.template" },
    { OPENOFFICE_DRAW_TEMPLATE, "OPENOFFICE_DRAW_TEMPLATE", "org.openoffice.draw.template" },
    { OPENOFFICE_IMPRESS_TEMPLATE, "OPENOFFICE_IMPRESS_TEMPLATE", "org.openoffice.impress.template" },
    { OPENOFFICE_WRITER_TEMPLATE, "OPENOFFICE_WRITER_TEMPLATE", "org.openoffice.writer.template" },
    { STAROFFICE, "STAROFFICE", "com.staroffice" },
    { STAROFFICE_DRAW, "STAROFFICE_DRAW", "com.staroffice.draw" },
    { STAROFFICE_CALC, "STAROFFICE_CALC", "com.staroffice.calc" },
    { STAROFFICE_IMPRESS, "STAROFFICE_IMPRESS", "com.staroffice.impress" },
    { STAROFFICE_WRITER, "STAROFFICE_WRITER", "com.staroffice.writer" },
    { STAROFFICE_CHART, "STAROFFICE_CHART", "com.staroffice.chart" },
    { STAROFFICE_MAIL, "STAROFFICE_MAIL", "com.staroffice.mail" },
    { STAROFFICE_WRITER_GLOBAL, "STAROFFICE_WRITER_GLOBAL", "com.staroffice.writer-global" },
    { STAROFFICE_MATH, "STAROFFICE_MATH", "com.staroffice.math" },
    { STAROFFICE_TEMPLATE, "STAROFFICE_TEMPLATE", "com.staroffice.template" },
    { TUG_BIB, "TUG_BIB", "org.tug.bib" },
    { TUG_CLS, "TUG_CLS", "org.tug.cls" },
    { TUG_STY, "TUG_STY", "org.tug.sty" },
    { TUG_TEX, "TUG_TEX", "org.tug.tex" },
    { LATEX, "LATEX", "org.latex-project.latex" },
    { ADVANCED_SYSTEMS_FORMAT, "ADVANCED_SYSTEMS_FORMAT", "com.microsoft.advanced-systems-format" },
    { ADVANCED_STREAM_REDIRECTOR, "ADVANCED_STREAM_REDIRECTOR", "com.microsoft.advanced-stream-redirector" },
    { MATROSKA_VIDEO, "MATROSKA_VIDEO", "org.matroska.mkv" },
    { MATROSKA_AUDIO, "MATROSKA_AUDIO", "org.matroska.mka" },
    { SGI_MOVIE, "SGI_MOVIE", "com.sgi.movie" },
    { APPLE_M4V, "APPLE_M4V", "com.apple.m4v" },
    { WEBM, "WEBM", "org.webmproject.webm" },
    { QUICKTIME_MOVIE, "QUICKTIME_MOVIE", "com.apple.quicktime-movie" },
    { CORELDRAW_CDR, "CORELDRAW_CDR", "com.coreldraw.cdr" },
    { CORELDRAW_CDT, "CORELDRAW_CDT", "com.coreldraw.cdt" },
    { CORELDRAW_CPT, "CORELDRAW_CPT", "com.coreldraw.cpt" },
    { CORELDRAW_PAT, "CORELDRAW_PAT", "com.coreldraw.pat" },
    { MICROSOFT_CUR, "MICROSOFT_CUR", "com.microsoft.cur" },
    { SUN_RASTER, "SUN_RASTER", "com.sun.raster" },
    { GOOGLE_WEBP, "GOOGLE_WEBP", "com.google.webp" },
    { KOAN_AUDIO, "KOAN_AUDIO", "com.sseyo.koan-audio" },
    { QT_MOC, "QT_MOC", "io.qt.moc" },
    { GHOSTSCRIPT_FONT, "GHOSTSCRIPT_FONT", "com.ghostscript.font" },
    { X_PCF_FONT, "X_PCF_FONT", "org.x.pcf-font" },
    { WINDOWS_MEDIA_WMD, "WINDOWS_MEDIA_WMD", "com.microsoft.windows-media-wmd" },
    { WINDOWS_MEDIA_WMZ, "WINDOWS_MEDIA_WMZ", "com.microsoft.windows-media-wmz" },
    { WINDOWS_INSTALLER, "WINDOWS_INSTALLER", "com.microsoft.windows-installer" },
    { PUBLISHER_PUB, "PUBLISHER_PUB", "com.microsoft.publisher.pub" },
    { WINDOWS_MEDIA_PLAYLIST, "WINDOWS_MEDIA_PLAYLIST", "com.microsoft.windows-media-playlist" },
    { ACCESS_MDB, "ACCESS_MDB", "com.microsoft.access.mdb" },
    { STEREOLITHOGRAPHY, "STEREOLITHOGRAPHY", "com.3dsystems.stereolithography" },
    { APPLE_MEDIA_PLAYLIST, "APPLE_MEDIA_PLAYLIST", "com.apple.media.playlist" },
    { ABISOURCE_WORD, "ABISOURCE_WORD", "com.abisource.word" },
    { ADOBE_FRAMEMAKER, "ADOBE_FRAMEMAKER", "com.adobe.framemaker" },
    { WOLFRAM_CDF, "WOLFRAM_CDF", "com.wolfram.cdf" },
    { CINDERELLA_CDY, "CINDERELLA_CDY", "de.cinderella.cdy" },
    { ADOBE_DCR, "ADOBE_DCR", "com.adobe.dcr" },
    { ADOBE_DIR, "ADOBE_DIR", "com.adobe.dir" },
    { ADOBE_DXR, "ADOBE_DXR", "com.adobe.dxr" },
    { GNUMERIC_SPREADSHEET, "GNUMERIC_SPREADSHEET", "org.gnumeric.spreadsheet" },
    { HDFGROUP_HDF, "HDFGROUP_HDF", "org.hdfgroup.hdf" },
    { BINHEX_ARCHIVE, "BINHEX_ARCHIVE", "com.apple.binhex-archive" },
    { MICROSOFT_HTA, "MICROSOFT_HTA", "com.microsoft.hta" },
    { INTERNET_INS, "INTERNET_INS", "com.microsoft.internet.ins" },
    { INTERNET_ISP, "INTERNET_ISP", "com.microsoft.internet.isp" },
    { TROFF, "TROFF", "org.troff" },
    { ADOBE_MIF, "ADOBE_MIF", "com.adobe.framemaker.mif" },
    { FREEMIND, "FREEMIND", "io.sourceforge.freemind" },
    { YAMAHA_SMAF, "YAMAHA_SMAF", "com.yamaha.smaf" },
    { MATHEMATICA_NOTEBOOK, "MATHEMATICA_NOTEBOOK", "com.wolfram.mathematica.notebook" },
    { XIPH_OGG, "XIPH_OGG", "org.xiph.ogg" },
    { PROXY_AUTOCONFIG, "PROXY_AUTOCONFIG", "com.netscape.proxy-autoconfig" },
    { PKCS_12, "PKCS_12", "com.rsa.pkcs-12" },
    { PGP_SIGNATURE, "PGP_SIGNATURE", "org.openpgp.signature" },
    { QUICKTIME_LINK, "QUICKTIME_LINK", "com.apple.quicktime-link" },
    { RAR_ARCHIVE, "RAR_ARCHIVE", "com.rarlab.rar-archive" },
    { SEVEN_ZIP_ARCHIVE, "SEVEN_ZIP_ARCHIVE", "org.7-zip.7-zip-archive" },
    { RED_BEAN_SGF, "RED_BEAN_SGF", "com.red-bean.sgf" },
    { SIT_ARCHIVE, "SIT_ARCHIVE", "com.stuffit.sit-archive" },
    { FUTURESPLASH, "FUTURESPLASH", "com.adobe.futuresplash" },
    { FLASH, "FLASH", "com.adobe.flash" },
    { TEXINFO, "TEXINFO", "org.gnu.texinfo" },
    { TORRENT, "TORRENT", "org.bittorrent.torrent" },
    { DOOM, "DOOM", "com.idsoftware.doom" },
    { APPLE_WEBARCHIVE, "APPLE_WEBARCHIVE", "com.apple.webarchive" },
    { ANDROID_WEBARCHIVE, "ANDROID_WEBARCHIVE", "com.android.webarchive" },
    { GIMP_XCF, "GIMP_XCF", "org.gimp.xcf" },
    { EDRWMAX, "EDRWMAX", "com.edrawsoft.edrawmax" },
    { EDRWMIND, "EDRWMIND", "com.edrawsoft.edrawmind" },
    { CNKI_CAJ, "CNKI_CAJ", "net.cnki.caj" },
    { DBASE_DBF, "DBASE_DBF", "com.dbase.dbf" },
    { AUTODESK_DWG, "AUTODESK_DWG", "com.autodesk.dwg" },
    { AUTODESK_DXF, "AUTODESK_DXF", "com.autodesk.dxf" },
    { AUTODESK_DWS, "AUTODESK_DWS", "com.autodesk.dws" },
    { AUTODESK_DWT, "AUTODESK_DWT", "com.autodesk.dwt" },
    { AUTODESK_DWF, "AUTODESK_DWF", "com.autodesk.dwf" },
    { AUTODESK_DWFX, "AUTODESK_DWFX", "com.autodesk.dwfx" },
    { AUTODESK_SHP, "AUTODESK_SHP", "com.autodesk.shp" },
    { AUTODESK_SHX, "AUTODESK_SHX", "com.autodesk.shx" },
    { AUTODESK_SLIDE_LIB, "AUTODESK_SLIDE_LIB", "com.autodesk.slide-library" },
    { AUTODESK_LINE, "AUTODESK_LINE", "com.autodesk.line" },
    { AUTODESK_PLOTTER, "AUTODESK_PLOTTER", "com.autodesk.plotter" },
    { HP_GRAPHICS_LANG, "HP_GRAPHICS_LANG", "com.hp.graphics-language" },
    { MICROSOFT_METAFILE, "MICROSOFT_METAFILE", "com.microsoft.metafile" },
    { ACIS_SAT, "ACIS_SAT", "com.spatial.acis.sat" },
    { AVIF_IMAGE, "AVIF_IMAGE", "org.aomedia.avif-image" },
    { MICROSOFT_DDS, "MICROSOFT_DDS", "com.microsoft.dds" },
    { IFF_ILBM, "IFF_ILBM", "com.ea.iff-ilbm" },
    { CR2_RAW_IMAGE, "CR2_RAW_IMAGE", "com.canon.cr2-raw-image" },
    { CR3_RAW_IMAGE, "CR3_RAW_IMAGE", "com.canon.cr3-raw-image" },
    { CRW_RAW_IMAGE, "CRW_RAW_IMAGE", "com.canon.crw-raw-image" },
    { DNG_RAW_IMAGE, "DNG_RAW_IMAGE", "com.adobe.dng-raw-image" },
    { ARW_RAW_IMAGE, "ARW_RAW_IMAGE", "com.sony.arw-raw-image" },
    { NEF_RAW_IMAGE, "NEF_RAW_IMAGE", "com.nikon.nef-raw-image" },
    { MINDMANAGER_MMAP, "MINDMANAGER_MMAP", "com.mindjet.mindmanager.mmap" },
    { MICROSOFT_EMAIL, "MICROSOFT_EMAIL", "com.microsoft.email" },
    { MICROSOFT_MESSAGE, "MICROSOFT_MESSAGE", "com.microsoft.message" },
    { MICROSOFT_PST, "MICROSOFT_PST", "com.microsoft.pst" },
    { KINGSOFT_OFFICE, "KINGSOFT_OFFICE", "com.kingsoft.office	general.zip-archive" },
    { KINGSOFT_WRITER_WPS, "KINGSOFT_WRITER_WPS", "com.kingsoft.office.writer.wps" },
    { KINGSOFT_WRITER_WPT, "KINGSOFT_WRITER_WPT", "com.kingsoft.office.writer.wpt" },
    { KINGSOFT_PRESENTATION_DPS, "KINGSOFT_PRESENTATION_DPS", "com.kingsoft.office.presentation.dps" },
    { KINGSOFT_PRESENTATION_TEMPLATE, "KINGSOFT_PRESENTATION_TEMPLATE", "com.kingsoft.office.presentation.template" },
    { KINGSOFT_SPREADSHEETS_ET, "KINGSOFT_SPREADSHEETS_ET", "com.kingsoft.office.spreadsheets.et" },
    { KINGSOFT_SPREADSHEETS_TEMPLATE, "KINGSOFT_SPREADSHEETS_TEMPLATE", "com.kingsoft.office.spreadsheets.template" },
    { MICROSOFT_INI, "MICROSOFT_INI", "com.microsoft.ini" },
    { JSON, "JSON", "general.json" },
    { YAML, "YAML", "general.yaml" },
    { LOG, "LOG", "general.log" },
    { URI, "URI", "general.uri" },
    { FILE_URI, "FILE_URI", "general.file-uri" },
    { TEXT_LST, "TEXT_LST", "general.text-lst" },
    { ANDROID_APK, "ANDROID_APK", "com.android.apk" },
    { BZ_ARCHIVE, "BZ_ARCHIVE", "general.bz-archive" },
    { TBZ_ARCHIVE, "TBZ_ARCHIVE", "general.tar-bzip-archive" },
    { TBZ2_ARCHIVE, "TBZ2_ARCHIVE", "general.tar-bzip2-archive" },
    { XZ_ARCHIVE, "XZ_ARCHIVE", "org.tukaani.xz-archive" },
    { TXZ_ARCHIVE, "TXZ_ARCHIVE", "org.tukaani.tar-xz-archive" },
    { XAR_ARCHIVE, "XAR_ARCHIVE", "general.xar-archive" },
    { CAB_ARCHIVE, "CAB_ARCHIVE", "com.microsoft.cab-archive" },
    { RPM_ARCHIVE, "RPM_ARCHIVE", "redhat.rpm-archive" },
    { TPZ_ARCHIVE, "TPZ_ARCHIVE", "org.godotengine.tpz-archive", },
    { LZA_ARCHIVE, "LZA_ARCHIVE", "general.lza-archive" },
    { ARJ_ARCHIVE, "ARJ_ARCHIVE", "general.arj-archive" },
    { ZIPX_ARCHIVE, "ZIPX_ARCHIVE", "com.winzip.zipx" },
    { LZMA_ARCHIVE, "LZMA_ARCHIVE", "general.lzma-archive" },
    { LZMA86_ARCHIVE, "LZMA86_ARCHIVE", "general.lzma86-archive" },
    { XPI_ARCHIVE, "XPI_ARCHIVE", "org.mozilla.xpinstall" },
    { HFS_DISK_IMAGE, "HFS_DISK_IMAGE", "general.hfs-disk-image" },
    { IMG_DISK_IMAGE, "IMG_DISK_IMAGE", "general.img-disk-image" },
    { ISZ_DISK_IMAGE, "ISZ_DISK_IMAGE", "com.ezbsystems.zipped-iso" },
    { WIM_DISK_IMAGE, "WIM_DISK_IMAGE", "com.microsoft.wim" },
    { SWM_DISK_IMAGE, "SWM_DISK_IMAGE", "com.microsoft.swm" },
    { KINGSOFT_SPREADSHEETS_ETX, "KINGSOFT_SPREADSHEETS_ETX", "com.kingsoft.office.spreadsheets.etx" },
    { KINGSOFT_SPREADSHEETS_ETTX, "KINGSOFT_SPREADSHEETS_ETTX", "com.kingsoft.office.spreadsheets.ettx" },
    { EXCEL_DIF, "EXCEL_DIF", "com.microsoft.excel.dif" },
    { OPENHARMONY_APP, "OPENHARMONY_APP", "openharmony.app" },
    { HMOS_WIFI, "HMOS_WIFI", "com.huawei.hmos.settings.wifi" },
    { TEL, "TEL", "general.tel" },
    { ETS, "ETS", "general.ets" },
    { JSON5, "JSON5", "general.json5" },
    { APE_AUDIO, "APE_AUDIO", "com.monkeysaudio.ape-audio" },
    { OPUS_AUDIO, "OPUS_AUDIO", "org.xiph.opus-audio"},
    { CONF, "CONF", "general.conf" },
    { MICROSOFT_DOS_BATCH, "MICROSOFT_DOS_BATCH", "com.microsoft.dos-batch" },
    { MICROSOFT_VBSCRIPT, "MICROSOFT_VBSCRIPT", "com.microsoft.vbscript" },
    { ION, "ION", "general.ion" },
    { MICROSOFT_REGISTRY, "MICROSOFT_REGISTRY", "com.microsoft.registry" },
    { MICROSOFT_CATALOG, "MICROSOFT_CATALOG", "com.microsoft.catalog" },
    { MICROSOFT_POWERSHELL_SCRIPT, "MICROSOFT_POWERSHELL_SCRIPT", "com.microsoft.powershell-script" },
    { W3_WOFF, "W3_WOFF", "org.w3.woff" },
    { SQLITE_DATABASE, "SQLITE_DATABASE", "org.sqlite.database" },
    { MICROSOFT_SYS, "MICROSOFT_SYS", "com.microsoft.sys" },
    { MICROSOFT_INF, "MICROSOFT_INF", "com.microsoft.inf" },
    { MICROSOFT_PDB, "MICROSOFT_PDB", "com.microsoft.pdb" },
    { MICROSOFT_TLB, "MICROSOFT_TLB", "com.microsoft.tlb" },
    { MICROSOFT_SCCD, "MICROSOFT_SCCD", "com.microsoft.sccd" },
    { ADOBE_F4V, "ADOBE_F4V", "com.adobe.f4v" },
    { MP2T, "MP2T", "general.mp2t" },
    { YOUTUBE_VIDEO, "YOUTUBE_VIDEO", "com.youtube.video" },
    { WEBEX_VIDEO, "WEBEX_VIDEO", "com.cisco.webex-video" },
    { MPEG2, "MPEG2", "general.mpeg-2" },
    { MPEG1, "MPEG1", "general.mpeg-1" },
    { REALMEDIA_VBR, "REALMEDIA_VBR", "com.real.realmedia-vbr" },
    { REAL_REALVIDEO, "REAL_REALVIDEO", "com.real.realvideo" },
    { DIVX_VIDEO, "DIVX_VIDEO", "general.divx-video" },
    { CSIRO_ANNODEX, "CSIRO_ANNODEX", "org.csiro.annodex" },
    { OGV, "OGV", "general.ogv" },
    { LSF_VIDEO, "LSF_VIDEO", "com.microsoft.lsf-video" },
    { H264_VIDEO, "H264_VIDEO", "general.h264-video" },
    { JPEG2000, "JPEG2000", "general.jpeg-2000" },
    { RAF_RAW_IMAGE, "RAF_RAW_IMAGE", "com.fujifilm.raf-raw-image" },
    { NRW_RAW_IMAGE, "NRW_RAW_IMAGE", "com.nikon.nrw-raw-image" },
    { RW2_RAW_IMAGE, "RW2_RAW_IMAGE", "com.panasonic.rw2-raw-image" },
    { PEF_RAW_IMAGE, "PEF_RAW_IMAGE", "com.pentax.pef-raw-image" },
    { SRW_RAW_IMAGE, "SRW_RAW_IMAGE", "com.sumsung.srw-raw-image" },
    { ERF_RAW_IMAGE, "ERF_RAW_IMAGE", "com.epson.erf-raw-image" },
    { ORF_RAW_IMAGE, "ORF_RAW_IMAGE", "com.olympus.orf-raw-image" },
    { IEF_IMAGE, "IEF_IMAGE", "general.ief-image" },
    { ART_IMAGE, "ART_IMAGE", "com.aol.art-image" },
    { CONTENT_FORM, "CONTENT_FORM", "general.content-form" },
    { M4P_AUDIO, "M4P_AUDIO", "com.apple.m4p-audio" },
    { AC3_AUDIO, "AC3_AUDIO", "general.ac3-audio" },
    { OPENHARMONY_HSP, "OPENHARMONY_HSP", "openharmony.hsp" },
    { OPENHARMONY_HAR, "OPENHARMONY_HAR", "openharmony.har" },
    { OPENHARMONY_GOPAINT, "OPENHARMONY_GOPAINT", "openharmony.gopaint" },
    { OPENHARMONY_GOBRUSH, "OPENHARMONY_GOBRUSH", "openharmony.gobrush" },
    { OPENHARMONY_GOBRUSHES, "OPENHARMONY_GOBRUSHES", "openharmony.gobrushes" },
    { OPENHARMONY_GOCOLOR, "OPENHARMONY_GOCOLOR", "openharmony.gocolor" },
    { OPENHARMONY_DLP, "OPENHARMONY_DLP", "openharmony.dlp"}
};

static constexpr std::initializer_list<std::string_view> NOT_NEED_COUNT_VALUE_LIST = {
    UNIFORM_DATA_TYPE, ARRAY_BUFFER_LENGTH, THUMB_DATA_LENGTH, APP_ICON_LENGTH, APPLICATION_DEFINED_RECORD_MARK,
    FILE_TYPE, PERMISSION_POLICY
};

static const std::initializer_list<std::string> FILE_SUB_TYPES = {
    "general.image", "general.video", "general.audio", "general.folder", "general.file" };

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

bool UnifiedDataUtils::IsPersist(const int32_t &visibility)
{
    return visibility >= static_cast<int32_t>(VISIBILITY_ALL) && visibility < static_cast<int32_t>(VISIBILITY_BUTT);
}

bool UnifiedDataUtils::IsFileMangerIntention(const std::string &intention)
{
    Intention optionIntention = GetIntentionByString(intention);
    if (optionIntention == UD_INTENTION_SYSTEM_SHARE ||
        optionIntention == UD_INTENTION_MENU ||
        optionIntention == UD_INTENTION_PICKER) {
        return true;
    }
    return false;
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

std::string UnifiedDataUtils::FindIntentionMap(const Intention &queryIntention)
{
    auto find = UD_INTENTION_MAP.find(queryIntention);
    return find == UD_INTENTION_MAP.end() ? "" : find->second;
}

bool UnifiedDataUtils::IsValidOptions(UnifiedKey &key, const std::string &intention,
    const std::string &validIntention)
{
    if (key.key.empty() && intention.empty()) {
        return false;
    }
    bool isIntentionValid = intention.empty() || intention == validIntention;
    if (!isIntentionValid) {
        return false;
    }
    bool isValidKey = key.key.empty() || (key.IsValid() && key.intention == validIntention);
    if (!isValidKey) {
        return false;
    }
    return true;
}

bool UnifiedDataUtils::IsValidOptions(UnifiedKey &key, const std::string &intention)
{
    if (key.key.empty() && intention.empty()) {
        return false;
    }

    bool isIntentionValid = intention.empty() || IsPersist(intention);
    if (!isIntentionValid) {
        return false;
    }

    bool isValidKey = key.key.empty() || (key.IsValid() && IsPersist(key.intention));
    if (!isValidKey) {
        return false;
    }

    if (!key.key.empty() && !intention.empty()) {
        return key.intention == intention;
    }
    return true;
}

bool UnifiedDataUtils::IsValidOptionsNonDrag(UnifiedKey &key, const std::string &intention)
{
    if (IsValidOptions(key, intention)) {
        return !key.key.empty() || intention == UD_INTENTION_MAP.at(Intention::UD_INTENTION_DATA_HUB);
    }
    return false;
}

std::string UnifiedDataUtils::GetBelongsToFileType(const std::string &utdId)
{
    if (utdId.empty() || utdId == "general.html" || utdId == "general.plain-text") {
        LOG_ERROR(UDMF_FRAMEWORK, "The utdId is empty or the utdId is general.html or general.plain-text");
        return "";
    }
    std::shared_ptr<TypeDescriptor> descriptor;
    UtdClient::GetInstance().GetTypeDescriptor(utdId, descriptor);
    if (descriptor == nullptr) {
        LOG_INFO(UDMF_FRAMEWORK, "The descriptor is null");
        return "";
    }
    for (const auto &type : FILE_SUB_TYPES) {
        bool isSpecificType = false;
        descriptor->BelongsTo(type, isSpecificType);
        if (isSpecificType) {
            return type;
        }
    }
    if (!descriptor->GetFilenameExtensions().empty()) {
        LOG_INFO(UDMF_FRAMEWORK, "The type descriptor has file extensions");
        return "general.file";
    }
    LOG_INFO(UDMF_FRAMEWORK, "Return empty");
    return "";
}

bool UnifiedDataUtils::IsFilterFileType(const std::string &type)
{
    return std::find(FILE_SUB_TYPES.begin(), FILE_SUB_TYPES.end(), type) != FILE_SUB_TYPES.end();
}

std::shared_ptr<Object> ObjectUtils::ConvertToObject(UDDetails &details)
{
    Object object;
    for (auto [key, value] : details) {
        ConvertVariant(std::move(value), object.value_[key]);
    }
    return std::make_shared<Object>(object);
}

UDDetails ObjectUtils::ConvertToUDDetails(std::shared_ptr<Object> object)
{
    UDDetails details;
    if (object == nullptr) {
        return details;
    }
    for (auto [key, value] : object->value_) {
        if (!ConvertVariant(std::move(value), details[key])) {
            LOG_ERROR(UnifiedRecord, "object convert to UDDetails failed, object key is %{public}s", key.c_str());
        }
    }
    return details;
}

int64_t ObjectUtils::GetValueSize(const ValueType &value, bool isCalValueType)
{
    if (value.index() == 0) {
        return 0;
    }
    if (std::holds_alternative<std::string>(value)) {
        return std::get<std::string>(value).size();
    }
    if (std::holds_alternative<std::shared_ptr<Object>>(value)) {
        return GetObjectValueSize(std::get<std::shared_ptr<Object>>(value), isCalValueType);
    }
    if (std::holds_alternative<std::vector<uint8_t>>(value)) {
        return std::get<std::vector<uint8_t>>(value).size();
    }
    if (std::holds_alternative<std::shared_ptr<OHOS::Media::PixelMap>>(value)) {
        auto pixelMap = std::get<std::shared_ptr<OHOS::Media::PixelMap>>(value);
        return pixelMap->GetByteCount();
    }
    if (std::holds_alternative<std::shared_ptr<OHOS::AAFwk::Want>>(value)) {
        auto want = std::get<std::shared_ptr<OHOS::AAFwk::Want>>(value);
        Parcel parcel;
        if (!want->Marshalling(parcel)) {
            LOG_ERROR(UDMF_FRAMEWORK, "Marshalling want error when GetValueSize!");
            return 0;
        }
        return parcel.GetDataSize();
    }
    return std::visit([] (const auto &val) { return sizeof(val); }, value);
}

int64_t ObjectUtils::GetObjectValueSize(const std::shared_ptr<Object> object, bool isCalValueType)
{
    if (object == nullptr) {
        return 0;
    }
    int64_t size = 0;
    for (auto [key, value] : object->value_) {
        if (std::find(NOT_NEED_COUNT_VALUE_LIST.begin(), NOT_NEED_COUNT_VALUE_LIST.end(), key)
            != NOT_NEED_COUNT_VALUE_LIST.end()) {
            continue;
        }
        if (key == VALUE_TYPE && isCalValueType) {
            size += GetValueSize(value, false);
            continue;
        }
        if (key == DETAILS) {
            if (!std::holds_alternative<std::shared_ptr<Object>>(value)) {
                LOG_ERROR(UDMF_FRAMEWORK, "Details is not correct!");
                continue;
            }
            size += GetAllObjectSize(std::get<std::shared_ptr<Object>>(value));
            continue;
        }
        size += GetValueSize(value, false);
    }
    return size;
}


int64_t ObjectUtils::GetAllObjectSize(const std::shared_ptr<Object> object)
{
    if (object == nullptr) {
        return 0;
    }
    int64_t size = 0;
    for (auto [key, value] : object->value_) {
        size += static_cast<int64_t>(key.size()) + GetValueSize(value, false);
    }
    return size;
}


void ObjectUtils::ProcessFileUriType(UDType &utdType, ValueType &value)
{
    auto fileUri = std::get<std::shared_ptr<Object>>(value);
    std::string uniformDataType;
    if (!fileUri->GetValue(UNIFORM_DATA_TYPE, uniformDataType) || uniformDataType != GENERAL_FILE_URI) {
        LOG_INFO(UDMF_FRAMEWORK, "Attribute uniformDataType not equals to 'general.file-uri'!");
        return;
    }
    utdType = FILE;
    std::string fileType;
    if (fileUri->GetValue(FILE_TYPE, fileType)) {
        std::string fileTypeStr = UnifiedDataUtils::GetBelongsToFileType(fileType);
        if (fileTypeStr.empty()) {
            return;
        }
        utdType = static_cast<UDType>(UtdUtils::GetUtdEnumFromUtdId(fileTypeStr));
        LOG_INFO(UDMF_FRAMEWORK, "Change type to %{public}s", fileTypeStr.c_str());
        return;
    }
}
} // namespace UDMF
} // namespace OHOS