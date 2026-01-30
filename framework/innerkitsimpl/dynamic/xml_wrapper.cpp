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
#include "xml_wrapper.h"
#include "logger.h"
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>

using namespace OHOS::UDMF;
using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

char** ExtractImgSrc(const char *htmlContent)
{
    pthread_mutex_lock(&g_mutex);
    int options = HTML_PARSE_RECOVER | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING;
    xmlDocPtr doc = htmlReadDoc((const xmlChar *)htmlContent, NULL, NULL, options);
    if (doc == NULL) {
        LOG_WARN(UDMF_CLIENT, "parse html failed");
        pthread_mutex_unlock(&g_mutex);
        return NULL;
    }

    char** uris = FindAllImgsWithSrc(doc);
    xmlFreeDoc(doc);
    FilterFileUris(uris);
    pthread_mutex_unlock(&g_mutex);
    return uris;
}

void FilterFileUris(char **uris)
{
    const char *prefix = "file:///";
    size_t prefixLen = strlen(prefix);
    int writePos = 0;

    for (int readPos = 0; uris[readPos] != NULL; readPos++) {
        if (uris[readPos] != NULL &&
            strncmp(uris[readPos], prefix, prefixLen) == 0) {
            if (writePos != readPos) {
                uris[writePos] = uris[readPos];
            }
            writePos++;
        } else {
            if (uris[readPos] != NULL) {
                free(uris[readPos]);
                uris[readPos] = NULL;
            }
        }
    }
    uris[writePos] = NULL;
}

char** FindAllImgsWithSrc(xmlDocPtr doc)
{
    return ExecuteXPath(doc, "//img[@src]");
}

char** ExecuteXPath(xmlDocPtr doc, const char *xpathExpr)
{
    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    if (context == NULL) {
        LOG_WARN(UDMF_CLIENT, "xpath new context failed");
        return NULL;
    }

    xmlXPathObjectPtr result = xmlXPathEvalExpression(reinterpret_cast<const xmlChar *>(xpathExpr), context);
    xmlXPathFreeContext(context);
    if (result == NULL) {
        LOG_WARN(UDMF_CLIENT, "xpath eval expr failed");
        return NULL;
    }

    xmlNodeSetPtr nodeSet = result->nodesetval;
    if (nodeSet == NULL || nodeSet->nodeNr == 0) {
        xmlXPathFreeObject(result);
        return NULL;
    }
    char **results =  (char**)calloc(nodeSet->nodeNr, sizeof(char*));
    if (results == NULL) {
        xmlXPathFreeObject(result);
        return NULL;
    }

    int outCount = 0;
    for (int i = 0; i < nodeSet->nodeNr; ++i) {
        xmlNodePtr node = nodeSet->nodeTab[i];
        if (node == NULL) {
            continue;
        }

        xmlChar *src = xmlGetProp(node, reinterpret_cast<const xmlChar *>("src"));
        if (src == NULL) {
            continue;
        }
        char *srcStr = SafeXmlToString(src);
        xmlFree(src);

        if (srcStr != NULL && srcStr[0] != '\0') {
            results[outCount] = srcStr;
            outCount++;
        } else if (srcStr != NULL) {
            free(srcStr);
        }
    }
    results[outCount] = NULL;
    xmlXPathFreeObject(result);
    return results;
}

char* SafeXmlToString(const xmlChar *xmlStr)
{
    if (xmlStr == NULL) {
        return NULL;
    }

    size_t len = strlen((const char *)xmlStr);
    char *result = (char*)malloc(len + 1);
    if (result != NULL) {
        strcpy(result, (const char *)xmlStr);
    }
    return result;
}
#ifdef __cplusplus
};
#endif