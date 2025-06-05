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

import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import unifiedDataChannel from '@ohos.data.unifiedDataChannel';
import uniformTypeDescriptor from '@ohos.data.uniformTypeDescriptor';

const TAG = "[udmfStageTest]"

export default function stageUdmfCallbackJsTest() {
  describe('stageUdmfCallbackJsTest', ():void =>{
    console.log(TAG + "*************Unit Test Begin*************");
    beforeAll(():void => {
      console.log('stageUdmfCallbackJsTest TestAbility context' + globalThis.abilityContext);
      console.info('beforeAll')
    })
    afterAll(():void =>{
      console.info('afterAll')
    })

    /**
     * @tc.number    : SUB_DistributedData_UDMF_SDK_UnifiedDataCallbackJsAPITest_0100
     * @tc.name      : unifiedDataChannel insertData callback interface test
     * @tc.desc      : unifiedDataChannel insertData callback interface test.
     * @tc.size      : MEDIUM
     * @tc.type      : Function
     * @tc.level     : Level 3
     */
    it('SUB_DistributedData_UDMF_SDK_UnifiedDataCallbackJsAPITest_0100', 0, (done) => {
      let options: unifiedDataChannel.Options = {}
      let plainText = new unifiedDataChannel.PlainText();
      plainText.textContent = 'this is textContent';
      let unifiedData = new unifiedDataChannel.UnifiedData(plainText);
      try {
        unifiedDataChannel.insertData(options, unifiedData, (err, data) => {
          if (err === undefined) {
            console.info(TAG + `data = ${data}, options = ${options}`);
            expect(err === undefined).assertFail();
            done();
          } else {
            console.error(TAG, `Failed, code is ${err.code},message is ${err.message} `);
            expect(err !== null).assertFail();
            done();
          }
        })
      } catch (error) {
        console.error(TAG, `Failed to insertData0100 code is ${error.code},message is ${error.message} `);
        expect(error.code).assertEqual('401');
        done();
      }
    });

    /**
     * @tc.name UdmfTestVisibilityOwn
     * @tc.desc insertData with visibility Own
     * @tc.type: Function
     * @tc.require: issueNumber
     */
    it('UdmfTestVisibilityOwn', 1, (done) {
      const TAG = 'UdmfTestVisibilityOwn:';
      console.info(TAG, 'start');
      try {
        let options: unifiedDataChannel.Options = { intention : unifiedDataChannel.Intention.DATA_HUB, 
          visibility : unifiedDataChannel.Visibility.OWN_PROCESS };
        let content = "content";
        let plainText = new unifiedDataChannel.PlainText();
        plainText.textContent = content;
        let unifiedData = new unifiedDataChannel.UnifiedData(plainText);
        unifiedDataChannel.insertData(options, unifiedData).then((data) => {
          console.info(TAG, `insert success. The key: ${data}`);
          let options = { key: data };
          console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
          unifiedDataChannel.queryData(options).then((data) => {
            console.info(TAG, 'query success.');
            expect(data.length).assertEqual(1);
            expect(data[0].getRecords()[0].textContent).assertEqual(content);
            unifiedDataChannel.deleteData(options).then((data) => {
              console.info(TAG, 'delete success.');
              expect(data.length).assertEqual(1);
              done();
            }).catch(() => {
              console.error(TAG, 'Unreachable code!');
              expect(null).assertFail();
              done();
            });
          }).catch(() => {
            console.error(TAG, 'Unreachable code!');
            expect(null).assertFail();
            done();
          });
        }).catch(() => {
          console.error(TAG, 'Unreachable code!');
          expect(null).assertFail();
          done();
        });
      } catch (e) {
        console.error(TAG, 'Unreachable code!');
        expect(null).assertFail();
        done();
      }
      console.info(TAG, 'end');
    });

    /**
     * @tc.name UdmfTestVisibilityAll
     * @tc.desc insertData with visibility All
     * @tc.type: Function
     * @tc.require: issueNumber
     */
    it('UdmfTestVisibilityAll', 1, (done) {
      const TAG = 'UdmfTestVisibilityAll:';
      console.info(TAG, 'start');
      try {
        let options: unifiedDataChannel.Options = { intention : unifiedDataChannel.Intention.DATA_HUB, 
          visibility : unifiedDataChannel.Visibility.ALL };
        let content = "content";
        let plainText = new unifiedDataChannel.PlainText();
        plainText.textContent = content;
        let unifiedData = new unifiedDataChannel.UnifiedData(plainText);
        unifiedDataChannel.insertData(options, unifiedData).then((data) => {
          console.info(TAG, `insert success. The key: ${data}`);
          let options = { key: data };
          console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
          unifiedDataChannel.queryData(options).then((data) => {
            console.info(TAG, 'query success.');
            expect(data.length).assertEqual(1);
            expect(data[0].getRecords()[0].textContent).assertEqual(content);
            unifiedDataChannel.deleteData(options).then((data) => {
              console.info(TAG, 'delete success.');
              expect(data.length).assertEqual(1);
              done();
            }).catch(() => {
              console.error(TAG, 'Unreachable code!');
              expect(null).assertFail();
              done();
            });
          }).catch(() => {
            console.error(TAG, 'Unreachable code!');
            expect(null).assertFail();
            done();
          });
        }).catch(() => {
          console.error(TAG, 'Unreachable code!');
          expect(null).assertFail();
          done();
        });
      } catch (e) {
        console.error(TAG, 'Unreachable code!');
        expect(null).assertFail();
        done();
      }
      console.info(TAG, 'end');
    });
  })

  console.log(TAG + "*************Unit Test End*************");
}