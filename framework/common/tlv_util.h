/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef UDMF_TLV_UTIL_H
#define UDMF_TLV_UTIL_H

#include <utility>
#include <vector>
#include "unified_types.h"
#include "unified_data.h"
#include "unified_key.h"
#include "tlv_object.h"
#include "unified_record.h"


namespace OHOS {
namespace TLVUtil {
using namespace OHOS::UDMF;

template <typename T> bool API_EXPORT ReadTlv(T &output, TLVObject &data, TAG tag);

template <typename T> size_t API_EXPORT CountBufferSize(const T &input, TLVObject &data);
template <typename T> bool API_EXPORT Writing(const T &input, TLVObject &data, TAG tag);
template <typename T> bool API_EXPORT Reading(T &output, TLVObject &data, const TLVHead &head);

template <typename... _Types> size_t API_EXPORT CountBufferSize(const std::variant<_Types...> &input, TLVObject &data);
template <typename... _Types> bool API_EXPORT Writing(const std::variant<_Types...> &input, TLVObject &data, TAG tag);
template <typename... _Types>
bool API_EXPORT Reading(std::variant<_Types...> &output, TLVObject &data, const TLVHead &head);

template <typename T> size_t API_EXPORT CountBufferSize(const std::shared_ptr<T> &input, TLVObject &data);
template <typename T> bool API_EXPORT Writing(const std::shared_ptr<T> &input, TLVObject &data, TAG tag);
template <typename T> bool API_EXPORT Reading(std::shared_ptr<T> &output, TLVObject &data, const TLVHead &head);

template <typename T> size_t API_EXPORT CountBufferSize(const std::vector<T> &input, TLVObject &data);
template <typename T> bool API_EXPORT Writing(const std::vector<T> &input, TLVObject &data, TAG tag);
template <typename T> bool API_EXPORT Reading(std::vector<T> &output, TLVObject &data, const TLVHead &head);

template <typename T, typename R> size_t API_EXPORT CountBufferSize(const std::map<T, R> &input, TLVObject &data);
template <typename T, typename R> bool API_EXPORT Writing(const std::map<T, R> &input, TLVObject &data, TAG tag);
template <typename T, typename R> bool API_EXPORT Reading(std::map<T, R> &output, TLVObject &data, const TLVHead &head);

template <> size_t API_EXPORT CountBufferSize(const std::nullptr_t &input, TLVObject &data);
template <> bool API_EXPORT Writing(const std::nullptr_t &input, TLVObject &data, TAG tag);
template <> bool API_EXPORT Reading(std::nullptr_t &output, TLVObject &data, const TLVHead &head);

template <> size_t API_EXPORT CountBufferSize(const std::monostate &input, TLVObject &data);
template <> bool API_EXPORT Writing(const std::monostate &input, TLVObject &data, TAG tag);
template <> bool API_EXPORT Reading(std::monostate &output, TLVObject &data, const TLVHead &head);

template <> size_t API_EXPORT CountBufferSize(const std::string &input, TLVObject &data);
template <> bool API_EXPORT Writing(const std::string &input, TLVObject &data, TAG tag);
template <> bool API_EXPORT Reading(std::string &output, TLVObject &data, const TLVHead &head);

template <> size_t API_EXPORT CountBufferSize(const std::vector<uint8_t> &input, TLVObject &data);
template <> bool API_EXPORT Writing(const std::vector<uint8_t> &input, TLVObject &data, TAG tag);
template <> bool API_EXPORT Reading(std::vector<uint8_t> &output, TLVObject &data, const TLVHead &head);

template <> size_t API_EXPORT CountBufferSize(const UDType &input, TLVObject &data);
template <> bool API_EXPORT Writing(const UDType &input, TLVObject &data, TAG tag);
template <> bool API_EXPORT Reading(UDType &output, TLVObject &data, const TLVHead &head);

template <> size_t API_EXPORT CountBufferSize(const DataStatus &input, TLVObject &data);
template <> bool API_EXPORT Writing(const DataStatus &input, TLVObject &data, TAG tag);
template <> bool API_EXPORT Reading(DataStatus &output, TLVObject &data, const TLVHead &head);

template <> size_t API_EXPORT CountBufferSize(const Object &input, TLVObject &data);
template <> bool API_EXPORT Writing(const Object &input, TLVObject &data, TAG tag);
template <> bool API_EXPORT Reading(Object &output, TLVObject &data, const TLVHead &head);

template <> size_t API_EXPORT CountBufferSize(const UnifiedKey &input, TLVObject &data);
template <> bool API_EXPORT Writing(const UnifiedKey &input, TLVObject &data, TAG tag);
template <> bool API_EXPORT Reading(UnifiedKey &output, TLVObject &data, const TLVHead &head);

template <> size_t API_EXPORT CountBufferSize(const UnifiedData &input, TLVObject &data);
template <> bool API_EXPORT Writing(const UnifiedData &input, TLVObject &data, TAG tag);
template <> bool API_EXPORT Reading(UnifiedData &output, TLVObject &data, const TLVHead &head);

template <> size_t API_EXPORT CountBufferSize(const UnifiedRecord &input, TLVObject &data);
template <> bool API_EXPORT Writing(const UnifiedRecord &input, TLVObject &data, TAG tag);
template <> bool API_EXPORT Reading(UnifiedRecord &output, TLVObject &data, const TLVHead &head);

template <> size_t API_EXPORT CountBufferSize(const Runtime &input, TLVObject &data);
template <> bool API_EXPORT Writing(const Runtime &input, TLVObject &data, TAG tag);
template <> bool API_EXPORT Reading(Runtime &output, TLVObject &data, const TLVHead &head);

template <> size_t API_EXPORT CountBufferSize(const Privilege &input, TLVObject &data);
template <> bool API_EXPORT Writing(const Privilege &input, TLVObject &data, TAG tag);
template <> bool API_EXPORT Reading(Privilege &output, TLVObject &data, const TLVHead &head);

template <> size_t API_EXPORT CountBufferSize(const UriInfo &input, TLVObject &data);
template <> bool API_EXPORT Writing(const UriInfo &input, TLVObject &data, TAG tag);
template <> bool API_EXPORT Reading(UriInfo &output, TLVObject &data, const TLVHead &head);

template <> size_t API_EXPORT CountBufferSize(const std::shared_ptr<OHOS::Media::PixelMap> &input, TLVObject &data);
template <> bool API_EXPORT Writing(const std::shared_ptr<OHOS::Media::PixelMap> &input, TLVObject &data, TAG tag);
template <>
bool API_EXPORT Reading(std::shared_ptr<OHOS::Media::PixelMap> &output, TLVObject &data, const TLVHead &head);

template <> size_t API_EXPORT CountBufferSize(const std::shared_ptr<std::map<std::string, ValueType>> &input,
    TLVObject &data);
template <> bool API_EXPORT Writing(const std::shared_ptr<std::map<std::string, ValueType>> &input,
    TLVObject &data, TAG tag);
template <>
bool API_EXPORT Reading(std::shared_ptr<std::map<std::string, ValueType>> &output,
    TLVObject &data, const TLVHead &head);

template <> size_t API_EXPORT CountBufferSize(const std::shared_ptr<OHOS::AAFwk::Want> &input, TLVObject &data);
template <> bool API_EXPORT Writing(const std::shared_ptr<OHOS::AAFwk::Want> &input, TLVObject &data, TAG tag);
template <> bool API_EXPORT Reading(std::shared_ptr<OHOS::AAFwk::Want> &output, TLVObject &data, const TLVHead &head);

template <typename T> bool ReadTlv(T &output, TLVObject &data, TAG tag)
{
    while (data.GetCursor() < data.GetTotal()) {
        TLVHead head{};
        if (!data.ReadHead(head)) {
            return false;
        }
        if (head.tag != static_cast<uint16_t>(tag)) {
            data.Skip(head);
            continue;
        }
        if (!Reading(output, data, head)) {
            return false;
        }
    }
    return true;
}

template <typename T> void InitWhenFirst(const T &input, TLVObject &data)
{
    if (data.GetCursor() == data.GetTotal()) {
        CountBufferSize(input, data);
        data.UpdateSize();
    }
}

template <typename T> size_t CountBufferSize(const T &input, TLVObject &data)
{
    return data.CountBasic(input);
}

template <typename T> bool Writing(const T &input, TLVObject &data, TAG tag)
{
    InitWhenFirst(input, data);
    return data.WriteBasic(tag, input);
}

template <typename T> bool Reading(T &output, TLVObject &data, const TLVHead &head)
{
    return data.ReadBasic(output, head);
}

template <typename T> size_t CountBufferSize(const std::shared_ptr<T> &input, TLVObject &data)
{
    if (input == nullptr) {
        return data.CountHead();
    }
    return CountBufferSize(*input, data);
}

template <typename T> bool Writing(const std::shared_ptr<T> &input, TLVObject &data, TAG tag)
{
    if (input == nullptr) {
        return false;
    }
    InitWhenFirst(input, data);
    return Writing(*input, data, tag);
}

template <typename T> bool Reading(std::shared_ptr<T> &output, TLVObject &data, const TLVHead &head)
{
    if (output == nullptr) {
        output = std::make_shared<T>();
    }
    return Reading(*output, data, head);
}

template <typename T> size_t CountBufferSize(const std::vector<T> &input, TLVObject &data)
{
    auto size = data.CountHead() + data.CountBasic(input.size());
    for (auto item : input) {
        size += CountBufferSize(item, data);
    }
    return size;
}

template <typename T> bool Writing(const std::vector<T> &input, TLVObject &data, TAG tag)
{
    InitWhenFirst(input, data);
    auto tagCursor = data.GetCursor();
    data.OffsetHead();
    if (!data.WriteBasic(TAG::TAG_VECTOR_SIZE, input.size())) {
        return false;
    }
    if (!input.empty()) {
        for (auto item : input) {
            if (!Writing(item, data, TAG::TAG_VECTOR_ITEM)) {
                return false;
            }
        }
    }
    return data.WriteBackHead(static_cast<uint16_t>(tag), tagCursor, data.GetCursor() - tagCursor - sizeof(TLVHead));
}

template <typename T> bool Reading(std::vector<T> &output, TLVObject &data, const TLVHead &head)
{
    auto endCursor = data.GetCursor() + head.len;
    while (data.GetCursor() < endCursor) {
        TLVHead itemHead{};
        if (!data.ReadHead(itemHead)) {
            return false;
        }
        if (itemHead.tag == static_cast<uint16_t>(TAG::TAG_VECTOR_ITEM)) {
            T item{};
            if (!Reading(item, data, itemHead)) {
                return false;
            }
            output.push_back(std::move(item));
            continue;
        }
        if (!data.Skip(itemHead)) {
            return false;
        }
    }
    return true;
}

template <typename T, typename R> size_t CountBufferSize(const std::map<T, R> &input, TLVObject &data)
{
    auto size = data.CountHead();
    for (auto item : input) {
        size += data.CountHead() + CountBufferSize(item.first, data) + CountBufferSize(item.second, data);
    }
    return size;
}

template <typename T, typename R> bool Writing(const std::map<T, R> &input, TLVObject &data, TAG tag)
{
    InitWhenFirst(input, data);
    auto tagCursor = data.GetCursor();
    data.OffsetHead();
    if (!input.empty()) {
        for (auto item : input) {
            auto pairCursor = data.GetCursor();
            data.OffsetHead();
            if (!TLVUtil::Writing(item.first, data, TAG::TAG_MAP_KEY)) {
                return false;
            }
            if (!TLVUtil::Writing(item.second, data, TAG::TAG_MAP_VALUE)) {
                return false;
            }
            if (!data.WriteBackHead(static_cast<uint16_t>(TAG::TAG_MAP_PAIR), pairCursor,
                data.GetCursor() - pairCursor - sizeof(TLVHead))) {
                return false;
            }
        }
    }
    return data.WriteBackHead(static_cast<uint16_t>(tag), tagCursor, data.GetCursor() - tagCursor - sizeof(TLVHead));
}

template <typename T, typename R> bool Reading(std::map<T, R> &output, TLVObject &data, const TLVHead &head)
{
    auto endCursor = data.GetCursor() + head.len;
    while (data.GetCursor() < endCursor) {
        TLVHead headPair{};
        if (!data.ReadHead(headPair)) {
            return false;
        }
        if (headPair.tag != static_cast<uint16_t>(TAG::TAG_MAP_PAIR)) {
            return false;
        }
        TLVHead headKey{};
        if (!data.ReadHead(headKey) || headKey.tag != static_cast<uint16_t>(TAG::TAG_MAP_KEY)) {
            return false;
        }
        T itemKey{};
        if (!Reading(itemKey, data, headKey)) {
            return false;
        }
        TLVHead headValue{};
        if (!data.ReadHead(headValue) || headValue.tag != static_cast<uint16_t>(TAG::TAG_MAP_VALUE)) {
            return false;
        }
        R itemValue{};
        if (!Reading(itemValue, data, headValue)) {
            return false;
        }
        output.emplace(std::move(itemKey), std::move(itemValue));
    }
    return true;
}

template <typename _InTp> size_t CountVariant(TLVObject &data, uint32_t step, const _InTp &input)
{
    return 0;
}

template <typename _InTp, typename _First, typename... _Rest>
size_t CountVariant(TLVObject &data, uint32_t step, const _InTp &input)
{
    if (step == input.index()) {
        return CountBufferSize(std::get<_First>(input), data);
    }
    return CountVariant<_InTp, _Rest...>(data, step + 1, input);
}

template <typename... _Types> size_t CountBufferSize(const std::variant<_Types...> &input, TLVObject &data)
{
    if (input.index() > size_t(std::numeric_limits<uint32_t>::max())) {
        return 0;
    }
    uint32_t index = static_cast<uint32_t>(input.index());
    return data.CountHead() + data.CountBasic(index) + CountVariant<decltype(input), _Types...>(data, 0, input);
}

template <typename _InTp> bool WriteVariant(TLVObject &data, uint32_t step, const _InTp &input, TAG tag)
{
    return true;
}

template <typename _InTp, typename _First, typename... _Rest>
bool WriteVariant(TLVObject &data, uint32_t step, const _InTp &input, TAG tag)
{
    if (step == input.index()) {
        auto val = std::get<_First>(input);
        return Writing(val, data, tag);
    }
    return WriteVariant<_InTp, _Rest...>(data, step + 1, input, tag);
}

template <typename... _Types> bool Writing(const std::variant<_Types...> &input, TLVObject &data, TAG tag)
{
    InitWhenFirst(input, data);
    auto tagCursor = data.GetCursor();
    data.OffsetHead();
    uint32_t index = input.index();
    if (!data.WriteBasic(TAG::TAG_VARIANT_INDEX, index)) {
        return false;
    }
    if (!WriteVariant<decltype(input), _Types...>(data, 0, input, TAG::TAG_VARIANT_ITEM)) {
        return false;
    }
    return data.WriteBackHead(static_cast<uint16_t>(tag), tagCursor, data.GetCursor() - tagCursor - sizeof(TLVHead));
}

template <typename _OutTp> bool ReadVariant(TLVObject &data, uint32_t step, uint32_t index, _OutTp &value, TLVHead head)
{
    return true;
}

template <typename _OutTp, typename _First, typename... _Rest>
bool ReadVariant(TLVObject &data, uint32_t step, uint32_t index, _OutTp &value, TLVHead head)
{
    if (step == index) {
        _First output{};
        auto success = Reading(output, data, head);
        value = output;
        return success;
    }
    return ReadVariant<_OutTp, _Rest...>(data, step + 1, index, value, head);
}

template <typename... _Types> bool Reading(std::variant<_Types...> &output, TLVObject &data, const TLVHead &head)
{
    uint32_t index = 0;
    auto endCursor = data.GetCursor() + head.len;
    while (data.GetCursor() < endCursor) {
        TLVHead headItem{};
        if (!data.ReadHead(headItem)) {
            return false;
        }
        if (headItem.tag == static_cast<uint16_t>(TAG::TAG_VARIANT_INDEX)) {
            if (!Reading(index, data, headItem)) {
                return false;
            }
        } else {
            return ReadVariant<decltype(output), _Types...>(data, 0, index, output, headItem);
        }
    }
    return true;
}
} // namespace TLVUtil
} // namespace OHOS
#endif // UDMF_TLV_UTIL_H
