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
    let unifiedData = new UDC.UnifiedData(text);
    expect(unifiedData.hasType(textType)).assertEqual(true);
    expect(unifiedData.hasType(htmlType)).assertEqual(false);
    expect(unifiedData.hasType(plaintextType)).assertEqual(false);
    let types = unifiedData.getTypes();
    expect(types.length).assertEqual(1);
    expect(types[0]).assertEqual(textType);

    let html = new UDC.HTML();
    unifiedData.addRecord(html);
    expect(unifiedData.hasType(textType)).assertEqual(true);
    expect(unifiedData.hasType(htmlType)).assertEqual(true);
    expect(unifiedData.hasType(plaintextType)).assertEqual(false);
    types = unifiedData.getTypes();
    expect(types.length).assertEqual(2);
    expect(types[0]).assertEqual(textType);
    expect(types[1]).assertEqual(htmlType);
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
});