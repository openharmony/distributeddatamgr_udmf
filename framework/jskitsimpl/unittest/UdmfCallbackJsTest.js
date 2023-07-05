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
import UDMF from '@ohos.data.UDMF';

const TEXT_CONTEXT_01 = 'TextContent01';
const TEXT_CONTEXT_02 = 'TextContent02';
const ERROR_PARAMETER = '401';

describe('UdmfCallbackJSTest', function () {

  let gPlainText1 = new UDMF.PlainText();
  gPlainText1.textContent = TEXT_CONTEXT_01;
  let gPlainText2 = new UDMF.PlainText();
  gPlainText2.textContent = TEXT_CONTEXT_02;

  const optionsValid = { intention: 'DataHub', };
  const optionsInValidIntention = { intention: 'Drag', };
  const optionsInValidKey = { key: 'udmf://drag/com.test.demo/123456789', };
  const optionsInValidAll = { intention: 'DataHub', key: 'udmf://drag/com.test.demo/123456789' };
  const unifiedData01 = new UDMF.UnifiedData(gPlainText1);
  const unifiedData02 = new UDMF.UnifiedData(gPlainText2);
  const unifiedDataInvalid = new UDMF.UnifiedData();

  /**
   * @tc.name UdmfInsertCallbackInvalidOptionsTest
   * @tc.desc Test Js Api insertData with invalid options
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfInsertCallbackInvalidOptionsTest', 0, async function (done) {
    const TAG = 'UdmfInsertCallbackInvalidOptionsTest:';
    console.info(TAG, 'start');
    try {
      UDMF.insertData(optionsInValidIntention, unifiedData01, (err, data) => {
        console.info(TAG, 'Unreachable code!');
        expect(null).assertFail();
        done();
      });
    } catch (e) {
      console.error(TAG, `get e. code is ${e.code},message is ${e.message} `);
      expect(e.code === ERROR_PARAMETER).assertTrue();
      done();
    }
    console.info(TAG, 'end');
  });

  /**
   * @tc.name UdmfInsertCallbackInvalidDataTest
   * @tc.desc Test Js Api insertData with invalid UnifiedData
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfInsertCallbackInvalidDataTest', 0, async function (done) {
    const TAG = 'UdmfInsertCallbackInvalidDataTest:';
    console.info(TAG, 'start');
    try {
      UDMF.insertData(optionsValid, unifiedDataInvalid, (err, data) => {
        expect(data).assertUndefined();
        console.error(TAG, `get fail. code is ${err.code},message is ${err.message} `);
        expect(err.code === ERROR_PARAMETER).assertTrue();
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
   * @tc.name UdmfInsertCallbackSucTest
   * @tc.desc Test Js Api insertData successful
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfInsertCallbackSucTest', 0, async function (done) {
    const TAG = 'UdmfInsertCallbackSucTest:';
    console.info(TAG, 'start');
    try {
      UDMF.insertData(optionsValid, unifiedData01, (err, data) => {
        expect(err).assertUndefined();
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDMF.queryData(options, (err, data) => {
          expect(err).assertUndefined();
          console.info(TAG, 'query success.');
          console.info(TAG, `data.length = ${data.length}.`);
          expect(data.length).assertEqual(1);
          let records = data[0].getRecords();
          console.info(TAG, `records.length = ${records.length}.`);
          console.info(TAG, `records[0].getType() = ${records[0].getType()}.`);
          console.info(TAG, `records[0].textContent = ${records[0].textContent}.`);
          expect(records.length).assertEqual(1);
          expect(records[0].getType()).assertEqual(UDMF.UnifiedDataType.PLAIN_TEXT);
          expect(records[0].textContent).assertEqual(TEXT_CONTEXT_01);
          done();
        });
      });
    } catch (e) {
      console.error(TAG, 'Unreachable code!');
      expect(null).assertFail();
      done();
    }
    console.info(TAG, 'end');
  });

  /**
   * @tc.name UdmfUpdateCallbackInvalidOptionsTest
   * @tc.desc Test Js Api updateData with invalid options
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfUpdateCallbackInvalidOptionsTest', 0, async function (done) {
    const TAG = 'UdmfUpdateCallbackInvalidOptionsTest:';
    console.info(TAG, 'start');
    try {
      UDMF.updateData(optionsInValidKey, unifiedData01, (err) => {
        console.error(TAG, 'Unreachable code!');
        expect(null).assertFail();
      });
      done();
    } catch (e) {
      console.error(TAG, `get e. code is ${e.code},message is ${e.message} `);
      expect(e.code === ERROR_PARAMETER).assertTrue();
      done();
    }
    console.info(TAG, 'end');
  });

  /**
   * @tc.name UdmfUpdateCallbackInvalidDataTest
   * @tc.desc Test Js Api updateData with invalid UnifiedData
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfUpdateCallbackInvalidDataTest', 0, async function (done) {
    const TAG = 'UdmfUpdateCallbackInvalidDataTest:';
    console.info(TAG, 'start');
    try {
      UDMF.insertData(optionsValid, unifiedData01, (err, data) => {
        expect(err).assertUndefined();
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `update start. The options: ${JSON.stringify(options)}`);
        UDMF.updateData(options, unifiedDataInvalid, (err) => {
          console.error(TAG, `get fail. code is ${err.code},message is ${err.message} `);
          expect(err.code === ERROR_PARAMETER).assertTrue();
          done();
        });
      });
    } catch (e) {
      console.error(TAG, 'Unreachable code!');
      expect(null).assertFail();
      done();
    }
    console.info(TAG, 'end');
  });

  /**
   * @tc.name UdmfUpdateCallbackSucTest
   * @tc.desc Test Js Api updateData successful
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfUpdateCallbackSucTest', 0, async function (done) {
    const TAG = 'UdmfUpdateCallbackSucTest:';
    console.info(TAG, 'start');
    try {
      UDMF.insertData(optionsValid, unifiedData01, (err, data) => {
        expect(err).assertUndefined();
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `update start. The options: ${JSON.stringify(options)}`);
        UDMF.updateData(options, unifiedData02, (err) => {
          expect(err).assertUndefined();
          console.info(TAG, 'update success.');
          UDMF.queryData(options, (err, data) => {
            expect(err).assertUndefined();
            console.info(TAG, 'query success.');
            expect(data.length).assertEqual(1);
            let records = data[0].getRecords();
            expect(records.length).assertEqual(1);
            expect(records[0].getType()).assertEqual(UDMF.UnifiedDataType.PLAIN_TEXT);
            expect(records[0].textContent).assertEqual(TEXT_CONTEXT_02);
            done();
          });
        });
      });

    } catch (e) {
      console.error(TAG, 'Unreachable code!');
      expect(null).assertFail();
      done();
    }
    console.info(TAG, 'end');
  });


  /**
   * @tc.name UdmfQueryCallbackInvalidOptionsTest
   * @tc.desc Test Js Api queryData with invalid options
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfQueryCallbackInvalidOptionsTest', 0, async function (done) {
    const TAG = 'UdmfQueryCallbackInvalidOptionsTest:';
    console.info(TAG, 'start');
    try {
      UDMF.queryData(optionsInValidAll, (err, data) => {
        console.error(TAG, 'Unreachable code!');
        expect(null).assertFail();
        done();
      });
    } catch (e) {
      console.error(TAG, `get e. code is ${e.code},message is ${e.message} `);
      expect(e.code === ERROR_PARAMETER).assertTrue();
      done();
    }
    console.info(TAG, 'end');
  });

  /**
   * @tc.name UdmfQueryCallbackSucTest
   * @tc.desc Test Js Api queryData successful
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfQueryCallbackSucTest', 0, async function (done) {
    const TAG = 'UdmfQueryCallbackSucTest:';
    console.info(TAG, 'start');
    try {
      UDMF.deleteData(optionsValid, (err, data) => {
        expect(err).assertUndefined();
        console.info(TAG, 'delete success.');
        UDMF.queryData(optionsValid, (err, data) => {
          console.info(TAG, 'query has no data.');
          expect(data).assertUndefined();
          UDMF.insertData(optionsValid, unifiedData01, (err, data) => {
            expect(err).assertUndefined();
            console.info(TAG, `insert success. The key: ${data}`);
            UDMF.insertData(optionsValid, unifiedData02, (err, data) => {
              expect(err).assertUndefined();
              console.info(TAG, `insert success. The key: ${data}`);
              UDMF.queryData(optionsValid, function (err, data) {
                expect(err).assertUndefined();
                console.info(TAG, 'query success.');
                expect(data.length).assertEqual(2);
                done();
              });
            });
          });
        });
      });
    } catch (e) {
      console.error(TAG, 'Unreachable code!');
      expect(null).assertFail();
      done();
    }
    console.info(TAG, 'end');
  });


  /**
   * @tc.name UdmfDeleteCallbackInvalidOptionsTest
   * @tc.desc Test Js Api deleteData with invalid options
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfDeleteCallbackInvalidOptionsTest', 0, async function (done) {
    const TAG = 'UdmfDeleteCallbackInvalidOptionsTest:';
    console.info(TAG, 'start');
    try {
      UDMF.deleteData(optionsInValidAll, (err, data) => {
        console.error(TAG, 'Unreachable code!');
        expect(null).assertFail();
        done();
      });
    } catch (e) {
      console.error(TAG, `get e. code is ${e.code},message is ${e.message} `);
      expect(e.code === ERROR_PARAMETER).assertTrue();
      done();
    }
    console.info(TAG, 'end');
  });

  /**
   * @tc.name UdmfDeleteCallbackSucTest
   * @tc.desc Test Js Api deleteData successful
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfDeleteCallbackSucTest', 0, async function (done) {
    const TAG = 'UdmfDeleteCallbackSucTest:';
    console.info(TAG, 'start');
    try {
      UDMF.insertData(optionsValid, unifiedData01, (err, data) => {
        expect(err).assertUndefined();
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDMF.queryData(options, (err, data) => {
          expect(err).assertUndefined();
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          UDMF.deleteData(options, (err, data) => {
            expect(err).assertUndefined();
            console.info(TAG, 'delete success.');
            expect(data.length).assertEqual(1);
            let records = data[0].getRecords();
            expect(records.length).assertEqual(1);
            expect(records[0].getType()).assertEqual(UDMF.UnifiedDataType.PLAIN_TEXT);
            expect(records[0].textContent).assertEqual(TEXT_CONTEXT_01);
            UDMF.queryData(options, (err, data) => {
              expect(data).assertUndefined();
              console.info(TAG, 'query has no data.');
              done();
            });
          });
        });
      });
    } catch (e) {
      console.error(TAG, 'Unreachable code!');
      expect(null).assertFail();
      done();
    }
    console.info(TAG, 'end');
  });
});