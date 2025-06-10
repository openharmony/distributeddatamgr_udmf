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

#ifndef UDMF_FILE_TAIHE_H
#define UDMF_FILE_TAIHE_H

#include "ohos.data.unifiedDataChannel.proj.hpp"
#include "ohos.data.unifiedDataChannel.impl.hpp"
#include "file.h"

namespace taiheUdmf = OHOS::UDMF;

class FileImpl {
public:
    FileImpl();

    ::taihe::string GetType();

    ::ohos::data::unifiedDataChannel::ValueType GetValue();
    ::taihe::string GetUri();

    void SetUri(::taihe::string_view uri);

    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> GetDetails();

    void SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details);

    int64_t GetInner();

    std::shared_ptr<taiheUdmf::File> value_;
};

#endif // UDMF_FILE_TAIHE_H