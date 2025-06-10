/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef UDMF_UNIFIED_DATA_IMPL_H
#define UDMF_UNIFIED_DATA_IMPL_H

#include <memory>

#include "cj_common_ffi.h"
#include "unified_data.h"
#include "unified_record_impl.h"

namespace OHOS {
namespace UDMF {
using namespace OHOS::UDMF;

typedef CArrI64 CArrUnifiedRecord;

struct CParameters {
    int8_t valueType;
    char *key;
    void *value;
    int64_t size;
};

struct CArrParameters {
    CParameters *head;
    int64_t size;
};

struct CUnifiedDataProperties {
    CArrParameters extras;
    char *tag;
    int64_t timestamp;
    int32_t shareOptions;
};

class CUnifiedData : public OHOS::FFI::FFIData {
    DECL_TYPE(CUnifiedData, OHOS::FFI::FFIData)
public:
    CUnifiedData();
    CUnifiedData(sptr<UDMF::CUnifiedRecord> record);

    void AddRecord(sptr<UDMF::CUnifiedRecord> record);
    CArrUnifiedRecord GetRecords();
    bool HasType(const char *type);
    CArrString GetTypes();
    std::shared_ptr<UDMF::UnifiedData> unifiedData_;
            
private:
    std::vector<sptr<UDMF::CUnifiedRecord>> records_;
};
} // namespace UDMF
} // namespace OHOS

#endif