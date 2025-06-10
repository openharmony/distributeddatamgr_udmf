
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

#include "unified_data_impl.h"

#include <cstdlib>
#include <string>
#include <variant>
#include <vector>
#include <map>
#include <iomanip>

#include "cj_common_ffi.h"
#include "ffi_remote_data.h"
#include "unified_data_ffi.h"
#include "unified_record_impl.h"
#include "utils.h"

#include "application_defined_record_napi.h"
#include "audio_napi.h"
#include "file_napi.h"
#include "folder_napi.h"
#include "html_napi.h"
#include "image_napi.h"
#include "link_napi.h"
#include "napi_data_utils.h"
#include "napi_error_utils.h"
#include "plain_text_napi.h"
#include "system_defined_appitem_napi.h"
#include "system_defined_form_napi.h"
#include "system_defined_pixelmap_napi.h"
#include "system_defined_record_napi.h"
#include "text_napi.h"
#include "unified_data.h"
#include "unified_record_napi.h"
#include "video_napi.h"

using namespace OHOS::FFI;
using namespace OHOS::UDMF;

namespace OHOS {
namespace UDMF {

CUnifiedData::CUnifiedData()
{
    unifiedData_ = std::make_shared<UnifiedData>();
}

CUnifiedData::CUnifiedData(sptr<UDMF::CUnifiedRecord> record)
{
    unifiedData_ = std::make_shared<UnifiedData>();

    if (record == nullptr) {
        return;
    }
    unifiedData_->AddRecord(record->GetUnifiedRecord());
    this->records_.push_back(record);
}

void CUnifiedData::AddRecord(sptr<UDMF::CUnifiedRecord> record)
{
    if (record == nullptr) {
        return;
    }
    this->records_.push_back(record);
    unifiedData_->AddRecord(record->GetUnifiedRecord());
}

static CArrUnifiedRecord VectorToArray(std::vector<int64_t> vector)
{
    if (vector.size() == 0) {
        return CArrUnifiedRecord {};
    }
    int64_t *head = static_cast<int64_t*>(malloc(vector.size() * sizeof(int64_t)));
    if (head == nullptr) {
        return CArrUnifiedRecord {};
    }
    for (size_t i = 0; i < vector.size(); i++) {
        head[i] = vector[i];
    }
    CArrUnifiedRecord int64Array = {head, vector.size()};
    return int64Array;
}

CArrUnifiedRecord CUnifiedData::GetRecords()
{
    std::vector<int64_t> recordIds;
    for (auto record : this->records_) {
        if (record == nullptr) {
            break;
        }
        recordIds.push_back(record->GetID());
    }
    return VectorToArray(recordIds);
}

bool CUnifiedData::HasType(const char *type)
{
    return unifiedData_->HasType(type);
}

static CArrString StringVectorToArray(std::vector<std::string> vector)
{
    if (vector.size() == 0) {
        return CArrString {};
    }
    char **head = static_cast<char**>(malloc(vector.size() * sizeof(char*)));
    if (head == nullptr) {
        return CArrString {};
    }
    for (unsigned long i = 0; i < vector.size(); i++) {
        head[i] = Utils::MallocCString(vector[i]);
    }
    CArrString stringArray = {head, vector.size()};
    return stringArray;
}

CArrString CUnifiedData::GetTypes()
{
    std::vector<std::string> types = unifiedData_->GetTypesLabels();
    return StringVectorToArray(types);
}
} // namespace UDMF
} // namespace OHOS
