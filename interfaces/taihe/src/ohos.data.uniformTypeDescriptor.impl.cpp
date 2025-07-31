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

#include "napi_error_utils.h"
#include "ohos.data.uniformTypeDescriptor.impl.hpp"
#include "ohos.data.uniformTypeDescriptor.proj.hpp"
#include "stdexcept"
#include "taihe_common_utils.h"
#include "taihe/runtime.hpp"
#include "utd_client.h"

using namespace taihe;
using namespace ohos::data::uniformTypeDescriptor;

namespace OHOS {
namespace UDMF {

::taihe::string GetUniformDataTypeByFilenameExtension(const ::taihe::string_view &filenameExtension,
    ::taihe::optional_view<::taihe::string> belongsTo)
{
    std::string fileName(filenameExtension);
    std::string typeId;
    auto status = E_OK;
    if (!belongsTo.has_value() || belongsTo.value().empty()) {
        status = UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(fileName, typeId);
    } else {
        std::string belongs(belongsTo.value());
        status = UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(fileName, typeId, belongs);
    }
    if (status != E_OK) {
        auto errorMsg = GetErrorCode(status);
        NapiErrorCode napiError;
        if (errorMsg.has_value()) {
            napiError = errorMsg.value();
        } else {
            napiError.jsCode = PARAMETERSERROR;
            napiError.message = "Parameter error.";
        }
        set_business_error(napiError.jsCode, napiError.message);
        return "";
    }
    return typeId;
}
} // namespace UDMF
} // namespace OHOS

TH_EXPORT_CPP_API_getUniformDataTypeByFilenameExtension(OHOS::UDMF::GetUniformDataTypeByFilenameExtension);