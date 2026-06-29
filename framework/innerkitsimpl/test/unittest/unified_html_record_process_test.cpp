/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#define LOG_TAG "UnifiedHtmlRecordProcessTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <string>

#include "logger.h"
#include "udmf_capi_common.h"
#include "unified_html_record_process.h"
#include "html.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class UnifiedHtmlRecordProcessTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void UnifiedHtmlRecordProcessTest::SetUpTestCase()
{
}

void UnifiedHtmlRecordProcessTest::TearDownTestCase()
{
}

void UnifiedHtmlRecordProcessTest::SetUp()
{
}

void UnifiedHtmlRecordProcessTest::TearDown()
{
}

/**
* @tc.name: RebuildHtmlRecord001
* @tc.desc: Abnormal testcase of RebuildHtmlRecord with nullptr Object in entry
* @tc.type: FUNC
*/
HWTEST_F(UnifiedHtmlRecordProcessTest, RebuildHtmlRecord001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "RebuildHtmlRecord001 begin.");
    UnifiedData data;
    auto html = std::make_shared<Html>();
    html->SetUtdId("general.html");
    std::shared_ptr<Object> nullObj = nullptr;
    html->AddEntry("general.html", nullObj);
    UriInfo uriInfo = {
        .oriUri = "file:///test.jpg",
        .position = 0,
    };
    html->SetUris({uriInfo});
    data.AddRecord(html);
    EXPECT_NO_FATAL_FAILURE(UnifiedHtmlRecordProcess::RebuildHtmlRecord(data));
    LOG_INFO(UDMF_TEST, "RebuildHtmlRecord001 end.");
}

/**
* @tc.name: RebuildHtmlRecord002
* @tc.desc: Abnormal testcase of RebuildHtmlRecord with nullptr record
* @tc.type: FUNC
*/
HWTEST_F(UnifiedHtmlRecordProcessTest, RebuildHtmlRecord002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "RebuildHtmlRecord002 begin.");
    UnifiedData data;
    data.records_ = {nullptr};
    EXPECT_NO_FATAL_FAILURE(UnifiedHtmlRecordProcess::RebuildHtmlRecord(data));
    LOG_INFO(UDMF_TEST, "RebuildHtmlRecord002 end.");
}

/**
* @tc.name: GetUriFromHtmlRecord001
* @tc.desc: Abnormal testcase of GetUriFromHtmlRecord with nullptr Object in entry
* @tc.type: FUNC
*/
HWTEST_F(UnifiedHtmlRecordProcessTest, GetUriFromHtmlRecord001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetUriFromHtmlRecord001 begin.");
    Html html;
    html.SetUtdId("general.html");
    std::shared_ptr<Object> nullObj = nullptr;
    html.AddEntry("general.html", nullObj);
    EXPECT_NO_FATAL_FAILURE(UnifiedHtmlRecordProcess::GetUriFromHtmlRecord(html));
    LOG_INFO(UDMF_TEST, "GetUriFromHtmlRecord001 end.");
}
} // OHOS::Test