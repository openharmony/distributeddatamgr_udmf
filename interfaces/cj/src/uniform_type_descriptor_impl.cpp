
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


#include "uniform_type_descriptor_impl.h"
#include "cj_common_ffi.h"

#include <string>
#include <vector>
#include "utd_client.h"
#include "type_descriptor_impl.h"

#include "ffi_remote_data.h"

#include "utils.h"

using namespace OHOS::FFI;
using namespace OHOS::UDMF;

namespace OHOS {
namespace UDMF {
    int64_t GetTypeDescriptor(const char *typeId)
    {
        std::shared_ptr<TypeDescriptor> descriptor;
        UtdClient::GetInstance().GetTypeDescriptor(typeId, descriptor);
        if (descriptor == nullptr) {
            return -1;
        }
        auto nativeCJTypeDescriptor = FFIData::Create<CTypeDescriptor>(descriptor);
        if (nativeCJTypeDescriptor == nullptr) {
            return -1;
        }
        return nativeCJTypeDescriptor->GetID();
    }

    
    char * GetUniformDataTypeByFilenameExtension(const char *cFilenameExtension, const char *cBelongsTo)
    {
        std::string belongsTo = cBelongsTo;
        std::string typeId;
        auto status = E_OK;
        if (belongsTo.empty()) {
            LOGI("call GetUniformDataTypeByFilenameExtension with not cBelongsTo")
            status = UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(cFilenameExtension, typeId);
        } else {
            LOGI("call GetUniformDataTypeByFilenameExtension with cBelongsTo")
            status = UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(cFilenameExtension, typeId, belongsTo);
        }
        if(status != E_OK){
            LOGE("invalid arguments!")
            return nullptr;
        }
        if (!typeId.empty()) {
            return Utils::MallocCString(typeId);
        } else {
            return nullptr;
        }

    }

    char * GetUniformDataTypeByMIMEType(const char *cMimeType, const char *cBelongsTo)
    {
        std::string belongsTo = cBelongsTo;
        std::string typeId;
        auto status = E_OK;
        if (belongsTo.empty()) {
            LOGI("call GetUniformDataTypeByMIMEType with not cBelongsTo")
            status = UtdClient::GetInstance().GetUniformDataTypeByMIMEType(cMimeType, typeId);
        } else {
            LOGI("call GetUniformDataTypeByMIMEType with cBelongsTo")
            status = UtdClient::GetInstance().GetUniformDataTypeByMIMEType(cMimeType, typeId, belongsTo);
        }
        if(status != E_OK){
            LOGE("invalid arguments!")
            return nullptr;
        }
        if (!typeId.empty()) {
            return Utils::MallocCString(typeId);
        } else {
            return nullptr;
        }
    }

}
}
