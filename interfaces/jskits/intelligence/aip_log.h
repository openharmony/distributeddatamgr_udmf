/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef AIP_LOG_H
#define AIP_LOG_H

#include <cstdint>
#include "hilog/log.h"

#ifndef LOG_DOMAIN
#define LOG_DOMAIN 0xD001660
#endif

namespace OHOS {
namespace DataIntelligence {
#ifndef AIP_FUNC_FMT
#define AIP_FUNC_FMT "in %{public}s, "
#endif

#ifndef AIP_FUNC_INFO
#define AIP_FUNC_INFO __FUNCTION__
#endif

#define AIP_HILOGD(fmt, ...)                                                   \
    do {                                                                       \
        HILOG_DEBUG(LOG_CORE, AIP_FUNC_FMT fmt, AIP_FUNC_INFO, ##__VA_ARGS__); \
    } while (0)

#define AIP_HILOGI(fmt, ...)                                                  \
    do {                                                                      \
        HILOG_INFO(LOG_CORE, AIP_FUNC_FMT fmt, AIP_FUNC_INFO, ##__VA_ARGS__); \
    } while (0)

#define AIP_HILOGW(fmt, ...)                                                  \
    do {                                                                      \
        HILOG_WARN(LOG_CORE, AIP_FUNC_FMT fmt, AIP_FUNC_INFO, ##__VA_ARGS__); \
    } while (0)

#define AIP_HILOGE(fmt, ...)                                                   \
    do {                                                                       \
        HILOG_ERROR(LOG_CORE, AIP_FUNC_FMT fmt, AIP_FUNC_INFO, ##__VA_ARGS__); \
    } while (0)

#define AIP_HILOGF(fmt, ...)                                                   \
    do {                                                                       \
        HILOG_FATAL(LOG_CORE, AIP_FUNC_FMT fmt, AIP_FUNC_INFO, ##__VA_ARGS__); \
    } while (0)
} // namespace DataIntelligence
} // namespace OHOS
#endif // AIP_LOG_H
