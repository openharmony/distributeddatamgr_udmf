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

#include "video_taihe.h"
#include "taihe_common_utils.h"
namespace OHOS {
namespace UDMF {
VideoTaihe::VideoTaihe()
{
    this->value_ = std::make_shared<Video>();
}

::taihe::string VideoTaihe::GetType()
{
    return ::taihe::string(UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
}

::taiheChannel::ValueType VideoTaihe::GetValue()
{
    return ConvertValueType(this->value_->GetValue());
}

::taihe::string VideoTaihe::GetUri()
{
    return ::taihe::string(this->value_->GetUri());
}

void VideoTaihe::SetUri(::taihe::string_view uri)
{
    std::string uriStr(uri);
    this->value_->SetUri(uriStr);
}

::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> VideoTaihe::GetDetails()
{
    return ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>::make(
        ConvertUDDetailsToString(this->value_->GetDetails()));
}

void VideoTaihe::SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details)
{
    if (details.size() == 0) {
        return;
    }
    auto udmfDetails = ConvertUDDetails(details);
    this->value_->SetDetails(udmfDetails);
}

::taihe::string VideoTaihe::GetVideoUri()
{
    return ::taihe::string(this->value_->GetUri());
}

void VideoTaihe::SetVideoUri(::taihe::string_view videoUri)
{
    std::string videoUriStr(videoUri);
    this->value_->SetUri(videoUriStr);
}

int64_t VideoTaihe::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}
} // namespace UDMF
} // namespace OHOS

::taiheChannel::VideoInner CreateUnifiedVideo()
{
    return taihe::make_holder<OHOS::UDMF::VideoTaihe, ::taiheChannel::VideoInner>();
}

TH_EXPORT_CPP_API_CreateUnifiedVideo(CreateUnifiedVideo);