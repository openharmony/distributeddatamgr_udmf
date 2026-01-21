/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#define LOG_TAG "UtdNotifierTest"
#include "utd_notifier.h"
#include "gtest/gtest.h"

namespace OHOS::UDMF {
using namespace testing::ext;
class UtdNotifierTest : public testing::Test {
public:
    static void SetUpTestCase(void) {}
    static void TearDownTestCase(void) {}
    void SetUp() {}
    void TearDown() {}
};

/**
* @tc.name: OnRemoteRequest001
* @tc.desc: Abnormal test of OnRemoteRequest, code is invalid
* @tc.type: FUNC
* @tc.require
*/
HWTEST_F(UtdNotifierTest, OnRemoteRequest001, TestSize.Level1)
{
    uint32_t code = 17; // invalid code
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    UtdNotifierClient UtdNotifierClient;
    int ret = UtdNotifierClient.OnRemoteRequest(code, data, reply, option);
    EXPECT_EQ(ret, E_IPC);
}

/**
* @tc.name: OnRemoteRequest002
* @tc.desc: Abnormal test of OnRemoteRequest, code is invalid
* @tc.type: FUNC
* @tc.require
*/
HWTEST_F(UtdNotifierTest, OnRemoteRequest002, TestSize.Level1)
{
    uint32_t code = E_IPC; // invalid code
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    UtdNotifierClient UtdNotifierClient;
    int ret = UtdNotifierClient.OnRemoteRequest(code, data, reply, option);
    EXPECT_EQ(ret, E_IPC);
}

/**
* @tc.name: OnRegisterDynamicUtd001
* @tc.desc: Abnormal test of OnSetData, data is invalid
* @tc.type: FUNC
* @tc.require
*/
HWTEST_F(UtdNotifierTest, OnRegisterDynamicUtd001, TestSize.Level1)
{
    MessageParcel data;
    MessageParcel reply;
    UtdNotifierClient UtdNotifierClient;
    int ret = UtdNotifierClient.OnRegisterDynamicUtd(data, reply);
    EXPECT_EQ(ret, E_READ_PARCEL_ERROR);
}

/**
* @tc.name: OnUnregisterDynamicUtd001
* @tc.desc: Abnormal test of OnGetData, data is invalid
* @tc.type: FUNC
* @tc.require
*/
HWTEST_F(UtdNotifierTest, OnUnregisterDynamicUtd001, TestSize.Level1)
{
    MessageParcel data;
    MessageParcel reply;
    UtdNotifierClient UtdNotifierClient;
    int ret = UtdNotifierClient.OnUnregisterDynamicUtd(data, reply);
    EXPECT_EQ(ret, E_READ_PARCEL_ERROR);
}
} // namespace OHOS::Test