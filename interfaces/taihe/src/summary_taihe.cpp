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

#define LOG_TAG "UDMF_SUMMARY"

#include <dlfcn.h>

#include "interop_js/arkts_esvalue.h"
#include "interop_js/arkts_interop_js_api.h"
#include "logger.h"
#include "summary_napi.h"
#include "summary_taihe.h"
#include "taihe_common_utils.h"
#include "taihe/runtime.hpp"

namespace taiheChannel = ohos::data::unifiedDataChannel;
namespace OHOS {
namespace UDMF {
using CreateInstance = napi_value (*)(napi_env, std::shared_ptr<Summary>);
SummaryTaihe::SummaryTaihe()
{
    this->value_ = std::make_shared<Summary>();
}

SummaryTaihe::SummaryTaihe(std::shared_ptr<Summary> value)
{
    this->value_ = value;
}

int64_t SummaryTaihe::GetTotalSize()
{
    return this->value_->totalSize;
}

void SummaryTaihe::SetTotalSize(int64_t totalSize)
{
    if (this->value_ == nullptr) {
        return;
    }
    this->value_->totalSize = totalSize;
}

::taihe::map<::taihe::string, int64_t> SummaryTaihe::GetSummary()
{
    ::taihe::map<::taihe::string, int64_t> summary;
    for (auto &item : this->value_->summary) {
        if (item.first.empty()) {
            continue;
        }
        summary.emplace(::taihe::string(item.first), item.second);
    }
    return summary;
}

void SummaryTaihe::SetSummary(::taihe::map_view<::taihe::string, int64_t> summary)
{
    if (this->value_ == nullptr) {
        return;
    }
    this->value_->summary.clear();
    for (const auto &item : summary) {
        if (item.first.empty()) {
            continue;
        }
        this->value_->summary.emplace(std::string(item.first), item.second);
    }
}

int64_t SummaryTaihe::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}

::taiheChannel::Summary CreateSummary()
{
    return taihe::make_holder<SummaryTaihe, ::taiheChannel::Summary>();
}

::taiheChannel::Summary SummaryTransferStaticImpl(uintptr_t input)
{
    ani_object esValue = reinterpret_cast<ani_object>(input);
    void *nativePtr = nullptr;
    if (!arkts_esvalue_unwrap(taihe::get_env(), esValue, &nativePtr) || nativePtr == nullptr) {
        LOG_ERROR(UDMF_ANI, "unwrap esvalue failed");
        return taihe::make_holder<SummaryTaihe, ::taiheChannel::Summary>();
    }
    auto summaryNapi = reinterpret_cast<OHOS::UDMF::SummaryNapi *>(nativePtr);
    if (summaryNapi == nullptr || summaryNapi->value_ == nullptr) {
        LOG_ERROR(UDMF_ANI, "cast SummaryNapi failed");
        return taihe::make_holder<SummaryTaihe, ::taiheChannel::Summary>();
    }
    return taihe::make_holder<SummaryTaihe, ::taiheChannel::Summary>(summaryNapi->value_);
}

uintptr_t SummaryTransferDynamicImpl(::taiheChannel::Summary const& input)
{
    auto summaryPtr = input->GetInner();
    auto summaryInnerPtr = reinterpret_cast<SummaryTaihe *>(summaryPtr);
    if (summaryInnerPtr == nullptr) {
        LOG_ERROR(UDMF_ANI, "cast native pointer failed");
        return 0;
    }
    std::shared_ptr<Summary> summary = summaryInnerPtr->value_;
    summaryInnerPtr = nullptr;
    napi_env jsenv;
    if (!arkts_napi_scope_open(taihe::get_env(), &jsenv)) {
        LOG_ERROR(UDMF_ANI, "arkts_napi_scope_open failed");
        return 0;
    }
    auto handle = dlopen(NEW_INSTANCE_LIB.c_str(), RTLD_NOW);
    if (handle == nullptr) {
        LOG_ERROR(UDMF_ANI, "dlopen failed");
        arkts_napi_scope_close_n(jsenv, 0, nullptr, nullptr);
        return 0;
    }
    CreateInstance newInstance = reinterpret_cast<CreateInstance>(dlsym(handle, "GetEtsSummary"));
    if (newInstance == nullptr) {
        LOG_ERROR(UDMF_ANI, "dlsym get func failed, %{public}s", dlerror());
        arkts_napi_scope_close_n(jsenv, 0, nullptr, nullptr);
        dlclose(handle);
        return 0;
    }
    napi_value instance = newInstance(jsenv, summary);
    dlclose(handle);
    if (instance == nullptr) {
        LOG_ERROR(UDMF_ANI, "instance is nullptr");
        arkts_napi_scope_close_n(jsenv, 0, nullptr, nullptr);
        return 0;
    }
    uintptr_t result = 0;
    arkts_napi_scope_close_n(jsenv, 1, &instance, reinterpret_cast<ani_ref*>(&result));
    return result;
}
} // namespace UDMF
} // namespace OHOS

TH_EXPORT_CPP_API_CreateSummary(OHOS::UDMF::CreateSummary);
TH_EXPORT_CPP_API_SummaryTransferStaticImpl(OHOS::UDMF::SummaryTransferStaticImpl);
TH_EXPORT_CPP_API_SummaryTransferDynamicImpl(OHOS::UDMF::SummaryTransferDynamicImpl);