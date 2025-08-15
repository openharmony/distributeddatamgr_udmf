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

#include <functional>
#include <memory>
#include <optional>
#include "pixel_map.h"

namespace OHOS::UDMF {

struct PixelMapDetails {
    int32_t width = 0;
    int32_t height = 0;
    int32_t pixelFormat = 0;
    int32_t alphaType = 0;
    // Use as an input parameter. To avoid copying, pass a reference.
    std::optional<std::reference_wrapper<std::vector<uint8_t>>> rawData;
    // Use as an output parameter.
    std::optional<std::vector<uint8_t>> rawDataResult;
};

typedef OHOS::Media::PixelMap *(*LoadDecodeTlv)(const PixelMapDetails);
typedef bool (*LoadEncodeTlv)(const OHOS::Media::PixelMap *, PixelMapDetails *);
typedef OHOS::Media::PixelMap *(*LoadGetPixelMapFromRawData)(const PixelMapDetails);
typedef PixelMapDetails *(*LoadParseInfoFromPixelMap)(OHOS::Media::PixelMap *);

class PixelMapLoader {
public:
    PixelMapLoader();

    std::shared_ptr<OHOS::Media::PixelMap> DecodeTlv(std::vector<uint8_t> &buff);
    bool EncodeTlv(const std::shared_ptr<OHOS::Media::PixelMap> pixelmap, std::vector<uint8_t> &buff);
    std::shared_ptr<OHOS::Media::PixelMap> GetPixelMapFromRawData(const PixelMapDetails &details);
    std::shared_ptr<PixelMapDetails> ParseInfoFromPixelMap(const std::shared_ptr<OHOS::Media::PixelMap> pixelMap);

private:
    class SoAutoUnloadManager {
    public:
        static std::shared_ptr<void> GetHandler();
    private:
        static std::weak_ptr<void> weakHandler_;
        static std::mutex mutex_;
    };

    std::shared_ptr<void> handler_;
};

} // namespace OHOS::UDMF

#endif // PIXELMAP_LOADER