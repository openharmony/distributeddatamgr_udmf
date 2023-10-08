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

#ifndef UDMF_TYPE_DESCRIPTOR_H
#define UDMF_TYPE_DESCRIPTOR_H

#include <string>
#include <set>
#include <vector>

namespace OHOS {
namespace UDMF {
class TypeDescriptor {
public:
    explicit TypeDescriptor(const std::string &typeId);
    ~TypeDescriptor();
    bool Equals(std::shared_ptr<TypeDescriptor> descriptor);
    std::string GetTypeId();
    void SetBelongingToTypes(const std::set<std::string> &belongingToTypes);
    std::set<std::string> GetBelongingToTypes();
    void SetIconFile(const std::string &iconFile);
    std::string GetIconFile();
    void SetDescription(std::string description);
    std::string GetDescription();
    void SetReferenceURL(std::string referenceURL);
    std::string GetReferenceURL();
    void SetFilenameExtensions(const std::vector<std::string> &filenameExtensions);
    std::vector<std::string> GetFilenameExtensions();
    void SetMimeTypes(const std::vector<std::string> &mimeTypes);
    std::vector<std::string> GetMimeTypes();

private:
    std::string typeId_;
    std::set<std::string> belongingToTypes_;
    std::string iconFile_;
    std::vector<std::string> filenameExtensions_;
    std::vector<std::string> mimeTypes_;

    std::string description_;
    std::string referenceURL_;
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_TYPE_DESCRIPTOR_H
