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
import UDC from '@ohos.data.unifiedDataChannel';
import UTD from '@ohos.data.uniformTypeDescriptor';
import image from '@ohos.multimedia.image';

const TEST_BUNDLE_NAME = 'MyBundleName';
const KEY_TEST_ELEMENT = 'TestKey';
const VALUE_TEST_ELEMENT = 'TestValue';
const TEST_ID = 123456;
const TEST_ABILITY_NAME = 'MyAbilityName';
const TEST_MODULE = 'MyModule';
const NUM_2M = 2 * 1024 * 1024;
const NUM_4M = 4 * 1024 * 1024;
const LONG_TEST2M = 'a'.repeat(NUM_2M);
const LONG_TESTOVER2M = 'a'.repeat((NUM_2M + 1));

let U8_ARRAY = new Uint8Array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10]);
const ERROR_PARAMETER = '401';
const NO_PERMISSION = '201';

describe('UdmfJSTest', function () {

  const optionsValid = { intention: 'DataHub', };

  /**
   * @tc.name UdmfTextTest
   * @tc.desc Test Js Api Text testcase
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfTextTest', 0, function () {
    console.info('UdmfTextTest start');
    let text = new UDC.Text();
    text.details = {
      Key: 'text' + KEY_TEST_ELEMENT,
      Value: 'text' + VALUE_TEST_ELEMENT,
    };
    let unifiedData = new UDC.UnifiedData(text);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(1);
    expect(records[0].details.Key).assertEqual('text' + KEY_TEST_ELEMENT);
    expect(records[0].details.Value).assertEqual('text' + VALUE_TEST_ELEMENT);
    console.info('UdmfTextTest end');
  });

  /**
   * @tc.name UdmfPlainTextTest
   * @tc.desc Test Js Api PlainText testcase
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfPlainTextTest', 0, function () {
    console.info('UdmfPlainTextTest start');
    let plainText = new UDC.PlainText();
    plainText.details = {
      Key: 'text' + KEY_TEST_ELEMENT,
      Value: 'text' + VALUE_TEST_ELEMENT,
    };
    plainText.textContent = 'textContent';
    plainText.abstract = 'abstract';
    let unifiedData = new UDC.UnifiedData(plainText);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(1);
    expect(records[0].details.Key).assertEqual('text' + KEY_TEST_ELEMENT);
    expect(records[0].details.Value).assertEqual('text' + VALUE_TEST_ELEMENT);
    expect(records[0].textContent).assertEqual('textContent');
    expect(records[0].abstract).assertEqual('abstract');
    console.info('UdmfPlainTextTest end');
  });

  /**
   * @tc.name UdmfHyperlinkTest
   * @tc.desc Test Js Api Hyperlink testcase
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfHyperlinkTest', 0, function () {
    console.info('UdmfHyperlinkTest start');
    let link = new UDC.Hyperlink();
    link.details = {
      Key: 'link' + KEY_TEST_ELEMENT,
      Value: 'link' + VALUE_TEST_ELEMENT,
    };
    link.url = 'url';
    link.description = 'description';
    let unifiedData = new UDC.UnifiedData(link);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(1);
    expect(records[0].details.Key).assertEqual('link' + KEY_TEST_ELEMENT);
    expect(records[0].details.Value).assertEqual('link' + VALUE_TEST_ELEMENT);
    expect(records[0].url).assertEqual('url');
    expect(records[0].description).assertEqual('description');
    console.info('UdmfHyperlinkTest end');
  });

  /**
   * @tc.name UdmfHtmlTest
   * @tc.desc Test Js Api HTML testcase
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfHtmlTest', 0, function () {
    console.info('UdmfHtmlTest start');
    let html = new UDC.HTML();
    html.details = {
      Key: 'html' + KEY_TEST_ELEMENT,
      Value: 'html' + VALUE_TEST_ELEMENT,
    };
    html.htmlContent = 'htmlContent';
    html.plainContent = 'plainContent';
    let unifiedData = new UDC.UnifiedData(html);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(1);
    expect(records[0].details.Key).assertEqual('html' + KEY_TEST_ELEMENT);
    expect(records[0].details.Value).assertEqual('html' + VALUE_TEST_ELEMENT);
    expect(records[0].htmlContent).assertEqual('htmlContent');
    expect(records[0].plainContent).assertEqual('plainContent');
    console.info('UdmfHtmlTest end');
  });

  /**
   * @tc.name UdmfFileTest
   * @tc.desc Test Js Api File testcase
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfFileTest', 0, function () {
    console.info('UdmfFileTest start');
    let file = new UDC.File();
    file.details = {
      Key: 'file' + KEY_TEST_ELEMENT,
      Value: 'file' + VALUE_TEST_ELEMENT,
    };
    file.uri = 'uri';
    let unifiedData = new UDC.UnifiedData(file);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(1);
    expect(records[0].details.Key).assertEqual('file' + KEY_TEST_ELEMENT);
    expect(records[0].details.Value).assertEqual('file' + VALUE_TEST_ELEMENT);
    expect(records[0].uri).assertEqual('uri');
    console.info('UdmfFileTest end');
  });

  /**
   * @tc.name UdmfFolderTest
   * @tc.desc Test Js Api Folder testcase
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfFolderTest', 0, function () {
    console.info('UdmfFolderTest start');
    let folder = new UDC.Folder();
    folder.details = {
      Key: 'folder' + KEY_TEST_ELEMENT,
      Value: 'folder' + VALUE_TEST_ELEMENT,
    };
    folder.uri = 'folderUri';
    let unifiedData = new UDC.UnifiedData(folder);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(1);
    expect(records[0].details.Key).assertEqual('folder' + KEY_TEST_ELEMENT);
    expect(records[0].details.Value).assertEqual('folder' + VALUE_TEST_ELEMENT);
    expect(records[0].uri).assertEqual('folderUri');
    console.info('UdmfFolderTest end');
  });

  /**
   * @tc.name UdmfImageTest
   * @tc.desc Test Js Api Image testcase
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfImageTest', 0, function () {
    console.info('UdmfImageTest start');
    let image = new UDC.Image();
    image.details = {
      Key: 'image' + KEY_TEST_ELEMENT,
      Value: 'image' + VALUE_TEST_ELEMENT,
    };
    image.imageUri = 'imageUri';
    let unifiedData = new UDC.UnifiedData(image);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(1);
    expect(records[0].details.Key).assertEqual('image' + KEY_TEST_ELEMENT);
    expect(records[0].details.Value).assertEqual('image' + VALUE_TEST_ELEMENT);
    expect(records[0].imageUri).assertEqual('imageUri');
    console.info('UdmfImageTest end');
  });

  /**
   * @tc.name UdmfVideoTest
   * @tc.desc Test Js Api Video testcase
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfVideoTest', 0, function () {
    console.info('UdmfVideoTest start');
    let video = new UDC.Video();
    video.details = {
      Key: 'video' + KEY_TEST_ELEMENT,
      Value: 'video' + VALUE_TEST_ELEMENT,
    };
    video.videoUri = 'videoUri';
    let unifiedData = new UDC.UnifiedData(video);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(1);
    expect(records[0].details.Key).assertEqual('video' + KEY_TEST_ELEMENT);
    expect(records[0].details.Value).assertEqual('video' + VALUE_TEST_ELEMENT);
    expect(records[0].videoUri).assertEqual('videoUri');
    console.info('UdmfVideoTest end');
  });

  /**
   * @tc.name UdmfSystemDefinedRecordTest
   * @tc.desc Test Js Api SystemDefinedRecord testcase
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfSystemDefinedRecordTest', 0, function () {
    console.info('UdmfSystemDefinedRecordTest start');
    let systemDefinedRecord = new UDC.SystemDefinedRecord();
    systemDefinedRecord.details = {
      recordKey1: 'systemDefinedRecord' + KEY_TEST_ELEMENT,
      recordKey2: 1,
      recordKey3: U8_ARRAY,
    };
    let unifiedData = new UDC.UnifiedData(systemDefinedRecord);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(1);
    expect(records[0].details.recordKey1).assertEqual('systemDefinedRecord' + KEY_TEST_ELEMENT);
    expect(records[0].details.recordKey2).assertEqual(1);
    for (let i = 0; i < U8_ARRAY.length; i++) {
      expect(records[0].details.recordKey3[i]).assertEqual(U8_ARRAY[i]);
    }
    console.info('UdmfSystemDefinedRecordTest end');
  });

  /**
   * @tc.name UdmfSystemDefinedPixelMapTest
   * @tc.desc Test Js Api SystemDefinedPixelMap testcase
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfSystemDefinedPixelMapTest', 0, function () {
    console.info('UdmfSystemDefinedPixelMapTest start');
    let systemDefinedPixelMap = new UDC.SystemDefinedPixelMap();
    systemDefinedPixelMap.details = {
      recordKey1: 'systemDefinedPixelMap' + KEY_TEST_ELEMENT,
      recordKey2: 1,
      recordKey3: U8_ARRAY,
    };
    systemDefinedPixelMap.rawData = U8_ARRAY;
    let unifiedData = new UDC.UnifiedData(systemDefinedPixelMap);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(1);
    expect(records[0].details.recordKey1).assertEqual('systemDefinedPixelMap' + KEY_TEST_ELEMENT);
    expect(records[0].details.recordKey2).assertEqual(1);
    for (let i = 0; i < U8_ARRAY.length; i++) {
      expect(records[0].details.recordKey3[i]).assertEqual(U8_ARRAY[i]);
    }
    for (let i = 0; i < U8_ARRAY.length; i++) {
      expect(records[0].rawData[i]).assertEqual(U8_ARRAY[i]);
    }
    console.info('UdmfSystemDefinedPixelMapTest end');
  });

  /**
   * @tc.name UdmfSystemDefinedFormTest
   * @tc.desc Test Js Api SystemDefinedForm testcase
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfSystemDefinedFormTest', 0, function () {
    console.info('UdmfSystemDefinedFormTest start');
    let form = new UDC.SystemDefinedForm();
    form.formId = TEST_ID;
    form.formName = 'MyFormName';
    form.bundleName = TEST_BUNDLE_NAME;
    form.abilityName = TEST_ABILITY_NAME;
    form.module = TEST_MODULE;
    form.details = {
      formKey1: 1,
      formKey2: 'form' + VALUE_TEST_ELEMENT,
      formKey3: U8_ARRAY,
    };
    let unifiedData = new UDC.UnifiedData(form);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(1);
    expect(records[0].details.formKey1).assertEqual(1);
    expect(records[0].details.formKey2).assertEqual('form' + VALUE_TEST_ELEMENT);
    for (let i = 0; i < U8_ARRAY.length; i++) {
      expect(records[0].details.formKey3[i]).assertEqual(U8_ARRAY[i]);
    }
    expect(records[0].formId).assertEqual(TEST_ID);
    expect(records[0].formName).assertEqual('MyFormName');
    expect(records[0].bundleName).assertEqual(TEST_BUNDLE_NAME);
    expect(records[0].abilityName).assertEqual(TEST_ABILITY_NAME);
    expect(records[0].module).assertEqual(TEST_MODULE);
    console.info('UdmfSystemDefinedFormTest end');
  });

  /**
   * @tc.name UdmfSystemDefinedAppItemTest
   * @tc.desc Test Js Api SystemDefinedAppItem testcase
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfSystemDefinedAppItemTest', 0, function () {
    console.info('UdmfSystemDefinedAppItemTest start');
    let appItem = new UDC.SystemDefinedAppItem();
    appItem.appId = 'MyAppId';
    appItem.appName = 'MyAppName';
    appItem.abilityName = TEST_ABILITY_NAME;
    appItem.bundleName = TEST_BUNDLE_NAME;
    appItem.appIconId = 'MyAppIconId';
    appItem.appLabelId = 'MyAppLabelId';
    appItem.details = {
      appItemKey1: 1,
      appItemKey2: 'appItem' + VALUE_TEST_ELEMENT,
      appItemKey3: U8_ARRAY,
    };
    let unifiedData = new UDC.UnifiedData(appItem);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(1);
    expect(records[0].details.appItemKey1).assertEqual(1);
    expect(records[0].details.appItemKey2).assertEqual('appItem' + VALUE_TEST_ELEMENT);
    for (let i = 0; i < U8_ARRAY.length; i++) {
      expect(records[0].details.appItemKey3[i]).assertEqual(U8_ARRAY[i]);
    }
    expect(records[0].appId).assertEqual('MyAppId');
    expect(records[0].appName).assertEqual('MyAppName');
    expect(records[0].abilityName).assertEqual(TEST_ABILITY_NAME);
    expect(records[0].bundleName).assertEqual(TEST_BUNDLE_NAME);
    expect(records[0].appIconId).assertEqual('MyAppIconId');
    expect(records[0].appLabelId).assertEqual('MyAppLabelId');
    console.info('UdmfSystemDefinedAppItemTest end');
  });

  /**
   * @tc.name UdmfSystemDefinedFormTest
   * @tc.desc Test Js Api ApplicationDefinedRecord testcase
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfApplicationDefinedRecord', 0, function () {
    console.info('UdmfApplicationDefinedRecord start');
    let applicationDefinedRecord = new UDC.ApplicationDefinedRecord();
    applicationDefinedRecord.applicationDefinedType = 'applicationDefinedType';
    applicationDefinedRecord.rawData = U8_ARRAY;
    let unifiedData = new UDC.UnifiedData(applicationDefinedRecord);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(1);
    expect(records[0].applicationDefinedType).assertEqual('applicationDefinedType');
    for (let i = 0; i < U8_ARRAY.length; i++) {
      expect(records[0].rawData[i]).assertEqual(U8_ARRAY[i]);
    }
    console.info('UdmfApplicationDefinedRecord end');
  });

  /**
   * @tc.name UdmfAllRecordsTest
   * @tc.desc Test Js AllRecords testcase
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfAllRecordsTest', 0, function () {
    console.info('UdmfAllRecordsTest start');
    let text = new UDC.Text();
    let unifiedDatas = new UDC.UnifiedData(text);
    let plainText = new UDC.PlainText();
    unifiedDatas.addRecord(plainText);
    let link = new UDC.Hyperlink();
    unifiedDatas.addRecord(link);
    let html = new UDC.HTML();
    unifiedDatas.addRecord(html);
    let file = new UDC.File();
    unifiedDatas.addRecord(file);
    let folder = new UDC.Folder();
    unifiedDatas.addRecord(folder);
    let image = new UDC.Image();
    unifiedDatas.addRecord(image);
    let video = new UDC.Video();
    unifiedDatas.addRecord(video);
    let systemDefinedRecord = new UDC.SystemDefinedRecord();
    unifiedDatas.addRecord(systemDefinedRecord);
    let systemDefinedPixelMap = new UDC.SystemDefinedPixelMap();
    unifiedDatas.addRecord(systemDefinedPixelMap);
    let form = new UDC.SystemDefinedForm();
    unifiedDatas.addRecord(form);
    let appItem = new UDC.SystemDefinedAppItem();
    unifiedDatas.addRecord(appItem);
    let applicationDefinedRecord = new UDC.ApplicationDefinedRecord();
    unifiedDatas.addRecord(applicationDefinedRecord);
    let records = unifiedDatas.getRecords();
    expect(records.length).assertEqual(13);
    expect(records[0].getType()).assertEqual(UTD.UniformDataType.TEXT);
    expect(records[1].getType()).assertEqual(UTD.UniformDataType.PLAIN_TEXT);
    expect(records[2].getType()).assertEqual(UTD.UniformDataType.HYPERLINK);
    expect(records[3].getType()).assertEqual(UTD.UniformDataType.HTML);
    expect(records[4].getType()).assertEqual(UTD.UniformDataType.FILE);
    expect(records[5].getType()).assertEqual(UTD.UniformDataType.FOLDER);
    expect(records[6].getType()).assertEqual(UTD.UniformDataType.IMAGE);
    expect(records[7].getType()).assertEqual(UTD.UniformDataType.VIDEO);
    expect(records[9].getType()).assertEqual(UTD.UniformDataType.OPENHARMONY_PIXEL_MAP);
    expect(records[10].getType()).assertEqual(UTD.UniformDataType.OPENHARMONY_FORM);
    expect(records[11].getType()).assertEqual(UTD.UniformDataType.OPENHARMONY_APP_ITEM);
    console.info('UdmfAllRecordsTest end');
  });

  /**
   * @tc.name UdmfText2MPlainText
   * @tc.desc PlainText 2MB
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfText2MPlainText', 0, async function (done) {
    const TAG = 'UdmfText2MPlainText:';
    console.info(TAG, 'start');
    try {
      let plainText = new UDC.PlainText();
      plainText.textContent = LONG_TEST2M;
      let unifiedData = new UDC.UnifiedData(plainText);
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          expect(data[0].getRecords()[0].textContent).assertEqual(LONG_TEST2M);
          UDC.deleteData(options).then((data) => {
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
   * @tc.name UdmfTextOver2MTest
   * @tc.desc Test Over 2MB
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfTextOver2MTest', 0, async function (done) {
    const TAG = 'UdmfTextOver2MTest:';
    console.info(TAG, 'start');
    try {
      let text = new UDC.Text();
      text.details = {
        title: '',
        content: LONG_TESTOVER2M,
      };
      let unifiedData = new UDC.UnifiedData(text);
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          expect(data[0].getRecords()[0].details.content).assertEqual(LONG_TESTOVER2M);
          UDC.deleteData(options).then((data) => {
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
   * @tc.name UdmfTextOver2MPlainText
   * @tc.desc PlainText Over 2MB
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfTextOver2MPlainText', 0, async function (done) {
    const TAG = 'UdmfTextOver2MPlainText:';
    console.info(TAG, 'start');
    try {
      let plainText = new UDC.PlainText();
      plainText.textContent = LONG_TESTOVER2M;
      let unifiedData = new UDC.UnifiedData(plainText);
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          expect(data[0].getRecords()[0].textContent).assertEqual(LONG_TESTOVER2M);
          UDC.deleteData(options).then((data) => {
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
   * @tc.name UdmfTextOver2MHyperlink
   * @tc.desc Hyperlink Over 2MB
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfTextOver2MHyperlink', 0, async function (done) {
    const TAG = 'UdmfTextOver2MHyperlink:';
    console.info(TAG, 'start');
    try {
      let link = new UDC.Hyperlink();
      link.url = LONG_TESTOVER2M;
      let unifiedData = new UDC.UnifiedData(link);
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          expect(data[0].getRecords()[0].url).assertEqual(LONG_TESTOVER2M);
          UDC.deleteData(options).then((data) => {
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
   * @tc.name UdmfTextOver2MHTML
   * @tc.desc HTML Over 2MB
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfTextOver2MHTML', 0, async function (done) {
    const TAG = 'UdmfTextOver2MHTML:';
    console.info(TAG, 'start');
    try {
      let html = new UDC.HTML();
      html.htmlContent = LONG_TESTOVER2M;
      let unifiedData = new UDC.UnifiedData(html);
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          expect(data[0].getRecords()[0].htmlContent).assertEqual(LONG_TESTOVER2M);
          UDC.deleteData(options).then((data) => {
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
   * @tc.name UdmfTextOver2MSystemDefinedRecord
   * @tc.desc SystemDefinedRecord Over 2MB
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfTextOver2MSystemDefinedRecord', 0, async function (done) {
    const TAG = 'UdmfTextOver2MSystemDefinedRecord:';
    console.info(TAG, 'start');
    try {
      let systemDefinedRecord = new UDC.SystemDefinedRecord();
      systemDefinedRecord.details = {
        title: '',
        content: LONG_TESTOVER2M
      };
      let unifiedData = new UDC.UnifiedData(systemDefinedRecord);
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          expect(data[0].getRecords()[0].details.content).assertEqual(LONG_TESTOVER2M);
          UDC.deleteData(options).then((data) => {
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
   * @tc.name UdmfTextOver2MSystemDefinedForm
   * @tc.desc SystemDefinedForm Over 2MB
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfTextOver2MSystemDefinedForm', 0, async function (done) {
    const TAG = 'UdmfTextOver2MSystemDefinedForm:';
    console.info(TAG, 'start');
    try {
      let systemDefinedForm = new UDC.SystemDefinedForm();
      systemDefinedForm.formId = 123;
      systemDefinedForm.formName = '1';
      systemDefinedForm.bundleName = 'MyBundleName';
      systemDefinedForm.abilityName = 'abilityName';
      systemDefinedForm.module = LONG_TESTOVER2M;
      let unifiedData = new UDC.UnifiedData(systemDefinedForm);
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          console.info(TAG, 'formId= ' + data[0].getRecords()[0].formId);
          console.info(TAG, 'formName= ' + data[0].getRecords()[0].formName);
          console.info(TAG, 'bundleName= ' + data[0].getRecords()[0].bundleName);
          console.info(TAG, 'abilityName= ' + data[0].getRecords()[0].abilityName);
          expect(data[0].getRecords()[0].module).assertEqual(LONG_TESTOVER2M);
          UDC.deleteData(options).then((data) => {
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
   * @tc.name UdmfTextOver2MSystemDefinedAppItem
   * @tc.desc SystemDefinedAppItem Over 2MB
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfTextOver2MSystemDefinedAppItem', 0, async function (done) {
    const TAG = 'UdmfTextOver2MSystemDefinedAppItem:';
    console.info(TAG, 'start');
    try {
      let systemDefinedAppItem = new UDC.SystemDefinedAppItem();
      systemDefinedAppItem.appId = '1';
      systemDefinedAppItem.appName = '2';
      systemDefinedAppItem.appIconId = '3';
      systemDefinedAppItem.appLabelId = '4';
      systemDefinedAppItem.bundleName = '5';
      systemDefinedAppItem.abilityName = LONG_TESTOVER2M;
      let unifiedData = new UDC.UnifiedData(systemDefinedAppItem);
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          console.info(TAG, 'appId= ' + data[0].getRecords()[0].appId);
          console.info(TAG, 'appName= ' + data[0].getRecords()[0].appName);
          console.info(TAG, 'appIconId= ' + data[0].getRecords()[0].appIconId);
          console.info(TAG, 'appLabelId= ' + data[0].getRecords()[0].appLabelId);
          console.info(TAG, 'bundleName= ' + data[0].getRecords()[0].bundleName);
          expect(data[0].getRecords()[0].abilityName).assertEqual(LONG_TESTOVER2M);
          UDC.deleteData(options).then((data) => {
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
   * @tc.name UdmfTextOver2MSystemDefinedPixelMap
   * @tc.desc SystemDefinedPixelMap Over 2MB
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfTextOver2MSystemDefinedPixelMap', 0, async function (done) {
    const TAG = 'UdmfTextOver2MSystemDefinedPixelMap:';
    console.info(TAG, 'start');
    try {
      let text = new UDC.SystemDefinedPixelMap();
      let longU8ArrayData = new Uint8Array(NUM_4M);
      longU8ArrayData.fill(0);
      text.rawData = longU8ArrayData;
      text.details = {
        recordKey1: 'systemDefinedPixelMap' + KEY_TEST_ELEMENT,
        recordKey2: U8_ARRAY,
      };
      let unifiedData = new UDC.UnifiedData(text);
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);          
          let records = data[0].getRecords();
          expect(records.length).assertEqual(1);
          expect(records[0].details.recordKey1).assertEqual('systemDefinedPixelMap' + KEY_TEST_ELEMENT);
          for (let i = 0; i < U8_ARRAY.length; i++) {
            expect(records[0].details.recordKey2[i]).assertEqual(U8_ARRAY[i]);
          }
          expect(records[0].rawData.toString()).assertEqual(longU8ArrayData.toString());
          UDC.deleteData(options).then((data) => {
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
   * @tc.name UdmfTextOver2MApplicationDefinedRecord
   * @tc.desc ApplicationDefinedRecord Over 2MB
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfTextOver2MApplicationDefinedRecord', 0, async function (done) {
    const TAG = 'UdmfTextOver2MApplicationDefinedRecord:';
    console.info(TAG, 'start');
    try {
      let text = new UDC.ApplicationDefinedRecord();
      text.applicationDefinedType = '1';
      text.rawData = new Uint8Array(NUM_4M);
      let unifiedData = new UDC.UnifiedData(text);
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          UDC.deleteData(options).then((data) => {
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
   * @tc.name UdmfText4M
   * @tc.desc UdmfText4M 4MB
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfText4M', 0, async function (done) {
    const TAG = 'UdmfText4M:';
    console.info(TAG, 'start');
    try {
      let text = new UDC.PlainText();
      text.textContent = LONG_TEST2M;
      let unifiedData = new UDC.UnifiedData(text);
      let html = new UDC.HTML();
      html.htmlContent = LONG_TEST2M;
      unifiedData.addRecord(html);
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          let records = data[0].getRecords();
          console.info(TAG, `records.length = ${records.length}.`);
          console.info(TAG, `records[0] = ${records[0].textContent === LONG_TEST2M}.`);
          console.info(TAG, `records[1] = ${records[1].htmlContent === LONG_TEST2M}.`);
          console.info(TAG, `records[0].getType() = ${records[0].getType()}.`);
          console.info(TAG, `records[1].getType() = ${records[1].getType()}.`);
          console.info(TAG, `records[0].getType() = ${records[0].getType() === UTD.UniformDataType.PLAIN_TEXT}.`);
          console.info(TAG, `records[1].getType() = ${records[1].getType() === UTD.UniformDataType.HTML}.`);
          expect(records[0].textContent).assertEqual(LONG_TEST2M);
          expect(records[1].htmlContent).assertEqual(LONG_TEST2M);
          UDC.deleteData(options).then((data) => {
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
   * @tc.name UnifiedDataPropertiesTest001
   * @tc.desc Test Js UnifiedDataProperties testcase
   * @tc.type: FUNC
   * @tc.require:
   */
  it('UnifiedDataPropertiesTest001', 0, function () {
    const TAG = 'UnifiedDataPropertiesTest001';
    console.info(TAG, 'start');
    let text = new UDC.Text();
    let unifiedDatas = new UDC.UnifiedData();
    unifiedDatas.addRecord(text);
    let properties = unifiedDatas.properties;
    expect(typeof properties).assertEqual('object');
    expect(typeof properties.extras).assertEqual('object');
    expect(typeof properties.tag).assertEqual('string');
    expect(typeof properties.timestamp).assertEqual('object');
    expect(typeof properties.shareOptions).assertEqual('number');
    expect(typeof properties.getDelayData).assertEqual('undefined');
  });

  /**
   * @tc.name UnifiedDataPropertiesTest002
   * @tc.desc Test Js UnifiedDataProperties testcase
   * @tc.type: FUNC
   * @tc.require:
   */
  it('UnifiedDataPropertiesTest002', 0, function () {
    const TAG = 'UnifiedDataPropertiesTest002';
    console.info(TAG, 'start');
    let text = new UDC.Text();
    let unifiedData = new UDC.UnifiedData(text);
    let properties = new UDC.UnifiedDataProperties();

    expect(properties.shareOptions).assertEqual(UDC.ShareOptions.CROSS_APP);
    properties.shareOptions = UDC.ShareOptions.IN_APP;
    unifiedData.properties = properties;
    expect(unifiedData.properties.shareOptions).assertEqual(UDC.ShareOptions.IN_APP);
    unifiedData.properties.shareOptions = UDC.ShareOptions.CROSS_APP;
    expect(unifiedData.properties.shareOptions).assertEqual(UDC.ShareOptions.CROSS_APP);

    expect(unifiedData.properties.tag).assertEqual('');
    unifiedData.properties.tag = 'DataTag';
    expect(unifiedData.properties.tag).assertEqual('DataTag');

    expect(Object.keys(unifiedData.properties.extras).length).assertEqual(0);
    let person = {fname: 'John', lname: 'Doe', age: 25};
    unifiedData.properties.extras = person;
    expect(Object.keys(unifiedData.properties.extras).length).assertEqual(3);
    expect(unifiedData.properties.extras.fname).assertEqual(person.fname);
  });

  /**
   * @tc.name UnifiedDataPropertiesTest003
   * @tc.desc Test Js UnifiedDataProperties testcase
   * @tc.type: FUNC
   * @tc.require:
   */
  it('UnifiedDataPropertiesTest003', 0, function () {
    const TAG = 'UnifiedDataPropertiesTest003';
    console.info(TAG, 'start');
    let text = new UDC.Text();
    let unifiedData = new UDC.UnifiedData(text);

    function func(inputStr) {
      console.info(TAG, 'execute func');
      let text = new UDC.Text();
      text.details = {
        Key: inputStr + KEY_TEST_ELEMENT,
        Value: inputStr + VALUE_TEST_ELEMENT,
      };
      let data = new UDC.UnifiedData(text);
      data.properties.tag = 'FileTag';
      return data;
    }
    unifiedData.properties.getDelayData = func;
    const data = unifiedData.properties.getDelayData('inputTest');
    let records = data.getRecords();
    expect(records.length).assertEqual(1);
    expect(records[0].details.Key).assertEqual('inputTest' + KEY_TEST_ELEMENT);
    expect(records[0].details.Value).assertEqual('inputTest' + VALUE_TEST_ELEMENT);
    expect(data.properties.tag).assertEqual('FileTag');
  });

  /**
   * @tc.name UnifiedDataHasType
   * @tc.desc Test Js UnifiedDataProperties testcase
   * @tc.type: FUNC
   * @tc.require:
   */
  it('UnifiedDataHasType', 0, function () {
    const TAG = 'UnifiedDataHasType';
    console.info(TAG, 'start');
    const textType = 'general.text';
    const plaintextType = 'general.plain-text';
    const htmlType = 'general.html';

    let text = new UDC.Text();
    let systemDefinedValue = 'systemDefinedValue';
    let hyperlinkValue = 'hyperlinkValue';
    text.addEntry(UTD.UniformDataType.HYPERLINK, hyperlinkValue);
    text.addEntry('openharmony.app-item', systemDefinedValue);
    let unifiedData = new UDC.UnifiedData(text);
    expect(unifiedData.hasType(textType)).assertEqual(true);
    expect(unifiedData.hasType(htmlType)).assertEqual(false);
    expect(unifiedData.hasType(UTD.UniformDataType.HYPERLINK)).assertEqual(true);
    expect(unifiedData.hasType('openharmony.app-item')).assertEqual(true);
    let types = unifiedData.getTypes();
    expect(types.length).assertEqual(1);
    expect(types.includes(textType)).assertTrue();
    expect(types.includes(UTD.UniformDataType.HYPERLINK)).assertFalse();
    expect(types.includes('openharmony.app-item')).assertFalse();

    let html = new UDC.HTML();
    unifiedData.addRecord(html);
    expect(unifiedData.hasType(textType)).assertEqual(true);
    expect(unifiedData.hasType(htmlType)).assertEqual(true);
    expect(unifiedData.hasType(plaintextType)).assertEqual(false);
    types = unifiedData.getTypes();
    expect(types.length).assertEqual(2);
    expect(types.includes(textType)).assertTrue();
    expect(types.includes(htmlType)).assertTrue();
    expect(types.includes(textType)).assertTrue();
    expect(types.includes(UTD.UniformDataType.HYPERLINK)).assertFalse();
    expect(types.includes('openharmony.app-item')).assertFalse();
  });

  /**
   * @tc.name UnifiedRecordConstruct001
   * @tc.desc Test Js UnifiedRecord testcase
   * @tc.type: FUNC
   * @tc.require:
   */
  it('UnifiedRecordConstruct001', 0, async function () {
    const TAG = 'UnifiedRecordConstruct001';
    console.info(TAG, 'start');

    const dataUri = new ArrayBuffer(256);
    let view1 = new Uint32Array(dataUri);
    view1[0] = 123456;
    let record1 = new UDC.UnifiedRecord('general.message', dataUri);
    const data1 = record1.getValue();
    expect(data1.byteLength).assertEqual(256);
    let view2 = new Uint32Array(data1);
    expect(view1[0]).assertEqual(view2[0]);

    let record2 = new UDC.UnifiedRecord('general.message', 'xxx.com');
    const data2 = record2.getValue();
    expect(data2).assertEqual('xxx.com');

    let record3 = new UDC.UnifiedRecord('general.message', 8899);
    const data3 = record3.getValue();
    expect(data3).assertEqual(8899);

    let record4 = new UDC.UnifiedRecord('general.message', 8899.7788);
    const data4 = record4.getValue();
    expect(data4).assertEqual(8899.7788);

    const buffer = new ArrayBuffer(128);
    const opt = {
      size: { height: 5, width: 5 },
      pixelFormat: 3,
      editable: true,
      alphaType: 1,
      scaleMode: 1,
    };
    const pixelMap = await image.createPixelMap(buffer, opt);
    let record5 = new UDC.UnifiedRecord('openharmony.pixel-map', pixelMap);
    const data5 = record5.getValue();
    data5.getImageInfo().then((imageInfo)=>{
      expect(imageInfo.size.height).assertEqual(opt.size.height);
      expect(imageInfo.pixelFormat).assertEqual(opt.pixelFormat);
    });
    
    const wantText = {
      bundleName: 'com.example.myapplication1',
      abilityName: 'com.example.myapplication1.MainAbility',
    };
    let record6 = new UDC.UnifiedRecord('openharmony.want', wantText);
    const data6 = record6.getValue();
    expect(data6.bundleName).assertEqual(wantText.bundleName);
    expect(data6.abilityName).assertEqual(wantText.abilityName);
  });

  /**
   * @tc.name UnifiedRecordConstruct002
   * @tc.desc Test Js UnifiedData GetRecords testcase
   * @tc.type: FUNC
   * @tc.require:
   */
  it('UnifiedRecordConstruct002', 0, async function () {
    const TAG = 'UnifiedRecordConstruct002';
    console.info(TAG, 'start');

    const dataUri = new ArrayBuffer(256);
    let view1 = new Uint32Array(dataUri);
    view1[0] = 123456;
    let record1 = new UDC.UnifiedRecord('general.message', dataUri);

    let unifiedData = new UDC.UnifiedData(record1);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(1);

    let record2 = new UDC.UnifiedRecord('general.message', 'xxx.com');
    unifiedData.addRecord(record2);
    let record3 = new UDC.UnifiedRecord('general.message', 8899);
    unifiedData.addRecord(record3);
    let record4 = new UDC.UnifiedRecord('general.message', 8899.7788);
    unifiedData.addRecord(record4);
    const buffer = new ArrayBuffer(128);
    const opt = {
      size: { height: 5, width: 5 },
      pixelFormat: 3,
      editable: true,
      alphaType: 1,
      scaleMode: 1,
    };
    const pixelMap = await image.createPixelMap(buffer, opt);
    let record5 = new UDC.UnifiedRecord('openharmony.pixel-map', pixelMap);
    unifiedData.addRecord(record5);
    const wantText = {
      bundleName: 'com.example.myapplication1',
      abilityName: 'com.example.myapplication1.MainAbility',
    };
    let record6 = new UDC.UnifiedRecord('openharmony.want', wantText);
    unifiedData.addRecord(record6);
    
    records = unifiedData.getRecords();
    expect(records.length).assertEqual(6);
    const data1 = records[0].getValue();
    expect(data1.byteLength).assertEqual(256);
    let view2 = new Uint32Array(data1);
    expect(view1[0]).assertEqual(view2[0]);
    const data2 = records[1].getValue();
    expect(data2).assertEqual('xxx.com');
    const data3 = records[2].getValue();
    expect(data3).assertEqual(8899);
    const data4 = records[3].getValue();
    expect(data4).assertEqual(8899.7788);
    const data5 = records[4].getValue();
    data5.getImageInfo().then((imageInfo)=>{
      expect(imageInfo.size.height).assertEqual(opt.size.height);
      expect(imageInfo.pixelFormat).assertEqual(opt.pixelFormat);
    });
    const data6 = records[5].getValue();
    expect(data6.bundleName).assertEqual(wantText.bundleName);
    expect(data6.abilityName).assertEqual(wantText.abilityName);
  });

  /**
   * @tc.name UnifiedRecordConstruct003
   * @tc.desc Test Js UnifiedData GetRecords testcase
   * @tc.type: FUNC
   * @tc.require:
   */
  it('UnifiedRecordConstruct003', 0, async function () {
    const TAG = 'UnifiedRecordConstruct003';
    console.info(TAG, 'start');

    const dataUri = new ArrayBuffer(256);
    let view1 = new Uint32Array(dataUri);
    view1[0] = 123456;
    let record1 = new UDC.UnifiedRecord('general.text', dataUri);
    let unifiedData = new UDC.UnifiedData(record1);
    let record2 = new UDC.UnifiedRecord('general.text', 'xxx.com');
    unifiedData.addRecord(record2);
    let record3 = new UDC.UnifiedRecord('general.text', 8899);
    unifiedData.addRecord(record3);
    let record4 = new UDC.UnifiedRecord('general.text', 8899.7788);
    unifiedData.addRecord(record4);

    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(4);
    const data1 = records[0].getValue();
    expect(data1.byteLength).assertEqual(256);
    let view2 = new Uint32Array(data1);
    expect(view1[0]).assertEqual(view2[0]);
    const data2 = records[1].getValue();
    expect(data2).assertEqual('xxx.com');
    const data3 = records[2].getValue();
    expect(data3).assertEqual(8899);
    const data4 = records[3].getValue();
    expect(data4).assertEqual(8899.7788);
  });

  /**
   * @tc.name UnifiedRecordConstruct004
   * @tc.desc Test Js UnifiedData GetRecords testcase
   * @tc.type: FUNC
   * @tc.require:
   */
  it('UnifiedRecordConstruct004', 0, async function () {
    const TAG = 'UnifiedRecordConstruct004';
    console.info(TAG, 'start');

    const dataUri = new ArrayBuffer(256);
    let view1 = new Uint32Array(dataUri);
    view1[0] = 123456;
    let record1 = new UDC.UnifiedRecord('otherType', dataUri);
    let unifiedData = new UDC.UnifiedData(record1);
    let record2 = new UDC.UnifiedRecord('otherType', 'xxx.com');
    unifiedData.addRecord(record2);
    let record3 = new UDC.UnifiedRecord('otherType', 8899);
    unifiedData.addRecord(record3);
    let record4 = new UDC.UnifiedRecord('otherType', 8899.7788);
    unifiedData.addRecord(record4);

    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(4);
    const data1 = records[0].getValue();
    expect(data1.byteLength).assertEqual(256);
    let view2 = new Uint32Array(data1);
    expect(view1[0]).assertEqual(view2[0]);
    const data2 = records[1].getValue();
    expect(data2).assertEqual('xxx.com');
    const data3 = records[2].getValue();
    expect(data3).assertEqual(8899);
    const data4 = records[3].getValue();
    expect(data4).assertEqual(8899.7788);
  });

  /**
   * @tc.name UDSTest001
   * @tc.desc
   * @tc.type: FUNC
   * @tc.require:
   */
  it('UDSTest001', 0, async function () {
    const TAG = 'UDSTest001';
    console.info(TAG, 'start');

    let plainTextDetails = {
      'key1': 'value1',
      'key2': 'value2',
    };
    let plainText = {
      uniformDataType: UTD.UniformDataType.PLAIN_TEXT,
      textContent: 'This is plainText textContent example',
      abstract: 'this is abstract',
      details: plainTextDetails
    };
    let record1 = new UDC.UnifiedRecord(UTD.UniformDataType.PLAIN_TEXT, plainText);
    let unifiedData = new UDC.UnifiedData(record1);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(1);
    const value1 = records[0].getValue();

    expect(value1.uniformDataType).assertEqual(plainText.uniformDataType);
    expect(value1.textContent).assertEqual(plainText.textContent);
    expect(value1.abstract).assertEqual(plainText.abstract);
    expect(value1.details.key1).assertEqual(plainText.details.key1);
    expect(value1.details.key2).assertEqual(plainText.details.key2);
  });

  /**
   * @tc.name UDSTest002
   * @tc.desc
   * @tc.type: FUNC
   * @tc.require:
   */
  it('UDSTest002', 0, async function (done) {
    const TAG = 'UDSTest002';
    console.info(TAG, 'start');

    let plainTextDetails = {
      'key1': 'value1',
      'key2': 'value2',
    };
    let plainText = {
      uniformDataType: UTD.UniformDataType.PLAIN_TEXT,
      textContent: 'This is plainText textContent example',
      abstract: 'this is abstract',
      details: plainTextDetails
    };
    let record1 = new UDC.UnifiedRecord(UTD.UniformDataType.PLAIN_TEXT, plainText);
    let unifiedData = new UDC.UnifiedData(record1);
    
    try {
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          let records = data[0].getRecords();
          expect(records.length).assertEqual(1);
          let value = records[0].getValue();
          expect(value.uniformDataType).assertEqual(plainText.uniformDataType);
          expect(value.textContent).assertEqual(plainText.textContent);
          expect(value.abstract).assertEqual(plainText.abstract);
          expect(value.details.key1).assertEqual(plainText.details.key1);
          expect(value.details.key2).assertEqual(plainText.details.key2);
          UDC.deleteData(options).then((data) => {
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
  });

  /**
   * @tc.name UDSTest003
   * @tc.desc
   * @tc.type: FUNC
   * @tc.require:
   */
  it('UDSTest003', 0, async function (done) {
    const TAG = 'UDSTest003';
    console.info(TAG, 'start');

    let hyperLinkDetails = {
      'key1': 'value1',
      'key2': 'value2',
    };
    let hyperLink = {
      uniformDataType: UTD.UniformDataType.HYPERLINK,
      url: 'www.xxx',
      description: 'hyperlinkDescription',
      details: hyperLinkDetails
    };
    let record1 = new UDC.UnifiedRecord(UTD.UniformDataType.HYPERLINK, hyperLink);
    let unifiedData = new UDC.UnifiedData(record1);
    
    try {
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          let records = data[0].getRecords();
          expect(records.length).assertEqual(1);
          let value = records[0].getValue();
          expect(value.uniformDataType).assertEqual(hyperLink.uniformDataType);
          expect(value.url).assertEqual(hyperLink.url);
          expect(value.description).assertEqual(hyperLink.description);
          expect(value.details.key1).assertEqual(hyperLink.details.key1);
          expect(value.details.key2).assertEqual(hyperLink.details.key2);
          UDC.deleteData(options).then((data) => {
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
  });

  /**
   * @tc.name UDSTest004
   * @tc.desc
   * @tc.type: FUNC
   * @tc.require:
   */
  it('UDSTest004', 0, async function (done) {
    const TAG = 'UDSTest004';
    console.info(TAG, 'start');

    let htmlDetails = {
      'key1': 'value1',
      'key2': 'value2',
    };
    let html = {
      uniformDataType: UTD.UniformDataType.HTML,
      htmlContent: 'www.xxx',
      plainContent: 'htmlDescription',
      details: htmlDetails
    };
    let record1 = new UDC.UnifiedRecord(UTD.UniformDataType.HTML, html);
    let unifiedData = new UDC.UnifiedData(record1);
    
    try {
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          let records = data[0].getRecords();
          expect(records.length).assertEqual(1);
          let value = records[0].getValue();
          expect(value.uniformDataType).assertEqual(html.uniformDataType);
          expect(value.htmlContent).assertEqual(html.htmlContent);
          expect(value.plainContent).assertEqual(html.plainContent);
          expect(value.details.key1).assertEqual(html.details.key1);
          expect(value.details.key2).assertEqual(html.details.key2);
          UDC.deleteData(options).then((data) => {
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
  });

  /**
   * @tc.name UDSTest005
   * @tc.desc
   * @tc.type: FUNC
   * @tc.require:
   */
  it('UDSTest005', 0, async function (done) {
    const TAG = 'UDSTest005';
    console.info(TAG, 'start');

    let systemDefinedDetails = {
      'key1': 'value1',
      'key2': 'value2',
    };
    let systemDefined = {
      uniformDataType: 'openharmony.app-item',
      appId: 'app-itemAppId',
      appName: 'app-itemAppName',
      appIconId: 'app-itemAppIconId',
      appLabelId: 'app-itemAppLabelId',
      bundleName: 'app-itemBundleName',
      abilityName: 'app-itemAbilityName',
      details: systemDefinedDetails
    };
    let record1 = new UDC.UnifiedRecord('openharmony.app-item', systemDefined);
    let unifiedData = new UDC.UnifiedData(record1);
    
    try {
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          let records = data[0].getRecords();
          expect(records.length).assertEqual(1);
          let value = records[0].getValue();
          expect(value.uniformDataType).assertEqual(systemDefined.uniformDataType);
          expect(value.appId).assertEqual(systemDefined.appId);
          expect(value.appName).assertEqual(systemDefined.appName);
          expect(value.appIconId).assertEqual(systemDefined.appIconId);
          expect(value.appLabelId).assertEqual(systemDefined.appLabelId);
          expect(value.bundleName).assertEqual(systemDefined.bundleName);
          expect(value.abilityName).assertEqual(systemDefined.abilityName);
          expect(value.details.key1).assertEqual(systemDefined.details.key1);
          expect(value.details.key2).assertEqual(systemDefined.details.key2);
          UDC.deleteData(options).then((data) => {
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
  });

  /**
   * @tc.name ObjectTest001
   * @tc.desc
   * @tc.type: FUNC
   * @tc.require:
   */
  it('ObjectTest001', 0, async function (done) {
    const TAG = 'ObjectTest001';
    console.info(TAG, 'start');

    const data = new ArrayBuffer(256);
    let view1 = new Uint32Array(data);
    view1[0] = 123456;

    let ObjectDetails1 = {
      'key1': 'value001',
      'key2': data,
      'key3': undefined,
      'key4': null,
    };
    let ObjectDetails2 = {
      'key1': 'value100',
      'key2': data,
      'key3': undefined,
      'key4': null,
      details: ObjectDetails1
    };
    let systemDefined = {
      labelId: 'LabelId',
      details: ObjectDetails2
    };
    let record1 = new UDC.UnifiedRecord('self_defined_type', systemDefined);
    let unifiedData = new UDC.UnifiedData(record1);

    try {
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          let records = data[0].getRecords();
          expect(records.length).assertEqual(1);
          let value = records[0].getValue();
          expect(value.labelId).assertEqual(systemDefined.labelId);
          expect(value.details.key1).assertEqual(systemDefined.details.key1);
          expect(value.details.key2.byteLength).assertEqual(systemDefined.details.key2.byteLength);
          let view2 = new Uint32Array(value.details.key2);
          expect(view2[0]).assertEqual(view1[0]);
          expect(value.details.key3).assertEqual(systemDefined.details.key3);
          expect(value.details.key4).assertEqual(systemDefined.details.key4);
          expect(value.details.details.key1).assertEqual(systemDefined.details.details.key1);
          expect(value.details.details.key2.byteLength).assertEqual(systemDefined.details.details.key2.byteLength);
          let view3 = new Uint32Array(value.details.details.key2);
          expect(view3[0]).assertEqual(view1[0]);
          expect(value.details.details.key3).assertEqual(systemDefined.details.details.key3);
          expect(value.details.details.key4).assertEqual(systemDefined.details.details.key4);
          UDC.deleteData(options).then((data) => {
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
  });

  /**
   * @tc.name UdmfSetAppShareOptionsTest001
   * @tc.desc Test Js Api setAppShareOptions, error intention
   * @tc.type: FUNC
   * @tc.require:
   */
  it('UdmfSetAppShareOptionsTest001', 0, function () {
    const TAG = 'UdmfSetAppShareOptionsTest001:';
    console.info(TAG, 'start');
    try {
      UDC.setAppShareOptions(UDC.Intention.DATA_HUB, UDC.ShareOptions.IN_APP);
      console.error(TAG, 'Unreachable code!');
      expect(null).assertFail();
    } catch (e) {
      console.error(TAG, `get e. code is ${e.code},message is ${e.message} `);
      expect(e.code === ERROR_PARAMETER).assertTrue();
    }
    console.info(TAG, 'end');
  });

  /**
   * @tc.name UdmfRemoveAppShareOptionsTest001
   * @tc.desc Test Js Api removeAppShareOptions, error intention
   * @tc.type: FUNC
   * @tc.require:
   */
  it('UdmfRemoveAppShareOptionsTest001', 0, function () {
    const TAG = 'UdmfRemoveAppShareOptionsTest001:';
    console.info(TAG, 'start');
    try {
      UDC.removeAppShareOptions(UDC.Intention.DATA_HUB);
      console.error(TAG, 'Unreachable code!');
      expect(null).assertFail();
    } catch (e) {
      console.error(TAG, `get e. code is ${e.code},message is ${e.message} `);
      expect(e.code === ERROR_PARAMETER).assertTrue();
    }
    console.info(TAG, 'end');
  });

  /**
   * @tc.name MultiEntryTest001
   * @tc.desc
   * @tc.type: FUNC
   * @tc.require:
   */
  it('MultiEntryTest001', 0, async function (done) {
    const TAG = 'MultiEntryTest001';
    console.info(TAG, 'start');
    let hyperLinkDetails = {
      'key1': 'value1',
      'key2': 'value2',
    };
    let hyperLink = {
      uniformDataType: UTD.UniformDataType.HYPERLINK,
      url: 'www.xxx',
      description: 'hyperlinkDescription',
      details: hyperLinkDetails
    };
    let systemDefinedDetails = {
      'key1': 'value1',
      'key2': 'value2',
    };
    let systemDefined = {
      uniformDataType: 'openharmony.app-item',
      appId: 'app-itemAppId',
      appName: 'app-itemAppName',
      appIconId: 'app-itemAppIconId',
      appLabelId: 'app-itemAppLabelId',
      bundleName: 'app-itemBundleName',
      abilityName: 'app-itemAbilityName',
      details: systemDefinedDetails
    };

    let plainTextDetails = {
      'key1': 'value1',
      'key2': 'value2',
    };
    let plainText = {
      uniformDataType: UTD.UniformDataType.PLAIN_TEXT,
      textContent: 'This is plainText textContent example',
      abstract: 'this is abstract',
      details: plainTextDetails
    };

    const buffer = new ArrayBuffer(128);
    const opt = {
      size: { height: 5, width: 5 },
      pixelFormat: 3,
      editable: true,
      alphaType: 1,
      scaleMode: 1,
    };
    const pixelMap = await image.createPixelMap(buffer, opt);
    let pixelMapUds = {
      uniformDataType: 'openharmony.pixel-map',
      pixelMap: pixelMap,
      details: {
        'key1': 'value1',
        'key2': 'value2',
      }
    };
    let record1 = new UDC.UnifiedRecord(UTD.UniformDataType.PLAIN_TEXT, plainText);
    record1.addEntry(UTD.UniformDataType.HYPERLINK, hyperLink);
    record1.addEntry('openharmony.app-item', systemDefined);
    record1.addEntry('openharmony.pixel-map', pixelMapUds);
    let entries = record1.getEntries();
    
    let unifiedData = new UDC.UnifiedData(record1);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(1);
    const value1 = records[0].getValue();
    let types = records[0].getTypes();
    let systemDefined1 = records[0].getEntry('openharmony.app-item');
    let hyperlink1 = records[0].getEntry(UTD.UniformDataType.HYPERLINK);
    let pixelMapUds1 = records[0].getEntry('openharmony.pixel-map');
    
    expect(value1.uniformDataType).assertEqual(plainText.uniformDataType);
    expect(value1.textContent).assertEqual(plainText.textContent);
    expect(value1.abstract).assertEqual(plainText.abstract);
    expect(value1.details.key1).assertEqual(plainText.details.key1);
    expect(value1.details.key2).assertEqual(plainText.details.key2);
    expect(hyperlink1.url).assertEqual('www.xxx');
    pixelMapUds1.pixelMap.getImageInfo().then((imageInfo)=>{
      expect(imageInfo.size.height).assertEqual(opt.size.height);
      expect(imageInfo.pixelFormat).assertEqual(opt.pixelFormat);
    });
    expect(pixelMapUds1.details.key1).assertEqual('value1');
    expect(hyperlink1.details.key1).assertEqual('value1');
    expect(systemDefined1.appId).assertEqual('app-itemAppId');
    expect(systemDefined1.details.key1).assertEqual('value1');
    expect(types.length).assertEqual(4);
    expect(types.includes(UTD.UniformDataType.PLAIN_TEXT)).assertTrue();
    expect(types.includes(UTD.UniformDataType.HYPERLINK)).assertTrue();
    expect(types.includes('openharmony.pixel-map')).assertTrue();
    expect(types.includes('openharmony.app-item')).assertTrue();
    expect(entries['openharmony.app-item'].appIconId).assertEqual('app-itemAppIconId');
    expect(entries['openharmony.app-item'].details.key1).assertEqual('value1');
    expect(entries['general.hyperlink'].url).assertEqual('www.xxx');
    expect(entries['general.hyperlink'].details.key1).assertEqual('value1');
    expect(entries['general.plain-text'].textContent).assertEqual('This is plainText textContent example');
    expect(entries['general.plain-text'].details.key1).assertEqual('value1');
    entries['openharmony.pixel-map'].pixelMap.getImageInfo().then((imageInfo)=>{
      expect(imageInfo.size.height).assertEqual(opt.size.height);
      expect(imageInfo.pixelFormat).assertEqual(opt.pixelFormat);
    });
    expect(entries['openharmony.pixel-map'].details.key1).assertEqual('value1');

    try {
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          let records = data[0].getRecords();
          expect(records.length).assertEqual(1);
          const valueQuery = records[0].getValue();
          const hyperlinkQuery = records[0].getEntry(UTD.UniformDataType.HYPERLINK);
          const systemDefinedQuery = records[0].getEntry('openharmony.app-item');
          const entriesQuery = records[0].getEntries();
          const types1 = records[0].getTypes();
          expect(valueQuery.uniformDataType).assertEqual(plainText.uniformDataType);
          expect(valueQuery.textContent).assertEqual(plainText.textContent);
          expect(valueQuery.abstract).assertEqual(plainText.abstract);
          expect(valueQuery.details.key1).assertEqual(plainText.details.key1);
          expect(valueQuery.details.key2).assertEqual(plainText.details.key2);
          expect(hyperlinkQuery.url).assertEqual('www.xxx');
          expect(hyperlinkQuery.details.key1).assertEqual('value1');
          expect(systemDefinedQuery.appId).assertEqual('app-itemAppId');
          expect(systemDefinedQuery.details.key1).assertEqual('value1');
          expect(types1.length).assertEqual(4);
          expect(types1.includes(UTD.UniformDataType.PLAIN_TEXT)).assertTrue();
          expect(types1.includes(UTD.UniformDataType.HYPERLINK)).assertTrue();
          expect(types1.includes('openharmony.pixel-map')).assertTrue();
          expect(types1.includes('openharmony.app-item')).assertTrue();

          expect(entriesQuery['openharmony.app-item'].appIconId).assertEqual('app-itemAppIconId');
          expect(entriesQuery['openharmony.app-item'].details.key1).assertEqual('value1');
          expect(entriesQuery['general.hyperlink'].url).assertEqual('www.xxx');
          expect(entriesQuery['general.hyperlink'].details.key1).assertEqual('value1');
          expect(entriesQuery['general.plain-text'].textContent).assertEqual('This is plainText textContent example');
          expect(entriesQuery['general.plain-text'].details.key1).assertEqual('value1');
          entriesQuery['openharmony.pixel-map'].pixelMap.getImageInfo().then((imageInfo)=>{
            expect(imageInfo.size.height).assertEqual(opt.size.height);
            expect(imageInfo.pixelFormat).assertEqual(opt.pixelFormat);
          });
          expect(entriesQuery['openharmony.pixel-map'].details.key1).assertEqual('value1');

          UDC.deleteData(options).then((data) => {
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
  });

  /**
   * @tc.name MultiEntryTest002
   * @tc.desc
   * @tc.type: FUNC
   * @tc.require:
   */
  it('MultiEntryTest002', 0, async function (done) {
    const TAG = 'MultiEntryTest002';
    console.info(TAG, 'start');
    let hyperLinkDetails = {
      'key1': 'value1',
      'key2': 'value2',
    };
    let hyperLink = {
      uniformDataType: UTD.UniformDataType.HYPERLINK,
      url: 'www.xxx',
      description: 'hyperlinkDescription',
      details: hyperLinkDetails
    };
    let plainTextDetails = {
      'key1': 'value1',
      'key2': 'value2',
    };
    let plainText = new UDC.PlainText();
    plainText.textContent = 'This is plainText textContent example';
    plainText.abstract = 'this is abstract';
    plainText.details = plainTextDetails;
    plainText.addEntry(UTD.UniformDataType.HYPERLINK, hyperLink);
    
    let unifiedData = new UDC.UnifiedData(plainText);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(1);
    let entries = records[0].getEntries();
    let types = records[0].getTypes();
    let hyperlink1 = records[0].getEntry(UTD.UniformDataType.HYPERLINK);
    expect(records[0].textContent).assertEqual(plainText.textContent);
    expect(records[0].abstract).assertEqual(plainText.abstract);
    expect(records[0].details.key1).assertEqual(plainText.details.key1);
    expect(records[0].details.key2).assertEqual(plainText.details.key2);
    expect(hyperlink1.url).assertEqual('www.xxx');
    expect(hyperlink1.details.key1).assertEqual('value1');
    expect(types.length).assertEqual(2);
    expect(types.includes(UTD.UniformDataType.PLAIN_TEXT)).assertTrue();
    expect(types.includes(UTD.UniformDataType.HYPERLINK)).assertTrue();
    expect(entries['general.hyperlink'].url).assertEqual('www.xxx');
    expect(entries['general.hyperlink'].details.key1).assertEqual('value1');
    expect(entries['general.plain-text'].textContent).assertEqual('This is plainText textContent example');
    expect(entries['general.plain-text'].details.key1).assertEqual('value1');

    try {
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          let records = data[0].getRecords();
          expect(records.length).assertEqual(1);
          const hyperlinkQuery = records[0].getEntry(UTD.UniformDataType.HYPERLINK);
          const systemDefinedQuery = records[0].getEntry('openharmony.app-item');
          const entriesQuery = records[0].getEntries();
          let types1 = records[0].getTypes();
          expect(records[0].textContent).assertEqual(plainText.textContent);
          expect(records[0].abstract).assertEqual(plainText.abstract);
          expect(records[0].details.key1).assertEqual(plainText.details.key1);
          expect(records[0].details.key2).assertEqual(plainText.details.key2);
          expect(systemDefinedQuery).assertEqual(undefined);
          expect(hyperlinkQuery.url).assertEqual('www.xxx');
          expect(hyperlinkQuery.details.key1).assertEqual('value1');
          expect(types1.length).assertEqual(2);
          expect(types1.includes(UTD.UniformDataType.PLAIN_TEXT)).assertTrue();
          expect(types1.includes(UTD.UniformDataType.HYPERLINK)).assertTrue();

          expect(entriesQuery['general.hyperlink'].url).assertEqual('www.xxx');
          expect(entriesQuery['general.hyperlink'].details.key1).assertEqual('value1');
          expect(entriesQuery['general.plain-text'].textContent).assertEqual('This is plainText textContent example');
          expect(entriesQuery['general.plain-text'].details.key1).assertEqual('value1');

          UDC.deleteData(options).then((data) => {
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
  });

  /**
   * @tc.name MultiEntryTest003
   * @tc.desc
   * @tc.type: FUNC
   * @tc.require:
   */
  it('MultiEntryTest003', 0, async function (done) {
    const TAG = 'MultiEntryTest003';
    console.info(TAG, 'start');

    let plaintextValue = 'plaintextValue';
    let systemDefinedValue = 'systemDefinedValue';
    let hyperlinkValue = 'hyperlinkValue';
    let record1 = new UDC.UnifiedRecord(UTD.UniformDataType.PLAIN_TEXT, plaintextValue);
    record1.addEntry(UTD.UniformDataType.HYPERLINK, hyperlinkValue);
    record1.addEntry('openharmony.app-item', systemDefinedValue);

    let entries = record1.getEntries();
    
    let unifiedData = new UDC.UnifiedData(record1);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(1);
    const value1 = records[0].getValue();
    let types = records[0].getTypes();
    let systemDefined1 = records[0].getEntry('openharmony.app-item');
    let hyperlink1 = records[0].getEntry(UTD.UniformDataType.HYPERLINK);
    expect(value1).assertEqual(plaintextValue);
    expect(value1.textContent).assertEqual(undefined);
    expect(hyperlink1).assertEqual(hyperlinkValue);
    expect(hyperlink1.details).assertEqual(undefined);
    expect(systemDefined1).assertEqual(systemDefinedValue);
    expect(systemDefined1.details).assertEqual(undefined);
    expect(types.length).assertEqual(3);
    expect(types.includes(UTD.UniformDataType.PLAIN_TEXT)).assertTrue();
    expect(types.includes(UTD.UniformDataType.HYPERLINK)).assertTrue();
    expect(types.includes('openharmony.app-item')).assertTrue();
    expect(entries['openharmony.app-item']).assertEqual(systemDefinedValue);
    expect(entries['general.hyperlink']).assertEqual(hyperlinkValue);
    expect(entries['general.plain-text'].VALUE_TYPE).assertEqual(plaintextValue);

    try {
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          let records = data[0].getRecords();
          expect(records.length).assertEqual(1);
          const valueQuery = records[0].getValue();
          const hyperlinkQuery = records[0].getEntry(UTD.UniformDataType.HYPERLINK);
          const systemDefinedQuery = records[0].getEntry('openharmony.app-item');
          const entriesQuery = records[0].getEntries();
          const types1 = records[0].getTypes();
          expect(valueQuery).assertEqual(plaintextValue);
          expect(hyperlinkQuery).assertEqual(hyperlinkValue);
          expect(systemDefinedQuery).assertEqual(systemDefinedValue);
          expect(types1.length).assertEqual(3);
          expect(types1.includes(UTD.UniformDataType.PLAIN_TEXT)).assertTrue();
          expect(types1.includes(UTD.UniformDataType.HYPERLINK)).assertTrue();
          expect(types1.includes('openharmony.app-item')).assertTrue();
          expect(entriesQuery['openharmony.app-item']).assertEqual(systemDefinedValue);
          expect(entriesQuery['general.hyperlink']).assertEqual(hyperlinkValue);
          expect(entriesQuery['general.plain-text'].VALUE_TYPE).assertEqual(plaintextValue);

          UDC.deleteData(options).then((data) => {
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
  });

  /**
   * @tc.name MultiEntryTest004
   * @tc.desc
   * @tc.type: FUNC
   * @tc.require:
   */
  it('MultiEntryTest004', 0, async function (done) {
    const TAG = 'MultiEntryTest004';
    console.info(TAG, 'start');
    const buffer = new ArrayBuffer(128);
    const opt = {
      size: { height: 5, width: 5 },
      pixelFormat: 3,
      editable: true,
      alphaType: 1,
      scaleMode: 1,
    };
    const pixelMap = await image.createPixelMap(buffer, opt);
    let pixelMapUds = {
      uniformDataType: 'openharmony.pixel-map',
      pixelMap: pixelMap,
      details: {
        'key1': 'value1',
        'key2': 'value2',
      }
    };
    let record = new UDC.UnifiedRecord('openharmony.pixel-map', pixelMapUds);
    let unifiedData = new UDC.UnifiedData(record);

    try {
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          let records = data[0].getRecords();
          expect(records.length).assertEqual(1);
          const valueQuery = records[0].getValue();
          expect(valueQuery.uniformDataType).assertEqual('openharmony.pixel-map');
          valueQuery.pixelMap.getImageInfo().then((imageInfo)=>{
            expect(imageInfo.size.height).assertEqual(opt.size.height);
            expect(imageInfo.pixelFormat).assertEqual(opt.pixelFormat);
          });
          expect(valueQuery.details.key1).assertEqual('value1');
          UDC.deleteData(options).then((data) => {
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
  });

    /**
   * @tc.name MultiEntryTest005
   * @tc.desc
   * @tc.type: FUNC
   * @tc.require:
   */
    it('MultiEntryTest005', 0, async function () {
      const TAG = 'MultiEntryTest005';
      console.info(TAG, 'start');
      try {
        let plaintextValue = 'plaintextValue';
        let systemDefinedValue = 'systemDefinedValue';
        let record = new UDC.UnifiedRecord(UTD.UniformDataType.PLAIN_TEXT, plaintextValue);
        record.addEntry(undefined, systemDefinedValue);
      } catch (e) {
        console.error(TAG, `get e. code is ${e.code},message is ${e.message} `);
        expect(e.code === ERROR_PARAMETER).assertTrue();
      }
      try {
        let plaintextValue = 'plaintextValue';
        let systemDefinedValue = 'systemDefinedValue';
        let record = new UDC.UnifiedRecord(UTD.UniformDataType.PLAIN_TEXT, plaintextValue);
        record.addEntry(null, systemDefinedValue);
      } catch (e) {
        console.error(TAG, `get e. code is ${e.code},message is ${e.message} `);
        expect(e.code === ERROR_PARAMETER).assertTrue();
      }
      console.info(TAG, 'end');
    });
  
    /**
     * @tc.name MultiEntryTest006
     * @tc.desc
     * @tc.type: FUNC
     * @tc.require:
     */
    it('MultiEntryTest006', 0, async function () {
      const TAG = 'MultiEntryTest006';
      console.info(TAG, 'start');
      try {
        let plaintextValue = 'plaintextValue';
        let systemDefinedValue = 'systemDefinedValue';
        let record = new UDC.UnifiedRecord(UTD.UniformDataType.PLAIN_TEXT, plaintextValue);
        record.addEntry('openharmony.app-item', systemDefinedValue);
        record.getEntry(undefined);
      } catch (e) {
        console.error(TAG, `get e. code is ${e.code},message is ${e.message} `);
        expect(e.code === ERROR_PARAMETER).assertTrue();
      }
      try {
        let plaintextValue = 'plaintextValue';
        let systemDefinedValue = 'systemDefinedValue';
        let record = new UDC.UnifiedRecord(UTD.UniformDataType.PLAIN_TEXT, plaintextValue);
        record.addEntry('openharmony.app-item', systemDefinedValue);
        record.getEntry(null);
      } catch (e) {
        console.error(TAG, `get e. code is ${e.code},message is ${e.message} `);
        expect(e.code === ERROR_PARAMETER).assertTrue();
      }
      console.info(TAG, 'end');
    });

  /**
   * @tc.name FileUriTest001
   * @tc.desc
   * @tc.type: FUNC
   * @tc.require: test constructor UnifiedRecord(UDType type, ValueType value) and sub image
   */
  it('FileUriTest001', 0, async function (done) {
    const TAG = 'FileUriTest001';
    console.info(TAG, 'start');
    let fileUriDetails = {
      'fileUriKey1': 123,
      'fileUriKey2': 'fileUriValue',
    };
    let fileUri = {
      uniformDataType : 'general.file-uri',
      oriUri : 'www.xx.com',
      fileType : 'general.jpeg',
      details : fileUriDetails
    };
    let u8Array = new Uint8Array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10]);
    let arrayBuffer = new ArrayBuffer(4 * 200 * 200);
    let opt = { editable: true, pixelFormat: 3, size: { height: 200, width: 200 }, alphaType: 3 };
    let pixelMapDetails = {
      'pixelMapKey1': 123,
      'pixelMapKey2': 'pixelMapValue',
      'pixelMapKey3': u8Array,
    };
    let pixelMap = {
      uniformDataType : 'openharmony.pixel-map',
      pixelMap : image.createPixelMapSync(arrayBuffer, opt),
      details : pixelMapDetails
    };
    let record = new UDC.UnifiedRecord('general.file-uri', fileUri);
    record.addEntry('openharmony.pixel-map', pixelMap);
    let rawType = record.getType();
    expect(rawType).assertEqual('general.image');
    let rawRecordTypes = record.getTypes();
    expect(rawRecordTypes.includes('general.file-uri')).assertTrue();
    expect(rawRecordTypes.includes('openharmony.pixel-map')).assertTrue();

    let unifiedData = new UDC.UnifiedData(record);
    let rawDataTypes = unifiedData.getTypes();
    expect(rawDataTypes.includes('general.image')).assertTrue();
    expect(rawDataTypes.includes('openharmony.pixel-map')).assertFalse();
    expect(unifiedData.hasType('general.file-uri')).assertTrue();
    expect(unifiedData.hasType('general.image')).assertTrue();
    expect(unifiedData.hasType('general.jpeg')).assertTrue();
    try {
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          let records = data[0].getRecords();
          let rawType = records[0].getType();
          expect(rawType).assertEqual('general.image');
          let getRecordTypes = records[0].getTypes();
          expect(getRecordTypes.includes('general.file-uri')).assertTrue();
          expect(getRecordTypes.includes('openharmony.pixel-map')).assertTrue();

          let getDataTypes = data[0].getTypes();
          expect(getDataTypes.includes('general.image')).assertTrue();
          for (let i = 0; i < records.length; i++) {
            if (records[i].getType() === 'general.image') {
              let getImageUri = records[i].imageUri;
              expect(getImageUri).assertEqual('www.xx.com');
            }
          }
          let getValue = records[0].getValue();
          expect(getValue.uniformDataType).assertEqual('general.file-uri');
          expect(getValue.oriUri).assertEqual('www.xx.com');
          expect(getValue.fileType).assertEqual('general.jpeg');
          expect(getValue.details.fileUriKey1).assertEqual(123);
          expect(getValue.details.fileUriKey2).assertEqual('fileUriValue');

          let getEntryFileUri = records[0].getEntry('general.file-uri');
          expect(getEntryFileUri.uniformDataType).assertEqual('general.file-uri');
          expect(getEntryFileUri.oriUri).assertEqual('www.xx.com');
          expect(getEntryFileUri.fileType).assertEqual('general.jpeg');
          expect(getEntryFileUri.details.fileUriKey1).assertEqual(123);

          let getEntryPixelMap = records[0].getEntry('openharmony.pixel-map');
          expect(getEntryPixelMap.uniformDataType).assertEqual('openharmony.pixel-map');
          getEntryPixelMap.pixelMap.getImageInfo().then((imageInfo)=>{
            expect(imageInfo.size.height).assertEqual(opt.size.height);
            expect(imageInfo.pixelFormat).assertEqual(opt.pixelFormat);
          });
          expect(getEntryPixelMap.details.pixelMapKey1).assertEqual(123);
          expect(getEntryPixelMap.details.pixelMapKey2).assertEqual('pixelMapValue');
          expect(data[0].hasType('general.file-uri')).assertTrue();
          expect(data[0].hasType('general.image')).assertTrue();
          expect(data[0].hasType('general.jpeg')).assertTrue();

          UDC.deleteData(options).then((data) => {
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
  });

  /**
   * @tc.name FileUriTest002
   * @tc.desc
   * @tc.type: FUNC
   * @tc.require: test constructor UnifiedRecord(UDType type, ValueType value)
   */
  it('FileUriTest002', 0, async function (done) {
    const TAG = 'FileUriTest002';
    console.info(TAG, 'start');
    let u8Array = new Uint8Array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10]);
    let fileUriDetails = {
      'fileUriKey1': 123,
      'fileUriKey2': 'fileUriValue',
      'fileUriKey3': u8Array,
    };
    let fileUri = {
      uniformDataType : 'general.file-uri',
      oriUri : 'www.xx.com',
      fileType : 'general.image',
      details : fileUriDetails
    };
    let record = new UDC.UnifiedRecord('general.file-uri', fileUri);
    let rawType = record.getType();
    expect(rawType).assertEqual('general.image');
    let rawRecordTypes = record.getTypes();
    expect(rawRecordTypes.includes('general.file-uri')).assertTrue();

    let unifiedData = new UDC.UnifiedData(record);
    let rawDataTypes = unifiedData.getTypes();
    expect(rawDataTypes.includes('general.image')).assertTrue();
    expect(unifiedData.hasType('general.file-uri')).assertTrue();
    expect(unifiedData.hasType('general.image')).assertTrue();
    try {
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          let records = data[0].getRecords();
          expect(records.length).assertEqual(1);
          let rawType = records[0].getType();
          expect(rawType).assertEqual('general.image');
          let rawRecordTypes = records[0].getTypes();
          expect(rawRecordTypes.includes('general.file-uri')).assertTrue();

          let rawDataTypes = data[0].getTypes();
          expect(rawDataTypes.includes('general.image')).assertTrue();
          for (let i = 0; i < records.length; i++) {
            if (records[i].getType() === 'general.image') {
              let getImageUri = records[i].imageUri;
              expect(getImageUri).assertEqual('www.xx.com');
            }
          }
          let getValue = records[0].getValue();
          expect(getValue.uniformDataType).assertEqual('general.file-uri');
          expect(getValue.oriUri).assertEqual('www.xx.com');
          expect(getValue.fileType).assertEqual('general.image');
          expect(getValue.details.fileUriKey1).assertEqual(123);
          expect(getValue.details.fileUriKey2).assertEqual('fileUriValue');

          let getEntry = records[0].getEntry('general.file-uri');
          expect(getEntry.uniformDataType).assertEqual('general.file-uri');
          expect(getEntry.oriUri).assertEqual('www.xx.com');
          expect(getEntry.fileType).assertEqual('general.image');
          expect(getEntry.details.fileUriKey1).assertEqual(123);
          expect(data[0].hasType('general.file-uri')).assertTrue();
          expect(data[0].hasType('general.image')).assertTrue();

          UDC.deleteData(options).then((data) => {
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
  });

  /**
   * @tc.name FileUriTest003
   * @tc.desc
   * @tc.type: FUNC
   * @tc.require: test constructor UDC
   */
  it('FileUriTest003', 0, async function (done) {
    const TAG = 'FileUriTest003';
    console.info(TAG, 'start');
    let fileUriDetails = {
      'fileUriKey1': 123,
      'fileUriKey2': 'fileUriValue',
    };
    let fileUri = {
      uniformDataType : 'general.file-uri',
      oriUri : 'www.xx.com',
      fileType : 'general.jpeg',
      details : fileUriDetails
    };
    let u8Array = new Uint8Array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10]);
    let arrayBuffer = new ArrayBuffer(4 * 200 * 200);
    let opt = { editable: true, pixelFormat: 3, size: { height: 200, width: 200 }, alphaType: 3 };
    let pixelMapDetails = {
      'pixelMapKey1': 123,
      'pixelMapKey2': 'pixelMapValue',
      'pixelMapKey3': u8Array,
    };
    let pixelMap = {
      uniformDataType : 'openharmony.pixel-map',
      pixelMap : image.createPixelMapSync(arrayBuffer, opt),
      details : pixelMapDetails
    };
    let record = new UDC.File();
    record.details = {
      name: 'test',
      type: 'txt',
    };
    record.uri = 'schema://com.samples.test/files/test.txt';
    record.addEntry('openharmony.pixel-map', pixelMap);
    record.addEntry('general.file-uri', fileUri);
    let rawType = record.getType();
    expect(rawType).assertEqual('general.image');
    let rawRecordTypes = record.getTypes();
    expect(rawRecordTypes.includes('general.file')).assertFalse();
    expect(rawRecordTypes.includes('general.file-uri')).assertTrue();
    expect(rawRecordTypes.includes('openharmony.pixel-map')).assertTrue();

    let unifiedData = new UDC.UnifiedData(record);
    let rawDataTypes = unifiedData.getTypes();
    expect(rawDataTypes.includes('general.image')).assertTrue();
    expect(rawDataTypes.includes('general.file-uri')).assertFalse();
    expect(rawDataTypes.includes('openharmony.pixel-map')).assertFalse();
    expect(unifiedData.hasType('general.file-uri')).assertTrue();
    expect(unifiedData.hasType('general.image')).assertTrue();
    expect(unifiedData.hasType('general.jpeg')).assertTrue();
    try {
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          let records = data[0].getRecords();
          let rawType = records[0].getType();
          expect(rawType).assertEqual('general.image');
          let getRecordTypes = records[0].getTypes();
          expect(getRecordTypes.includes('general.file')).assertFalse();
          expect(getRecordTypes.includes('general.file-uri')).assertTrue();
          expect(getRecordTypes.includes('openharmony.pixel-map')).assertTrue();

          let getDataTypes = data[0].getTypes();
          expect(getDataTypes.includes('general.image')).assertTrue();
          expect(getDataTypes.includes('general.file-uri')).assertFalse();
          expect(getDataTypes.includes('openharmony.pixel-map')).assertFalse();
          for (let i = 0; i < records.length; i++) {
            if (records[i].getType() === 'general.file') {
              let getUri = records[i].uri;
              expect(getUri).assertEqual('schema://com.samples.test/files/test.txt');
            }
          }
          let getValue = records[0].getValue();
          expect(getValue.uniformDataType).assertEqual('general.file-uri');
          expect(getValue.oriUri).assertEqual('www.xx.com');
          expect(getValue.fileType).assertEqual('general.jpeg');
          expect(getValue.details.fileUriKey1).assertEqual(123);

          let getEntryFileUri = records[0].getEntry('general.file-uri');
          expect(getEntryFileUri.uniformDataType).assertEqual('general.file-uri');
          expect(getEntryFileUri.oriUri).assertEqual('www.xx.com');
          expect(getEntryFileUri.fileType).assertEqual('general.jpeg');
          expect(getEntryFileUri.details.fileUriKey1).assertEqual(123);

          let getEntryPixelMap = records[0].getEntry('openharmony.pixel-map');
          expect(getEntryPixelMap.uniformDataType).assertEqual('openharmony.pixel-map');
          getEntryPixelMap.pixelMap.getImageInfo().then((imageInfo)=>{
            expect(imageInfo.size.height).assertEqual(opt.size.height);
            expect(imageInfo.pixelFormat).assertEqual(opt.pixelFormat);
          });
          expect(getEntryPixelMap.details.pixelMapKey1).assertEqual(123);
          expect(getEntryPixelMap.details.pixelMapKey2).assertEqual('pixelMapValue');
          expect(data[0].hasType('general.file-uri')).assertTrue();
          expect(data[0].hasType('general.image')).assertTrue();
          expect(data[0].hasType('general.jpeg')).assertTrue();

          UDC.deleteData(options).then((data) => {
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
  });

  /**
   * @tc.name FileUriTest004
   * @tc.desc
   * @tc.type: FUNC
   * @tc.require: test constructor no parameter
   */
  it('FileUriTest004', 0, async function (done) {
    const TAG = 'FileUriTest004';
    console.info(TAG, 'start');
    let fileUriDetails = {
      'fileUriKey1': 123,
      'fileUriKey2': 'fileUriValue',
    };
    let fileUri = {
      uniformDataType : 'general.file-uri',
      oriUri : 'www.xx.com',
      fileType : 'general.vob',
      details : fileUriDetails
    };
    let u8Array = new Uint8Array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10]);
    let arrayBuffer = new ArrayBuffer(4 * 200 * 200);
    let opt = { editable: true, pixelFormat: 3, size: { height: 200, width: 200 }, alphaType: 3 };
    let pixelMapDetails = {
      'pixelMapKey1': 123,
      'pixelMapKey2': 'pixelMapValue',
      'pixelMapKey3': u8Array,
    };
    let pixelMap = {
      uniformDataType : 'openharmony.pixel-map',
      pixelMap : image.createPixelMapSync(arrayBuffer, opt),
      details : pixelMapDetails
    };
    let record = new UDC.UnifiedRecord();
    record.addEntry('general.file-uri', fileUri);
    record.addEntry('openharmony.pixel-map', pixelMap);
    let rawType = record.getType();
    expect(rawType).assertEqual('general.video');
    let rawRecordTypes = record.getTypes();
    expect(rawRecordTypes.includes('general.file-uri')).assertTrue();
    expect(rawRecordTypes.includes('openharmony.pixel-map')).assertTrue();
    let unifiedData = new UDC.UnifiedData(record);
    let rawDataTypes = unifiedData.getTypes();
    expect(rawDataTypes.includes('general.video')).assertTrue();
    expect(rawDataTypes.includes('openharmony.pixel-map')).assertFalse();
    expect(unifiedData.hasType('general.file-uri')).assertTrue();
    expect(unifiedData.hasType('general.video')).assertTrue();
    expect(unifiedData.hasType('general.vob')).assertTrue();
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(1);
    try {
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          let records = data[0].getRecords();
          let rawType = records[0].getType();
          expect(rawType).assertEqual('general.video');
          let getRecordTypes = records[0].getTypes();
          expect(getRecordTypes.includes('general.file-uri')).assertTrue();
          expect(getRecordTypes.includes('openharmony.pixel-map')).assertTrue();

          let getDataTypes = data[0].getTypes();
          expect(getDataTypes.includes('general.video')).assertTrue();
          expect(getDataTypes.includes('openharmony.pixel-map')).assertFalse();
          for (let i = 0; i < records.length; i++) {
            if (records[i].getType() === 'general.video') {
              let getUri = records[i].videoUri;
              expect(getUri).assertEqual('www.xx.com');
            }
          }
          let getValue = records[0].getValue();
          expect(getValue.uniformDataType).assertEqual('general.file-uri');
          expect(getValue.oriUri).assertEqual('www.xx.com');
          expect(getValue.fileType).assertEqual('general.vob');
          expect(getValue.details.fileUriKey1).assertEqual(123);
          expect(getValue.details.fileUriKey2).assertEqual('fileUriValue');

          let getEntryFileUri = records[0].getEntry('general.file-uri');
          expect(getEntryFileUri.uniformDataType).assertEqual('general.file-uri');
          expect(getEntryFileUri.oriUri).assertEqual('www.xx.com');
          expect(getEntryFileUri.fileType).assertEqual('general.vob');
          expect(getEntryFileUri.details.fileUriKey1).assertEqual(123);

          let getEntryPixelMap = records[0].getEntry('openharmony.pixel-map');
          expect(getEntryPixelMap.uniformDataType).assertEqual('openharmony.pixel-map');
          getEntryPixelMap.pixelMap.getImageInfo().then((imageInfo)=>{
            expect(imageInfo.size.height).assertEqual(opt.size.height);
            expect(imageInfo.pixelFormat).assertEqual(opt.pixelFormat);
          });
          expect(getEntryPixelMap.details.pixelMapKey1).assertEqual(123);
          expect(getEntryPixelMap.details.pixelMapKey2).assertEqual('pixelMapValue');
          expect(data[0].hasType('general.file-uri')).assertTrue();
          expect(data[0].hasType('general.video')).assertTrue();
          expect(data[0].hasType('general.vob')).assertTrue();

          UDC.deleteData(options).then((data) => {
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
  });

  /**
   * @tc.name FileUriTest005
   * @tc.desc
   * @tc.type: FUNC
   * @tc.require: test constructor no parameter
   */
  it('FileUriTest005', 0, async function (done) {
    const TAG = 'FileUriTest005';
    console.info(TAG, 'start');
    let fileUriDetails = {
      'fileUriKey1': 123,
      'fileUriKey2': 'fileUriValue',
    };
    let fileUri = {
      uniformDataType : 'general.file-uri',
      oriUri : 'www.xx.com',
      fileType : 'general.vob',
      details : fileUriDetails
    };
    let u8Array = new Uint8Array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10]);
    let arrayBuffer = new ArrayBuffer(4 * 200 * 200);
    let opt = { editable: true, pixelFormat: 3, size: { height: 200, width: 200 }, alphaType: 3 };
    let pixelMapDetails = {
      'pixelMapKey1': 123,
      'pixelMapKey2': 'pixelMapValue',
      'pixelMapKey3': u8Array,
    };
    let pixelMap = {
      uniformDataType : 'openharmony.pixel-map',
      pixelMap : image.createPixelMapSync(arrayBuffer, opt),
      details : pixelMapDetails
    };
    let record = new UDC.UnifiedRecord('general.vob', fileUri);
    record.addEntry('openharmony.pixel-map', pixelMap);
    let rawType = record.getType();
    expect(rawType).assertEqual('general.vob');
    let rawRecordTypes = record.getTypes();
    expect(rawRecordTypes.includes('general.vob')).assertTrue();
    expect(rawRecordTypes.includes('general.file-uri')).assertFalse();
    expect(rawRecordTypes.includes('openharmony.pixel-map')).assertTrue();
    let unifiedData = new UDC.UnifiedData(record);
    let rawDataTypes = unifiedData.getTypes();
    expect(rawDataTypes.includes('general.vob')).assertTrue();
    expect(rawDataTypes.includes('openharmony.pixel-map')).assertFalse();
    expect(unifiedData.hasType('general.file-uri')).assertFalse();
    expect(unifiedData.hasType('general.video')).assertTrue();
    expect(unifiedData.hasType('general.vob')).assertTrue();
    try {
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          let records = data[0].getRecords();
          let rawType = records[0].getType();
          expect(rawType).assertEqual('general.vob');
          let getRecordTypes = records[0].getTypes();
          expect(getRecordTypes.includes('general.vob')).assertTrue();
          expect(getRecordTypes.includes('general.file-uri')).assertFalse();
          expect(getRecordTypes.includes('openharmony.pixel-map')).assertTrue();

          let getDataTypes = data[0].getTypes();
          expect(getDataTypes.includes('general.vob')).assertTrue();
          expect(getDataTypes.includes('general.file-uri')).assertFalse();
          expect(getDataTypes.includes('openharmony.pixel-map')).assertFalse();

          let getValue = records[0].getValue();
          expect(getValue.uniformDataType).assertEqual('general.file-uri');
          expect(getValue.oriUri).assertEqual('www.xx.com');
          expect(getValue.fileType).assertEqual('general.vob');
          expect(getValue.details.fileUriKey1).assertEqual(123);
          expect(getValue.details.fileUriKey2).assertEqual('fileUriValue');

          let getEntryFileUri = records[0].getEntry('general.file-uri');
          expect(getEntryFileUri).assertEqual(undefined);

          let getEntryVob = records[0].getEntry('general.vob');
          expect(getEntryVob.uniformDataType).assertEqual('general.file-uri');
          expect(getEntryVob.oriUri).assertEqual('www.xx.com');
          expect(getEntryVob.fileType).assertEqual('general.vob');
          expect(getEntryVob.details.fileUriKey1).assertEqual(123);

          let getEntryPixelMap = records[0].getEntry('openharmony.pixel-map');
          expect(getEntryPixelMap.uniformDataType).assertEqual('openharmony.pixel-map');
          getEntryPixelMap.pixelMap.getImageInfo().then((imageInfo)=>{
            expect(imageInfo.size.height).assertEqual(opt.size.height);
            expect(imageInfo.pixelFormat).assertEqual(opt.pixelFormat);
          });
          expect(getEntryPixelMap.details.pixelMapKey1).assertEqual(123);
          expect(getEntryPixelMap.details.pixelMapKey2).assertEqual('pixelMapValue');
          expect(data[0].hasType('general.file-uri')).assertFalse();
          expect(data[0].hasType('general.video')).assertTrue();
          expect(data[0].hasType('general.vob')).assertTrue();

          UDC.deleteData(options).then((data) => {
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
  });

  /**
   * @tc.name FileUriTest006
   * @tc.desc
   * @tc.type: FUNC
   * @tc.require: test constructor no parameter
   */
  it('FileUriTest006', 0, async function (done) {
    const TAG = 'FileUriTest006';
    console.info(TAG, 'start');
    let fileUriDetails = {
      'fileUriKey1': 123,
      'fileUriKey2': 'fileUriValue',
    };
    let fileUri = {
      uniformDataType : 'general.file-uri',
      oriUri : 'www.xx.com',
      fileType : 'general.vob',
      details : fileUriDetails
    };
    let u8Array = new Uint8Array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10]);
    let arrayBuffer = new ArrayBuffer(4 * 200 * 200);
    let opt = { editable: true, pixelFormat: 3, size: { height: 200, width: 200 }, alphaType: 3 };
    let pixelMapDetails = {
      'pixelMapKey1': 123,
      'pixelMapKey2': 'pixelMapValue',
      'pixelMapKey3': u8Array,
    };
    let pixelMap = {
      uniformDataType : 'openharmony.pixel-map',
      pixelMap : image.createPixelMapSync(arrayBuffer, opt),
      details : pixelMapDetails
    };
    let record = new UDC.UnifiedRecord('openharmony.pixel-map', pixelMap);
    record.addEntry('general.file-uri', fileUri);
    let rawType = record.getType();
    expect(rawType).assertEqual('openharmony.pixel-map');
    let rawRecordTypes = record.getTypes();
    expect(rawRecordTypes.includes('general.vob')).assertFalse();
    expect(rawRecordTypes.includes('general.file-uri')).assertTrue();
    expect(rawRecordTypes.includes('openharmony.pixel-map')).assertTrue();
    let unifiedData = new UDC.UnifiedData(record);
    let rawDataTypes = unifiedData.getTypes();
    expect(rawDataTypes.includes('general.vob')).assertFalse();
    expect(rawDataTypes.includes('general.file-uri')).assertFalse();
    expect(rawDataTypes.includes('openharmony.pixel-map')).assertTrue();
    expect(unifiedData.hasType('general.file-uri')).assertTrue();
    expect(unifiedData.hasType('general.video')).assertTrue();
    expect(unifiedData.hasType('general.vob')).assertTrue();
    expect(unifiedData.hasType('openharmony.pixel-map')).assertTrue();
    try {
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          let records = data[0].getRecords();
          let rawType = records[0].getType();
          expect(rawType).assertEqual('openharmony.pixel-map');
          let getRecordTypes = records[0].getTypes();
          expect(getRecordTypes.includes('general.vob')).assertFalse();
          expect(getRecordTypes.includes('general.file-uri')).assertTrue();
          expect(getRecordTypes.includes('openharmony.pixel-map')).assertTrue();

          let getDataTypes = data[0].getTypes();
          expect(getDataTypes.includes('general.vob')).assertFalse();
          expect(getDataTypes.includes('general.file-uri')).assertFalse();
          expect(getDataTypes.includes('openharmony.pixel-map')).assertTrue();

          let getValue = records[0].getValue();
          expect(getValue.uniformDataType).assertEqual('openharmony.pixel-map');
          getValue.pixelMap.getImageInfo().then((imageInfo)=>{
            expect(imageInfo.size.height).assertEqual(opt.size.height);
            expect(imageInfo.pixelFormat).assertEqual(opt.pixelFormat);
          });
          expect(getValue.details.pixelMapKey1).assertEqual(123);
          expect(getValue.details.pixelMapKey2).assertEqual('pixelMapValue');

          let getEntryFileUri = records[0].getEntry('general.file-uri');
          expect(getEntryFileUri.uniformDataType).assertEqual('general.file-uri');
          expect(getEntryFileUri.oriUri).assertEqual('www.xx.com');
          expect(getEntryFileUri.fileType).assertEqual('general.vob');
          expect(getEntryFileUri.details.fileUriKey1).assertEqual(123);

          let getEntryPixelMap = records[0].getEntry('openharmony.pixel-map');
          expect(getEntryPixelMap.uniformDataType).assertEqual('openharmony.pixel-map');
          getEntryPixelMap.pixelMap.getImageInfo().then((imageInfo)=>{
            expect(imageInfo.size.height).assertEqual(opt.size.height);
            expect(imageInfo.pixelFormat).assertEqual(opt.pixelFormat);
          });
          expect(getEntryPixelMap.details.pixelMapKey1).assertEqual(123);
          expect(getEntryPixelMap.details.pixelMapKey2).assertEqual('pixelMapValue');
          expect(data[0].hasType('general.file-uri')).assertTrue();
          expect(data[0].hasType('general.video')).assertTrue();
          expect(data[0].hasType('general.vob')).assertTrue();
          expect(data[0].hasType('openharmony.pixel-map')).assertTrue();

          UDC.deleteData(options).then((data) => {
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
  });
  
  /**
   * @tc.name MultiEntryTest007
   * @tc.desc Build a record with no params, then add entries. test if UnifiedData::getRecords() function works well.
   * @tc.type: FUNC
   * @tc.require:
   */
  it('MultiEntryTest007', 0, async function (done) {
    const TAG = 'MultiEntryTest007';
    console.info(TAG, 'start');

    let plaintextValue = 'plaintextValue';
    let systemDefinedValue = 'systemDefinedValue';
    let hyperlinkValue = 'hyperlinkValue';
    let record = new UDC.UnifiedRecord();
    record.addEntry(UTD.UniformDataType.PLAIN_TEXT, plaintextValue);
    record.addEntry(UTD.UniformDataType.HYPERLINK, hyperlinkValue);
    record.addEntry('openharmony.app-item', systemDefinedValue);

    let recordFile = new UDC.File();
    recordFile.uri = 'schema://com.samples.test/files/test.txt';
    recordFile.addEntry(UTD.UniformDataType.PLAIN_TEXT, plaintextValue);
    recordFile.addEntry(UTD.UniformDataType.HYPERLINK, hyperlinkValue);

    let recordAppDefined = new UDC.ApplicationDefinedRecord();
    let u8Array = new Uint8Array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10]);
    recordAppDefined.applicationDefinedType = 'ApplicationDefinedType';
    recordAppDefined.rawData = u8Array;

    let recordAny = new UDC.UnifiedRecord('test.utd-id', 'test.utd-value');
    recordAny.addEntry(UTD.UniformDataType.PLAIN_TEXT, plaintextValue);
    recordAny.addEntry(UTD.UniformDataType.HYPERLINK, hyperlinkValue);

    let unifiedData = new UDC.UnifiedData(record);
    unifiedData.addRecord(recordFile);
    unifiedData.addRecord(recordAppDefined);
    unifiedData.addRecord(recordAny);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(4);

    try {
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          let records = data[0].getRecords();
          expect(records.length).assertEqual(4);

          UDC.deleteData(options).then((data) => {
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
  });

  /**
   * @tc.name MultiEntryTest008
   * @tc.desc UDC to get first entry works well test
   * @tc.type: FUNC
   * @tc.require:
   */
  it('MultiEntryTest008', 0, async function (done) {
    const TAG = 'MultiEntryTest008';
    console.info(TAG, 'start');
    let plaintextValue = 'plaintextValue';
    let record = new UDC.UnifiedRecord();
    record.addEntry(UTD.UniformDataType.PLAIN_TEXT, plaintextValue);
    let recordFile = new UDC.File();
    recordFile.uri = 'schema://com.samples.test/files/test.txt';
    let recordAppDefined = new UDC.ApplicationDefinedRecord();
    let u8Array = new Uint8Array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10]);
    recordAppDefined.applicationDefinedType = 'ApplicationDefinedType';
    recordAppDefined.rawData = u8Array;
    let recordAny = new UDC.UnifiedRecord('general.log', 'test.utd-value');
    let recordHyperlink = new UDC.UnifiedRecord('general.hyperlink', 'test.hyperlink');
    let unifiedData = new UDC.UnifiedData(record);
    unifiedData.addRecord(recordFile);
    unifiedData.addRecord(recordAppDefined);
    unifiedData.addRecord(recordAny);
    unifiedData.addRecord(recordHyperlink);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(5);
    try {
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          let records = data[0].getRecords();
          let firstEntry1 = records[0].getEntry(UTD.UniformDataType.PLAIN_TEXT);
          expect(firstEntry1.textContent).assertEqual('plaintextValue');
          let firstEntry2 = records[1].getEntry(UTD.UniformDataType.FILE_URI);
          expect(firstEntry2.oriUri).assertEqual('schema://com.samples.test/files/test.txt');
          let firstEntry3 = records[2].getEntry('ApplicationDefinedType');
          expect(firstEntry3.arrayBuffer.length).assertEqual(u8Array.length);
          let firstEntry4 = records[3].getEntry('general.log');
          expect(firstEntry4).assertEqual('test.utd-value');
          let firstEntry5 = records[4].getEntry('general.hyperlink');
          expect(firstEntry5.url).assertEqual('test.hyperlink');
          UDC.deleteData(options).then((data) => {
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
  });

  /**
   * @tc.name toEntriesTest001
   * @tc.desc test toEntries function normal
   * @tc.type: FUNC
   * @tc.require:
   */
  it('toEntriesTest001', 0, async function (done) {
    const TAG = 'toEntriesTest001';
    console.info(TAG, 'start');
    let file = new UDC.File();
    file.uri = 'schema://com.samples.test/files/test.txt';
    let plainText = new UDC.PlainText();
    plainText.textContent = 'this is textContent';
    plainText.abstract = 'this is abstract';
    let link = new UDC.Hyperlink();
    link.url = 'www.XXX.com';
    link.description = 'this is description';
    let html = new UDC.HTML();
    html.htmlContent = '<div><p>标题</p></div>';
    html.plainContent = 'this is plainContent';
    let form = new UDC.SystemDefinedForm();
    form.formId = 123456;
    form.formName = 'MyFormName';
    form.bundleName = 'MyBundleName';
    form.abilityName = 'MyAbilityName';
    form.module = 'MyModule';
    form.details = {
      'formKey1': 123,
      'formKey2': 'formValue',
      'formKey3': U8_ARRAY,
    };
    let applicationDefinedRecord = new UDC.ApplicationDefinedRecord();
    applicationDefinedRecord.applicationDefinedType = 'ApplicationDefinedType';
    applicationDefinedRecord.rawData = U8_ARRAY;
    let unifiedData = new UDC.UnifiedData();
    unifiedData.addRecord(file);
    unifiedData.addRecord(plainText);
    unifiedData.addRecord(link);
    unifiedData.addRecord(html);
    unifiedData.addRecord(form);
    unifiedData.addRecord(applicationDefinedRecord);
    unifiedData.properties.tag = 'records_to_entries_data_format';
    expect(unifiedData.getRecords().length).assertEqual(6);
    UDC.convertRecordsToEntries(unifiedData);
    expect(unifiedData.getRecords().length).assertEqual(1);
    let records = unifiedData.getRecords();
    let recordEntries = records[0];
    expect(recordEntries.uri).assertEqual('schema://com.samples.test/files/test.txt');
    expect(recordEntries.getType()).assertEqual('general.file');
    expect(recordEntries.getValue()).assertEqual(undefined);
    let fileEntry = recordEntries.getEntry('general.file-uri');
    expect(fileEntry.uniformDataType).assertEqual('general.file-uri');
    expect(fileEntry.oriUri).assertEqual('schema://com.samples.test/files/test.txt');
    expect(fileEntry.fileType).assertEqual('general.file');
    let plainTextEntry = recordEntries.getEntry('general.plain-text');
    expect(plainTextEntry.textContent).assertEqual('this is textContent');
    expect(plainTextEntry.abstract).assertEqual('this is abstract');
    let linkEntry = recordEntries.getEntry('general.hyperlink');
    expect(linkEntry.url).assertEqual('www.XXX.com');
    expect(linkEntry.description).assertEqual('this is description');
    let htmlEntry = recordEntries.getEntry('general.html');
    expect(htmlEntry.htmlContent).assertEqual('<div><p>标题</p></div>');
    expect(htmlEntry.plainContent).assertEqual('this is plainContent');
    let formEntry = recordEntries.getEntry('openharmony.form');
    expect(formEntry.formId).assertEqual(123456);
    expect(formEntry.formName).assertEqual('MyFormName');
    expect(formEntry.bundleName).assertEqual('MyBundleName');
    expect(formEntry.abilityName).assertEqual('MyAbilityName');
    expect(formEntry.module).assertEqual('MyModule');
    expect(formEntry.details.formKey1).assertEqual(123);
    expect(formEntry.details.formKey2).assertEqual('formValue');
    let applicationDefinedEntry = recordEntries.getEntry('ApplicationDefinedType');
    for (let i = 0; i < U8_ARRAY.length; i++) {
      expect(applicationDefinedEntry.arrayBuffer[i]).assertEqual(U8_ARRAY[i]);
    }
    expect(applicationDefinedEntry.uniformDataType).assertEqual('ApplicationDefinedType');
    let entries = recordEntries.getEntries();
    expect(entries['general.file-uri'].uniformDataType).assertEqual('general.file-uri');
    expect(entries['general.file-uri'].oriUri).assertEqual('schema://com.samples.test/files/test.txt');
    expect(entries['general.file-uri'].fileType).assertEqual('general.file');
    expect(entries['general.plain-text'].uniformDataType).assertEqual('general.plain-text');
    expect(entries['general.plain-text'].textContent).assertEqual('this is textContent');
    expect(entries['general.plain-text'].abstract).assertEqual('this is abstract');
    expect(entries['general.hyperlink'].uniformDataType).assertEqual('general.hyperlink');
    expect(entries['general.hyperlink'].url).assertEqual('www.XXX.com');
    expect(entries['general.hyperlink'].description).assertEqual('this is description');
    expect(entries['general.html'].uniformDataType).assertEqual('general.html');
    expect(entries['general.html'].htmlContent).assertEqual('<div><p>标题</p></div>');
    expect(entries['general.html'].plainContent).assertEqual('this is plainContent');
    expect(entries['openharmony.form'].uniformDataType).assertEqual('openharmony.form');
    expect(entries['openharmony.form'].formId).assertEqual(123456);
    expect(entries['openharmony.form'].formName).assertEqual('MyFormName');
    expect(entries['openharmony.form'].bundleName).assertEqual('MyBundleName');
    expect(entries['openharmony.form'].abilityName).assertEqual('MyAbilityName');
    expect(entries['openharmony.form'].module).assertEqual('MyModule');
    expect(entries['openharmony.form'].details.formKey1).assertEqual(123);
    expect(entries['openharmony.form'].details.formKey2).assertEqual('formValue');
    for (let i = 0; i < U8_ARRAY.length; i++) {
      expect(entries.ApplicationDefinedType.arrayBuffer[i]).assertEqual(U8_ARRAY[i]);
    }
    expect(entries.ApplicationDefinedType.uniformDataType).assertEqual('ApplicationDefinedType');
    done();
  });

  /**
   * @tc.name toEntriesTest002
   * @tc.desc test toEntries function with duplicate type
   * @tc.type: FUNC
   * @tc.require:
   */
  it('toEntriesTest002', 0, async function (done) {
    const TAG = 'toEntriesTest002';
    console.info(TAG, 'start');
    let image = new UDC.Image();
    image.uri = 'schema://com.samples.test/files/test.jpg';
    let plainText = new UDC.PlainText();
    plainText.textContent = 'this is textContent';
    plainText.abstract = 'this is abstract';
    let video = new UDC.Video();
    video.uri = 'schema://com.samples.test/files/test.mp4';
    let unifiedData = new UDC.UnifiedData();
    unifiedData.addRecord(image);
    unifiedData.addRecord(plainText);
    unifiedData.addRecord(video);
    unifiedData.properties.tag = 'records_to_entries_data_format';
    expect(unifiedData.getRecords().length).assertEqual(3);
    UDC.convertRecordsToEntries(unifiedData);
    expect(unifiedData.getRecords().length).assertEqual(1);
    let records = unifiedData.getRecords();
    let recordEntries = records[0];
    expect(recordEntries.uri).assertEqual('schema://com.samples.test/files/test.jpg');
    expect(recordEntries.getType()).assertEqual('general.image');
    expect(recordEntries.getValue()).assertEqual(undefined);
    let entries = recordEntries.getEntries();
    expect(entries['general.file-uri'].uniformDataType).assertEqual('general.file-uri');
    expect(entries['general.file-uri'].oriUri).assertEqual('schema://com.samples.test/files/test.jpg');
    expect(entries['general.file-uri'].fileType).assertEqual('general.image');
    expect(entries['general.plain-text'].uniformDataType).assertEqual('general.plain-text');
    expect(entries['general.plain-text'].textContent).assertEqual('this is textContent');
    expect(entries['general.plain-text'].abstract).assertEqual('this is abstract');
    expect(entries['general.video']).assertEqual(undefined);
    done();
  });

  /**
   * @tc.name toEntriesTest003
   * @tc.desc test toEntries function with duplicate type
   * @tc.type: FUNC
   * @tc.require:
   */
  it('toEntriesTest003', 0, async function (done) {
    const TAG = 'toEntriesTest003';
    console.info(TAG, 'start');
    let recordFile = new UDC.UnifiedRecord('general.file', 'schema://com.samples.test/files/test.txt');
    let recordVideo = new UDC.UnifiedRecord('general.video', 'schema://com.samples.test/files/test.mp4');
    let recordPlainText = new UDC.UnifiedRecord('general.plain-text', 'this is textContent');
    let unifiedData = new UDC.UnifiedData();
    unifiedData.addRecord(recordFile);
    unifiedData.addRecord(recordVideo);
    unifiedData.addRecord(recordPlainText);
    unifiedData.properties.tag = 'records_to_entries_data_format';
    expect(unifiedData.getRecords().length).assertEqual(3);
    UDC.convertRecordsToEntries(unifiedData);
    expect(unifiedData.getRecords().length).assertEqual(1);
    let records = unifiedData.getRecords();
    let recordEntries = records[0];
    expect(recordEntries.uri).assertEqual('schema://com.samples.test/files/test.txt');
    expect(recordEntries.getType()).assertEqual('general.file');
    expect(recordEntries.getValue()).assertEqual('schema://com.samples.test/files/test.txt');
    let videoEntry = recordEntries.getEntry('general.file-uri');
    expect(videoEntry.oriUri).assertEqual('schema://com.samples.test/files/test.txt');
    expect(videoEntry.fileType).assertEqual('general.file');
    let plainTextEntry = recordEntries.getEntry('general.plain-text');
    expect(plainTextEntry.textContent).assertEqual('this is textContent');
    let entries = recordEntries.getEntries();
    expect(entries['general.file-uri'].uniformDataType).assertEqual('general.file-uri');
    expect(entries['general.file-uri'].oriUri).assertEqual('schema://com.samples.test/files/test.txt');
    expect(entries['general.file-uri'].fileType).assertEqual('general.file');
    expect(entries['general.plain-text'].uniformDataType).assertEqual('general.plain-text');
    expect(entries['general.plain-text'].textContent).assertEqual('this is textContent');
    expect(entries['general.video']).assertEqual(undefined);
    expect(entries['general.file']).assertEqual(undefined);
    done();
   });

   /**
   * @tc.name toEntriesTest004
   * @tc.desc test toEntries function with invalid data
   * @tc.type: FUNC
   * @tc.require:
   */
  it('toEntriesTest004', 0, function () {
    const TAG = 'toEntriesTest004';
    console.info(TAG, 'start');
    try {
      UDC.convertRecordsToEntries();
      console.error(TAG, 'Unreachable code!');
      expect(null).assertFail();
    } catch (e) {
      console.error(TAG, `get e. code is ${e.code},message is ${e.message} `);
      expect(e.code === ERROR_PARAMETER).assertTrue();
    }
    console.info(TAG, 'end');
   });

   /**
   * @tc.name toEntriesTest005
   * @tc.desc test toEntries function with invalid data
   * @tc.type: FUNC
   * @tc.require:
   */
  it('toEntriesTest005', 0, function () {
    const TAG = 'toEntriesTest005';
    console.info(TAG, 'start');
    try {
      UDC.convertRecordsToEntries(1);
      console.error(TAG, 'Unreachable code!');
      expect(null).assertFail();
    } catch (e) {
      console.error(TAG, `get e. code is ${e.code},message is ${e.message} `);
      expect(e.code === ERROR_PARAMETER).assertTrue();
    }
    console.info(TAG, 'end');
   });
});