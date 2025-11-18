/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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
#define LOG_TAG "UdmfImgExtractor"
#include "udmf_img_extractor.h"

#include <algorithm>
#include <memory>
#include "logger.h"

namespace OHOS {
namespace UDMF {

UdmfImgExtractor &UdmfImgExtractor::GetInstance()
{
    static UdmfImgExtractor instance;
    return instance;
}

UdmfImgExtractor::UdmfImgExtractor()
{
    std::lock_guard lock(mutex_);
    xmlInitParser();
}

UdmfImgExtractor::~UdmfImgExtractor()
{
    std::lock_guard lock(mutex_);
    xmlCleanupParser();
}

std::vector<std::string> UdmfImgExtractor::ExtractImgSrc(const std::string &htmlContent)
{
    std::lock_guard lock(mutex_);
    int options = HTML_PARSE_RECOVER | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING;
    xmlDocPtr doc = htmlReadDoc(reinterpret_cast<const xmlChar *>(htmlContent.c_str()), nullptr, nullptr, options);
    if (doc == nullptr) {
        LOG_WARN(UDMF_CLIENT, "parse html failed");
        return {};
    }

    std::unique_ptr<xmlDoc, decltype(&xmlFreeDoc)> docGuard(doc, xmlFreeDoc);
    auto uris = FindAllImgsWithSrc(doc);
    FilterFileUris(uris);
    return uris;
}

void UdmfImgExtractor::FilterFileUris(std::vector<std::string> &uris)
{
    uris.erase(std::remove_if(uris.begin(), uris.end(),
        [](const std::string &str) { return str.find("file:///") != 0; }),
        uris.end()
    );
}

std::vector<std::string> UdmfImgExtractor::FindAllImgsWithSrc(xmlDocPtr doc)
{
    return ExecuteXPath(doc, "//img[@src]");
}

std::vector<std::string> UdmfImgExtractor::ExecuteXPath(xmlDocPtr doc, const char *xpathExpr)
{
    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    if (context == nullptr) {
        LOG_WARN(UDMF_CLIENT, "xpath new context failed");
        return {};
    }

    std::unique_ptr<xmlXPathContext, decltype(&xmlXPathFreeContext)> contextGuard(context, xmlXPathFreeContext);
    xmlXPathObjectPtr result = xmlXPathEvalExpression(reinterpret_cast<const xmlChar *>(xpathExpr), context);
    if (result == nullptr) {
        LOG_WARN(UDMF_CLIENT, "xpath eval expr failed");
        return {};
    }

    std::unique_ptr<xmlXPathObject, decltype(&xmlXPathFreeObject)> resultGuard(result, xmlXPathFreeObject);
    if (!result->nodesetval) {
        return {};
    }

    std::vector<std::string> results;
    xmlNodeSetPtr nodeSet = result->nodesetval;
    for (size_t i = 0; i < nodeSet->nodeNr; ++i) {
        xmlNodePtr node = nodeSet->nodeTab[i];
        if (node == nullptr) {
            continue;
        }

        xmlChar *src = xmlGetProp(node, reinterpret_cast<const xmlChar *>("src"));
        if (src == nullptr) {
            continue;
        }

        std::string srcStr = SafeXmlToString(src);
        if (!srcStr.empty()) {
            results.push_back(srcStr);
        }
        xmlFree(src);
    }
    return results;
}

std::string UdmfImgExtractor::SafeXmlToString(const xmlChar *xmlStr)
{
    if (xmlStr == nullptr) {
        return "";
    }

    return std::string(reinterpret_cast<const char *>(xmlStr));
}
} // namespace UDMF
} // namespace OHOS