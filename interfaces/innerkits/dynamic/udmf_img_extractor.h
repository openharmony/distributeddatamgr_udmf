/*
 * Copyright (C) 2026 Huawei Device Co., Ltd.
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

#ifndef UDMF_IMG_EXTRACTOR_H
#define UDMF_IMG_EXTRACTOR_H

#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>
#include <mutex>
#include <string>
#include <vector>

namespace OHOS {
namespace UDMF {
class UdmfImgExtractor {
public:
    static void FilterFileUris(std::vector<std::string> &uris);
    static std::vector<std::string> FindAllImgsWithSrc(xmlDocPtr doc);
    static std::vector<std::string> ExecuteXPath(xmlDocPtr doc, const char *xpathExpr);
    static std::string SafeXmlToString(const xmlChar *xmlStr);
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_IMG_EXTRACTOR_H