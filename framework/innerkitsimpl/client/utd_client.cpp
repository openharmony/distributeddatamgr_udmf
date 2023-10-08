/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "utd_client.h"

#include "error_code.h"
#include "logger.h"
#include "udmf_service_client.h"
#include "utd_config.h"

namespace OHOS {
namespace UDMF {
UtdClient::UtdClient()
{
    InitDescriptor();
}

UtdClient::~UtdClient()
{
}

UtdClient &UtdClient::GetInstance()
{
    static auto instance_ = new UtdClient();
    return *instance_;
}

void UtdClient::InitDescriptor()
{
    descriptors_ = UtdConfig::GetInstance().GetDescriptorsFromConfig();
}

Status UtdClient::GetTypeDescriptor(const std::string &typeId, std::shared_ptr<TypeDescriptor> &descriptor)
{
    auto iter = descriptors_.find(typeId);
    if (iter != descriptors_.end()) {
        descriptor = std::make_shared<TypeDescriptor>(iter->second);
        LOG_DEBUG(UDMF_CLIENT, "got descriptor success. %{public}s ", typeId.c_str());
        return Status::E_OK;
    }
    return Status::E_OK;
}
} // namespace UDMF
} // namespace OHOS