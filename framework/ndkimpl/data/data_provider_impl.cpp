/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#define LOG_TAG "DataProviderImpl"
#include "data_provider_impl.h"
#include "unified_meta.h"
#include "udmf_capi_common.h"
#include "logger.h"

namespace OHOS {
namespace UDMF {
void DataProviderImpl::SetInnerProvider(OH_UdmfRecordProvider* provider)
{
    innerProvider_ = provider;
}

OH_UdmfRecordProvider* DataProviderImpl::GetInnerProvider()
{
    return innerProvider_;
}

ValueType DataProviderImpl::GetValueByType(const std::string &utdId)
{
    if (utdId.empty()) {
        return std::monostate();
    }
    if (innerProvider_ == nullptr) {
        LOG_ERROR(UDMF_CAPI, innerProvider_ is null!);
        return std::monostate();
    }
    auto value = (innerProvider_->callback)(innerProvider_->context, utdId.c_str());
    if (value == nullptr) {
        LOG_ERROR(
            UDMF_CAPI, "get empty data when execute custom callback function, utdId is %{public}s", utdId.c_str());
        return std::monostate();
    }
    UdsObject* object = static_cast<UdsObject *>(value);
    if (IsInvalidUdsObjectByType(object, static_cast<UDType>(UtdUtils::GetUtdEnumFromUtdId(utdId)))) {
        LOG_ERROR(UDMF_CAPI, "data type mismatch");
        return std::monostate();
    }
    std::shared_ptr<OHOS::UDMF::Object> obj = std::move(object->obj);
    delete object;
    return obj;
}

} // namespace UDMF
} // namespace OHOS