/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef XML_LOADER
#define XML_LOADER

#include <memory>
#include <mutex>

namespace OHOS::UDMF {
typedef char** (*LoadExtractImgSrc)(const char *htmlContent, size_t &vectorSize);

class XmlLoader {
public:
    XmlLoader();
    std::vector<std::string> ExtractImgSrc(const std::string &htmlContent);

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
#endif // XML_LOADER