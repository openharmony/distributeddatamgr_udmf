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
#define LOG_TAG "XmlLoader"

#include <dlfcn.h>
#include <thread>

#include "logger.h"
#include "xml_loader.h"

namespace OHOS {
namespace UDMF {

static constexpr const char *XML_WRAPPER_SO_NAME = "libxml_wrapper.z.so";
static constexpr const char *EXTRACT_IMG_SRC = "ExtractImgSrc";

std::weak_ptr<void> XmlLoader::SoAutoUnloadManager::weakHandler_;
std::mutex XmlLoader::SoAutoUnloadManager::mutex_;

std::shared_ptr<void> XmlLoader::SoAutoUnloadManager::GetHandler()
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (auto real = weakHandler_.lock()) {
            return real;
        }
    }
    LOG_INFO(UDMF_KITS_INNER, "dlopen start");
    void *rawHandler = dlopen(XML_WRAPPER_SO_NAME, RTLD_NOW);
    if (rawHandler == nullptr) {
        LOG_ERROR(UDMF_KITS_INNER, "dlopen error! msg=%{public}s", dlerror());
        return nullptr;
    }

    auto deleter = [](void *h) {
        if (h) dlclose(h);
    };
    std::shared_ptr<void> sp(rawHandler, deleter);

    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (auto existed = weakHandler_.lock()) {
            return existed;
        }
        weakHandler_ = sp;
        return sp;
    }
}

XmlLoader::XmlLoader()
{
    handler_ = SoAutoUnloadManager::GetHandler();
    if (handler_ == nullptr) {
        LOG_ERROR(UDMF_KITS_INNER, "load so fail! msg=%{public}s", dlerror());
    }
}

std::vector<std::string> XmlLoader::ExtractImgSrc(const std::string &htmlContent)
{
    if (handler_ == nullptr) {
        LOG_ERROR(UDMF_KITS_INNER, "handler is null!");
        return {};
    }
    auto loadExtractImgSrc = reinterpret_cast<LoadExtractImgSrc>(dlsym(handler_.get(), EXTRACT_IMG_SRC));
    if (loadExtractImgSrc == nullptr) {
        LOG_ERROR(UDMF_KITS_INNER, "dlsym error! msg=%{public}s", dlerror());
        return {};
    }
    size_t vectorSize;
    auto uris = loadExtractImgSrc(htmlContent.c_str(), vectorSize);
    if (uris == nullptr) {
        return {};
    }

    std::vector<std::string> result;
    for (size_t i = 0; i < vectorSize; ++i) {
        if (uris[i] == nullptr) {
            LOG_ERROR(UDMF_KITS_INNER, "uris[readPos] is NULL");
            continue;
        }
        result.emplace_back(uris[i]);
        delete[] uris[i];
    }
    delete[] uris;
    return result;
}

} // namespace UDMF
} // namespace OHOS