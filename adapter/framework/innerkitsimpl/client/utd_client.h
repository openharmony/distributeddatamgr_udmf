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

#include <shared_mutex>
#include <string>
#include <vector>
#include <map>

#include "error_code.h"
#include "flexible_type.h"
#include "preset_type_descriptors.h"
#include "preset_type_descriptors.h"
#include "type_descriptor.h"
#include "utd_common.h"
#include "visibility.h"
namespace OHOS {
namespace UDMF {
class TypeDescriptor;
class UtdChangeSubscriber;
class UtdClient {
public:
    static UtdClient API_EXPORT &GetInstance();
    Status API_EXPORT GetTypeDescriptor(const std::string &typeId, std::shared_ptr<TypeDescriptor> &descriptor);
    Status API_EXPORT GetUniformDataTypeByFilenameExtension(const std::string &fileExtension, std::string &typeId,
                                                 std::string belongsTo = DEFAULT_TYPE_ID);
    Status API_EXPORT GetUniformDataTypesByFilenameExtension(const std::string &fileExtension,
                    std::vector<std::string> &typeIds, const std::string &belongsTo = DEFAULT_TYPE_ID);
    Status API_EXPORT GetUniformDataTypeByMIMEType(const std::string &mimeType, std::string &typeId,
                                        std::string belongsTo = DEFAULT_TYPE_ID);
    Status API_EXPORT GetUniformDataTypesByMIMEType(const std::string &mimeType, std::vector<std::string> &typeIds,
                                        const std::string &belongsTo = DEFAULT_TYPE_ID);
    Status API_EXPORT IsUtd(std::string typeId, bool &result);

private:
    UtdClient();
    ~UtdClient();
    UtdClient(const UtdClient &obj) = delete;
    UtdClient &operator=(const UtdClient &obj) = delete;
    void Init();
    bool IsHapTokenType();
    std::string GetCustomUtdPath();
    Status GetCurrentActiveUserId(int32_t& userId);
    bool IsValidFileExtension(const std::string &fileExtension);
    bool IsValidMimeType(const std::string &mimeType);
    Status GetFlexibleTypeDescriptor(const std::string &typeId, std::shared_ptr<TypeDescriptor> &descriptor);
    std::string GetTypeIdFromCfg(const std::string &mimeType);
    std::vector<std::string> GetTypeIdsFromCfg(const std::string &mimeType);
    void SubscribeUtdChange();

    std::vector<TypeDescriptorCfg> descriptorCfgs_;
    std::shared_ptr<UtdChangeSubscriber> subscriber_;
    std::shared_mutex utdMutex_;
};
} // namespace UDMF
} // namespace OHOS
#endif // UTD_CLIENT_H