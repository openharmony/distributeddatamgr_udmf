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

#ifndef UDMF_HYPERLINK_TAIHE_H
#define UDMF_HYPERLINK_TAIHE_H

#include "ohos.data.unifiedDataChannel.proj.hpp"
#include "ohos.data.unifiedDataChannel.impl.hpp"
#include "link.h"

namespace taiheUdmf = OHOS::UDMF;

class HyperlinkInnerImpl {
public:
    HyperlinkInnerImpl();

    ::taihe::string GetType();
    ::ohos::data::unifiedDataChannel::ValueType GetValue();
    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> GetDetails();
    void SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details);
    void SetUrl(::taihe::string_view url);
    ::taihe::string GetUrl();
    void SetDescription(::taihe::string_view description);
    ::taihe::string GetDescription();
    int64_t GetInner();

    std::shared_ptr<taiheUdmf::Link> value_;
};
#endif // UDMF_HYPERLINK_TAIHE_H