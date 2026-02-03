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

import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from 'deccjsunit/index';
import intelligence from '@ohos.data.intelligence';
import deviceInfo from '@ohos.deviceInfo';

const TAG = ['Intelligence_Test'];

let textConfig = {
  version: intelligence.ModelVersion.BASIC_MODEL,
  isNpuAvailable: false,
  cachePath: 'test'
};

let imageConfig = {
  version: intelligence.ModelVersion.BASIC_MODEL,
  isNpuAvailable: false,
  cachePath: 'image'
};

let currentDeviceIsPc = false;

describe('UdmfIntelligenceJsTest', function () {

  beforeAll(async () => {
    console.info(TAG + 'beforeAll');
    let deviceTypeInfo = deviceInfo.deviceType;
    currentDeviceIsPc = deviceTypeInfo === '2in1' ? true : false;
    console.info(TAG + 'the value of the deviceType is : ' + deviceInfo.deviceType);
  });
  beforeEach(async () => {
    console.info(TAG + 'beforeEach');
  });
  afterEach(async () => {
    console.info(TAG + 'afterEach');
  });
  afterAll(async () => {
    console.info(TAG + 'afterAll');
  });

  console.info('*************intelligence Test begin**************');
  let retArray = [401, 801, 313000000];


  /**
     * @tc.name intelligenceApiTest0100
     * @tc.number SUB_DistributedData_Intelligence_SDK_intelligenceApiTest_0100
     * @tc.desc splitText interface test
     * @tc.type Function
     */
  it('intelligenceApiTest0100', 0, async function (done) {
    console.info(TAG + 'intelligenceApiTest0100 start');
    let text =
      '日常生活中，我们对接触到的事物，会产生一个不假思索地看法，或者说直觉性的认知.百科全书里这样解释道“ 认知包括感觉、知觉、记忆、思维、想象和语言等。';
    let config = {
      size: 50,
      overlapRatio: 0.5
    };
    if (currentDeviceIsPc) {
      await intelligence.splitText(text, config)
        .then((data) => {
          console.info(TAG + 'get result:' + data);
          let dataSize = data.length;
          let ret = dataSize > 0;
          expect(ret).assertEqual(true);
          done();
        });
    } else {
      await intelligence.splitText(text, config)
        .then((data) => {
          console.info(TAG + 'get result:' + data);
          expect().assertFail();
          done();
        })
        .catch((err) => {
          console.info(TAG + 'get promise result:' + err.code);
          expect(err.code).assertEqual(801);
          done();
        });
    }
  });

  
});