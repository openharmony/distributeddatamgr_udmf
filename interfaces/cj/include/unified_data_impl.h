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

#include "unified_data.h"
#include "unified_record_impl.h"
#include "cj_common_ffi.h"

namespace OHOS {
namespace UDMF {
    using namespace OHOS::UDMF;

    typedef CArrI64 CArrUnifiedRecord;

    class CUnifiedData : public OHOS::FFI::FFIData {
        DECL_TYPE(CUnifiedData, OHOS::FFI::FFIData)
        public:
            CUnifiedData();
            CUnifiedData(UDMF::CUnifiedRecord *record);

            void AddRecord(UDMF::CUnifiedRecord *record);
            CArrUnifiedRecord GetRecords();
            bool HasType(const char *type);
            CArrString GetTypes();

        private:
            std::shared_ptr<UDMF::UnifiedData> unifiedData_;
            std::vector<UDMF::CUnifiedRecord *> records_;
    };

}
} // namespace OHOS::UDMF

#endif