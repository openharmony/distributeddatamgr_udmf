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
#define LOG_TAG "XmlmapWrapper"
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>

#include "logger.h"
#include "xml_wrapper.h"
#include "securec.h"

using namespace OHOS::UDMF;
using namespace std;

#ifdef __cplusplus
extern "C" {
#endif
static std::mutex mutex_;
static constexpr size_t MAX_TYPES_ARRAY_COUNT = 4 * 1024 * 1024;

char **ExtractImgSrc(const char *htmlContent, size_t &vectorSize)
{
    std::lock_guard<std::mutex> lock(mutex_);
    int options = HTML_PARSE_RECOVER | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING;
    xmlDocPtr doc = htmlReadDoc((const xmlChar *)htmlContent, nullptr, nullptr, options);
    if (doc == nullptr) {
        LOG_WARN(UDMF_CLIENT, "parse html failed");
        return nullptr;
    }

    std::unique_ptr<xmlDoc, decltype(&xmlFreeDoc)> docGuard(doc, xmlFreeDoc);
    std::vector<std::string> uris = UdmfImgExtractor::FindAllImgsWithSrc(doc);
    UdmfImgExtractor::FilterFileUris(uris);
    vectorSize = uris.size();
    if (vectorSize == 0 || vectorSize > MAX_TYPES_ARRAY_COUNT) {
        return nullptr;
    }
    char **typesArray = new (std::nothrow) char* [vectorSize];
    if (typesArray == nullptr) {
        return nullptr;
    }
    for (size_t i = 0; i < vectorSize; ++i) {
        size_t strLen = uris[i].length() + 1;
        typesArray[i] = new (std::nothrow) char[strLen];
        if (typesArray[i] == nullptr) {
            LOG_ERROR(UDMF_CLIENT, "Allocate memory failed");
            size_t allocatedSize = i + 1;
            DestroyImgSrc(typesArray, allocatedSize);
            return nullptr;
        }

        if (strcpy_s(typesArray[i], strLen, uris[i].c_str()) != 0) {
            LOG_ERROR(UDMF_CAPI, "String copy failed");
            unsigned int allocatedSize = i + 1;
            DestroyImgSrc(typesArray, allocatedSize);
            return nullptr;
        }
    }
    return typesArray;
}

void DestroyImgSrc(char **typesArray, const size_t &vectorSize)
{
    if (typesArray == nullptr) {
        return;
    }
    for (size_t j = 0; j < vectorSize; j++) {
        if (typesArray[j] != nullptr) {
            delete[] typesArray[j];
            typesArray[j] = nullptr;
        }
    }
    delete[] typesArray;
    typesArray = nullptr;
}
#ifdef __cplusplus
};
#endif
