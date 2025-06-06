/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef UDMF_AUDIO_H
#define UDMF_AUDIO_H

#include "file.h"
#include "visibility.h"
namespace OHOS {
namespace UDMF {
class Audio : public File {
public:
    API_EXPORT Audio();
    explicit API_EXPORT Audio(const std::string &uri);
    API_EXPORT Audio(UDType type, ValueType value);
    void InitObject() override;
};
} // namespace UDMF
} // namespace OHOS

#endif // UDMF_AUDIO_H
