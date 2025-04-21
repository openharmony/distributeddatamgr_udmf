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
#ifndef DATA_INTELLIGENCE_NAPI_TRACE_H
#define DATA_INTELLIGENCE_NAPI_TRACE_H

#define DO_NOTHING

#ifdef DATA_INTELLIGENCE_TRACE_ON
#include "hitrace.h"

#ifndef DATA_INTELLIGENCE_HITRACE
#define DATA_INTELLIGENCE_HITRACE(trace) OHOS::DataIntelligence::HiTrace hitrace(trace)
#endif

#else
#define DATA_INTELLIGENCE_HITRACE(trace) DO_NOTHING
#endif

#endif