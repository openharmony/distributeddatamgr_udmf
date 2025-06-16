#pragma once
#include "taihe/common.hpp"
#include "taihe/string.hpp"
namespace ohos::data::uniformTypeDescriptor {
struct UniformDataType {
    public:
    enum class key_t: int {
        OPENHARMONY_PIXEL_MAP,
        FOLDER,
        FILE,
        AUDIO,
        VIDEO,
        IMAGE,
        HYPERLINK,
        HTML,
        PLAIN_TEXT,
        TEXT,
        JPEG,
        PNG,
        MPEG4,
        OPENHARMONY_ATOMIC_SERVICE,
        PDF,
        OPENHARMONY_APP_ITEM,
    };
    UniformDataType(UniformDataType const& other) : key(other.key) {}
    UniformDataType& operator=(UniformDataType other) {
        key = other.key;
        return *this;
    }
    UniformDataType(key_t key) : key(key) {}
    key_t get_key() const {
        return this->key;
    }
    bool is_valid() const {
        return (int)key >= 0 && (int)key < 16;
    }
    static constexpr char const* table[] = {
        "openharmony.pixel-map",
        "general.folder",
        "general.file",
        "general.audio",
        "general.video",
        "general.image",
        "general.hyperlink",
        "general.html",
        "general.plain-text",
        "general.text",
        "general.jpeg",
        "general.png",
        "general.mpeg-4",
        "openharmony.atomic-service",
        "com.adobe.pdf",
        "openharmony.app-item",
    };
    char const* get_value() const {
        return table[(int)key];
    }
    operator char const*() const {
        return table[(int)key];
    }
    static ::ohos::data::uniformTypeDescriptor::UniformDataType from_value(::taihe::string_view value) {
        for (size_t i = 0; i < 16; ++i) {
            if (::taihe::same(table[i], value)) {
                return ::ohos::data::uniformTypeDescriptor::UniformDataType((key_t)i);
            }
        }
        return ::ohos::data::uniformTypeDescriptor::UniformDataType((key_t)-1);
    }
    private:
    key_t key;
};
}
namespace taihe {
inline bool same_impl(adl_helper_t, ::ohos::data::uniformTypeDescriptor::UniformDataType lhs, ::ohos::data::uniformTypeDescriptor::UniformDataType rhs) {
    return lhs.get_key() == rhs.get_key();
}
}
namespace taihe {
inline auto hash_impl(adl_helper_t, ::ohos::data::uniformTypeDescriptor::UniformDataType val) -> ::std::size_t {
    return ::std::hash<int>{}((int)val.get_key());
}
}
namespace taihe {
template<>
struct as_abi<::ohos::data::uniformTypeDescriptor::UniformDataType> {
    using type = int;
};
template<>
struct as_param<::ohos::data::uniformTypeDescriptor::UniformDataType> {
    using type = ::ohos::data::uniformTypeDescriptor::UniformDataType;
};
}
