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

#ifndef UDMF_SERVICE_CLIENT_MOCK_H
#define UDMF_SERVICE_CLIENT_MOCK_H

#include <gmock/gmock.h>

#include "udmf_service_client.h"
#include "unified_types.h"

namespace OHOS {
namespace UDMF {
class MUdmfServiceClient {
public:
    virtual ~MUdmfServiceClient() = default;
public:
    virtual std::shared_ptr<UdmfServiceClient> GetInstance() = 0;

    virtual int32_t SetData(CustomOption &, UnifiedData &, std::string &) = 0;
    virtual int32_t GetData(const QueryOption &, UnifiedData &) = 0;
    virtual int32_t GetBatchData(const QueryOption &, std::vector<UnifiedData> &) = 0;
    virtual int32_t UpdateData(const QueryOption &, UnifiedData &) = 0;
    virtual int32_t DeleteData(const QueryOption &, std::vector<UnifiedData> &) = 0;
    virtual int32_t GetSummary(const QueryOption &, Summary &) = 0;
    virtual int32_t AddPrivilege(const QueryOption &, Privilege &) = 0;
    virtual int32_t Sync(const QueryOption &, const std::vector<std::string> &) = 0;
    virtual int32_t IsRemoteData(const QueryOption &, bool &) = 0;
    virtual int32_t SetAppShareOption(const std::string &, int32_t shareOption) = 0;
    virtual int32_t GetAppShareOption(const std::string &, int32_t &) = 0;
    virtual int32_t RemoveAppShareOption(const std::string &) = 0;
    virtual int32_t ObtainAsynProcess(AsyncProcessInfo&) = 0;
    virtual int32_t ClearAsynProcessByKey(const std::string &businessUdKey) = 0;
    virtual int32_t SetDelayInfo(const DataLoadInfo &, sptr<IRemoteObject>, std::string &) = 0;
    virtual int32_t PushDelayData(const std::string &, const UnifiedData &) = 0;
    virtual int32_t GetDataIfAvailable(const std::string &key, const DataLoadInfo &, sptr<IRemoteObject>,
        std::shared_ptr<UnifiedData>) = 0;
    virtual int32_t PushAcceptableInfo(const QueryOption &query, const std::vector<std::string> &devices) = 0;
    virtual int32_t SaveAcceptableInfo(const std::string &key, DataLoadInfo &info) = 0;
public:
    static inline std::shared_ptr<MUdmfServiceClient> udmfServiceClient = nullptr;
};

class UdmfServiceClientMock : public MUdmfServiceClient {
public:
    MOCK_METHOD(std::shared_ptr<UdmfServiceClient>, GetInstance, ());
    MOCK_METHOD(int32_t, SetData, (CustomOption &, UnifiedData &, std::string &));
    MOCK_METHOD(int32_t, GetData, (const QueryOption &, UnifiedData &));
    MOCK_METHOD(int32_t, GetBatchData, (const QueryOption &, std::vector<UnifiedData> &));
    MOCK_METHOD(int32_t, UpdateData, (const QueryOption &, UnifiedData &));
    MOCK_METHOD(int32_t, DeleteData, (const QueryOption &, std::vector<UnifiedData> &));
    MOCK_METHOD(int32_t, GetSummary, (const QueryOption &, Summary &));
    MOCK_METHOD(int32_t, AddPrivilege, (const QueryOption &, Privilege &));
    MOCK_METHOD(int32_t, Sync, (const QueryOption &, const std::vector<std::string> &));
    MOCK_METHOD(int32_t, IsRemoteData, (const QueryOption &, bool &));
    MOCK_METHOD(int32_t, SetAppShareOption, (const std::string &, int32_t shareOption));
    MOCK_METHOD(int32_t, GetAppShareOption, (const std::string &, int32_t &));
    MOCK_METHOD(int32_t, RemoveAppShareOption, (const std::string &));
    MOCK_METHOD(int32_t, ObtainAsynProcess, (AsyncProcessInfo&));
    MOCK_METHOD(int32_t, ClearAsynProcessByKey, (const std::string &));
    MOCK_METHOD(int32_t, SetDelayInfo, (const DataLoadInfo &, sptr<IRemoteObject>, std::string &));
    MOCK_METHOD(int32_t, PushDelayData, (const std::string &, const UnifiedData &));
    MOCK_METHOD(int32_t, GetDataIfAvailable, (const std::string &, const DataLoadInfo &, sptr<IRemoteObject>,
        std::shared_ptr<UnifiedData>));
    MOCK_METHOD(int32_t, PushAcceptableInfo, (const QueryOption &query, const std::vector<std::string> &devices));
    MOCK_METHOD(int32_t, SaveAcceptableInfo, (const std::string &key, DataLoadInfo &info));
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_SERVICE_CLIENT_MOCK_H