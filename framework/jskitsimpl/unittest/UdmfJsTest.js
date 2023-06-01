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

import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from 'deccjsunit/index'
import UDMF from '@ohos.data.UDMF'

const TEST_BUNDLE_NAME = 'MyBundleName';
const KEY_TEST_ELEMENT = 'TestKey';
const VALUE_TEST_ELEMENT = 'TestValue';
const TEST_ID = 123456;
const TEST_ABILITY_NAME = 'MyAbilityName';
const TEST_MODULE = 'MyModule';

let u8Array = new Uint8Array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10]);
let unifiedDataAll;

function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

describe('UdmfJSTest', function () {

  /**
   * @tc.name UdmfTextTest
   * @tc.desc Test Js Api Text testcase
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfTextTest', 0, function () {
    console.info('UdmfTextTest start');
    let text = new UDMF.Text();
    text.details = {
      Key: 'text' + KEY_TEST_ELEMENT,
      Value: 'text' + VALUE_TEST_ELEMENT,
    };
    unifiedDataAll = new UDMF.UnifiedData(text);
    let unifiedData = new UDMF.UnifiedData(text);
    let records = unifiedData.getRecords();
    let record = <UDMF.Text> (records[0]);
    expect(records.length).assertEqual(1);
    expect(record.details.Key).assertEqual('text' + KEY_TEST_ELEMENT);
    expect(record.details.Value).assertEqual('text' + VALUE_TEST_ELEMENT);
    console.info("UdmfTextTest end");
  })

  /**
   * @tc.name UdmfPlainTextTest
   * @tc.desc Test Js Api PlainText testcase
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfPlainTextTest', 0, function () {
    console.info('UdmfPlainTextTest start');
    let plainText = new UDMF.PlainText();
    plainText.details = {
      Key: 'text' + KEY_TEST_ELEMENT,
      Value: 'text' + VALUE_TEST_ELEMENT,
    };
    plainText.textContent = 'textContent';
    plainText.abstract = 'abstract';
    unifiedDataAll.addRecord(plainText);
    let unifiedData = new UDMF.UnifiedData(plainText);
    let records = unifiedData.getRecords();
    let record = <UDMF.PlainText> (records[0]);
    expect(records.length).assertEqual(1);
    expect(record.details.Key).assertEqual('text' + KEY_TEST_ELEMENT);
    expect(record.details.Value).assertEqual('text' + VALUE_TEST_ELEMENT);
    expect(record.textContent).assertEqual('textContent');
    expect(record.abstract).assertEqual('abstract');
    console.info("UdmfPlainTextTest end")
  })
  /**
   * @tc.name UdmfHyperlinkTest
   * @tc.desc Test Js Api Hyperlink testcase
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfHyperlinkTest', 0, function () {
    console.info('UdmfHyperlinkTest start');
    let link = new UDMF.Hyperlink();
    link.details = {
      Key: 'link' + KEY_TEST_ELEMENT,
      Value: 'link' + VALUE_TEST_ELEMENT,
    };
    link.url = 'url';
    link.description = 'description';
    unifiedDataAll.addRecord(link);
    let unifiedData = new UDMF.UnifiedData(link);
    let records = unifiedData.getRecords();
    let record = <UDMF.Hyperlink> (records[0]);
    expect(records.length).assertEqual(1);
    expect(record.details.Key).assertEqual('link' + KEY_TEST_ELEMENT);
    expect(record.details.Value).assertEqual('link' + VALUE_TEST_ELEMENT);
    expect(record.url).assertEqual('url');
    expect(record.description).assertEqual('description');
    console.info("UdmfHyperlinkTest end")
  })

  /**
   * @tc.name UdmfHtmlTest
   * @tc.desc Test Js Api HTML testcase
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfHtmlTest', 0, function () {
    console.info('UdmfHtmlTest start');
    let html = new UDMF.HTML();
    html.details = {
      Key: 'html' + KEY_TEST_ELEMENT,
      Value: 'html' + VALUE_TEST_ELEMENT,
    };
    html.htmlContent = 'htmlContent';
    html.plainContent = 'plainContent';
    unifiedDataAll.addRecord(html);
    let unifiedData = new UDMF.UnifiedData(html);
    let records = unifiedData.getRecords();
    let record = <UDMF.HTML> (records[0]);
    expect(records.length).assertEqual(1);
    expect(record.details.Key).assertEqual('html' + KEY_TEST_ELEMENT);
    expect(record.details.Value).assertEqual('html' + VALUE_TEST_ELEMENT);
    expect(record.htmlContent).assertEqual('htmlContent');
    expect(record.plainContent).assertEqual('plainContent');
    console.info("UdmfHtmlTest end")
  })

  /**
   * @tc.name UdmfFileTest
   * @tc.desc Test Js Api File testcase
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfFileTest', 0, function () {
    console.info('UdmfFileTest start');
    let file = new UDMF.File();
    file.details = {
      Key: 'file' + KEY_TEST_ELEMENT,
      Value: 'file' + VALUE_TEST_ELEMENT,
    };
    file.uri = 'uri';
    unifiedDataAll.addRecord(file);
    let unifiedData = new UDMF.UnifiedData(file);
    let records = unifiedData.getRecords();
    let record = <UDMF.File> (records[0]);
    expect(records.length).assertEqual(1);
    expect(record.details.Key).assertEqual('file' + KEY_TEST_ELEMENT);
    expect(record.details.Value).assertEqual('file' + VALUE_TEST_ELEMENT);
    expect(record.uri).assertEqual('uri');
    console.info("UdmfFileTest end")
  })

  /**
   * @tc.name UdmfFolderTest
   * @tc.desc Test Js Api Folder testcase
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfFolderTest', 0, function () {
    console.info('UdmfFolderTest start');
    let folder = new UDMF.Folder();
    folder.details = {
      Key: 'folder' + KEY_TEST_ELEMENT,
      Value: 'folder' + VALUE_TEST_ELEMENT,
    };
    folder.uri = 'folderUri';
    unifiedDataAll.addRecord(folder);
    let unifiedData = new UDMF.UnifiedData(folder);
    let records = unifiedData.getRecords();
    let record = <UDMF.Folder> (records[0]);
    expect(records.length).assertEqual(1);
    expect(record.details.Key).assertEqual('folder' + KEY_TEST_ELEMENT);
    expect(record.details.Value).assertEqual('folder' + VALUE_TEST_ELEMENT);
    expect(record.uri).assertEqual('folderUri');
    console.info("UdmfFolderTest end")
  })

  /**
   * @tc.name UdmfImageTest
   * @tc.desc Test Js Api Image testcase
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfImageTest', 0, function () {
    console.info('UdmfImageTest start');
    let image = new UDMF.Image();
    image.details = {
      Key: 'image' + KEY_TEST_ELEMENT,
      Value: 'image' + VALUE_TEST_ELEMENT,
    };
    image.imageUri = 'imageUri';
    unifiedDataAll.addRecord(image);
    let unifiedData = new UDMF.UnifiedData(image);
    let records = unifiedData.getRecords();
    let record = <UDMF.Image> (records[0]);
    expect(records.length).assertEqual(1);
    expect(record.details.Key).assertEqual('image' + KEY_TEST_ELEMENT);
    expect(record.details.Value).assertEqual('image' + VALUE_TEST_ELEMENT);
    expect(record.imageUri).assertEqual('imageUri');
    console.info("UdmfImageTest end")
  })

  /**
   * @tc.name UdmfVideoTest
   * @tc.desc Test Js Api Video testcase
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfVideoTest', 0, function () {
    console.info('UdmfVideoTest start');
    let video = new UDMF.Video();
    video.details = {
      Key: 'video' + KEY_TEST_ELEMENT,
      Value: 'video' + VALUE_TEST_ELEMENT,
    };
    video.videoUri = 'videoUri';
    unifiedDataAll.addRecord(video);
    let unifiedData = new UDMF.UnifiedData(video);
    let records = unifiedData.getRecords();
    let record = <UDMF.Video> (records[0]);
    expect(records.length).assertEqual(1);
    expect(record.details.Key).assertEqual('video' + KEY_TEST_ELEMENT);
    expect(record.details.Value).assertEqual('video' + VALUE_TEST_ELEMENT);
    expect(record.videoUri).assertEqual('videoUri');
    console.info("UdmfVideoTest end")
  })

  /**
   * @tc.name UdmfSystemDefinedRecordTest
   * @tc.desc Test Js Api SystemDefinedRecord testcase
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfSystemDefinedRecordTest', 0, function () {
    console.info('UdmfSystemDefinedRecordTest start');
    let systemDefinedRecord = new UDMF.SystemDefinedRecord();
    systemDefinedRecord.details = {
      recordKey1: 'systemDefinedRecord' + KEY_TEST_ELEMENT,
      recordKey2: 1,
      recordKey3: u8Array
    };
    unifiedDataAll.addRecord(systemDefinedRecord);
    let unifiedData = new UDMF.UnifiedData(systemDefinedRecord);
    let records = unifiedData.getRecords();
    let record = <UDMF.SystemDefinedRecord> (records[0]);
    expect(records.length).assertEqual(1);
    expect(record.details.recordKey1).assertEqual('systemDefinedRecord' + KEY_TEST_ELEMENT);
    expect(record.details.recordKey2).assertEqual(1);
    for (var i = 0; i < u8Array.length; i++) {
      expect(record.details.recordKey3[i]).assertEqual(u8Array[i]);
    }
    console.info("UdmfSystemDefinedRecordTest end")
  })

  /**
   * @tc.name UdmfSystemDefinedPixelMapTest
   * @tc.desc Test Js Api SystemDefinedPixelMap testcase
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfSystemDefinedPixelMapTest', 0, function () {
    console.info('UdmfSystemDefinedPixelMapTest start');
    let systemDefinedPixelMap = new UDMF.SystemDefinedPixelMap();
    systemDefinedPixelMap.details = {
      recordKey1: 'systemDefinedPixelMap' + KEY_TEST_ELEMENT,
      recordKey2: 1,
      recordKey3: u8Array
    };
    systemDefinedPixelMap.rawData = u8Array;
    unifiedDataAll.addRecord(systemDefinedPixelMap);
    let unifiedData = new UDMF.UnifiedData(systemDefinedPixelMap);
    let records = unifiedData.getRecords();
    let record = <UDMF.SystemDefinedPixelMap> (records[0]);
    expect(records.length).assertEqual(1);
    expect(record.details.recordKey1).assertEqual('systemDefinedPixelMap' + KEY_TEST_ELEMENT);
    expect(record.details.recordKey2).assertEqual(1);
    for (var i = 0; i < u8Array.length; i++) {
      expect(record.details.recordKey3[i]).assertEqual(u8Array[i]);
    }
    for (var i = 0; i < u8Array.length; i++) {
      expect(record.rawData[i]).assertEqual(u8Array[i]);
    }
    console.info("UdmfSystemDefinedPixelMapTest end")
  })

  /**
   * @tc.name UdmfSystemDefinedFormTest
   * @tc.desc Test Js Api SystemDefinedForm testcase
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfSystemDefinedFormTest', 0, function () {
    console.info('UdmfSystemDefinedFormTest start');
    let form = new UDMF.SystemDefinedForm();
    form.formId = TEST_ID;
    form.formName = 'MyFormName';
    form.bundleName = TEST_BUNDLE_NAME;
    form.abilityName = TEST_ABILITY_NAME;
    form.module = TEST_MODULE;
    form.details = {
      formKey1: 1,
      formKey2: 'form' + VALUE_TEST_ELEMENT,
      formKey3: u8Array,
    }
    unifiedDataAll.addRecord(form);
    let unifiedData = new UDMF.UnifiedData(form);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(1);
    let record = <UDMF.SystemDefinedForm> (records[0]);
    expect(record.details.formKey1).assertEqual(330);
    expect(record.details.formKey2).assertEqual('form' + VALUE_TEST_ELEMENT);
    for (var i = 0; i < u8Array.length; i++) {
      expect(record.details.formKey3[i]).assertEqual(u8Array[i]);
    }
    expect(record.formId).assertEqual(TEST_ID);
    expect(record.formName).assertEqual('MyFormName');
    expect(record.bundleName).assertEqual(TEST_BUNDLE_NAME);
    expect(record.abilityName).assertEqual(TEST_ABILITY_NAME);
    expect(record.module).assertEqual(TEST_MODULE);
    console.info("UdmfSystemDefinedFormTest end")
  })

  /**
   * @tc.name UdmfSystemDefinedAppItemTest
   * @tc.desc Test Js Api SystemDefinedAppItem testcase
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfSystemDefinedAppItemTest', 0, function () {
    console.info('UdmfSystemDefinedAppItemTest start');
    let appItem = new UDMF.SystemDefinedAppItem();
    appItem.appId = 'MyAppId';
    appItem.appName = 'MyAppName';
    appItem.abilityName = TEST_ABILITY_NAME;
    appItem.bundleName = TEST_BUNDLE_NAME;
    appItem.appIconId = 'MyAppIconId';
    appItem.appLabelId = 'MyAppLabelId';
    appItem.details = {
      appItemKey1: 1,
      appItemKey2: 'appItem' + VALUE_TEST_ELEMENT,
      appItemKey3: u8Array,
    }
    unifiedDataAll.addRecord(appItem);
    let unifiedData = new UDMF.UnifiedData(appItem);
    let records = unifiedData.getRecords();
    let record = <UDMF.SystemDefinedAppItem> (records[0]);
    expect(records.length).assertEqual(1);
    expect(record.details.appItemKey1).assertEqual(1);
    expect(record.details.appItemKey2).assertEqual('appItem' + VALUE_TEST_ELEMENT);
    for (var i = 0; i < u8Array.length; i++) {
      expect(record.details.appItemKey3[i]).assertEqual(u8Array[i]);
    }
    expect(record.appId).assertEqual('MyAppId');
    expect(record.appName).assertEqual('MyAppName');
    expect(record.abilityName).assertEqual(TEST_ABILITY_NAME);
    expect(record.bundleName).assertEqual(TEST_BUNDLE_NAME);
    expect(record.appIconId).assertEqual('MyAppIconId');
    expect(record.appLabelId).assertEqual('MyAppLabelId');
    console.info("UdmfSystemDefinedAppItemTest end")
  })

  /**
   * @tc.name UdmfSystemDefinedFormTest
   * @tc.desc Test Js Api ApplicationDefinedRecord testcase
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfApplicationDefinedRecord', 0, function () {
    console.info('UdmfApplicationDefinedRecord start');
    let applicationDefinedRecord = new UDMF.ApplicationDefinedRecord();
    applicationDefinedRecord.applicationDefinedType = 'applicationDefinedType';
    applicationDefinedRecord.rawData = u8Array;
    unifiedDataAll.addRecord(applicationDefinedRecord);
    let unifiedData = new UDMF.UnifiedData(applicationDefinedRecord);
    let records = unifiedData.getRecords();
    let record = <UDMF.ApplicationDefinedRecord> (records[0]);
    expect(records.length).assertEqual(1);
    expect(record.applicationDefinedType).assertEqual('applicationDefinedType');
    for (var i = 0; i < u8Array.length; i++) {
      expect(record.rawData[i]).assertEqual(u8Array[i]);
    }
    console.info("UdmfApplicationDefinedRecord end")
  })

  /**
   * @tc.name SingleKvStorePutStringCallbackTest001
   * @tc.desc Test Js Api SingleKvStore.Put(String) testcase 001
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfAllRecordsTest', 0, function () {
    let records = unifiedDataAll.getRecords();
    expect(records.length).assertEqual(13);
    let record1 = <UDMF.Text> (records[0]);
    let record2 = <UDMF.PlainText> (records[1]);
    let record3 = <UDMF.Hyperlink> (records[2]);
    let record4 = <UDMF.HTML> (records[3]);
    let record5 = <UDMF.File> (records[4]);
    let record6 = <UDMF.Folder> (records[5]);
    let record7 = <UDMF.Image> (records[6]);
    let record8 = <UDMF.Video> (records[7]);
    let record9 = <UDMF.SystemDefinedRecord> (records[8]);
    let record10 = <UDMF.SystemDefinedPixelMap> (records[9]);
    let record11 = <UDMF.SystemDefinedForm> (records[10]);
    let record12 = <UDMF.SystemDefinedAppItem> (records[11]);
    let record13 = <UDMF.ApplicationDefinedRecord> (records[12]);
    expect(record1.getType()).assertEqual(UDMF.UnifiedDataType.TEXT);
    expect(record2.getType()).assertEqual(UDMF.UnifiedDataType.PLAIN_TEXT);
    expect(record3.getType()).assertEqual(UDMF.UnifiedDataType.HYPERLINK);
    expect(record4.getType()).assertEqual(UDMF.UnifiedDataType.HTML);
    expect(record5.getType()).assertEqual(UDMF.UnifiedDataType.FILE);
    expect(record6.getType()).assertEqual(UDMF.UnifiedDataType.FOLDER);
    expect(record7.getType()).assertEqual(UDMF.UnifiedDataType.IMAGE);
    expect(record8.getType()).assertEqual(UDMF.UnifiedDataType.VIDEO);
    expect(record9.getType()).assertEqual(UDMF.UnifiedDataType.SYSTEM_DEFINED_RECORD);
    expect(record10.getType()).assertEqual(UDMF.UnifiedDataType.SYSTEM_DEFINED_PIXEL_MAP);
    expect(record11.getType()).assertEqual(UDMF.UnifiedDataType.SYSTEM_DEFINED_FORM);
    expect(record12.getType()).assertEqual(UDMF.UnifiedDataType.SYSTEM_DEFINED_APP_ITEM);
    expect(record13.getType()).assertEqual(UDMF.UnifiedDataType.APPLICATION_DEFINED_RECORD);
  })
})