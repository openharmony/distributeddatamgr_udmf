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

const TEST_BUNDLE_NAME = 'MyBundleName';
const KEY_TEST_ELEMENT = 'TestKey';
const VALUE_TEST_ELEMENT = 'TestValue';
const TEST_ID = 123456;
const TEST_ABILITY_NAME = 'MyAbilityName';
const TEST_MODULE = 'MyModule';

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
        content: '11'.repeat((1024 * 1000 + 1)),
      };
      let unifiedData = new UDC.UnifiedData(text);
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          expect(data[0].getRecords()[0].details.content).assertEqual('11'.repeat((1024 * 1000 + 1)));
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
      plainText.textContent = '11'.repeat((1024 * 1000 + 1))
      let unifiedData = new UDC.UnifiedData(plainText);
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          expect(data[0].getRecords()[0].textContent).assertEqual('11'.repeat((1024 * 1000 + 1)));
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
      link.url = '11'.repeat((1024 * 1000 + 1))
      let unifiedData = new UDC.UnifiedData(link);
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          expect(data[0].getRecords()[0].url).assertEqual('11'.repeat((1024 * 1000 + 1)));
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
      html.htmlContent = '11'.repeat((1024 * 1000 + 1))
      let unifiedData = new UDC.UnifiedData(html);
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          expect(data[0].getRecords()[0].htmlContent).assertEqual('11'.repeat((1024 * 1000 + 1)));
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
        content: '11'.repeat((1024 * 1000 + 1))
      }
      let unifiedData = new UDC.UnifiedData(systemDefinedRecord);
      UDC.insertData(optionsValid, unifiedData).then((data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          expect(data[0].getRecords()[0].details.content).assertEqual('11'.repeat((1024 * 1000 + 1)));
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
      systemDefinedForm.module = '11'.repeat((1024 * 1000 + 1))
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
          expect(data[0].getRecords()[0].module).assertEqual('11'.repeat((1024 * 1000 + 1)));
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
      systemDefinedAppItem.abilityName = '11'.repeat((1024 * 1000 + 1))
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
          expect(data[0].getRecords()[0].abilityName).assertEqual('11'.repeat((1024 * 1000 + 1)));
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
      text.rawData = new Uint8Array(Math.pow(2, 21));
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
      text.rawData = new Uint8Array(Math.pow(2, 21));
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
   * @tc.name UdmfTextOver4M
   * @tc.desc UdmfTextOver4M Over 4MB
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfTextOver4M', 0, async function (done) {
    const TAG = 'UdmfTextOver4M:';
    console.info(TAG, 'start');
    try {
      let text = new UDC.PlainText();
      text.textContent = '11'.repeat((1024 * 1000 + 1))
      let unifiedData = new UDC.UnifiedData(text);
      let html = new UDC.HTML();
      html.htmlContent = '11'.repeat((1024 * 1000 + 1))
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
          console.info(TAG, `records[0] = ${records[0].textContent === '11'.repeat((1024 * 1000 + 1))}.`);
          console.info(TAG, `records[1] = ${records[1].htmlContent === '11'.repeat((1024 * 1000 + 1))}.`);
          console.info(TAG, `records[0].getType() = ${records[0].getType()}.`);
          console.info(TAG, `records[1].getType() = ${records[1].getType()}.`);
          console.info(TAG, `records[0].getType() = ${records[0].getType() === UTD.UniformDataType.PLAIN_TEXT}.`);
          console.info(TAG, `records[1].getType() = ${records[1].getType() === UTD.UniformDataType.HTML}.`);
          expect(records[0].textContent).assertEqual('11'.repeat((1024 * 1000 + 1)));
          expect(records[1].htmlContent).assertEqual('11'.repeat((1024 * 1000 + 1)));
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
   * @tc.name UdmfTextAll plaintext 190MB
   * @tc.desc UdmfTextAll plaintext 190MB
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfTextAll', 0, async function (done) {
    const TAG = 'UdmfTextAll:';
    console.info(TAG, 'start');
    try {
      let text = new UDC.Text();
      let unifiedData = new UDC.UnifiedData(text);
      let link = new UDC.Hyperlink();
      unifiedData.addRecord(link);
      let html = new UDC.HTML();
      unifiedData.addRecord(html);
      let file = new UDC.File();
      unifiedData.addRecord(file);
      let folder = new UDC.Folder();
      unifiedData.addRecord(folder);
      let image = new UDC.Image();
      unifiedData.addRecord(image);
      let video = new UDC.Video();
      unifiedData.addRecord(video);
      let audio = new UDC.Audio();
      unifiedData.addRecord(audio);
      let systemDefinedRecord = new UDC.SystemDefinedRecord();
      unifiedData.addRecord(systemDefinedRecord);
      let systemDefinedPixelMap = new UDC.SystemDefinedPixelMap();
      unifiedData.addRecord(systemDefinedPixelMap);
      let form = new UDC.SystemDefinedForm();
      unifiedData.addRecord(form);
      let appItem = new UDC.SystemDefinedAppItem();
      unifiedData.addRecord(appItem);
      let applicationDefinedRecord = new UDC.ApplicationDefinedRecord();
      unifiedData.addRecord(applicationDefinedRecord);
      let plainText = new UDC.PlainText();
      let longText = '0123456789'.repeat((1024 * 2000));
      for (let i = 0; i < 10; i++) {
        plainText.textContent = longText
        unifiedData.addRecord(plainText)
      }
      await UDC.insertData(optionsValid, unifiedData).then(async (data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        await UDC.queryData(options).then((data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          let records = data[0].getRecords();
          console.info(TAG, `records.length = ${records.length}.`);
          for (let i = 0; i < records.length; i++) {
            console.info(TAG, `records[${i}].getType() = ${records[i].getType()}.`);
            if (records[i].getType() === UTD.UniformDataType.PLAIN_TEXT) {
              console.info(`content= ${records[i].textContent === '0123456789'.repeat((1024 * 2000))}`);
            }
          }
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
   * @tc.name UdmfText200M
   * @tc.desc UdmfText200M 200MB
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfText200M', 0, async function (done) {
    const TAG = 'UdmfText200M:';
    console.info(TAG, 'start');
    try {
      let plainText = new UDC.PlainText();
      let unifiedData = new UDC.UnifiedData(plainText);
      let longText = '0123456789'.repeat((1024 * 2000));
      for (let i = 0; i < 10; i++) {
        plainText.textContent = longText
        unifiedData.addRecord(plainText)
      }
      await UDC.insertData(optionsValid, unifiedData).then(async (data) => {
        console.info(TAG, `insert success. The key: ${data}`);
        let options = { key: data };
        console.info(TAG, `query start. The options: ${JSON.stringify(options)}`);
        await UDC.queryData(options).then(async (data) => {
          console.info(TAG, 'query success.');
          expect(data.length).assertEqual(1);
          let records = data[0].getRecords();
          console.info(TAG, `records.length = ${records.length}.`);
          for (let i = 0; i < records.length; i++) {
            if (ret[0].getRecords()[i].getType() === UTD.UniformDataType.PLAIN_TEXT) {
              console.info(`textContent = ${ret[0].getRecords()[i].textContent === '0123456789'.repeat((1024 * 2000))}`);
            }
          }
          await UDC.deleteData(options).then((data) => {
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
});