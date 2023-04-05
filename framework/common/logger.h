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

#ifndef UDMF_LOGGER_H
#define UDMF_LOGGER_H
#include <memory>

#include "hilog/log.h"

namespace OHOS {
namespace UDMF {
// param of log interface, such as UDMF_LABEL.
enum UdmfSubModule {
    UDMF_FRAMEWORK = 0, // for framework core module
    UDMF_KITS_INNER,    // for udmf innerkits module
    UDMF_KITS_NAPI,     // for udmf napi kits module
    UDMF_CLIENT,        // for udmf client module
    UDMF_SERVICE,       // for udmf service module
    UDMF_TEST,          // for udmf test module
};

// 0xD001600: subsystem:distributeddatamgr module:udmf, 8 bits reserved.
static constexpr unsigned int BASE_UDMF_DOMAIN_ID = 0xD001600;

enum UDMFDomainId {
    UDMF_FRAMEWORK_DOMAIN = BASE_UDMF_DOMAIN_ID + UDMF_FRAMEWORK,
    UDMF_KITS_INNER_DOMAIN,
    UDMF_KITS_NAPI_DOMAIN,
    UDMF_CLIENT_DOMAIN,
    UDMF_SERVICE_DOMAIN,
    UDMF_TEST_DOMAIN,
};

static constexpr OHOS::HiviewDFX::HiLogLabel UDMF_LABEL[UDMF_TEST + 1] = {
    { LOG_CORE, UDMF_FRAMEWORK_DOMAIN, "UDMF_FWK" },
    { LOG_CORE, UDMF_KITS_INNER_DOMAIN, "UDMF_KITS_INNER" },
    { LOG_CORE, UDMF_KITS_NAPI_DOMAIN, "UDMF_KITS_NAPI" },
    { LOG_CORE, UDMF_CLIENT_DOMAIN, "UDMF_CLIENT" },
    { LOG_CORE, UDMF_SERVICE_DOMAIN, "UDMF_SERVICE" },
    { LOG_CORE, UDMF_TEST_DOMAIN, "UDMF_TEST" }
};

// In order to improve performance, do not check the module range.
// Besides, make sure module is less than UDMF_SERVICE.
#define LOG_FATAL(module, fmt, ...)      \
    (void)OHOS::HiviewDFX::HiLog::Fatal( \
        UDMF_LABEL[module], "%{public}d: %{public}s " fmt " ", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define LOG_ERROR(module, fmt, ...)      \
    (void)OHOS::HiviewDFX::HiLog::Error( \
        UDMF_LABEL[module], "%{public}d: %{public}s " fmt " ", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define LOG_WARN(module, fmt, ...)      \
    (void)OHOS::HiviewDFX::HiLog::Warn( \
        UDMF_LABEL[module], "%{public}d: %{public}s " fmt " ", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define LOG_INFO(module, fmt, ...)      \
    (void)OHOS::HiviewDFX::HiLog::Info( \
        UDMF_LABEL[module], "%{public}d: %{public}s " fmt " ", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define LOG_DEBUG(module, fmt, ...)      \
    (void)OHOS::HiviewDFX::HiLog::Debug( \
        UDMF_LABEL[module], "%{public}d: %{public}s " fmt " ", __LINE__, __FUNCTION__, ##__VA_ARGS__)
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_LOGGER_H
