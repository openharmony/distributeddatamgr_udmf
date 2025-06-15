#pragma once
#include "taihe/common.hpp"
#include "ohos.data.unifiedDataChannel.AllRecords.proj.0.hpp"
#include "ohos.data.unifiedDataChannel.AllRecords.abi.1.h"
#include "ohos.data.unifiedDataChannel.FileInner.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.FolderInner.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.AudioInner.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.VideoInner.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.ImageInner.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.TextInner.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.PlainTextInner.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.HTMLInner.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.HyperlinkInner.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.SystemDefinedRecordInner.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.SystemDefinedFormInner.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.SystemDefinedAppItemInner.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.SystemDefinedPixelMapInner.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.UnifiedRecordInner.proj.2.hpp"
namespace ohos::data::unifiedDataChannel {
struct AllRecords {
    public:
    enum class tag_t : int {
        file,
        folder,
        audio,
        video,
        image,
        text,
        plainText,
        html,
        hyperlink,
        systemDefinedRecord,
        systemDefinedForm,
        systemDefinedAppItem,
        systemDefinedPixelMap,
        unifiedRecord,
    };
    union storage_t {
        storage_t() {}
        ~storage_t() {}
        ::ohos::data::unifiedDataChannel::FileInner file;
        ::ohos::data::unifiedDataChannel::FolderInner folder;
        ::ohos::data::unifiedDataChannel::AudioInner audio;
        ::ohos::data::unifiedDataChannel::VideoInner video;
        ::ohos::data::unifiedDataChannel::ImageInner image;
        ::ohos::data::unifiedDataChannel::TextInner text;
        ::ohos::data::unifiedDataChannel::PlainTextInner plainText;
        ::ohos::data::unifiedDataChannel::HTMLInner html;
        ::ohos::data::unifiedDataChannel::HyperlinkInner hyperlink;
        ::ohos::data::unifiedDataChannel::SystemDefinedRecordInner systemDefinedRecord;
        ::ohos::data::unifiedDataChannel::SystemDefinedFormInner systemDefinedForm;
        ::ohos::data::unifiedDataChannel::SystemDefinedAppItemInner systemDefinedAppItem;
        ::ohos::data::unifiedDataChannel::SystemDefinedPixelMapInner systemDefinedPixelMap;
        ::ohos::data::unifiedDataChannel::UnifiedRecordInner unifiedRecord;
    };
    AllRecords(AllRecords const& other) : m_tag(other.m_tag) {
        switch (m_tag) {
        case tag_t::file: {
            new (&m_data.file) decltype(m_data.file)(other.m_data.file);
            break;
        }
        case tag_t::folder: {
            new (&m_data.folder) decltype(m_data.folder)(other.m_data.folder);
            break;
        }
        case tag_t::audio: {
            new (&m_data.audio) decltype(m_data.audio)(other.m_data.audio);
            break;
        }
        case tag_t::video: {
            new (&m_data.video) decltype(m_data.video)(other.m_data.video);
            break;
        }
        case tag_t::image: {
            new (&m_data.image) decltype(m_data.image)(other.m_data.image);
            break;
        }
        case tag_t::text: {
            new (&m_data.text) decltype(m_data.text)(other.m_data.text);
            break;
        }
        case tag_t::plainText: {
            new (&m_data.plainText) decltype(m_data.plainText)(other.m_data.plainText);
            break;
        }
        case tag_t::html: {
            new (&m_data.html) decltype(m_data.html)(other.m_data.html);
            break;
        }
        case tag_t::hyperlink: {
            new (&m_data.hyperlink) decltype(m_data.hyperlink)(other.m_data.hyperlink);
            break;
        }
        case tag_t::systemDefinedRecord: {
            new (&m_data.systemDefinedRecord) decltype(m_data.systemDefinedRecord)(other.m_data.systemDefinedRecord);
            break;
        }
        case tag_t::systemDefinedForm: {
            new (&m_data.systemDefinedForm) decltype(m_data.systemDefinedForm)(other.m_data.systemDefinedForm);
            break;
        }
        case tag_t::systemDefinedAppItem: {
            new (&m_data.systemDefinedAppItem) decltype(m_data.systemDefinedAppItem)(other.m_data.systemDefinedAppItem);
            break;
        }
        case tag_t::systemDefinedPixelMap: {
            new (&m_data.systemDefinedPixelMap) decltype(m_data.systemDefinedPixelMap)(other.m_data.systemDefinedPixelMap);
            break;
        }
        case tag_t::unifiedRecord: {
            new (&m_data.unifiedRecord) decltype(m_data.unifiedRecord)(other.m_data.unifiedRecord);
            break;
        }
        default: {
            break;
        }
        }
    }
    AllRecords(AllRecords&& other) : m_tag(other.m_tag) {
        switch (m_tag) {
        case tag_t::file: {
            new (&m_data.file) decltype(m_data.file)(::std::move(other.m_data.file));
            break;
        }
        case tag_t::folder: {
            new (&m_data.folder) decltype(m_data.folder)(::std::move(other.m_data.folder));
            break;
        }
        case tag_t::audio: {
            new (&m_data.audio) decltype(m_data.audio)(::std::move(other.m_data.audio));
            break;
        }
        case tag_t::video: {
            new (&m_data.video) decltype(m_data.video)(::std::move(other.m_data.video));
            break;
        }
        case tag_t::image: {
            new (&m_data.image) decltype(m_data.image)(::std::move(other.m_data.image));
            break;
        }
        case tag_t::text: {
            new (&m_data.text) decltype(m_data.text)(::std::move(other.m_data.text));
            break;
        }
        case tag_t::plainText: {
            new (&m_data.plainText) decltype(m_data.plainText)(::std::move(other.m_data.plainText));
            break;
        }
        case tag_t::html: {
            new (&m_data.html) decltype(m_data.html)(::std::move(other.m_data.html));
            break;
        }
        case tag_t::hyperlink: {
            new (&m_data.hyperlink) decltype(m_data.hyperlink)(::std::move(other.m_data.hyperlink));
            break;
        }
        case tag_t::systemDefinedRecord: {
            new (&m_data.systemDefinedRecord) decltype(m_data.systemDefinedRecord)(::std::move(other.m_data.systemDefinedRecord));
            break;
        }
        case tag_t::systemDefinedForm: {
            new (&m_data.systemDefinedForm) decltype(m_data.systemDefinedForm)(::std::move(other.m_data.systemDefinedForm));
            break;
        }
        case tag_t::systemDefinedAppItem: {
            new (&m_data.systemDefinedAppItem) decltype(m_data.systemDefinedAppItem)(::std::move(other.m_data.systemDefinedAppItem));
            break;
        }
        case tag_t::systemDefinedPixelMap: {
            new (&m_data.systemDefinedPixelMap) decltype(m_data.systemDefinedPixelMap)(::std::move(other.m_data.systemDefinedPixelMap));
            break;
        }
        case tag_t::unifiedRecord: {
            new (&m_data.unifiedRecord) decltype(m_data.unifiedRecord)(::std::move(other.m_data.unifiedRecord));
            break;
        }
        default: {
            break;
        }
        }
    }
    AllRecords& operator=(AllRecords const& other) {
        if (this != &other) {
            ::std::destroy_at(this);
            new (this) AllRecords(other);
        }
        return *this;
    }
    AllRecords& operator=(AllRecords&& other) {
        if (this != &other) {
            ::std::destroy_at(this);
            new (this) AllRecords(::std::move(other));
        }
        return *this;
    }
    ~AllRecords() {
        switch (m_tag) {
        case tag_t::file: {
            ::std::destroy_at(&m_data.file);
            break;
        }
        case tag_t::folder: {
            ::std::destroy_at(&m_data.folder);
            break;
        }
        case tag_t::audio: {
            ::std::destroy_at(&m_data.audio);
            break;
        }
        case tag_t::video: {
            ::std::destroy_at(&m_data.video);
            break;
        }
        case tag_t::image: {
            ::std::destroy_at(&m_data.image);
            break;
        }
        case tag_t::text: {
            ::std::destroy_at(&m_data.text);
            break;
        }
        case tag_t::plainText: {
            ::std::destroy_at(&m_data.plainText);
            break;
        }
        case tag_t::html: {
            ::std::destroy_at(&m_data.html);
            break;
        }
        case tag_t::hyperlink: {
            ::std::destroy_at(&m_data.hyperlink);
            break;
        }
        case tag_t::systemDefinedRecord: {
            ::std::destroy_at(&m_data.systemDefinedRecord);
            break;
        }
        case tag_t::systemDefinedForm: {
            ::std::destroy_at(&m_data.systemDefinedForm);
            break;
        }
        case tag_t::systemDefinedAppItem: {
            ::std::destroy_at(&m_data.systemDefinedAppItem);
            break;
        }
        case tag_t::systemDefinedPixelMap: {
            ::std::destroy_at(&m_data.systemDefinedPixelMap);
            break;
        }
        case tag_t::unifiedRecord: {
            ::std::destroy_at(&m_data.unifiedRecord);
            break;
        }
        default: {
            break;
        }
        }
    }
    template<typename... Args>
    AllRecords(::taihe::static_tag_t<tag_t::file>, Args&&... args) : m_tag(tag_t::file) {
        new (&m_data.file) decltype(m_data.file)(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    AllRecords(::taihe::static_tag_t<tag_t::folder>, Args&&... args) : m_tag(tag_t::folder) {
        new (&m_data.folder) decltype(m_data.folder)(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    AllRecords(::taihe::static_tag_t<tag_t::audio>, Args&&... args) : m_tag(tag_t::audio) {
        new (&m_data.audio) decltype(m_data.audio)(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    AllRecords(::taihe::static_tag_t<tag_t::video>, Args&&... args) : m_tag(tag_t::video) {
        new (&m_data.video) decltype(m_data.video)(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    AllRecords(::taihe::static_tag_t<tag_t::image>, Args&&... args) : m_tag(tag_t::image) {
        new (&m_data.image) decltype(m_data.image)(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    AllRecords(::taihe::static_tag_t<tag_t::text>, Args&&... args) : m_tag(tag_t::text) {
        new (&m_data.text) decltype(m_data.text)(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    AllRecords(::taihe::static_tag_t<tag_t::plainText>, Args&&... args) : m_tag(tag_t::plainText) {
        new (&m_data.plainText) decltype(m_data.plainText)(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    AllRecords(::taihe::static_tag_t<tag_t::html>, Args&&... args) : m_tag(tag_t::html) {
        new (&m_data.html) decltype(m_data.html)(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    AllRecords(::taihe::static_tag_t<tag_t::hyperlink>, Args&&... args) : m_tag(tag_t::hyperlink) {
        new (&m_data.hyperlink) decltype(m_data.hyperlink)(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    AllRecords(::taihe::static_tag_t<tag_t::systemDefinedRecord>, Args&&... args) : m_tag(tag_t::systemDefinedRecord) {
        new (&m_data.systemDefinedRecord) decltype(m_data.systemDefinedRecord)(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    AllRecords(::taihe::static_tag_t<tag_t::systemDefinedForm>, Args&&... args) : m_tag(tag_t::systemDefinedForm) {
        new (&m_data.systemDefinedForm) decltype(m_data.systemDefinedForm)(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    AllRecords(::taihe::static_tag_t<tag_t::systemDefinedAppItem>, Args&&... args) : m_tag(tag_t::systemDefinedAppItem) {
        new (&m_data.systemDefinedAppItem) decltype(m_data.systemDefinedAppItem)(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    AllRecords(::taihe::static_tag_t<tag_t::systemDefinedPixelMap>, Args&&... args) : m_tag(tag_t::systemDefinedPixelMap) {
        new (&m_data.systemDefinedPixelMap) decltype(m_data.systemDefinedPixelMap)(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    AllRecords(::taihe::static_tag_t<tag_t::unifiedRecord>, Args&&... args) : m_tag(tag_t::unifiedRecord) {
        new (&m_data.unifiedRecord) decltype(m_data.unifiedRecord)(::std::forward<Args>(args)...);
    }
    template<tag_t tag, typename... Args>
    static AllRecords make(Args&&... args) {
        return AllRecords(::taihe::static_tag<tag>, ::std::forward<Args>(args)...);
    }
    template<tag_t tag, typename... Args>
    AllRecords const& emplace(Args&&... args) {
        ::std::destroy_at(this);
        new (this) AllRecords(::taihe::static_tag<tag>, ::std::forward<Args>(args)...);
        return *this;
    }
    template<tag_t tag>
    auto& get_ref() {
        if constexpr (tag == tag_t::file) {
            return m_data.file;
        }
        if constexpr (tag == tag_t::folder) {
            return m_data.folder;
        }
        if constexpr (tag == tag_t::audio) {
            return m_data.audio;
        }
        if constexpr (tag == tag_t::video) {
            return m_data.video;
        }
        if constexpr (tag == tag_t::image) {
            return m_data.image;
        }
        if constexpr (tag == tag_t::text) {
            return m_data.text;
        }
        if constexpr (tag == tag_t::plainText) {
            return m_data.plainText;
        }
        if constexpr (tag == tag_t::html) {
            return m_data.html;
        }
        if constexpr (tag == tag_t::hyperlink) {
            return m_data.hyperlink;
        }
        if constexpr (tag == tag_t::systemDefinedRecord) {
            return m_data.systemDefinedRecord;
        }
        if constexpr (tag == tag_t::systemDefinedForm) {
            return m_data.systemDefinedForm;
        }
        if constexpr (tag == tag_t::systemDefinedAppItem) {
            return m_data.systemDefinedAppItem;
        }
        if constexpr (tag == tag_t::systemDefinedPixelMap) {
            return m_data.systemDefinedPixelMap;
        }
        if constexpr (tag == tag_t::unifiedRecord) {
            return m_data.unifiedRecord;
        }
    }
    template<tag_t tag>
    auto* get_ptr() {
        return m_tag == tag ? &get_ref<tag>() : nullptr;
    }
    template<tag_t tag>
    auto const& get_ref() const {
        if constexpr (tag == tag_t::file) {
            return m_data.file;
        }
        if constexpr (tag == tag_t::folder) {
            return m_data.folder;
        }
        if constexpr (tag == tag_t::audio) {
            return m_data.audio;
        }
        if constexpr (tag == tag_t::video) {
            return m_data.video;
        }
        if constexpr (tag == tag_t::image) {
            return m_data.image;
        }
        if constexpr (tag == tag_t::text) {
            return m_data.text;
        }
        if constexpr (tag == tag_t::plainText) {
            return m_data.plainText;
        }
        if constexpr (tag == tag_t::html) {
            return m_data.html;
        }
        if constexpr (tag == tag_t::hyperlink) {
            return m_data.hyperlink;
        }
        if constexpr (tag == tag_t::systemDefinedRecord) {
            return m_data.systemDefinedRecord;
        }
        if constexpr (tag == tag_t::systemDefinedForm) {
            return m_data.systemDefinedForm;
        }
        if constexpr (tag == tag_t::systemDefinedAppItem) {
            return m_data.systemDefinedAppItem;
        }
        if constexpr (tag == tag_t::systemDefinedPixelMap) {
            return m_data.systemDefinedPixelMap;
        }
        if constexpr (tag == tag_t::unifiedRecord) {
            return m_data.unifiedRecord;
        }
    }
    template<tag_t tag>
    auto const* get_ptr() const {
        return m_tag == tag ? &get_ref<tag>() : nullptr;
    }
    template<tag_t tag>
    bool holds() const {
        return m_tag == tag;
    }
    tag_t get_tag() const {
        return m_tag;
    }
    template<typename Visitor>
    auto accept_template(Visitor&& visitor) {
        switch (m_tag) {
        case tag_t::file: {
            return visitor(::taihe::static_tag<tag_t::file>, m_data.file);
        }
        case tag_t::folder: {
            return visitor(::taihe::static_tag<tag_t::folder>, m_data.folder);
        }
        case tag_t::audio: {
            return visitor(::taihe::static_tag<tag_t::audio>, m_data.audio);
        }
        case tag_t::video: {
            return visitor(::taihe::static_tag<tag_t::video>, m_data.video);
        }
        case tag_t::image: {
            return visitor(::taihe::static_tag<tag_t::image>, m_data.image);
        }
        case tag_t::text: {
            return visitor(::taihe::static_tag<tag_t::text>, m_data.text);
        }
        case tag_t::plainText: {
            return visitor(::taihe::static_tag<tag_t::plainText>, m_data.plainText);
        }
        case tag_t::html: {
            return visitor(::taihe::static_tag<tag_t::html>, m_data.html);
        }
        case tag_t::hyperlink: {
            return visitor(::taihe::static_tag<tag_t::hyperlink>, m_data.hyperlink);
        }
        case tag_t::systemDefinedRecord: {
            return visitor(::taihe::static_tag<tag_t::systemDefinedRecord>, m_data.systemDefinedRecord);
        }
        case tag_t::systemDefinedForm: {
            return visitor(::taihe::static_tag<tag_t::systemDefinedForm>, m_data.systemDefinedForm);
        }
        case tag_t::systemDefinedAppItem: {
            return visitor(::taihe::static_tag<tag_t::systemDefinedAppItem>, m_data.systemDefinedAppItem);
        }
        case tag_t::systemDefinedPixelMap: {
            return visitor(::taihe::static_tag<tag_t::systemDefinedPixelMap>, m_data.systemDefinedPixelMap);
        }
        case tag_t::unifiedRecord: {
            return visitor(::taihe::static_tag<tag_t::unifiedRecord>, m_data.unifiedRecord);
        }
        }
    }
    template<typename Visitor>
    auto accept_template(Visitor&& visitor) const {
        switch (m_tag) {
        case tag_t::file: {
            return visitor(::taihe::static_tag<tag_t::file>, m_data.file);
        }
        case tag_t::folder: {
            return visitor(::taihe::static_tag<tag_t::folder>, m_data.folder);
        }
        case tag_t::audio: {
            return visitor(::taihe::static_tag<tag_t::audio>, m_data.audio);
        }
        case tag_t::video: {
            return visitor(::taihe::static_tag<tag_t::video>, m_data.video);
        }
        case tag_t::image: {
            return visitor(::taihe::static_tag<tag_t::image>, m_data.image);
        }
        case tag_t::text: {
            return visitor(::taihe::static_tag<tag_t::text>, m_data.text);
        }
        case tag_t::plainText: {
            return visitor(::taihe::static_tag<tag_t::plainText>, m_data.plainText);
        }
        case tag_t::html: {
            return visitor(::taihe::static_tag<tag_t::html>, m_data.html);
        }
        case tag_t::hyperlink: {
            return visitor(::taihe::static_tag<tag_t::hyperlink>, m_data.hyperlink);
        }
        case tag_t::systemDefinedRecord: {
            return visitor(::taihe::static_tag<tag_t::systemDefinedRecord>, m_data.systemDefinedRecord);
        }
        case tag_t::systemDefinedForm: {
            return visitor(::taihe::static_tag<tag_t::systemDefinedForm>, m_data.systemDefinedForm);
        }
        case tag_t::systemDefinedAppItem: {
            return visitor(::taihe::static_tag<tag_t::systemDefinedAppItem>, m_data.systemDefinedAppItem);
        }
        case tag_t::systemDefinedPixelMap: {
            return visitor(::taihe::static_tag<tag_t::systemDefinedPixelMap>, m_data.systemDefinedPixelMap);
        }
        case tag_t::unifiedRecord: {
            return visitor(::taihe::static_tag<tag_t::unifiedRecord>, m_data.unifiedRecord);
        }
        }
    }
    template<typename... Args>
    static AllRecords make_file(Args&&... args) {
        return make<tag_t::file>(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    AllRecords const& emplace_file(Args&&... args) {
        return emplace<tag_t::file>(::std::forward<Args>(args)...);
    }
    bool holds_file() const {
        return holds<tag_t::file>();
    }
    auto* get_file_ptr() {
        return get_ptr<tag_t::file>();
    }
    auto const* get_file_ptr() const {
        return get_ptr<tag_t::file>();
    }
    auto& get_file_ref() {
        return get_ref<tag_t::file>();
    }
    auto const& get_file_ref() const {
        return get_ref<tag_t::file>();
    }
    template<typename... Args>
    static AllRecords make_folder(Args&&... args) {
        return make<tag_t::folder>(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    AllRecords const& emplace_folder(Args&&... args) {
        return emplace<tag_t::folder>(::std::forward<Args>(args)...);
    }
    bool holds_folder() const {
        return holds<tag_t::folder>();
    }
    auto* get_folder_ptr() {
        return get_ptr<tag_t::folder>();
    }
    auto const* get_folder_ptr() const {
        return get_ptr<tag_t::folder>();
    }
    auto& get_folder_ref() {
        return get_ref<tag_t::folder>();
    }
    auto const& get_folder_ref() const {
        return get_ref<tag_t::folder>();
    }
    template<typename... Args>
    static AllRecords make_audio(Args&&... args) {
        return make<tag_t::audio>(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    AllRecords const& emplace_audio(Args&&... args) {
        return emplace<tag_t::audio>(::std::forward<Args>(args)...);
    }
    bool holds_audio() const {
        return holds<tag_t::audio>();
    }
    auto* get_audio_ptr() {
        return get_ptr<tag_t::audio>();
    }
    auto const* get_audio_ptr() const {
        return get_ptr<tag_t::audio>();
    }
    auto& get_audio_ref() {
        return get_ref<tag_t::audio>();
    }
    auto const& get_audio_ref() const {
        return get_ref<tag_t::audio>();
    }
    template<typename... Args>
    static AllRecords make_video(Args&&... args) {
        return make<tag_t::video>(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    AllRecords const& emplace_video(Args&&... args) {
        return emplace<tag_t::video>(::std::forward<Args>(args)...);
    }
    bool holds_video() const {
        return holds<tag_t::video>();
    }
    auto* get_video_ptr() {
        return get_ptr<tag_t::video>();
    }
    auto const* get_video_ptr() const {
        return get_ptr<tag_t::video>();
    }
    auto& get_video_ref() {
        return get_ref<tag_t::video>();
    }
    auto const& get_video_ref() const {
        return get_ref<tag_t::video>();
    }
    template<typename... Args>
    static AllRecords make_image(Args&&... args) {
        return make<tag_t::image>(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    AllRecords const& emplace_image(Args&&... args) {
        return emplace<tag_t::image>(::std::forward<Args>(args)...);
    }
    bool holds_image() const {
        return holds<tag_t::image>();
    }
    auto* get_image_ptr() {
        return get_ptr<tag_t::image>();
    }
    auto const* get_image_ptr() const {
        return get_ptr<tag_t::image>();
    }
    auto& get_image_ref() {
        return get_ref<tag_t::image>();
    }
    auto const& get_image_ref() const {
        return get_ref<tag_t::image>();
    }
    template<typename... Args>
    static AllRecords make_text(Args&&... args) {
        return make<tag_t::text>(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    AllRecords const& emplace_text(Args&&... args) {
        return emplace<tag_t::text>(::std::forward<Args>(args)...);
    }
    bool holds_text() const {
        return holds<tag_t::text>();
    }
    auto* get_text_ptr() {
        return get_ptr<tag_t::text>();
    }
    auto const* get_text_ptr() const {
        return get_ptr<tag_t::text>();
    }
    auto& get_text_ref() {
        return get_ref<tag_t::text>();
    }
    auto const& get_text_ref() const {
        return get_ref<tag_t::text>();
    }
    template<typename... Args>
    static AllRecords make_plainText(Args&&... args) {
        return make<tag_t::plainText>(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    AllRecords const& emplace_plainText(Args&&... args) {
        return emplace<tag_t::plainText>(::std::forward<Args>(args)...);
    }
    bool holds_plainText() const {
        return holds<tag_t::plainText>();
    }
    auto* get_plainText_ptr() {
        return get_ptr<tag_t::plainText>();
    }
    auto const* get_plainText_ptr() const {
        return get_ptr<tag_t::plainText>();
    }
    auto& get_plainText_ref() {
        return get_ref<tag_t::plainText>();
    }
    auto const& get_plainText_ref() const {
        return get_ref<tag_t::plainText>();
    }
    template<typename... Args>
    static AllRecords make_html(Args&&... args) {
        return make<tag_t::html>(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    AllRecords const& emplace_html(Args&&... args) {
        return emplace<tag_t::html>(::std::forward<Args>(args)...);
    }
    bool holds_html() const {
        return holds<tag_t::html>();
    }
    auto* get_html_ptr() {
        return get_ptr<tag_t::html>();
    }
    auto const* get_html_ptr() const {
        return get_ptr<tag_t::html>();
    }
    auto& get_html_ref() {
        return get_ref<tag_t::html>();
    }
    auto const& get_html_ref() const {
        return get_ref<tag_t::html>();
    }
    template<typename... Args>
    static AllRecords make_hyperlink(Args&&... args) {
        return make<tag_t::hyperlink>(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    AllRecords const& emplace_hyperlink(Args&&... args) {
        return emplace<tag_t::hyperlink>(::std::forward<Args>(args)...);
    }
    bool holds_hyperlink() const {
        return holds<tag_t::hyperlink>();
    }
    auto* get_hyperlink_ptr() {
        return get_ptr<tag_t::hyperlink>();
    }
    auto const* get_hyperlink_ptr() const {
        return get_ptr<tag_t::hyperlink>();
    }
    auto& get_hyperlink_ref() {
        return get_ref<tag_t::hyperlink>();
    }
    auto const& get_hyperlink_ref() const {
        return get_ref<tag_t::hyperlink>();
    }
    template<typename... Args>
    static AllRecords make_systemDefinedRecord(Args&&... args) {
        return make<tag_t::systemDefinedRecord>(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    AllRecords const& emplace_systemDefinedRecord(Args&&... args) {
        return emplace<tag_t::systemDefinedRecord>(::std::forward<Args>(args)...);
    }
    bool holds_systemDefinedRecord() const {
        return holds<tag_t::systemDefinedRecord>();
    }
    auto* get_systemDefinedRecord_ptr() {
        return get_ptr<tag_t::systemDefinedRecord>();
    }
    auto const* get_systemDefinedRecord_ptr() const {
        return get_ptr<tag_t::systemDefinedRecord>();
    }
    auto& get_systemDefinedRecord_ref() {
        return get_ref<tag_t::systemDefinedRecord>();
    }
    auto const& get_systemDefinedRecord_ref() const {
        return get_ref<tag_t::systemDefinedRecord>();
    }
    template<typename... Args>
    static AllRecords make_systemDefinedForm(Args&&... args) {
        return make<tag_t::systemDefinedForm>(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    AllRecords const& emplace_systemDefinedForm(Args&&... args) {
        return emplace<tag_t::systemDefinedForm>(::std::forward<Args>(args)...);
    }
    bool holds_systemDefinedForm() const {
        return holds<tag_t::systemDefinedForm>();
    }
    auto* get_systemDefinedForm_ptr() {
        return get_ptr<tag_t::systemDefinedForm>();
    }
    auto const* get_systemDefinedForm_ptr() const {
        return get_ptr<tag_t::systemDefinedForm>();
    }
    auto& get_systemDefinedForm_ref() {
        return get_ref<tag_t::systemDefinedForm>();
    }
    auto const& get_systemDefinedForm_ref() const {
        return get_ref<tag_t::systemDefinedForm>();
    }
    template<typename... Args>
    static AllRecords make_systemDefinedAppItem(Args&&... args) {
        return make<tag_t::systemDefinedAppItem>(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    AllRecords const& emplace_systemDefinedAppItem(Args&&... args) {
        return emplace<tag_t::systemDefinedAppItem>(::std::forward<Args>(args)...);
    }
    bool holds_systemDefinedAppItem() const {
        return holds<tag_t::systemDefinedAppItem>();
    }
    auto* get_systemDefinedAppItem_ptr() {
        return get_ptr<tag_t::systemDefinedAppItem>();
    }
    auto const* get_systemDefinedAppItem_ptr() const {
        return get_ptr<tag_t::systemDefinedAppItem>();
    }
    auto& get_systemDefinedAppItem_ref() {
        return get_ref<tag_t::systemDefinedAppItem>();
    }
    auto const& get_systemDefinedAppItem_ref() const {
        return get_ref<tag_t::systemDefinedAppItem>();
    }
    template<typename... Args>
    static AllRecords make_systemDefinedPixelMap(Args&&... args) {
        return make<tag_t::systemDefinedPixelMap>(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    AllRecords const& emplace_systemDefinedPixelMap(Args&&... args) {
        return emplace<tag_t::systemDefinedPixelMap>(::std::forward<Args>(args)...);
    }
    bool holds_systemDefinedPixelMap() const {
        return holds<tag_t::systemDefinedPixelMap>();
    }
    auto* get_systemDefinedPixelMap_ptr() {
        return get_ptr<tag_t::systemDefinedPixelMap>();
    }
    auto const* get_systemDefinedPixelMap_ptr() const {
        return get_ptr<tag_t::systemDefinedPixelMap>();
    }
    auto& get_systemDefinedPixelMap_ref() {
        return get_ref<tag_t::systemDefinedPixelMap>();
    }
    auto const& get_systemDefinedPixelMap_ref() const {
        return get_ref<tag_t::systemDefinedPixelMap>();
    }
    template<typename... Args>
    static AllRecords make_unifiedRecord(Args&&... args) {
        return make<tag_t::unifiedRecord>(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    AllRecords const& emplace_unifiedRecord(Args&&... args) {
        return emplace<tag_t::unifiedRecord>(::std::forward<Args>(args)...);
    }
    bool holds_unifiedRecord() const {
        return holds<tag_t::unifiedRecord>();
    }
    auto* get_unifiedRecord_ptr() {
        return get_ptr<tag_t::unifiedRecord>();
    }
    auto const* get_unifiedRecord_ptr() const {
        return get_ptr<tag_t::unifiedRecord>();
    }
    auto& get_unifiedRecord_ref() {
        return get_ref<tag_t::unifiedRecord>();
    }
    auto const& get_unifiedRecord_ref() const {
        return get_ref<tag_t::unifiedRecord>();
    }
    template<typename Visitor>
    auto accept(Visitor&& visitor) {
        switch (m_tag) {
        case tag_t::file: {
            return visitor.file(m_data.file);
        }
        case tag_t::folder: {
            return visitor.folder(m_data.folder);
        }
        case tag_t::audio: {
            return visitor.audio(m_data.audio);
        }
        case tag_t::video: {
            return visitor.video(m_data.video);
        }
        case tag_t::image: {
            return visitor.image(m_data.image);
        }
        case tag_t::text: {
            return visitor.text(m_data.text);
        }
        case tag_t::plainText: {
            return visitor.plainText(m_data.plainText);
        }
        case tag_t::html: {
            return visitor.html(m_data.html);
        }
        case tag_t::hyperlink: {
            return visitor.hyperlink(m_data.hyperlink);
        }
        case tag_t::systemDefinedRecord: {
            return visitor.systemDefinedRecord(m_data.systemDefinedRecord);
        }
        case tag_t::systemDefinedForm: {
            return visitor.systemDefinedForm(m_data.systemDefinedForm);
        }
        case tag_t::systemDefinedAppItem: {
            return visitor.systemDefinedAppItem(m_data.systemDefinedAppItem);
        }
        case tag_t::systemDefinedPixelMap: {
            return visitor.systemDefinedPixelMap(m_data.systemDefinedPixelMap);
        }
        case tag_t::unifiedRecord: {
            return visitor.unifiedRecord(m_data.unifiedRecord);
        }
        }
    }
    template<typename Visitor>
    auto accept(Visitor&& visitor) const {
        switch (m_tag) {
        case tag_t::file: {
            return visitor.file(m_data.file);
        }
        case tag_t::folder: {
            return visitor.folder(m_data.folder);
        }
        case tag_t::audio: {
            return visitor.audio(m_data.audio);
        }
        case tag_t::video: {
            return visitor.video(m_data.video);
        }
        case tag_t::image: {
            return visitor.image(m_data.image);
        }
        case tag_t::text: {
            return visitor.text(m_data.text);
        }
        case tag_t::plainText: {
            return visitor.plainText(m_data.plainText);
        }
        case tag_t::html: {
            return visitor.html(m_data.html);
        }
        case tag_t::hyperlink: {
            return visitor.hyperlink(m_data.hyperlink);
        }
        case tag_t::systemDefinedRecord: {
            return visitor.systemDefinedRecord(m_data.systemDefinedRecord);
        }
        case tag_t::systemDefinedForm: {
            return visitor.systemDefinedForm(m_data.systemDefinedForm);
        }
        case tag_t::systemDefinedAppItem: {
            return visitor.systemDefinedAppItem(m_data.systemDefinedAppItem);
        }
        case tag_t::systemDefinedPixelMap: {
            return visitor.systemDefinedPixelMap(m_data.systemDefinedPixelMap);
        }
        case tag_t::unifiedRecord: {
            return visitor.unifiedRecord(m_data.unifiedRecord);
        }
        }
    }
    private:
    tag_t m_tag;
    storage_t m_data;
};
}
namespace taihe {
inline bool same_impl(adl_helper_t, ::ohos::data::unifiedDataChannel::AllRecords const& lhs, ::ohos::data::unifiedDataChannel::AllRecords const& rhs) {
    return false || (lhs.holds_file() && rhs.holds_file() && same(lhs.get_file_ref(), rhs.get_file_ref())) || (lhs.holds_folder() && rhs.holds_folder() && same(lhs.get_folder_ref(), rhs.get_folder_ref())) || (lhs.holds_audio() && rhs.holds_audio() && same(lhs.get_audio_ref(), rhs.get_audio_ref())) || (lhs.holds_video() && rhs.holds_video() && same(lhs.get_video_ref(), rhs.get_video_ref())) || (lhs.holds_image() && rhs.holds_image() && same(lhs.get_image_ref(), rhs.get_image_ref())) || (lhs.holds_text() && rhs.holds_text() && same(lhs.get_text_ref(), rhs.get_text_ref())) || (lhs.holds_plainText() && rhs.holds_plainText() && same(lhs.get_plainText_ref(), rhs.get_plainText_ref())) || (lhs.holds_html() && rhs.holds_html() && same(lhs.get_html_ref(), rhs.get_html_ref())) || (lhs.holds_hyperlink() && rhs.holds_hyperlink() && same(lhs.get_hyperlink_ref(), rhs.get_hyperlink_ref())) || (lhs.holds_systemDefinedRecord() && rhs.holds_systemDefinedRecord() && same(lhs.get_systemDefinedRecord_ref(), rhs.get_systemDefinedRecord_ref())) || (lhs.holds_systemDefinedForm() && rhs.holds_systemDefinedForm() && same(lhs.get_systemDefinedForm_ref(), rhs.get_systemDefinedForm_ref())) || (lhs.holds_systemDefinedAppItem() && rhs.holds_systemDefinedAppItem() && same(lhs.get_systemDefinedAppItem_ref(), rhs.get_systemDefinedAppItem_ref())) || (lhs.holds_systemDefinedPixelMap() && rhs.holds_systemDefinedPixelMap() && same(lhs.get_systemDefinedPixelMap_ref(), rhs.get_systemDefinedPixelMap_ref())) || (lhs.holds_unifiedRecord() && rhs.holds_unifiedRecord() && same(lhs.get_unifiedRecord_ref(), rhs.get_unifiedRecord_ref()));
}
}
namespace taihe {
inline auto hash_impl(adl_helper_t, ::ohos::data::unifiedDataChannel::AllRecords const& val) -> ::std::size_t {
    switch (val.get_tag()) {
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::file: {
        ::std::size_t seed = (::std::size_t)::ohos::data::unifiedDataChannel::AllRecords::tag_t::file;
        return seed ^ (0x9e3779b9 + (seed << 6) + (seed >> 2) + hash(val.get_file_ref()));
    }
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::folder: {
        ::std::size_t seed = (::std::size_t)::ohos::data::unifiedDataChannel::AllRecords::tag_t::folder;
        return seed ^ (0x9e3779b9 + (seed << 6) + (seed >> 2) + hash(val.get_folder_ref()));
    }
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::audio: {
        ::std::size_t seed = (::std::size_t)::ohos::data::unifiedDataChannel::AllRecords::tag_t::audio;
        return seed ^ (0x9e3779b9 + (seed << 6) + (seed >> 2) + hash(val.get_audio_ref()));
    }
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::video: {
        ::std::size_t seed = (::std::size_t)::ohos::data::unifiedDataChannel::AllRecords::tag_t::video;
        return seed ^ (0x9e3779b9 + (seed << 6) + (seed >> 2) + hash(val.get_video_ref()));
    }
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::image: {
        ::std::size_t seed = (::std::size_t)::ohos::data::unifiedDataChannel::AllRecords::tag_t::image;
        return seed ^ (0x9e3779b9 + (seed << 6) + (seed >> 2) + hash(val.get_image_ref()));
    }
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::text: {
        ::std::size_t seed = (::std::size_t)::ohos::data::unifiedDataChannel::AllRecords::tag_t::text;
        return seed ^ (0x9e3779b9 + (seed << 6) + (seed >> 2) + hash(val.get_text_ref()));
    }
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::plainText: {
        ::std::size_t seed = (::std::size_t)::ohos::data::unifiedDataChannel::AllRecords::tag_t::plainText;
        return seed ^ (0x9e3779b9 + (seed << 6) + (seed >> 2) + hash(val.get_plainText_ref()));
    }
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::html: {
        ::std::size_t seed = (::std::size_t)::ohos::data::unifiedDataChannel::AllRecords::tag_t::html;
        return seed ^ (0x9e3779b9 + (seed << 6) + (seed >> 2) + hash(val.get_html_ref()));
    }
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::hyperlink: {
        ::std::size_t seed = (::std::size_t)::ohos::data::unifiedDataChannel::AllRecords::tag_t::hyperlink;
        return seed ^ (0x9e3779b9 + (seed << 6) + (seed >> 2) + hash(val.get_hyperlink_ref()));
    }
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::systemDefinedRecord: {
        ::std::size_t seed = (::std::size_t)::ohos::data::unifiedDataChannel::AllRecords::tag_t::systemDefinedRecord;
        return seed ^ (0x9e3779b9 + (seed << 6) + (seed >> 2) + hash(val.get_systemDefinedRecord_ref()));
    }
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::systemDefinedForm: {
        ::std::size_t seed = (::std::size_t)::ohos::data::unifiedDataChannel::AllRecords::tag_t::systemDefinedForm;
        return seed ^ (0x9e3779b9 + (seed << 6) + (seed >> 2) + hash(val.get_systemDefinedForm_ref()));
    }
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::systemDefinedAppItem: {
        ::std::size_t seed = (::std::size_t)::ohos::data::unifiedDataChannel::AllRecords::tag_t::systemDefinedAppItem;
        return seed ^ (0x9e3779b9 + (seed << 6) + (seed >> 2) + hash(val.get_systemDefinedAppItem_ref()));
    }
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::systemDefinedPixelMap: {
        ::std::size_t seed = (::std::size_t)::ohos::data::unifiedDataChannel::AllRecords::tag_t::systemDefinedPixelMap;
        return seed ^ (0x9e3779b9 + (seed << 6) + (seed >> 2) + hash(val.get_systemDefinedPixelMap_ref()));
    }
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::unifiedRecord: {
        ::std::size_t seed = (::std::size_t)::ohos::data::unifiedDataChannel::AllRecords::tag_t::unifiedRecord;
        return seed ^ (0x9e3779b9 + (seed << 6) + (seed >> 2) + hash(val.get_unifiedRecord_ref()));
    }
    }
}
}
namespace taihe {
template<>
struct as_abi<::ohos::data::unifiedDataChannel::AllRecords> {
    using type = struct ohos_data_unifiedDataChannel_AllRecords_t;
};
template<>
struct as_abi<::ohos::data::unifiedDataChannel::AllRecords const&> {
    using type = struct ohos_data_unifiedDataChannel_AllRecords_t const*;
};
template<>
struct as_param<::ohos::data::unifiedDataChannel::AllRecords> {
    using type = ::ohos::data::unifiedDataChannel::AllRecords const&;
};
}
