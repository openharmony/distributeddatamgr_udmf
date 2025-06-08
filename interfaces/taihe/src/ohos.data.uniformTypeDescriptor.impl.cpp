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

#define LOG_TAG "UniformTypeDescriptorTaiHe"

#include "ohos.data.uniformTypeDescriptor.impl.hpp"

#include "logger.h"
#include "napi_error_utils.h"
#include "ohos.data.uniformTypeDescriptor.proj.hpp"
#include "stdexcept"
#include "taihe/runtime.hpp"
#include "utd_client.h"

using namespace taihe;
using namespace ohos::data::uniformTypeDescriptor;
using namespace OHOS;
using namespace OHOS::UDMF;

namespace {
static constexpr int PARAMETERSERROR = 401;

string getUniformDataTypeByFilenameExtension(string_view filenameExtension, optional_view<string> belongsTo)
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
            LOG_ERROR(UDMF_ANI, "errorMsg is null!");
            napiError.jsCode = PARAMETERSERROR;
            napiError.message = "Parameter error.";
        }
        set_business_error(napiError.jsCode, napiError.message);
        LOG_ERROR(UDMF_ANI, "get type failed, status:%{public}d, jsCode:%{public}d", status, napiError.jsCode);
        return "";
    }
    return typeId;
}
}  // namespace

TH_EXPORT_CPP_API_getUniformDataTypeByFilenameExtension(getUniformDataTypeByFilenameExtension);