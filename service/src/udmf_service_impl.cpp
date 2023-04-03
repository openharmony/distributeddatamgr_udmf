/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "udmf_service_impl.h"

#include <cstdlib>

#include "iservice_registry.h"

#include "data_manager.h"
#include "logger.h"
#include "preprocess_utils.h"

namespace OHOS {
namespace UDMF {
using FeatureSystem = DistributedData::FeatureSystem;
__attribute__((used)) UdmfServiceImpl::Factory UdmfServiceImpl::factory_;
UdmfServiceImpl::Factory::Factory()
{
    LOG_ERROR(UDMF_SERVICE, "Register udmf creator!");
    FeatureSystem::GetInstance().RegisterCreator("udmf", [this]() {
        if (product_ == nullptr) {
            product_ = std::make_shared<UdmfServiceImpl>();
        }
        return product_;
    });
}

UdmfServiceImpl::Factory::~Factory()
{
    product_ = nullptr;
}

int32_t UdmfServiceImpl::SetData(CustomOption &option, UnifiedData &unifiedData, std::string &key)
{
    LOG_INFO(UDMF_SERVICE, "start");
    return DataManager::GetInstance().SaveData(option, unifiedData, key);
}

int32_t UdmfServiceImpl::GetData(QueryOption &query, UnifiedData &unifiedData)
{
    LOG_INFO(UDMF_SERVICE, "start");
    return DataManager::GetInstance().RetrieveData(query, unifiedData);
}

int32_t UdmfServiceImpl::GetSummary(QueryOption &query, Summary &summary)
{
    LOG_INFO(UDMF_SERVICE, "start");
    return DataManager::GetInstance().GetSummary(query, summary);
}

int32_t UdmfServiceImpl::AddPrivilege(QueryOption &query, Privilege &privilege)
{
    return DataManager::GetInstance().AddPrivilege(query, privilege);
}
} // namespace UDMF
} // namespace OHOS
