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
#ifndef PIXELMAP_WRAPPER
#define PIXELMAP_WRAPPER

#include "pixel_map.h"
#include "pixelmap_loader.h"

namespace OHOS::UDMF {
#ifdef __cplusplus
extern "C" {
#endif

OHOS::Media::PixelMap *DecodeTlv(const PixelMapDetails details);
bool EncodeTlv(const OHOS::Media::PixelMap *pixelMap, PixelMapDetails *details);
OHOS::Media::PixelMap *GetPixelMapFromRawData(const PixelMapDetails details);
PixelMapDetails *ParseInfoFromPixelMap(OHOS::Media::PixelMap *pixelMap);

#ifdef __cplusplus
};
#endif
} // OHOS::UDMF

#endif