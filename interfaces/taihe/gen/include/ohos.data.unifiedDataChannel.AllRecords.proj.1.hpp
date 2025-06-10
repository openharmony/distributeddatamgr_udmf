#pragma once
#include "taihe/common.hpp"
#include "ohos.data.unifiedDataChannel.AllRecords.proj.0.hpp"
#include "ohos.data.unifiedDataChannel.AllRecords.abi.1.h"
#include "ohos.data.unifiedDataChannel.File.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.UnifiedRecord.proj.2.hpp"
namespace ohos::data::unifiedDataChannel {
struct AllRecords {
    public:
    enum class tag_t : int {
        file,
        unifiedRecord,
    };
    union storage_t {
        storage_t() {}
        ~storage_t() {}
        ::ohos::data::unifiedDataChannel::File file;
        ::ohos::data::unifiedDataChannel::UnifiedRecord unifiedRecord;
    };
    AllRecords(AllRecords const& other) : m_tag(other.m_tag) {
        switch (m_tag) {
        case tag_t::file: {
            new (&m_data.file) decltype(m_data.file)(other.m_data.file);
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
    return false || (lhs.holds_file() && rhs.holds_file() && same(lhs.get_file_ref(), rhs.get_file_ref())) || (lhs.holds_unifiedRecord() && rhs.holds_unifiedRecord() && same(lhs.get_unifiedRecord_ref(), rhs.get_unifiedRecord_ref()));
}
}
namespace taihe {
inline auto hash_impl(adl_helper_t, ::ohos::data::unifiedDataChannel::AllRecords const& val) -> ::std::size_t {
    switch (val.get_tag()) {
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::file: {
        ::std::size_t seed = (::std::size_t)::ohos::data::unifiedDataChannel::AllRecords::tag_t::file;
        return seed ^ (0x9e3779b9 + (seed << 6) + (seed >> 2) + hash(val.get_file_ref()));
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
