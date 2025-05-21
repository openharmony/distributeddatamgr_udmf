/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License a
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "i_aip_core_manager_impl.h"

#include "aip_napi_error.h"

namespace OHOS {
namespace DataIntelligence {
int32_t IAipCoreManagerImpl::InitTextModel(const ModelConfigData &config)
{
    return DEVICE_EXCEPTION;
}

int32_t IAipCoreManagerImpl::InitImageModel(const ModelConfigData &config)
{
    return DEVICE_EXCEPTION;
}

int32_t IAipCoreManagerImpl::LoadTextModel()
{
    return DEVICE_EXCEPTION;
}

int32_t IAipCoreManagerImpl::ReleaseTextModel()
{
    return DEVICE_EXCEPTION;
}

int32_t IAipCoreManagerImpl::GetTextEmbedding(std::string file, std::vector<float> &results)
{
    return DEVICE_EXCEPTION;
}

int32_t IAipCoreManagerImpl::GetTextEmbedding(const std::vector<std::string> &files,
    std::vector<std::vector<float>> &results)
{
    return DEVICE_EXCEPTION;
}

int32_t IAipCoreManagerImpl::LoadImageModel()
{
    return DEVICE_EXCEPTION;
}

int32_t IAipCoreManagerImpl::ReleaseImageModel()
{
    return DEVICE_EXCEPTION;
}

int32_t IAipCoreManagerImpl::GetImageEmbedding(std::string uri, std::vector<float> &results)
{
    return DEVICE_EXCEPTION;
}

int32_t IAipCoreManagerImpl::SplitText(std::string text, int32_t size, float overlap,
    std::vector<std::string> &results)
{
    return DEVICE_EXCEPTION;
}

int32_t IAipCoreManagerImpl::CreateRAGSession(const ContextParam &contex, const ConfigStruct &config)
{
    return DEVICE_EXCEPTION;
}

int32_t IAipCoreManagerImpl::RAGSessionStreamRun(const std::string &question, const OptionStruct &option,
    std::function<void(const StreamStruct&, int32_t)> callback)
{
    return DEVICE_EXCEPTION;
}

int32_t IAipCoreManagerImpl::ReleaseRAGSession()
{
    return DEVICE_EXCEPTION;
}

int32_t IAipCoreManagerImpl::RAGSessionRun(const std::string &query, const OptionStruct &runOption,
    AnswerStruct &answer)
{
    return DEVICE_EXCEPTION;
}
++

} // namespace DataIntelligence
} // namespace OHOS
