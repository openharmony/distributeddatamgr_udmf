/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

/**
 * @addtogroup UDMF
 * @{
 *
 * @brief The Unified Data Management Framework(UDMF) aims to define various standards
 * for data across applications, devices, and platforms, providing a unified OpenHarmony
 * data language and standardized data access and reading paths.
 *
 * @syscap SystemCapability.DistributedDataManager.UDMF.Core
 *
 * @since 12
 */

/**
 * @file udmf_meta.h
 *
 * @brief Declaration the uniform data type information.
 *
 * @kit ArkData
 * @library libudmf.so
 * @syscap SystemCapability.DistributedDataManager.UDMF.Core
 *
 * @since 12
 */

#ifndef UDMF_META_H
#define UDMF_META_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_ENTITY "general.entity"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_OBJECT "general.object"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_COMPOSITE_OBJECT "general.composite-object"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_TEXT "general.text"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_PLAIN_TEXT "general.plain-text"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_HTML "general.html"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_HYPERLINK "general.hyperlink"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_XML "general.xml"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_SOURCE_CODE "general.source-code"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_SCRIPT "general.script"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_SHELL_SCRIPT "general.shell-script"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_CSH_SCRIPT "general.csh-script"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_PERL_SCRIPT "general.perl-script"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_PHP_SCRIPT "general.php-script"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_PYTHON_SCRIPT "general.python-script"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_RUBY_SCRIPT "general.ruby-script"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_TYPE_SCRIPT "general.type-script"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_JAVA_SCRIPT "general.java-script"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_C_HEADER "general.c-header"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_C_SOURCE "general.c-source"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_C_PLUS_PLUS_HEADER "general.c-plus-plus-header"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_C_PLUS_PLUS_SOURCE "general.c-plus-plus-source"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_JAVA_SOURCE "general.java-source"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_EBOOK "general.ebook"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_EPUB "general.epub"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_AZW "com.amazon.azw"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_AZW3 "com.amazon.azw3"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_KFX "com.amazon.kfx"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_MOBI "com.amazon.mobi"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_MEDIA "general.media"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_IMAGE "general.image"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_JPEG "general.jpeg"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_PNG "general.png"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_RAW_IMAGE "general.raw-image"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_TIFF "general.tiff"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_BMP "com.microsoft.bmp"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_ICO "com.microsoft.ico"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_PHOTOSHOP_IMAGE "com.adobe.photoshop-image"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_AI_IMAGE "com.adobe.illustrator.ai-image"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_WORD_DOC "com.microsoft.word.doc"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_EXCEL "com.microsoft.excel.xls"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_PPT "com.microsoft.powerpoint.ppt"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_PDF "com.adobe.pdf"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_POSTSCRIPT "com.adobe.postscript"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_ENCAPSULATED_POSTSCRIPT "com.adobe.encapsulated-postscript"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_VIDEO "general.video"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_AVI "general.avi"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_MPEG "general.mpeg"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_MPEG4 "general.mpeg-4"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_VIDEO_3GPP "general.3gpp"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_VIDEO_3GPP2 "general.3gpp2"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_WINDOWS_MEDIA_WM "com.microsoft.windows-media-wm"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_WINDOWS_MEDIA_WMV "com.microsoft.windows-media-wmv"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_WINDOWS_MEDIA_WMP "com.microsoft.windows-media-wmp"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_AUDIO "general.audio"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_AAC "general.aac"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_AIFF "general.aiff"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_ALAC "general.alac"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_FLAC "general.flac"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_MP3 "general.mp3"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_OGG "general.ogg"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_PCM "general.pcm"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_WINDOWS_MEDIA_WMA "com.microsoft.windows-media-wma"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_WAVEFORM_AUDIO "com.microsoft.waveform-audio"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_WINDOWS_MEDIA_WMX "com.microsoft.windows-media-wmx"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_WINDOWS_MEDIA_WVX "com.microsoft.windows-media-wvx"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_WINDOWS_MEDIA_WAX "com.microsoft.windows-media-wax"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_GENERAL_FILE "general.file"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_DIRECTORY "general.directory"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_FOLDER "general.folder"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_SYMLINK "general.symlink"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_ARCHIVE "general.archive"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_BZ2_ARCHIVE "general.bz2-archive"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_DISK_IMAGE "general.disk-image"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_TAR_ARCHIVE "general.tar-archive"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_ZIP_ARCHIVE "general.zip-archive"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_JAVA_ARCHIVE "com.sun.java-archive"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_GNU_TAR_ARCHIVE "org.gnu.gnu-tar-archive"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_GNU_ZIP_ARCHIVE "org.gnu.gnu-zip-archive"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_GNU_ZIP_TAR_ARCHIVE "org.gnu.gnu-zip-tar-archive"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_CALENDAR "general.calendar"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_CONTACT "general.contact"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_DATABASE "general.database"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_MESSAGE "general.message"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_VCARD "general.vcard"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_NAVIGATION "general.navigation"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_LOCATION "general.location"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_FORM "openharmony.form"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_APP_ITEM "openharmony.app-item"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_PIXEL_MAP "openharmony.pixel-map"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_ATOMIC_SERVICE "openharmony.atomic-service"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_PACKAGE "openharmony.package"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_HAP "openharmony.hap"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_SMIL "com.real.smil"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_MARKDOWN "general.markdown"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_FAX "general.fax"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_JFX_FAX "com.j2.jfx-fax"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_EFX_FAX "com.js.efx-fax"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_XBITMAP_IMAGE "general.xbitmap-image"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_TGA_IMAGE "com.truevision.tga-image"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_SGI_IMAGE "com.sgi.sgi-image"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_OPENEXR_IMAGE "com.ilm.openexr-image"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_FLASHPIX_IMAGE "com.kodak.flashpix.image"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_REALMEDIA "com.real.realmedia"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_AU_AUDIO "general.au-audio"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_AIFC_AUDIO "general.aifc-audio"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_SD2_AUDIO "com.digidesign.sd2-audio"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_REALAUDIO "com.real.realaudio"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_OPENXML "org.openxmlformats.openxml"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_WORDPROCESSINGML_DOCUMENT "org.openxmlformats.wordprocessingml.document"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_SPREADSHEETML_SHEET "org.openxmlformats.spreadsheetml.sheet"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_PRESENTATIONML_PRESENTATION "org.openxmlformats.presentationml.presentation"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_OPENDOCUMENT "org.oasis.opendocument"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_OPENDOCUMENT_TEXT "org.oasis.opendocument.text"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_OPENDOCUMENT_SPREADSHEET "org.oasis.opendocument.spreadsheet"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_OPENDOCUMENT_PRESENTATION "org.oasis.opendocument.presentation"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_OPENDOCUMENT_GRAPHICS "org.oasis.opendocument.graphics"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_OPENDOCUMENT_FORMULA "org.oasis.opendocument.formula"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_STUFFIT_ARCHIVE "com.allume.stuffit-archive"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_VCS "general.vcs"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_ICS "general.ics"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_EXECUTABLE "general.executable"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_PORTABLE_EXECUTABLE "com.microsoft.portable-executable"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_SUN_JAVA_CLASS "com.sun.java-class"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_FONT "general.font"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_TRUETYPE_FONT "general.truetype-font"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_TRUETYPE_COLLECTION_FONT "general.truetype-collection-font"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_OPENTYPE_FONT "general.opentype-font"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_POSTSCRIPT_FONT "com.adobe.postscript-font"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_POSTSCRIPT_PFB_FONT "com.adobe.postscript-pfb-font"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_POSTSCRIPT_PFA_FONT "com.adobe.postscript-pfa-font"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_HDOC "openharmony.hdoc"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_HINOTE "openharmony.hinote"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_STYLED_STRING "openharmony.styled-string"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_WANT "openharmony.want"

/**
 * @brief A specific type of uniform data type.
 *
 * @since 13
 */
#define UDMF_META_GENERAL_FILE_URI "general.file-uri"

#ifdef __cplusplus
};
#endif

/** @} */
#endif
