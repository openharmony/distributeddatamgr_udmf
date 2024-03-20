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
static inline OHOS::HiviewDFX::HiLogLabel LogLabel()
{
    return { LOG_CORE, 0xD001656, "UDMF" };
}

// In order to improve performance, do not check the module range.
// Besides, make sure module is less than UDMF_SERVICE.
#define LOG_FATAL(module, fmt, ...)                                                 \
    do {                                                                            \
        auto lable = LogLabel();                                                    \
        if (!HiLogIsLoggable(lable.domain, lable.tag, LogLevel::LOG_FATAL)) {       \
            break;                                                                  \
        }                                                                           \
        ((void)HILOG_IMPL(lable.type, LogLevel::LOG_FATAL, lable.domain, lable.tag, \
                          LOG_TAG ":%{public}s " fmt, __FUNCTION__, ##__VA_ARGS__)); \
    } while (0)

#define LOG_ERROR(module, fmt, ...)                                                 \
    do {                                                                            \
        auto lable = LogLabel();                                                    \
        if (!HiLogIsLoggable(lable.domain, lable.tag, LogLevel::LOG_ERROR)) {       \
            break;                                                                  \
        }                                                                           \
        ((void)HILOG_IMPL(lable.type, LogLevel::LOG_ERROR, lable.domain, lable.tag, \
                          LOG_TAG "::%{public}s " fmt, __FUNCTION__, ##__VA_ARGS__)); \
    } while (0)

#define LOG_WARN(module, fmt, ...)                                                  \
    do {                                                                            \
        auto lable = LogLabel();                                                    \
        if (!HiLogIsLoggable(lable.domain, lable.tag, LogLevel::LOG_WARN)) {        \
            break;                                                                  \
        }                                                                           \
        ((void)HILOG_IMPL(lable.type, LogLevel::LOG_WARN, lable.domain, lable.tag,  \
                          LOG_TAG "::%{public}s " fmt, __FUNCTION__, ##__VA_ARGS__)); \
    } while (0)

#define LOG_INFO(module, fmt, ...)                                                  \
    do {                                                                            \
        auto lable = LogLabel();                                                    \
        if (!HiLogIsLoggable(lable.domain, lable.tag, LogLevel::LOG_INFO)) {        \
            break;                                                                  \
        }                                                                           \
        ((void)HILOG_IMPL(lable.type, LogLevel::LOG_INFO, lable.domain, lable.tag,  \
                          LOG_TAG "::%{public}s " fmt, __FUNCTION__, ##__VA_ARGS__)); \
    } while (0)

#define LOG_DEBUG(module, fmt, ...)                                                 \
    do {                                                                            \
        auto lable = LogLabel();                                                    \
        if (!HiLogIsLoggable(lable.domain, lable.tag, LogLevel::LOG_DEBUG)) {       \
            break;                                                                  \
        }                                                                           \
        ((void)HILOG_IMPL(lable.type, LogLevel::LOG_DEBUG, lable.domain, lable.tag, \
                          LOG_TAG "::%{public}s " fmt, __FUNCTION__, ##__VA_ARGS__)); \
    } while (0)
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_LOGGER_H
