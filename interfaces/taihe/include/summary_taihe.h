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

#ifndef UDMF_SUMMARY_TAIHE_H
#define UDMF_SUMMARY_TAIHE_H

#include "ohos.data.unifiedDataChannel.proj.hpp"
#include "ohos.data.unifiedDataChannel.impl.hpp"
#include "unified_types.h"

namespace taiheUdmf = OHOS::UDMF;
class SummaryImpl {
public:
    SummaryImpl();

    ::taihe::map<::taihe::string, double> GetSummary();

    double GetTotalSize();

    int64_t GetInner();

    std::shared_ptr<taiheUdmf::Summary> value_;
};


#endif // UDMF_SUMMARY_TAIHE_H