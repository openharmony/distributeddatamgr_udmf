/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "utils.h"

char *Utils::MallocCString(const std::string &origin)
{
    if (origin.empty()) {
        return nullptr;
    }
    auto len = origin.length() + 1;
    char *res = static_cast<char*>(malloc(sizeof(char) * len));
    if (res == nullptr) {
        return nullptr;
    }
    return std::char_traits<char>::copy(res, origin.c_str(), len);
}

CArrString Utils::StringVectorToArray(std::vector<std::string> vector)
{
    if (vector.size() == 0) {
        return CArrString {};
    }
    char **head = static_cast<char**>(malloc(vector.size() * sizeof(char *)));
    if (head == nullptr) {
        return CArrString {};
    }
    for (unsigned long i = 0; i < vector.size(); i++) {
        head[i] = Utils::MallocCString(vector[i]);
    }
    CArrString stringArray = { head, vector.size() };
    return stringArray;
}

void Utils::FreeCArrString(CArrString &arrStr)
{
    if (arrStr.head == nullptr) {
        return;
    }
    for (int64_t i = 0; i < arrStr.size; i++) {
        free(arrStr.head[i]);
        arrStr.head[i] = nullptr;
    }
    free(arrStr.head);
    arrStr.head = nullptr;
}