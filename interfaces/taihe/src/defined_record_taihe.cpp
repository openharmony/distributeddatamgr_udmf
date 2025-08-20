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

#define LOG_TAG "UDMF_DEFINED_RECORD"

#include <dlfcn.h>

#include "defined_record_taihe.h"
#include "interop_js/arkts_esvalue.h"
#include "interop_js/arkts_interop_js_api.h"
#include "logger.h"
#include "system_defined_record_napi.h"
#include "taihe_common_utils.h"
#include "taihe/runtime.hpp"

namespace OHOS {
namespace UDMF {
using CreateInstance = napi_value (*)(napi_env, std::shared_ptr<SystemDefinedRecord>);
SystemDefinedRecordTaihe::SystemDefinedRecordTaihe()
{
    this->value_ = std::make_shared<SystemDefinedRecord>();
}

SystemDefinedRecordTaihe::SystemDefinedRecordTaihe(std::shared_ptr<SystemDefinedRecord> value)
{
    this->value_ = value;
}

::taihe::string SystemDefinedRecordTaihe::GetType()
{
    return ::taihe::string(UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
}

::taiheChannel::ValueType SystemDefinedRecordTaihe::GetValue()
{
    return ConvertValueType(this->value_->GetValue());
}

::taihe::optional<::taihe::map<::taihe::string, ::taiheChannel::DetailsValue>> SystemDefinedRecordTaihe::GetDetails()
{
    return ::taihe::optional<::taihe::map<::taihe::string, ::taiheChannel::DetailsValue>>::make(
        ConvertUDDetailsToUnion(this->value_->GetDetails()));
}

void SystemDefinedRecordTaihe::SetDetails(
    const::taihe::map_view<::taihe::string, ::taiheChannel::DetailsValue> &details)
{
    UDDetails udmfDetails = ConvertUDDetailsToUnion(details);
    this->value_->SetDetails(udmfDetails);
}

int64_t SystemDefinedRecordTaihe::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}

::taiheChannel::SystemDefinedRecordInner CreateSystemDefinedRecord()
{
    return taihe::make_holder<SystemDefinedRecordTaihe, ::taiheChannel::SystemDefinedRecordInner>();
}

::taiheChannel::SystemDefinedRecordInner SystemDefinedRecordTransferStaticImpl(uintptr_t input)
{
    ani_object esValue = reinterpret_cast<ani_object>(input);
    void *nativePtr = nullptr;
    if (!arkts_esvalue_unwrap(taihe::get_env(), esValue, &nativePtr) || nativePtr == nullptr) {
        LOG_ERROR(UDMF_ANI, "unwrap esvalue failed");
        return taihe::make_holder<SystemDefinedRecordTaihe, ::taiheChannel::SystemDefinedRecordInner>();
    }
    auto recordNapi = reinterpret_cast<SystemDefinedRecordNapi *>(nativePtr);
    if (recordNapi == nullptr || recordNapi->value_ == nullptr) {
        LOG_ERROR(UDMF_ANI, "cast SystemDefinedRecord failed");
        return taihe::make_holder<SystemDefinedRecordTaihe, ::taiheChannel::SystemDefinedRecordInner>();
    }
    return taihe::make_holder<SystemDefinedRecordTaihe, ::taiheChannel::SystemDefinedRecordInner>(recordNapi->value_);
}

uintptr_t SystemDefinedRecordTransferDynamicImpl(::taiheChannel::weak::SystemDefinedRecordInner input)
{
    auto recordPtr = input->GetInner();
    auto recordInnerPtr = reinterpret_cast<SystemDefinedRecordTaihe *>(recordPtr);
    if (recordInnerPtr == nullptr) {
        LOG_ERROR(UDMF_ANI, "cast native pointer failed");
        return 0;
    }
    std::shared_ptr<SystemDefinedRecord> systemDefinedRecord = recordInnerPtr->value_;
    recordInnerPtr = nullptr;
    napi_env jsenv;
    if (!arkts_napi_scope_open(taihe::get_env(), &jsenv)) {
        LOG_ERROR(UDMF_ANI, "arkts_napi_scope_open failed");
        return 0;
    }
    auto handle = dlopen(NEWINSTANCE_LIB.c_str(), RTLD_NOW);
    if (handle == nullptr) {
        LOG_ERROR(UDMF_ANI, "dlopen failed");
        arkts_napi_scope_close_n(jsenv, 0, nullptr, nullptr);
        return 0;
    }
    CreateInstance newInstance = reinterpret_cast<CreateInstance>(dlsym(handle, "GetEtsSysRecord"));
    if (newInstance == nullptr) {
        LOG_ERROR(UDMF_ANI, "dlsym get func failed, %{public}s", dlerror());
        arkts_napi_scope_close_n(jsenv, 0, nullptr, nullptr);
        dlclose(handle);
        return 0;
    }
    napi_value instance = newInstance(jsenv, systemDefinedRecord);
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

TH_EXPORT_CPP_API_CreateSystemDefinedRecord(OHOS::UDMF::CreateSystemDefinedRecord);
TH_EXPORT_CPP_API_SystemDefinedRecordTransferStaticImpl(OHOS::UDMF::SystemDefinedRecordTransferStaticImpl);
TH_EXPORT_CPP_API_SystemDefinedRecordTransferDynamicImpl(OHOS::UDMF::SystemDefinedRecordTransferDynamicImpl);