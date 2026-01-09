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
#include "tlv_util.h"

#include "logger.h"

namespace OHOS {
namespace TLVUtil {
template <> size_t CountBufferSize(const std::nullptr_t &input, TLVObject &data)
{
    return sizeof(TLVHead);
}

template <> bool Writing(const std::nullptr_t &input, TLVObject &data, TAG tag)
{
    return true;
}

template <> bool Reading(std::nullptr_t &output, TLVObject &data, const TLVHead &head)
{
    return true;
}

template <> size_t CountBufferSize(const std::monostate &input, TLVObject &data)
{
    return sizeof(TLVHead);
}

template <> bool Writing(const std::monostate &input, TLVObject &data, TAG tag)
{
    return true;
}

template <> bool Reading(std::monostate &output, TLVObject &data, const TLVHead &head)
{
    return true;
}

template <> size_t CountBufferSize(const std::string &input, TLVObject &data)
{
    return sizeof(TLVHead);
}

template <> bool Writing(const std::string &input, TLVObject &data, TAG tag)
{
    return true;
}

template <> bool Reading(std::string &output, TLVObject &data, const TLVHead &head)
{
    return true;
}

template <> size_t CountBufferSize(const std::vector<uint8_t> &input, TLVObject &data)
{
    return sizeof(TLVHead);
}

template <> bool Writing(const std::vector<uint8_t> &input, TLVObject &data, TAG tag)
{
    return true;
}

template <> bool Reading(std::vector<uint8_t> &output, TLVObject &data, const TLVHead &head)
{
    return true;
}

template <> size_t CountBufferSize(const UDType &input, TLVObject &data)
{
    return sizeof(TLVHead);
}

template <> bool Writing(const UDType &input, TLVObject &data, TAG tag)
{
    return true;
}

template <> bool Reading(UDType &output, TLVObject &data, const TLVHead &head)
{
    return true;
}

template <> size_t CountBufferSize(const DataStatus &input, TLVObject &data)
{
    return sizeof(TLVHead);
}

template <> bool Writing(const DataStatus &input, TLVObject &data, TAG tag)
{
    return true;
}

template <> bool Reading(DataStatus &output, TLVObject &data, const TLVHead &head)
{
    return true;
}

template <> size_t CountBufferSize(const Object &input, TLVObject &data)
{
    return sizeof(TLVHead);
}

template <> bool Writing(const Object &input, TLVObject &data, TAG tag)
{
    return true;
}
template <> bool Reading(Object &output, TLVObject &data, const TLVHead &head)
{
    return true;
}

bool CheckAndAdd(size_t &currentSize, size_t partSize)
{
    return true;
}

template <> size_t CountBufferSize(const UnifiedKey &input, TLVObject &data)
{
    return sizeof(TLVHead);
}
template <> bool Writing(const UnifiedKey &input, TLVObject &data, TAG tag)
{
    return true;
}

template <> bool Reading(UnifiedKey &output, TLVObject &data, const TLVHead &head)
{
    return true;
}

template <> size_t CountBufferSize(const UnifiedData &input, TLVObject &data)
{
    return sizeof(TLVHead);
}

template <> bool Writing(const UnifiedData &input, TLVObject &data, TAG tag)
{
    if (input.dataId_ == 0) {
        return false;
    }
    return true;
}

template <> bool Reading(UnifiedData &output, TLVObject &data, const TLVHead &head)
{
    return false;
}

template <> size_t CountBufferSize(const UnifiedRecord &input, TLVObject &data)
{
    return sizeof(TLVHead);
}

template <> bool Writing(const UnifiedRecord &input, TLVObject &data, TAG tag)
{
    return true;
}

template <> bool Reading(UnifiedRecord &output, TLVObject &data, const TLVHead &head)
{
    return true;
}

template <> size_t CountBufferSize(const Runtime &input, TLVObject &data)
{
    return sizeof(TLVHead);
}

template <> bool Writing(const Runtime &input, TLVObject &data, TAG tag)
{
    return true;
}

template <> bool Reading(Runtime &output, TLVObject &data, const TLVHead &head)
{
    return true;
}

template <> size_t CountBufferSize(const Privilege &input, TLVObject &data)
{
    return sizeof(TLVHead);
}

template <> bool Writing(const Privilege &input, TLVObject &data, TAG tag)
{
    return true;
}

template <> bool Reading(Privilege &output, TLVObject &data, const TLVHead &head)
{
    return true;
}

template <> size_t CountBufferSize(const std::shared_ptr<OHOS::Media::PixelMap> &input, TLVObject &data)
{
    return sizeof(TLVHead);
}

template <> bool Writing(const std::shared_ptr<OHOS::Media::PixelMap> &input, TLVObject &data, TAG tag)
{
    return true;
}

template <> bool Reading(std::shared_ptr<OHOS::Media::PixelMap> &output, TLVObject &data, const TLVHead &head)
{
    return true;
}

template <> size_t CountBufferSize(const std::shared_ptr<OHOS::AAFwk::Want> &input, TLVObject &data)
{
    return sizeof(TLVHead);
}

template <> bool Writing(const std::shared_ptr<OHOS::AAFwk::Want> &input, TLVObject &data, TAG tag)
{
    return true;
}


template <> bool Reading(std::shared_ptr<OHOS::AAFwk::Want> &output, TLVObject &data, const TLVHead &head)
{
    return true;
}

template <> size_t API_EXPORT CountBufferSize(const DataLoadInfo &input, TLVObject &data)
{
    return sizeof(TLVHead);
}

template <> bool API_EXPORT Writing(const DataLoadInfo &input, TLVObject &data, TAG tag)
{
    return true;
}

template <> bool API_EXPORT Reading(DataLoadInfo &output, TLVObject &data, const TLVHead &head)
{
    return true;
}
} // namespace TLVUtil
} // namespace OHOS
