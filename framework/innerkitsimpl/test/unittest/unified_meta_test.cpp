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
#define LOG_TAG "UnifiedMetaTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <string>

#include "logger.h"
#include "udmf_capi_common.h"
#include "unified_meta.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class UnifiedMetaTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    static constexpr int INT32_SIZE = 4;
    static constexpr int INT64_SIZE = 8;
    static constexpr int BOOL_SIZE = 1;
    static constexpr int DOUBLE_SIZE = 8;
};

void UnifiedMetaTest::SetUpTestCase()
{
}

void UnifiedMetaTest::TearDownTestCase()
{
}

void UnifiedMetaTest::SetUp()
{
}

void UnifiedMetaTest::TearDown()
{
}

/**
* @tc.name: IsValidType001
* @tc.desc: Normal testcase of IsValidType
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, IsValidType001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "IsValidType001 begin.");
    int32_t value = 0;
    bool ret = UnifiedDataUtils::IsValidType(value);
    EXPECT_EQ(ret, value >= ENTITY && value < UD_BUTT);
    LOG_INFO(UDMF_TEST, "IsValidType001 end.");
}

/**
* @tc.name: GetEnumNum001
* @tc.desc: Normal testcase of GetEnumNum
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, GetEnumNum001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetEnumNum001 begin.");
    const std::string shareOption = "";
    int32_t ret = ShareOptionsUtil::GetEnumNum(shareOption);
    EXPECT_EQ(ret, ShareOptions::SHARE_OPTIONS_BUTT);
    LOG_INFO(UDMF_TEST, "GetEnumNum001 end.");
}

/**
* @tc.name: GetEnumNum002
* @tc.desc: Abnormal testcase of GetEnumNum, shareOption is APP_SHARE_OPTIONS.enumNum
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, GetEnumNum002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetEnumNum002 begin.");
    const std::string shareOption = "CROSS_APP";
    int32_t ret = ShareOptionsUtil::GetEnumNum(shareOption);
    EXPECT_EQ(ret, 1);
    LOG_INFO(UDMF_TEST, "GetEnumNum002 end.");
}

/**
* @tc.name: GetEnumStr001
* @tc.desc: Normal testcase of GetEnumStr
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, GetEnumStr001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetEnumStr001 begin.");
    int32_t shareOption = 4;
    std::string ret = ShareOptionsUtil::GetEnumStr(shareOption);
    EXPECT_EQ(ret, "");
    LOG_INFO(UDMF_TEST, "GetEnumStr001 end.");
}

/**
* @tc.name: GetEnumStr002
* @tc.desc: Abnormal testcase of GetEnumStr, shareOption is APP_SHARE_OPTIONS.enumStr
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, GetEnumStr002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetEnumStr002 begin.");
    int32_t shareOption = 1;
    std::string ret = ShareOptionsUtil::GetEnumStr(shareOption);
    EXPECT_NE(ret, "");
    LOG_INFO(UDMF_TEST, "GetEnumStr002 end.");
}

/**
* @tc.name: IsValidUtdId001
* @tc.desc: Normal testcase of IsValidUtdId
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, IsValidUtdId001, TestSize.Level1)
{
    std::string utdId = "general.text";
    bool ret = UtdUtils::IsValidUtdId(utdId);
    EXPECT_TRUE(ret);
}

/**
* @tc.name: IsValidUtdId002
* @tc.desc: Abnormal testcase of IsValidUtdId
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, IsValidUtdId002, TestSize.Level1)
{
    std::string utdId = "general.ptp";
    bool ret = UtdUtils::IsValidUtdId(utdId);
    EXPECT_FALSE(ret);
}

/**
* @tc.name: GetUtdEnumFromUtdId001
* @tc.desc: Normal testcase of GetUtdEnumFromUtdId
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, GetUtdEnumFromUtdId001, TestSize.Level1)
{
    std::string utdId = "general.text";
    int32_t ret = UtdUtils::GetUtdEnumFromUtdId(utdId);
    EXPECT_EQ(ret, UDType::TEXT);
}

/**
* @tc.name: GetUtdEnumFromUtdId002
* @tc.desc: Abnormal testcase of GetUtdEnumFromUtdId
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, GetUtdEnumFromUtdId002, TestSize.Level1)
{
    std::string utdId = "general.ptp";
    int32_t ret = UtdUtils::GetUtdEnumFromUtdId(utdId);
    EXPECT_EQ(ret, UDType::UD_BUTT);
}

/**
* @tc.name: GetUtdIdFromUtdEnum001
* @tc.desc: Normal testcase of GetUtdIdFromUtdEnum
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, GetUtdIdFromUtdEnum001, TestSize.Level1)
{
    std::string ret = UtdUtils::GetUtdIdFromUtdEnum(UDType::TEXT);
    EXPECT_EQ(ret, "general.text");
}

/**
* @tc.name: GetUtdIdFromUtdEnum002
* @tc.desc: Abnormal testcase of GetUtdIdFromUtdEnum
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, GetUtdIdFromUtdEnum002, TestSize.Level1)
{
    std::string ret = UtdUtils::GetUtdIdFromUtdEnum(UDType::UD_BUTT);
    EXPECT_TRUE(ret.empty());

    std::string ret1 = UtdUtils::GetUtdIdFromUtdEnum(UDType::UD_BUTT + 1);
    EXPECT_TRUE(ret1.empty());
}

/**
* @tc.name: GetUtdTypes001
* @tc.desc: Normal testcase of GetUtdTypes
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, GetUtdTypes001, TestSize.Level1)
{
    std::vector<UtdType> ret = UtdUtils::GetUtdTypes();
    EXPECT_TRUE(ret.size() > 0);
}

/**
* @tc.name: UnifiedDataUtilsIsValidType001
* @tc.desc: Abnormal testcase of IsValidType
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, UnifiedDataUtilsIsValidType001, TestSize.Level1)
{
    bool ret = UnifiedDataUtils::IsValidType(UDType::UD_BUTT);
    EXPECT_FALSE(ret);

    bool ret1 = UnifiedDataUtils::IsValidType(UDType::ENTITY - 1);
    EXPECT_FALSE(ret1);

    bool ret2 = UnifiedDataUtils::IsValidType(UDType::UD_BUTT + 1);
    EXPECT_FALSE(ret2);
}

/**
* @tc.name: UnifiedDataUtilsIsValidType002
* @tc.desc: Normal testcase of IsValidType
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, UnifiedDataUtilsIsValidType002, TestSize.Level1)
{
    bool ret = UnifiedDataUtils::IsValidType(UDType::TEXT);
    EXPECT_TRUE(ret);

    bool ret1 = UnifiedDataUtils::IsValidType(UDType::ENTITY);
    EXPECT_TRUE(ret1);
}

/**
* @tc.name: IsValidIntention001
* @tc.desc: Normal testcase of IsValidIntention
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, IsValidIntention001, TestSize.Level1)
{
    bool ret = UnifiedDataUtils::IsValidIntention(Intention::UD_INTENTION_DRAG);
    EXPECT_TRUE(ret);

    bool ret1 = UnifiedDataUtils::IsValidIntention(Intention::UD_INTENTION_DATA_HUB);
    EXPECT_TRUE(ret1);

    bool ret2 = UnifiedDataUtils::IsValidIntention(Intention::UD_INTENTION_SYSTEM_SHARE);
    EXPECT_TRUE(ret2);

    bool ret3 = UnifiedDataUtils::IsValidIntention(Intention::UD_INTENTION_PICKER);
    EXPECT_TRUE(ret3);

    bool ret4 = UnifiedDataUtils::IsValidIntention(Intention::UD_INTENTION_MENU);
    EXPECT_TRUE(ret4);
}

/**
* @tc.name: IsValidIntention002
* @tc.desc: Abnormal testcase of IsValidIntention
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, IsValidIntention002, TestSize.Level1)
{
    bool ret = UnifiedDataUtils::IsValidIntention(Intention::UD_INTENTION_BASE);
    EXPECT_FALSE(ret);

    bool ret1 = UnifiedDataUtils::IsValidIntention(Intention::UD_INTENTION_BUTT);
    EXPECT_FALSE(ret1);

    bool ret2 = UnifiedDataUtils::IsValidIntention(Intention::UD_INTENTION_BASE - 1);
    EXPECT_FALSE(ret2);

    bool ret3 = UnifiedDataUtils::IsValidIntention(Intention::UD_INTENTION_BUTT + 1);
    EXPECT_FALSE(ret3);
}

/**
* @tc.name: ShareOptionsUtilIsValid001
* @tc.desc: Normal testcase of IsValid
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, ShareOptionsUtilIsValid001, TestSize.Level1)
{
    bool ret = ShareOptionsUtil::IsValid(ShareOptions::IN_APP);
    EXPECT_TRUE(ret);

    bool ret1 = ShareOptionsUtil::IsValid(ShareOptions::CROSS_APP);
    EXPECT_TRUE(ret1);
}

/**
* @tc.name: ShareOptionsUtilIsValid002
* @tc.desc: Abnormal testcase of IsValid
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, ShareOptionsUtilIsValid002, TestSize.Level1)
{
    bool ret = ShareOptionsUtil::IsValid(ShareOptions::IN_APP - 1);
    EXPECT_FALSE(ret);

    bool ret1 = ShareOptionsUtil::IsValid(ShareOptions::SHARE_OPTIONS_BUTT);
    EXPECT_FALSE(ret1);

    bool ret2 = ShareOptionsUtil::IsValid(ShareOptions::SHARE_OPTIONS_BUTT + 1);
    EXPECT_FALSE(ret2);
}

/**
* @tc.name: GetVariantSize001
* @tc.desc: Normal testcase of GetVariantSize
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, GetVariantSize001, TestSize.Level1)
{
    UDVariant variant;
    // case int32_t
    variant = (int32_t)100;
    size_t int32tSize = UnifiedDataUtils::GetVariantSize(variant);
    EXPECT_EQ(int32tSize, INT32_SIZE);

    variant = (int64_t)100;
    size_t int64tSize = UnifiedDataUtils::GetVariantSize(variant);
    EXPECT_EQ(int64tSize, INT64_SIZE);

    variant = true;
    size_t boolSize = UnifiedDataUtils::GetVariantSize(variant);
    EXPECT_EQ(boolSize, BOOL_SIZE);

    variant = 100.0001;
    size_t doubleSize = UnifiedDataUtils::GetVariantSize(variant);
    EXPECT_EQ(doubleSize, DOUBLE_SIZE);

    std::string str = "string size";
    variant = str;
    size_t strSize = UnifiedDataUtils::GetVariantSize(variant);
    EXPECT_EQ(strSize, str.size());

    std::vector<uint8_t> uVecEmpty;
    variant = uVecEmpty;
    size_t vecEmpSize = UnifiedDataUtils::GetVariantSize(variant);
    EXPECT_EQ(vecEmpSize, uVecEmpty.size());

    std::vector<uint8_t> uVec(100, 100);
    variant = uVec;
    size_t uVecSize = UnifiedDataUtils::GetVariantSize(variant);
    EXPECT_EQ(uVecSize, uVec.size());
}

/**
* @tc.name: GetDetailsSize001
* @tc.desc: Normal testcase of GetDetailsSize
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, GetDetailsSize001, TestSize.Level1)
{
    std::string int32Key = "int32Key";
    std::string int64Key = "int64Key";
    std::string strKey = "strKey";
    std::string str = "string size";
    UDDetails details = {
        {int32Key, (int32_t)100},
        {int64Key, (int64_t)100},
        {strKey, str}
    };
    size_t ret = UnifiedDataUtils::GetDetailsSize(details);
    EXPECT_EQ(ret, int32Key.size() + int64Key.size() + strKey.size() + INT32_SIZE + INT64_SIZE + str.size());
}

/**
* @tc.name: IsPersistByIntention001
* @tc.desc: Normal testcase of IsPersist
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, IsPersistByIntention001, TestSize.Level1)
{
    bool ret = UnifiedDataUtils::IsPersist(Intention::UD_INTENTION_DATA_HUB);
    EXPECT_TRUE(ret);

    bool ret1 = UnifiedDataUtils::IsPersist(Intention::UD_INTENTION_BUTT);
    EXPECT_FALSE(ret1);

    bool ret2 = UnifiedDataUtils::IsPersist(Intention::UD_INTENTION_DRAG);
    EXPECT_FALSE(ret2);

    bool ret3 = UnifiedDataUtils::IsPersist(Intention::UD_INTENTION_BASE);
    EXPECT_FALSE(ret3);

    bool ret4 = UnifiedDataUtils::IsPersist(Intention::UD_INTENTION_PICKER);
    EXPECT_TRUE(ret4);

    bool ret5 = UnifiedDataUtils::IsPersist(Intention::UD_INTENTION_MENU);
    EXPECT_TRUE(ret5);

    bool ret6 = UnifiedDataUtils::IsPersist(Intention::UD_INTENTION_SYSTEM_SHARE);
    EXPECT_TRUE(ret6);
}

/**
* @tc.name: IsPersistByStr001
* @tc.desc: Normal testcase of IsPersist
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, IsPersistByStr001, TestSize.Level1)
{
    bool ret = UnifiedDataUtils::IsPersist("DataHub");
    EXPECT_TRUE(ret);

    bool ret1 = UnifiedDataUtils::IsPersist("drag");
    EXPECT_FALSE(ret1);

    bool ret2 = UnifiedDataUtils::IsPersist("invalid param");
    EXPECT_FALSE(ret2);

    bool ret3 = UnifiedDataUtils::IsPersist("Picker");
    EXPECT_TRUE(ret3);

    bool ret4 = UnifiedDataUtils::IsPersist("Menu");
    EXPECT_TRUE(ret4);

    bool ret5 = UnifiedDataUtils::IsPersist("SystemShare");
    EXPECT_TRUE(ret5);
}

/**
* @tc.name: GetIntentionByString001
* @tc.desc: Normal testcase of IsPersist
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, GetIntentionByString001, TestSize.Level1)
{
    Intention ret = UnifiedDataUtils::GetIntentionByString("DataHub");
    EXPECT_EQ(ret, Intention::UD_INTENTION_DATA_HUB);

    Intention ret1 = UnifiedDataUtils::GetIntentionByString("drag");
    EXPECT_EQ(ret1, Intention::UD_INTENTION_DRAG);

    Intention ret2 = UnifiedDataUtils::GetIntentionByString("invalid param");
    EXPECT_EQ(ret2, UD_INTENTION_BUTT);

    Intention ret3 = UnifiedDataUtils::GetIntentionByString("Picker");
    EXPECT_EQ(ret3, Intention::UD_INTENTION_PICKER);

    Intention ret4 = UnifiedDataUtils::GetIntentionByString("Menu");
    EXPECT_EQ(ret4, Intention::UD_INTENTION_MENU);

    Intention ret5 = UnifiedDataUtils::GetIntentionByString("SystemShare");
    EXPECT_EQ(ret5, Intention::UD_INTENTION_SYSTEM_SHARE);
}

/**
* @tc.name: IsValidOptionsNonDrag001
* @tc.desc: Normal testcase of IsPersist
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, IsValidOptionsNonDrag001, TestSize.Level1)
{
    std::string keyDataHub = "udmf://DataHub/com.hmos.photos/CSl;cdcGFcmdkasaccCSCAAScscdc";
    std::string keyDrag = "udmf://drag/com.hmos.photos/CSl;cdcGFcmdkasaccCSCAAScscdc";
    std::string keyPicker = "udmf://Picker/com.hmos.photos/CSl;cdcGFcmdkasaccCSCAAScscdc";
    std::string keyMenu = "udmf://Menu/com.hmos.photos/CSl;cdcGFcmdkasaccCSCAAScscdc";
    std::string keySystemShare = "udmf://SystemShare/com.hmos.photos/CSl;cdcGFcmdkasaccCSCAAScscdc";
    std::string intentionDataHub = "DataHub";
    std::string intentionDrag = "drag";
    std::string intentionPicker = "Picker";
    std::string intentionMenu = "Menu";
    std::string intentionSystemShare = "SystemShare";
    std::string intentionEmpty = "";
    UnifiedKey key1("");

    bool ret = UnifiedDataUtils::IsValidOptionsNonDrag(key1, intentionDataHub);
    EXPECT_TRUE(ret);

    UnifiedKey key2(keyDataHub);
    bool ret1 = UnifiedDataUtils::IsValidOptionsNonDrag(key2, intentionEmpty);
    EXPECT_TRUE(ret1);
    bool ret2 = UnifiedDataUtils::IsValidOptionsNonDrag(key2, intentionDataHub);
    EXPECT_TRUE(ret2);
    bool ret3 = UnifiedDataUtils::IsValidOptionsNonDrag(key2, intentionDrag);
    EXPECT_FALSE(ret3);
    bool ret4 = UnifiedDataUtils::IsValidOptionsNonDrag(key2, intentionPicker);
    EXPECT_FALSE(ret4);
    bool ret5 = UnifiedDataUtils::IsValidOptionsNonDrag(key2, intentionMenu);
    EXPECT_FALSE(ret5);
    bool ret6 = UnifiedDataUtils::IsValidOptionsNonDrag(key2, intentionSystemShare);
    EXPECT_FALSE(ret6);
    UnifiedKey key3(keyDrag);
    bool ret7 = UnifiedDataUtils::IsValidOptionsNonDrag(key3, intentionDrag);
    EXPECT_FALSE(ret7);
    UnifiedKey key4(keyPicker);
    bool ret8 = UnifiedDataUtils::IsValidOptionsNonDrag(key4, intentionPicker);
    EXPECT_TRUE(ret8);
    UnifiedKey key5(keyMenu);
    bool ret9 = UnifiedDataUtils::IsValidOptionsNonDrag(key5, intentionMenu);
    EXPECT_TRUE(ret9);
    UnifiedKey key6(keySystemShare);
    bool ret10 = UnifiedDataUtils::IsValidOptionsNonDrag(key6, intentionSystemShare);
    EXPECT_TRUE(ret10);
}

/**
* @tc.name: IsValidOptionsNonDrag
* @tc.desc: Normal testcase of key and intention
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, IsAllowedQuery, TestSize.Level1)
{
    std::string keyDataHub = "udmf://DataHub/com.hmos.photos/CSl;cdcGFcmdkasaccCSCAAScscdc";
    std::string keyDrag = "udmf://drag/com.hmos.photos/CSl;cdcGFcmdkasaccCSCAAScscdc";
    std::string keyPicker = "udmf://Picker/com.hmos.photos/CSl;cdcGFcmdkasaccCSCAAScscdc";
    std::string keyMenu = "udmf://Menu/com.hmos.photos/CSl;cdcGFcmdkasaccCSCAAScscdc";
    std::string keySystemShare = "udmf://SystemShare/com.hmos.photos/CSl;cdcGFcmdkasaccCSCAAScscdc";
    std::string intentionDataHub = "DataHub";
    std::string intentionDrag = "drag";
    std::string intentionPicker = "Picker";
    std::string intentionMenu = "Menu";
    std::string intentionSystemShare = "SystemShare";
    std::string intentionEmpty = "";
    UnifiedKey key1("");

    bool ret = UnifiedDataUtils::IsValidOptionsNonDrag(key1, intentionDataHub);
    EXPECT_TRUE(ret);
    bool ret1 = UnifiedDataUtils::IsValidOptionsNonDrag(key1, intentionPicker);
    EXPECT_FALSE(ret1);
    UnifiedKey key2(keyDataHub);
    bool ret2 = UnifiedDataUtils::IsValidOptionsNonDrag(key2, intentionEmpty);
    EXPECT_TRUE(ret2);
    bool ret3 = UnifiedDataUtils::IsValidOptionsNonDrag(key2, intentionDataHub);
    EXPECT_TRUE(ret3);
    bool ret4 = UnifiedDataUtils::IsValidOptionsNonDrag(key2, intentionDrag);
    EXPECT_FALSE(ret4);
    bool ret5 = UnifiedDataUtils::IsValidOptionsNonDrag(key2, intentionPicker);
    EXPECT_FALSE(ret5);
    bool ret6 = UnifiedDataUtils::IsValidOptionsNonDrag(key2, intentionMenu);
    EXPECT_FALSE(ret6);
    bool ret7 = UnifiedDataUtils::IsValidOptionsNonDrag(key2, intentionSystemShare);
    EXPECT_FALSE(ret7);
    UnifiedKey key3(keyDrag);
    bool ret8 = UnifiedDataUtils::IsValidOptionsNonDrag(key3, intentionDrag);
    EXPECT_FALSE(ret8);
}

/**
* @tc.name: IsValidQuery001
* @tc.desc: Normal testcase of key and intention
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, IsValidQuery001, TestSize.Level1)
{
    std::string keyPicker = "udmf://Picker/com.hmos.photos/CSl;cdcGFcmdkasaccCSCAAScscdc";
    std::string intentionDataHub = "DataHub";
    std::string intentionDrag = "drag";
    std::string intentionPicker = "Picker";
    std::string intentionMenu = "Menu";
    std::string intentionSystemShare = "SystemShare";
    std::string intentionEmpty = "";

    UnifiedKey key(keyPicker);
    bool ret = UnifiedDataUtils::IsValidOptionsNonDrag(key, intentionPicker);
    EXPECT_TRUE(ret);

    bool ret1 = UnifiedDataUtils::IsValidOptionsNonDrag(key, intentionEmpty);
    EXPECT_TRUE(ret1);

    bool ret2 = UnifiedDataUtils::IsValidOptionsNonDrag(key, intentionDataHub);
    EXPECT_FALSE(ret2);

    bool ret3 = UnifiedDataUtils::IsValidOptionsNonDrag(key, intentionDrag);
    EXPECT_FALSE(ret3);

    bool ret4 = UnifiedDataUtils::IsValidOptionsNonDrag(key, intentionMenu);
    EXPECT_FALSE(ret4);

    bool ret5 = UnifiedDataUtils::IsValidOptionsNonDrag(key, intentionSystemShare);
    EXPECT_FALSE(ret5);
}

HWTEST_F(UnifiedMetaTest, IsValidOptions002, TestSize.Level1)
{
    UnifiedKey key;
    key.key = "key://";
    std::string intention;
    std::string validIntention;
    UnifiedDataUtils unifiedDataUtils;
    bool ret = unifiedDataUtils.IsValidOptions(key, intention, validIntention);
    EXPECT_FALSE(ret);
}

/**
* @tc.name: IsValidOptions003
* @tc.desc: Abnormal testcase of IsValidOptions, intention != validIntention
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, IsValidOptions003, TestSize.Level1)
{
    UnifiedKey key;
    key.key = "key://";
    std::string intention = "drag";
    std::string validIntention = "DataHub";
    UnifiedDataUtils unifiedDataUtils;
    bool ret = unifiedDataUtils.IsValidOptions(key, intention, validIntention);
    EXPECT_FALSE(ret);
}

/**
* @tc.name: IsValidOptions004
* @tc.desc: Abnormal testcase of IsValidOptions, key.intention != validIntention
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, IsValidOptions004, TestSize.Level1)
{
    UnifiedKey key;
    key.key = "key://";
    key.intention = "DataHub";
    std::string intention = "DataHub";
    std::string validIntention = "drag";
    UnifiedDataUtils unifiedDataUtils;
    bool ret = unifiedDataUtils.IsValidOptions(key, intention, validIntention);
    EXPECT_FALSE(ret);
}

/**
* @tc.name: ConvertToUDDetails001
* @tc.desc: Abnormal testcase of ConvertToUDDetails, object is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, ConvertToUDDetails001, TestSize.Level1)
{
    std::shared_ptr<Object> object = nullptr;
    EXPECT_NO_FATAL_FAILURE(ObjectUtils::ConvertToUDDetails(object));
}

/**
* @tc.name: GetValueSize001
* @tc.desc: Normal testcase of GetValueSize
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, GetValueSize001, TestSize.Level1)
{
    ValueType value = std::make_shared<OHOS::Media::PixelMap>();
    bool isCalValueType = true;
    int64_t ret = ObjectUtils::GetValueSize(value, isCalValueType);
    EXPECT_EQ(ret, (std::get<std::shared_ptr<OHOS::Media::PixelMap>>(value))->GetByteCount());
}

/**
* @tc.name: GetValueSize002
* @tc.desc: Normal testcase of GetValueSize
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, GetValueSize002, TestSize.Level1)
{
    ValueType value = std::make_shared<OHOS::AAFwk::Want>();
    bool isCalValueType = true;
    int64_t ret = ObjectUtils::GetValueSize(value, isCalValueType);
    EXPECT_NE(ret, 0);
}

/**
* @tc.name: GetValueSize003
* @tc.desc: Abnormal testcase of GetValueSize, value is invalid
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, GetValueSize003, TestSize.Level1)
{
    ValueType value = true;
    bool isCalValueType = true;
    int64_t ret = ObjectUtils::GetValueSize(value, isCalValueType);
    EXPECT_EQ(ret, std::visit([] (const auto &val) { return sizeof(val); }, value));
}

/* *
* @tc.name: GetObjectValueSize_001
* @tc.desc: Abnormal test of GetObjectValueSize, key is DETAILS
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, GetObjectValueSize_001, TestSize.Level1)
{
    std::shared_ptr<Object> object = std::make_shared<Object>();
    bool isCalValueType = true;
    object->value_["details"] = std::make_shared<OHOS::Media::PixelMap>();
    size_t ret = ObjectUtils::GetObjectValueSize(object, isCalValueType);
    EXPECT_EQ(ret, 0);
}

/* *
* @tc.name: GetAllObjectSize_001
* @tc.desc: Abnormal test of GetAllObjectSize, object is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, GetAllObjectSize_001, TestSize.Level1)
{
    std::shared_ptr<Object> object = nullptr;
    int64_t ret = ObjectUtils::GetAllObjectSize(object);
    EXPECT_EQ(ret, 0);
}

/**
* @tc.name: GetValue001
* @tc.desc: Normal testcase of IsPersist
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, GetValue001, TestSize.Level1)
{
    Object object;
    std::string key = "key";
    std::string content = "content";
    object.value_ = {
        {key, content}
    };
    std::string value;
    bool ret = object.GetValue(key, value);
    EXPECT_TRUE(ret);
    EXPECT_EQ(value, content);

    std::string valueEmpty;
    bool ret1 = object.GetValue("invalid key", valueEmpty);
    EXPECT_FALSE(ret1);
    EXPECT_TRUE(valueEmpty.empty());
}

/**
* @tc.name: GetValue002
* @tc.desc: Normal testcase of IsPersist
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, GetValue002, TestSize.Level1)
{
    Object object;
    std::shared_ptr<Object> objectInner = std::make_shared<Object>();
    std::string key = "key";
    std::string keyObj = "keyObj";
    std::string content = "content";
    objectInner->value_ = {
        {key, content}
    };
    object.value_ = {
        {key, content},
        {keyObj, objectInner}
    };
    std::shared_ptr<Object> value = std::make_shared<Object>();
    bool ret = object.GetValue(keyObj, value);
    EXPECT_TRUE(ret);

    std::string innerValue;
    bool ret1 = value->GetValue(key, innerValue);
    EXPECT_TRUE(ret1);
    EXPECT_EQ(innerValue, content);

    std::shared_ptr<Object> valueEmpty = std::make_shared<Object>();
    bool ret2 = object.GetValue("invalid key", valueEmpty);
    EXPECT_FALSE(ret2);
}

/**
* @tc.name: IsFileMangerIntention
* @tc.desc: IsFileMangerIntention testcase
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, IsFileMangerIntention, TestSize.Level1)
{
    std::string intentionDataHub = "DataHub";
    std::string intentionDrag = "drag";
    std::string intentionPicker = "Picker";
    std::string intentionMenu = "Menu";
    std::string intentionSystemShare = "SystemShare";

    bool ret = UnifiedDataUtils::IsFileMangerIntention(intentionDataHub);
    EXPECT_FALSE(ret);
    bool ret1 = UnifiedDataUtils::IsFileMangerIntention(intentionDrag);
    EXPECT_FALSE(ret1);
    bool ret2 = UnifiedDataUtils::IsFileMangerIntention(intentionPicker);
    EXPECT_TRUE(ret2);
    bool ret3 = UnifiedDataUtils::IsFileMangerIntention(intentionMenu);
    EXPECT_TRUE(ret3);
    bool ret4 = UnifiedDataUtils::IsFileMangerIntention(intentionSystemShare);
    EXPECT_TRUE(ret4);
}

/**
* @tc.name: IsFileMangerIntention
* @tc.desc: IsFileMangerIntention testcase
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, GetBelongsToFileType, TestSize.Level1)
{
    std::string utdId = "";
    std::string fileType = UnifiedDataUtils::GetBelongsToFileType(utdId);
    EXPECT_TRUE(fileType.empty());

    utdId = "general.html";
    fileType = UnifiedDataUtils::GetBelongsToFileType(utdId);
    EXPECT_TRUE(fileType.empty());

    utdId = "general.plain-text";
    fileType = UnifiedDataUtils::GetBelongsToFileType(utdId);
    EXPECT_TRUE(fileType.empty());

    utdId = "general.text";
    fileType = UnifiedDataUtils::GetBelongsToFileType(utdId);
    EXPECT_TRUE(fileType.empty());

    utdId = "aaccss";
    fileType = UnifiedDataUtils::GetBelongsToFileType(utdId);
    EXPECT_TRUE(fileType.empty());

    utdId = "general.file";
    fileType = UnifiedDataUtils::GetBelongsToFileType(utdId);
    EXPECT_EQ(fileType, "general.file");

    utdId = "general.image";
    fileType = UnifiedDataUtils::GetBelongsToFileType(utdId);
    EXPECT_EQ(fileType, "general.image");

    utdId = "general.avi";
    fileType = UnifiedDataUtils::GetBelongsToFileType(utdId);
    EXPECT_EQ(fileType, "general.video");

    utdId = "com.adobe.pdf";
    fileType = UnifiedDataUtils::GetBelongsToFileType(utdId);
    EXPECT_EQ(fileType, "general.file");
}
} // OHOS::Test