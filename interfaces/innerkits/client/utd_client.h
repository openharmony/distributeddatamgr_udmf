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

#ifndef UTD_CLIENT_H
#define UTD_CLIENT_H

#include <string>
#include <vector>
#include <map>
#include "utd_common.h"
#include "preset_type_descriptors.h"
#include "preset_type_descriptors.h"
#include "flexible_type.h"
#include "type_descriptor.h"
#include "error_code.h"

namespace OHOS {
namespace UDMF {
class TypeDescriptor;
class UtdClient {
public:
    static UtdClient &GetInstance();
    Status GetTypeDescriptor(const std::string &typeId, std::shared_ptr<TypeDescriptor> &descriptor);
    Status GetUniformDataTypeByFilenameExtension(const std::string &fileExtension, std::string &typeId,
                                                 std::string belongsTo = DEFAULT_TYPE_ID);
    Status GetUniformDataTypeByMIMEType(const std::string &mimeType, std::string &typeId,
                                        std::string belongsTo = DEFAULT_TYPE_ID);

private:
    UtdClient();
    ~UtdClient();
    UtdClient(const UtdClient &obj) = delete;
    UtdClient &operator=(const UtdClient &obj) = delete;
    void Init();
    bool IsValidFileExtension(const std::string &fileExtension);
    bool IsValidMimeType(const std::string &mimeType);
    Status GetFlexibleTypeDescriptor(const std::string &typeId, std::shared_ptr<TypeDescriptor> &descriptor);
    std::vector<TypeDescriptorCfg> descriptorCfgs_;
};
} // namespace UDMF
} // namespace OHOS
#endif // UTD_CLIENT_H