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

#ifndef PIXELMAP_LOADER
#define PIXELMAP_LOADER

#include "pixel_map.h"

namespace OHOS::UDMF {

struct PixelMapDetails {
    int32_t width = 0;
    int32_t height = 0;
    int32_t pixelFormat = 0;
    int32_t alphaType = 0;
};

typedef OHOS::Media::PixelMap*(*LoadDecodeTlv)(const unsigned char*, unsigned int);
typedef bool (*LoadEncodeTlv)(const OHOS::Media::PixelMap*, unsigned char**, unsigned int*);
typedef OHOS::Media::PixelMap*(*LoadGetPixelMapFromRawData)(const unsigned char*, unsigned int, const PixelMapDetails);
typedef PixelMapDetails*(*LoadParseInfoFromPixelMap)(OHOS::Media::PixelMap*, unsigned char**, unsigned int*);

class PixelMapLoader {
public:
    PixelMapLoader();
    ~PixelMapLoader();

    std::shared_ptr<OHOS::Media::PixelMap> DecodeTlv(const std::vector<uint8_t> &buff);
    bool EncodeTlv(const std::shared_ptr<OHOS::Media::PixelMap> pixelmap, std::vector<uint8_t> &buff);
    std::shared_ptr<OHOS::Media::PixelMap> GetPixelMapFromRawData(const std::vector<uint8_t> &buff, const PixelMapDetails &details);
    std::shared_ptr<PixelMapDetails> ParseInfoFromPixelMap(const std::shared_ptr<OHOS::Media::PixelMap> pixelMap, std::vector<uint8_t> &buff);

private:
    void *handler_;
};

} // namespace OHOS::UDMF

#endif // PIXELMAP_LOADER