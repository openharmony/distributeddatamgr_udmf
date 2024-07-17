/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "NdkDataConversionTest"

#include "ndk_data_conversion.h"
#include <gtest/gtest.h>
#include <memory>
#include "token_setproc.h"
#include "accesstoken_kit.h"
#include "nativetoken_kit.h"
#include "logger.h"
#include "error_code.h"
#include "udmf.h"
#include "udmf_capi_common.h"
#include "uds.h"

using namespace testing::ext;
using namespace OHOS::Security::AccessToken;
using namespace OHOS::UDMF;
using namespace OHOS;

namespace OHOS::Test {
    class NdkDataConversionTest : public testing::Test {
    public:
        static void SetUpTestCase(void);

        static void TearDownTestCase(void);

        void SetUp();

        void TearDown();
    };

    void NdkDataConversionTest::SetUpTestCase(void) {}

    void NdkDataConversionTest::TearDownTestCase(void) {}

    void NdkDataConversionTest::SetUp(void) {}

    void NdkDataConversionTest::TearDown(void) {}

    /**
     * @tc.name: GetNativeUnifiedData_001
     * @tc.desc: Normal testcase of GetNativeUnifiedData
     * @tc.type: FUNC
     */
    HWTEST_F(NdkDataConversionTest, GetNativeUnifiedData_001, TestSize.Level1) {
        LOG_INFO(UDMF_TEST, "GetNativeUnifiedData_001 begin.");
        UnifiedRecord unifiedRecord;
        const std::string uid("typeId");
        unifiedRecord.SetUid(uid);
        OH_UdmfData* ndkData = OH_UdmfData_Create();
        const std::shared_ptr<UnifiedRecord> recordPtr = std::make_shared<UnifiedRecord>(unifiedRecord);
        ndkData->unifiedData_->AddRecord(recordPtr);
        auto data = std::make_shared<UnifiedData>();

        Status status = NdkDataConversion::GetNativeUnifiedData(ndkData, data);
        ASSERT_EQ(E_OK, status);
        EXPECT_EQ("typeId", data->GetRecordAt(0)->GetUid());

        OH_UdmfData* ndkDataNull = nullptr;
        status = NdkDataConversion::GetNativeUnifiedData(ndkDataNull, data);
        ASSERT_EQ(E_INVALID_PARAMETERS, status);

        std::shared_ptr<UnifiedData> dataNull;
        status = NdkDataConversion::GetNativeUnifiedData(ndkData, dataNull);
        OH_UdmfData_Destroy(ndkData);
        ASSERT_EQ(E_INVALID_PARAMETERS, status);
        LOG_INFO(UDMF_TEST, "GetNativeUnifiedData_001 end.");
    }

    /**
     * @tc.name: GetNativeUnifiedData_002
     * @tc.desc: Normal testcase of GetNativeUnifiedData
     * @tc.type: FUNC
     */
    HWTEST_F(NdkDataConversionTest, GetNativeUnifiedData_002, TestSize.Level1) {
        LOG_INFO(UDMF_TEST, "GetNativeUnifiedData_002 begin.");
        auto plainText = OH_UdsPlainText_Create();
        OH_UdmfData* fakeNdkData = reinterpret_cast<OH_UdmfData*>(plainText);
        auto data = std::make_shared<UnifiedData>();
        Status status = NdkDataConversion::GetNativeUnifiedData(fakeNdkData, data);
        OH_UdsPlainText_Destroy(plainText);
        ASSERT_EQ(E_INVALID_PARAMETERS, status);
        LOG_INFO(UDMF_TEST, "GetNativeUnifiedData_002 end.");
    }

    /**
     * @tc.name: GetNdkUnifiedData_001
     * @tc.desc: Error testcase of GetNdkUnifiedData
     * @tc.type: FUNC
     */
    HWTEST_F(NdkDataConversionTest, GetNdkUnifiedData_001, TestSize.Level1) {
        LOG_INFO(UDMF_TEST, "GetNdkUnifiedData_001 begin.");
        UnifiedRecord unifiedRecord;
        const std::string uid("typeId");
        unifiedRecord.SetUid(uid);
        const std::shared_ptr<UnifiedRecord> recordPtr = std::make_shared<UnifiedRecord>(unifiedRecord);
        auto data= std::make_shared<UnifiedData>();
        data->AddRecord(recordPtr);
        OH_UdmfData* ndkData = OH_UdmfData_Create();
        Status status = NdkDataConversion::GetNdkUnifiedData(data, ndkData);
        ASSERT_EQ(E_OK, status);
        EXPECT_EQ("typeId", ndkData->unifiedData_->GetRecordAt(0)->GetUid());

        OH_UdmfData* ndkDataNull = nullptr;
        status = NdkDataConversion::GetNdkUnifiedData(data, ndkDataNull);
        ASSERT_EQ(E_INVALID_PARAMETERS, status);

        std::shared_ptr<UnifiedData> dataNull;
        status = NdkDataConversion::GetNdkUnifiedData(dataNull, ndkData);
        OH_UdmfData_Destroy(ndkData);
        ASSERT_EQ(E_INVALID_PARAMETERS, status);
        LOG_INFO(UDMF_TEST, "GetNdkUnifiedData_001 end.");
    }

    /**
     * @tc.name: GetNdkUnifiedData_002
     * @tc.desc: Error testcase of GetNdkUnifiedData
     * @tc.type: FUNC
     */
    HWTEST_F(NdkDataConversionTest, GetNdkUnifiedData_002, TestSize.Level1) {
        LOG_INFO(UDMF_TEST, "GetNdkUnifiedData_002 begin.");
        auto plainText = OH_UdsPlainText_Create();
        OH_UdmfData* fakeNdkData = reinterpret_cast<OH_UdmfData*>(plainText);
        auto data = std::make_shared<UnifiedData>();
        Status status = NdkDataConversion::GetNdkUnifiedData(data, fakeNdkData);
        OH_UdsPlainText_Destroy(plainText);
        ASSERT_EQ(E_INVALID_PARAMETERS, status);
        LOG_INFO(UDMF_TEST, "GetNdkUnifiedData_002 end.");
    }
}