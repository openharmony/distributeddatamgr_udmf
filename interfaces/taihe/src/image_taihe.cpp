/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "image_taihe.h"
#include "taihe_common_utils.h"

ImageInnerImpl::ImageInnerImpl()
{
    this->value_ = std::make_shared<taiheUdmf::Image>();
}

::taihe::string ImageInnerImpl::GetType()
{
    return ::taihe::string(taiheUdmf::UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
}

::ohos::data::unifiedDataChannel::ValueType ImageInnerImpl::GetValue()
{
    return taiheUdmf::ConvertValueType(this->value_->GetValue());
}

::taihe::string ImageInnerImpl::GetUri()
{
    return ::taihe::string(this->value_->GetUri());
}

void ImageInnerImpl::SetUri(::taihe::string_view uri)
{
    std::string uriStr(uri);
    this->value_->SetUri(uriStr);
}

::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> ImageInnerImpl::GetDetails()
{
    return ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>::make(
        taiheUdmf::ConvertUDDetailsToString(this->value_->GetDetails()));
}

void ImageInnerImpl::SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details)
{
    if (details.size() == 0) {
        return;
    }
    auto udmfDetails = taiheUdmf::ConvertUDDetails(details);
    this->value_->SetDetails(udmfDetails);
}

::taihe::string ImageInnerImpl::GetImageUri()
{
    return ::taihe::string(this->value_->GetUri());
}

void ImageInnerImpl::SetImageUri(::taihe::string_view imageUri)
{
    std::string imageUriStr(imageUri);
    this->value_->SetUri(imageUriStr);
}

int64_t ImageInnerImpl::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}

::ohos::data::unifiedDataChannel::ImageInner CreateUnifiedImage()
{
    return taihe::make_holder<ImageInnerImpl, ::ohos::data::unifiedDataChannel::ImageInner>();
}

TH_EXPORT_CPP_API_CreateUnifiedImage(CreateUnifiedImage);