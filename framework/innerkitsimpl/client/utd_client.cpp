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
#include "logger.h"
#include "preset_type_descriptors.h"

namespace OHOS {
namespace UDMF {
UtdClient::UtdClient()
{
    LOG_INFO(UDMF_CLIENT, "construct UtdClient sucess.");
}

UtdClient::~UtdClient()
{
}

UtdClient &UtdClient::GetInstance()
{
    static auto instance = new UtdClient();
    return *instance;
}

Status UtdClient::GetTypeDescriptor(const std::string &typeId, std::shared_ptr<TypeDescriptor> &descriptor)
{
    descriptors_ = PresetTypeDescriptors::GetInstance().GetTypeDescriptors();
    for (const auto &utdType : descriptors_) {
        if (utdType.GetTypeId() == typeId) {
            descriptor = std::make_shared<TypeDescriptor>(utdType);
            LOG_DEBUG(UDMF_CLIENT, "get descriptor success. %{public}s ", typeId.c_str());
        }
    }

    return Status::E_OK;
}
} // namespace UDMF
} // namespace OHOS