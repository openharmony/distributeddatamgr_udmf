/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "unified_data_parameter_parse.h"

#include <cinttypes>

#include "array_wrapper.h"
#include "bool_wrapper.h"
#include "byte_wrapper.h"
#include "double_wrapper.h"
#include "int_wrapper.h"
#include "long_wrapper.h"
#include "string_wrapper.h"
#include "udmf_log.h"
#include "utils.h"
#include "want_params_wrapper.h"

namespace OHOS {
namespace UDMF {

const int8_t I32_TYPE = 0;
const int8_t I64_TYPE = 1;
const int8_t DOUBLE_TYPE = 2;
const int8_t BOOL_TYPE = 3;
const int8_t STR_TYPE = 4;
const int8_t UINT8_ARRAY_TYPE = 5;

constexpr int32_t NO_ERROR = 0;
constexpr int32_t ERR_UDMF_FAILED = -1;
constexpr int32_t ERR_NO_MEMORY = -2;

const int32_t NONE_VALUE = 1;
using WantParams = OHOS::AAFwk::WantParams;

void ClearParametersPtr(CParameters **ptr, int count, bool isKey)
{
    CParameters *p = *ptr;
    for (int i = 0; i < count; i++) {
        free(p[i].key);
        free(p[i].value);
        p[i].key = nullptr;
        p[i].value = nullptr;
    }
    if (!isKey) {
        free(p[count].key);
        p[count].key = nullptr;
    }
    free(*ptr);
    *ptr = nullptr;
}

// WantParameters -> CArrParameters
int32_t InnerWrapWantParamsString(WantParams &wantParams, CParameters *p)
{
    auto value = wantParams.GetParam(p->key);
    AAFwk::IString *ao = AAFwk::IString::Query(value);
    if (ao == nullptr) {
        LOGE("No value");
        return NONE_VALUE;
    }
    std::string natValue = OHOS::AAFwk::String::Unbox(ao);
    p->value = Utils::MallocCString(natValue);
    p->size = static_cast<int64_t>(natValue.length()) + 1;
    p->valueType = STR_TYPE;
    return NO_ERROR;
}

template <class TBase, class T, class NativeT>
int32_t InnerWrapWantParamsT(WantParams &wantParams, CParameters *p)
{
    auto value = wantParams.GetParam(p->key);
    TBase *ao = TBase::Query(value);
    if (ao == nullptr) {
        LOGE("No value");
        return NONE_VALUE;
    }
    NativeT natValue = T::Unbox(ao);
    NativeT *ptr = static_cast<NativeT*>(malloc(sizeof(NativeT)));
    if (ptr == nullptr) {
        return ERR_NO_MEMORY;
    }
    *ptr = natValue;
    p->value = static_cast<void*>(ptr);
    p->size = sizeof(NativeT);
    return NO_ERROR;
}

template <class TBase, class T, class NativeT>
int32_t InnerWrapWantParamsArrayT(sptr<AAFwk::IArray> &ao, CParameters*p)
{
    long size = 0;
    if (ao->GetLength(size) != ERR_OK) {
        LOGE("fail to get length");
        return ERR_UDMF_FAILED;
    }
    if (size == 0) {
        return ERR_UDMF_FAILED;
    }
    NativeT *arrP = static_cast<NativeT*>(malloc(sizeof(NativeT) * size));
    if (arrP == nullptr) {
        LOGE("fail to malloc");
        return ERR_NO_MEMORY;
    }
    for (long i = 0; i < size; i++) {
        sptr<AAFwk::IInterface> iface = nullptr;
        if (ao->Get(i, iface) == ERR_OK) {
            TBase *iValue = TBase::Query(iface);
            if (iValue != nullptr) {
                arrP[i] = T::Unbox(iValue);
            }
        }
    }
    p->size = size;
    p->value = static_cast<void*>(arrP);
    return NO_ERROR;
}

bool InnerSetWantParamsArrayByte(const std::string &key, const std::vector<uint8_t> &value,
    AAFwk::WantParams &wantParams)
{
    size_t size = value.size();
    sptr<AAFwk::IArray> ao = new (std::nothrow) AAFwk::Array(size, AAFwk::g_IID_IByte);
    if (ao != nullptr) {
        for (size_t i = 0; i < size; i++) {
            ao->Set(i, AAFwk::Integer::Box(value[i]));
        }
        wantParams.SetParam(key, ao);
        return true;
    } else {
        return false;
    }
}

int32_t InnerWrapWantParamsArray(WantParams &wantParams, sptr<AAFwk::IArray> &ao, CParameters *p)
{
    LOGI("%{public}s called, key=%{public}s", __func__, p->key);
    if (AAFwk::Array::IsByteArray(ao)) {
        p->valueType = UINT8_ARRAY_TYPE;
        return InnerWrapWantParamsArrayT<AAFwk::IByte, AAFwk::Byte, uint8_t>(ao, p);
    }
    return ERR_UDMF_FAILED;
}

void SetDataParameters(CArrParameters parameters, WantParams &wantP)
{
    for (int i = 0; i < parameters.size; i++) {
        auto head = parameters.head + i;
        auto key = std::string(head->key);
        if (head->valueType == I32_TYPE) {
            wantP.SetParam(key, OHOS::AAFwk::Integer::Box(*static_cast<int32_t*>(head->value)));
        } else if (head->valueType == I64_TYPE) {
            wantP.SetParam(key, OHOS::AAFwk::Integer::Box(*static_cast<int64_t*>(head->value)));
        } else if (head->valueType == DOUBLE_TYPE) {
            wantP.SetParam(key, OHOS::AAFwk::Double::Box(*static_cast<double*>(head->value)));
        } else if (head->valueType == STR_TYPE) {
            wantP.SetParam(key, OHOS::AAFwk::String::Box(std::string(static_cast<char*>(head->value))));
        } else if (head->valueType == BOOL_TYPE) {
            wantP.SetParam(key, OHOS::AAFwk::Boolean::Box(*static_cast<bool*>(head->value)));
        } else if (head->valueType == UINT8_ARRAY_TYPE) {
            uint8_t *intArr = static_cast<uint8_t*>(head->value);
            std::vector<uint8_t> intVec(intArr, intArr + head->size);
            InnerSetWantParamsArrayByte(key, intVec, wantP);
        } else {
            LOGE("wrong type!");
        }
    }
}

void ParseParameters(WantParams &wantP, CArrParameters &parameters, int32_t &code)
{
    if (code != NO_ERROR) {
        return;
    }
    std::map<std::string, sptr<OHOS::AAFwk::IInterface>> paramsMap = wantP.GetParams();
    int count = 0;
    auto size = static_cast<int64_t>(paramsMap.size());
    if (size == 0) {
        return;
    }
    parameters.head = static_cast<CParameters*>(malloc(sizeof(CParameters) * size));
    if (parameters.head == nullptr) {
        code = ERR_NO_MEMORY;
        return;
    }
    parameters.size = size;
    for (auto iter = paramsMap.begin(); iter != paramsMap.end(); iter++) {
        auto ptr = parameters.head + count;
        ptr->key = Utils::MallocCString(iter->first);
        if (ptr->key == nullptr) {
            code = ERR_NO_MEMORY;
            return ClearParametersPtr(&parameters.head, count, true);
        }
        ptr->value = nullptr;
        ptr->size = 0;
        if (AAFwk::IString::Query(iter->second) != nullptr) {
            code = InnerWrapWantParamsString(wantP, ptr);
        } else if (AAFwk::IBoolean::Query(iter->second) != nullptr) {
            ptr->valueType = BOOL_TYPE;
            code = InnerWrapWantParamsT<AAFwk::IBoolean, AAFwk::Boolean, bool>(wantP, ptr);
        } else if (AAFwk::IInteger::Query(iter->second) != nullptr) {
            ptr->valueType = I32_TYPE;
            code = InnerWrapWantParamsT<AAFwk::IInteger, AAFwk::Integer, int>(wantP, ptr);
        } else if (AAFwk::ILong::Query(iter->second) != nullptr) {
            ptr->valueType = I64_TYPE;
            code = InnerWrapWantParamsT<AAFwk::ILong, AAFwk::Long, long>(wantP, ptr);
        } else if (AAFwk::IDouble::Query(iter->second) != nullptr) {
            ptr->valueType = DOUBLE_TYPE;
            code = InnerWrapWantParamsT<AAFwk::IDouble, AAFwk::Double, double>(wantP, ptr);
        } else if (AAFwk::IArray::Query(iter->second) != nullptr) {
            AAFwk::IArray *ao = AAFwk::IArray::Query(iter->second);
            sptr<AAFwk::IArray> array(ao);
            code = InnerWrapWantParamsArray(wantP, array, ptr);
        }
        if (code == ERR_NO_MEMORY || code == ERR_UDMF_FAILED) {
            return ClearParametersPtr(&parameters.head, count, false);
        }
        count++;
    }
}
} // namespace UDMF
} // namespace OHOS