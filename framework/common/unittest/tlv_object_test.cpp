/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#define LOG_TAG "TlvObjectTest"

#include "tlv_object.h"
#include "logger.h"
#include <gtest/gtest.h>

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;

namespace OHOS::Test {
class TlvObjectTest : public testing::Test {
public:
    static void SetUpTestCase(void);

    static void TearDownTestCase(void);

    void SetUp();

    void TearDown();
};

void TlvObjectTest::SetUpTestCase(void) {}
void TlvObjectTest::TearDownTestCase(void) {}
void TlvObjectTest::SetUp(void) {}
void TlvObjectTest::TearDown(void) {}

/* *
 * @tc.name: SetFile_001
 * @tc.desc: test for SetFile
 * @tc.type: FUNC
 */
HWTEST_F(TlvObjectTest, SetFile_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetFile_001 begin.");
    std::FILE *file = nullptr;
    std::vector<std::uint8_t> buffer = {1, 2, 3, 4, 5};
    TLVObject tLVObject(buffer);
    EXPECT_NO_FATAL_FAILURE(tLVObject.SetFile(file));
    LOG_INFO(UDMF_TEST, "SetFile_001 end.");
}
}
