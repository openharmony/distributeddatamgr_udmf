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
#ifndef XML_WRAPPER
#define XML_WRAPPER

#include "xml_loader.h"
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>

namespace OHOS::UDMF {
#ifdef __cplusplus
extern "C" {
#endif
static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

char** ExtractImgSrc(const char *htmlContent);
void FilterFileUris(char** uris);
char** FindAllImgsWithSrc(xmlDocPtr doc);
char** ExecuteXPath(xmlDocPtr doc, const char *xpathExpr);
char* SafeXmlToString(const xmlChar *xmlStr);
#ifdef __cplusplus
};
#endif
} // OHOS::UDMF

#endif