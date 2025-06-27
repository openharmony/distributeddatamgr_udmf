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
#define LOG_TAG "FlexibleType"
#include "flexible_type.h"
#include "logger.h"
#include "base32_utils.h"

namespace OHOS {
namespace UDMF {
std::string FlexibleType::EscapeStr(const std::string &chs)
{
    std::string output;
    for (auto ch : chs) {
        if (ch == '?' || ch == ':' || ch == '=' || ch == ',' || ch == '\\') {
            output += '\\';
        }
        output += ch;
    }
    return output;
}

bool FlexibleType::ParseFlexibleUtd(const std::string &typeId, TypeDescriptorCfg &flexibleTypeDescriptorCfg)
{
    flexibleTypeDescriptorCfg.typeId = typeId;
    std::string flexibleUtd = typeId;
    std::string flexibleFlag = FLEXIBLE_TYPE_FLAG;
    flexibleUtd.erase(0, flexibleFlag.size());
    std::string flexibleUtdDecode = Base32::Decode(flexibleUtd);
    if (flexibleUtdDecode.empty() || flexibleUtdDecode[0] != '?' ||
            flexibleUtdDecode.find("=") == flexibleUtdDecode.npos) {
        LOG_WARN(UDMF_CLIENT, "The typeId cannot be parsed, %{public}s ", typeId.c_str());
        return false;
    }
    std::vector<std::string> flexibleTypeAttrs = StrSplit(flexibleUtdDecode, ":");
    for (auto attr : flexibleTypeAttrs) {
        std::vector<std::string> attrkv = StrSplit(attr, "=");
        if (attrkv.size() != ATTRIBUTE_PAIR_SIZE) {
            continue;
        }
        if (attrkv[1].length() > MAX_TYPE_SIZE) {
            LOG_ERROR(UDMF_CLIENT, "Attribute too long, attribute: %{public}s", attr.c_str());
            return false;
        }
        std::string attrName = attrkv[0];
        if (attrName.find(std::to_string(BELONGINGTO_TYPE)) != attrName.npos) {
            flexibleTypeDescriptorCfg.belongingToTypes.push_back(attrkv[1]);
        } else if (attrName.find(std::to_string(MIMETYPE)) != attrName.npos) {
            flexibleTypeDescriptorCfg.mimeTypes.push_back(attrkv[1]);
        } else if (attrName.find(std::to_string(FILE_EXTENTSION)) != attrName.npos) {
            flexibleTypeDescriptorCfg.filenameExtensions.push_back(attrkv[1]);
        }
    }
    return true;
}

std::string FlexibleType::GenFlexibleUtd(const std::string &mimeType, const std::string &fileExtension,
                                         const std::string &belongsTo)
{
    std::string flexibleUtd = "?";
    if (!belongsTo.empty() && belongsTo!=DEFAULT_TYPE_ID) {
        flexibleUtd += std::to_string(BELONGINGTO_TYPE) + "=" + belongsTo;
    }
    if (!mimeType.empty()) {
        flexibleUtd += ":" + std::to_string(MIMETYPE) + "=" + mimeType;
    }
    if (!fileExtension.empty()) {
        flexibleUtd += ":" + std::to_string(FILE_EXTENTSION) + "=" + fileExtension;
    }
    std::string encodeUtd = Base32::Encode(flexibleUtd);
    return FLEXIBLE_TYPE_FLAG + encodeUtd;
}

std::vector<std::string> FlexibleType::StrSplit(const std::string &str, const std::string &delimiter)
{
    std::vector<std::string> result;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    result.push_back(str.substr(start));
    return result;
}

} // namespace UDMF
} // namespace OHOS

