#pragma once
#include "ohos.data.unifiedDataChannel.AllRecords.ani.0.h"
#include "ohos.data.unifiedDataChannel.AllRecords.proj.1.hpp"
#include "ohos.data.unifiedDataChannel.FileInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.FolderInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.AudioInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.VideoInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.ImageInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.TextInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.PlainTextInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.HTMLInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.HyperlinkInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.SystemDefinedRecordInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.SystemDefinedFormInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.SystemDefinedAppItemInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.SystemDefinedPixelMapInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.UnifiedRecordInner.ani.1.h"
inline ::ohos::data::unifiedDataChannel::AllRecords ohos_data_unifiedDataChannel_AllRecords_fromANI(ani_env* env, ani_ref ani_value) {
    ani_boolean ani_is_file;
    env->Object_InstanceOf(static_cast<ani_object>(ani_value), TH_ANI_FIND_CLASS(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FileInner;"), &ani_is_file);
    if (ani_is_file) {
        ::ohos::data::unifiedDataChannel::FileInner cpp_field_file = ohos_data_unifiedDataChannel_FileInner_fromANI(env, static_cast<ani_object>(ani_value));
        return ::ohos::data::unifiedDataChannel::AllRecords(::taihe::static_tag<::ohos::data::unifiedDataChannel::AllRecords::tag_t::file>, std::move(cpp_field_file));
    }
    ani_boolean ani_is_folder;
    env->Object_InstanceOf(static_cast<ani_object>(ani_value), TH_ANI_FIND_CLASS(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FolderInner;"), &ani_is_folder);
    if (ani_is_folder) {
        ::ohos::data::unifiedDataChannel::FolderInner cpp_field_folder = ohos_data_unifiedDataChannel_FolderInner_fromANI(env, static_cast<ani_object>(ani_value));
        return ::ohos::data::unifiedDataChannel::AllRecords(::taihe::static_tag<::ohos::data::unifiedDataChannel::AllRecords::tag_t::folder>, std::move(cpp_field_folder));
    }
    ani_boolean ani_is_audio;
    env->Object_InstanceOf(static_cast<ani_object>(ani_value), TH_ANI_FIND_CLASS(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/AudioInner;"), &ani_is_audio);
    if (ani_is_audio) {
        ::ohos::data::unifiedDataChannel::AudioInner cpp_field_audio = ohos_data_unifiedDataChannel_AudioInner_fromANI(env, static_cast<ani_object>(ani_value));
        return ::ohos::data::unifiedDataChannel::AllRecords(::taihe::static_tag<::ohos::data::unifiedDataChannel::AllRecords::tag_t::audio>, std::move(cpp_field_audio));
    }
    ani_boolean ani_is_video;
    env->Object_InstanceOf(static_cast<ani_object>(ani_value), TH_ANI_FIND_CLASS(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/VideoInner;"), &ani_is_video);
    if (ani_is_video) {
        ::ohos::data::unifiedDataChannel::VideoInner cpp_field_video = ohos_data_unifiedDataChannel_VideoInner_fromANI(env, static_cast<ani_object>(ani_value));
        return ::ohos::data::unifiedDataChannel::AllRecords(::taihe::static_tag<::ohos::data::unifiedDataChannel::AllRecords::tag_t::video>, std::move(cpp_field_video));
    }
    ani_boolean ani_is_image;
    env->Object_InstanceOf(static_cast<ani_object>(ani_value), TH_ANI_FIND_CLASS(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/ImageInner;"), &ani_is_image);
    if (ani_is_image) {
        ::ohos::data::unifiedDataChannel::ImageInner cpp_field_image = ohos_data_unifiedDataChannel_ImageInner_fromANI(env, static_cast<ani_object>(ani_value));
        return ::ohos::data::unifiedDataChannel::AllRecords(::taihe::static_tag<::ohos::data::unifiedDataChannel::AllRecords::tag_t::image>, std::move(cpp_field_image));
    }
    ani_boolean ani_is_text;
    env->Object_InstanceOf(static_cast<ani_object>(ani_value), TH_ANI_FIND_CLASS(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/TextInner;"), &ani_is_text);
    if (ani_is_text) {
        ::ohos::data::unifiedDataChannel::TextInner cpp_field_text = ohos_data_unifiedDataChannel_TextInner_fromANI(env, static_cast<ani_object>(ani_value));
        return ::ohos::data::unifiedDataChannel::AllRecords(::taihe::static_tag<::ohos::data::unifiedDataChannel::AllRecords::tag_t::text>, std::move(cpp_field_text));
    }
    ani_boolean ani_is_plainText;
    env->Object_InstanceOf(static_cast<ani_object>(ani_value), TH_ANI_FIND_CLASS(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainTextInner;"), &ani_is_plainText);
    if (ani_is_plainText) {
        ::ohos::data::unifiedDataChannel::PlainTextInner cpp_field_plainText = ohos_data_unifiedDataChannel_PlainTextInner_fromANI(env, static_cast<ani_object>(ani_value));
        return ::ohos::data::unifiedDataChannel::AllRecords(::taihe::static_tag<::ohos::data::unifiedDataChannel::AllRecords::tag_t::plainText>, std::move(cpp_field_plainText));
    }
    ani_boolean ani_is_html;
    env->Object_InstanceOf(static_cast<ani_object>(ani_value), TH_ANI_FIND_CLASS(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTMLInner;"), &ani_is_html);
    if (ani_is_html) {
        ::ohos::data::unifiedDataChannel::HTMLInner cpp_field_html = ohos_data_unifiedDataChannel_HTMLInner_fromANI(env, static_cast<ani_object>(ani_value));
        return ::ohos::data::unifiedDataChannel::AllRecords(::taihe::static_tag<::ohos::data::unifiedDataChannel::AllRecords::tag_t::html>, std::move(cpp_field_html));
    }
    ani_boolean ani_is_hyperlink;
    env->Object_InstanceOf(static_cast<ani_object>(ani_value), TH_ANI_FIND_CLASS(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HyperlinkInner;"), &ani_is_hyperlink);
    if (ani_is_hyperlink) {
        ::ohos::data::unifiedDataChannel::HyperlinkInner cpp_field_hyperlink = ohos_data_unifiedDataChannel_HyperlinkInner_fromANI(env, static_cast<ani_object>(ani_value));
        return ::ohos::data::unifiedDataChannel::AllRecords(::taihe::static_tag<::ohos::data::unifiedDataChannel::AllRecords::tag_t::hyperlink>, std::move(cpp_field_hyperlink));
    }
    ani_boolean ani_is_systemDefinedRecord;
    env->Object_InstanceOf(static_cast<ani_object>(ani_value), TH_ANI_FIND_CLASS(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedRecordInner;"), &ani_is_systemDefinedRecord);
    if (ani_is_systemDefinedRecord) {
        ::ohos::data::unifiedDataChannel::SystemDefinedRecordInner cpp_field_systemDefinedRecord = ohos_data_unifiedDataChannel_SystemDefinedRecordInner_fromANI(env, static_cast<ani_object>(ani_value));
        return ::ohos::data::unifiedDataChannel::AllRecords(::taihe::static_tag<::ohos::data::unifiedDataChannel::AllRecords::tag_t::systemDefinedRecord>, std::move(cpp_field_systemDefinedRecord));
    }
    ani_boolean ani_is_systemDefinedForm;
    env->Object_InstanceOf(static_cast<ani_object>(ani_value), TH_ANI_FIND_CLASS(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;"), &ani_is_systemDefinedForm);
    if (ani_is_systemDefinedForm) {
        ::ohos::data::unifiedDataChannel::SystemDefinedFormInner cpp_field_systemDefinedForm = ohos_data_unifiedDataChannel_SystemDefinedFormInner_fromANI(env, static_cast<ani_object>(ani_value));
        return ::ohos::data::unifiedDataChannel::AllRecords(::taihe::static_tag<::ohos::data::unifiedDataChannel::AllRecords::tag_t::systemDefinedForm>, std::move(cpp_field_systemDefinedForm));
    }
    ani_boolean ani_is_systemDefinedAppItem;
    env->Object_InstanceOf(static_cast<ani_object>(ani_value), TH_ANI_FIND_CLASS(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;"), &ani_is_systemDefinedAppItem);
    if (ani_is_systemDefinedAppItem) {
        ::ohos::data::unifiedDataChannel::SystemDefinedAppItemInner cpp_field_systemDefinedAppItem = ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_fromANI(env, static_cast<ani_object>(ani_value));
        return ::ohos::data::unifiedDataChannel::AllRecords(::taihe::static_tag<::ohos::data::unifiedDataChannel::AllRecords::tag_t::systemDefinedAppItem>, std::move(cpp_field_systemDefinedAppItem));
    }
    ani_boolean ani_is_systemDefinedPixelMap;
    env->Object_InstanceOf(static_cast<ani_object>(ani_value), TH_ANI_FIND_CLASS(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMapInner;"), &ani_is_systemDefinedPixelMap);
    if (ani_is_systemDefinedPixelMap) {
        ::ohos::data::unifiedDataChannel::SystemDefinedPixelMapInner cpp_field_systemDefinedPixelMap = ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_fromANI(env, static_cast<ani_object>(ani_value));
        return ::ohos::data::unifiedDataChannel::AllRecords(::taihe::static_tag<::ohos::data::unifiedDataChannel::AllRecords::tag_t::systemDefinedPixelMap>, std::move(cpp_field_systemDefinedPixelMap));
    }
    ani_boolean ani_is_unifiedRecord;
    env->Object_InstanceOf(static_cast<ani_object>(ani_value), TH_ANI_FIND_CLASS(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedRecordInner;"), &ani_is_unifiedRecord);
    if (ani_is_unifiedRecord) {
        ::ohos::data::unifiedDataChannel::UnifiedRecordInner cpp_field_unifiedRecord = ohos_data_unifiedDataChannel_UnifiedRecordInner_fromANI(env, static_cast<ani_object>(ani_value));
        return ::ohos::data::unifiedDataChannel::AllRecords(::taihe::static_tag<::ohos::data::unifiedDataChannel::AllRecords::tag_t::unifiedRecord>, std::move(cpp_field_unifiedRecord));
    }
    __builtin_unreachable();
}
inline ani_ref ohos_data_unifiedDataChannel_AllRecords_intoANI(ani_env* env, ::ohos::data::unifiedDataChannel::AllRecords const& cpp_value) {
    ani_ref ani_value;
    switch (cpp_value.get_tag()) {
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::file: {
        ani_object ani_field_file = ohos_data_unifiedDataChannel_FileInner_intoANI(env, cpp_value.get_file_ref());
        ani_value = ani_field_file;
        break;
    }
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::folder: {
        ani_object ani_field_folder = ohos_data_unifiedDataChannel_FolderInner_intoANI(env, cpp_value.get_folder_ref());
        ani_value = ani_field_folder;
        break;
    }
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::audio: {
        ani_object ani_field_audio = ohos_data_unifiedDataChannel_AudioInner_intoANI(env, cpp_value.get_audio_ref());
        ani_value = ani_field_audio;
        break;
    }
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::video: {
        ani_object ani_field_video = ohos_data_unifiedDataChannel_VideoInner_intoANI(env, cpp_value.get_video_ref());
        ani_value = ani_field_video;
        break;
    }
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::image: {
        ani_object ani_field_image = ohos_data_unifiedDataChannel_ImageInner_intoANI(env, cpp_value.get_image_ref());
        ani_value = ani_field_image;
        break;
    }
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::text: {
        ani_object ani_field_text = ohos_data_unifiedDataChannel_TextInner_intoANI(env, cpp_value.get_text_ref());
        ani_value = ani_field_text;
        break;
    }
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::plainText: {
        ani_object ani_field_plainText = ohos_data_unifiedDataChannel_PlainTextInner_intoANI(env, cpp_value.get_plainText_ref());
        ani_value = ani_field_plainText;
        break;
    }
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::html: {
        ani_object ani_field_html = ohos_data_unifiedDataChannel_HTMLInner_intoANI(env, cpp_value.get_html_ref());
        ani_value = ani_field_html;
        break;
    }
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::hyperlink: {
        ani_object ani_field_hyperlink = ohos_data_unifiedDataChannel_HyperlinkInner_intoANI(env, cpp_value.get_hyperlink_ref());
        ani_value = ani_field_hyperlink;
        break;
    }
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::systemDefinedRecord: {
        ani_object ani_field_systemDefinedRecord = ohos_data_unifiedDataChannel_SystemDefinedRecordInner_intoANI(env, cpp_value.get_systemDefinedRecord_ref());
        ani_value = ani_field_systemDefinedRecord;
        break;
    }
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::systemDefinedForm: {
        ani_object ani_field_systemDefinedForm = ohos_data_unifiedDataChannel_SystemDefinedFormInner_intoANI(env, cpp_value.get_systemDefinedForm_ref());
        ani_value = ani_field_systemDefinedForm;
        break;
    }
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::systemDefinedAppItem: {
        ani_object ani_field_systemDefinedAppItem = ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_intoANI(env, cpp_value.get_systemDefinedAppItem_ref());
        ani_value = ani_field_systemDefinedAppItem;
        break;
    }
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::systemDefinedPixelMap: {
        ani_object ani_field_systemDefinedPixelMap = ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_intoANI(env, cpp_value.get_systemDefinedPixelMap_ref());
        ani_value = ani_field_systemDefinedPixelMap;
        break;
    }
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::unifiedRecord: {
        ani_object ani_field_unifiedRecord = ohos_data_unifiedDataChannel_UnifiedRecordInner_intoANI(env, cpp_value.get_unifiedRecord_ref());
        ani_value = ani_field_unifiedRecord;
        break;
    }
    }
    return ani_value;
}
