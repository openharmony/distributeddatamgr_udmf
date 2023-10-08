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

import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from 'deccjsunit/index';
import UTD from '@ohos.data.uniformTypeDescriptor';

const ERROR_PARAMETER = '401';

describe('UdmfUtdJSTest', function () {
  /**
   * @tc.name UdmfTestTypeDescriptor001
   * @tc.desc Test Js Api 
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfTestTypeDescriptor001', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor001:';
    console.info(TAG, 'start');
    let typeObj = UTD.getTypeDescriptor("general.invallType");
    console.info(TAG, 'typeDescriptor, ret= ' + typeObj);
    if (typeObj == null) {
      console.info(TAG, 'typeDescriptor, typeObj == null is true');
    }
    expect((typeObj == null)).assertEqual(true);
    console.info(TAG, 'end');
  });

  /**
   * @tc.name UdmfTestTypeDescriptor002
   * @tc.desc Test Js Api 
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfTestTypeDescriptor002', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor002:';
    console.info(TAG, 'start');
    let typeObj = UTD.getTypeDescriptor("com.adobe.photoshop-image");
    console.info(TAG, 'typeDescriptor, ret ' + typeObj.toString());
    console.info(TAG, 'typeDescriptor, typeId ' + typeObj.typeId);
    console.info(TAG, 'typeDescriptor, belongingToTypes ' + typeObj.belongingToTypes);
    console.info(TAG, 'typeDescriptor, description ' + typeObj.description);
    console.info(TAG, 'typeDescriptor, referenceURL ' + typeObj.referenceURL);
    console.info(TAG, 'typeDescriptor, iconFile ' + typeObj.iconFile);
    expect(typeObj.typeId).assertEqual("com.adobe.photoshop-image");
    expect(typeObj.description).assertEqual("Adobe Photoshop document.");
    expect(typeObj.referenceURL).assertEqual("");
    expect(typeObj.iconFile).assertEqual("");
    console.info(TAG, 'end');
  });

  /**
   * @tc.name UdmfTestTypeDescriptor003
   * @tc.desc Test Js Api 
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
   it('UdmfTestTypeDescriptor003', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor003:';
    console.info(TAG, 'start');
    try {
      let typeObj = UTD.getTypeDescriptor("general.type-script");
      let typeObj2 = UTD.getTypeDescriptor("general.python-script");
      console.info(TAG, 'typeDescriptor, ret ' + typeObj);
      console.info(TAG, 'typeDescriptor, ret ' + typeObj2);
      let ret = typeObj.equals(typeObj2);
      console.info(TAG, 'typeObj equals with equals is ' + ret);
      expect(ret).assertEqual(false);
    } catch (e) {
      console.error(TAG, `get e. code is ${e.code},message is ${e.message} `);
      expect(e.code === ERROR_PARAMETER).assertTrue();
    }
    console.info(TAG, 'end');
  });

  /**
   * @tc.name UdmfTestTypeDescriptor004
   * @tc.desc Test Js Api 
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfTestTypeDescriptor004', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor004:';
    console.info(TAG, 'start');
    for (var utdType in UTD.UniformDataType) {
      console.info(TAG, 'typeDescriptor, utdType=' + UTD.UniformDataType[utdType]);
      let typeObj = UTD.getTypeDescriptor(UTD.UniformDataType[utdType]);
      if (typeObj != null) {
        console.info(TAG, 'typeDescriptor, typeId ' +  typeObj.typeId + ', belonging ' + typeObj.belongingToTypes);
        console.info(TAG, 'typeDescriptor, description ' + typeObj.description);
        console.info(TAG, 'typeDescriptor, referenceURL ' + typeObj.referenceURL + ', iconFile ' + typeObj.iconFile);
        expect(typeObj.typeId).assertEqual(UTD.UniformDataType[utdType]);
      } else {
        console.info(TAG, 'typeDescriptor, not found utdType object. utdType=' + UTD.UniformDataType[utdType]);
      }
    }
    console.info(TAG, 'end');
  });
});