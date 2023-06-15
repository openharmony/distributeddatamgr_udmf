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
    let unifiedData = new UDMF.UnifiedData(text);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(1);
    expect(records[0].details.Key).assertEqual('text' + KEY_TEST_ELEMENT);
    expect(records[0].details.Value).assertEqual('text' + VALUE_TEST_ELEMENT);
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
    let unifiedData = new UDMF.UnifiedData(plainText);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(1);
    expect(records[0].details.Key).assertEqual('text' + KEY_TEST_ELEMENT);
    expect(records[0].details.Value).assertEqual('text' + VALUE_TEST_ELEMENT);
    expect(records[0].textContent).assertEqual('textContent');
    expect(records[0].abstract).assertEqual('abstract');
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
    let unifiedData = new UDMF.UnifiedData(link);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(1);
    expect(records[0].details.Key).assertEqual('link' + KEY_TEST_ELEMENT);
    expect(records[0].details.Value).assertEqual('link' + VALUE_TEST_ELEMENT);
    expect(records[0].url).assertEqual('url');
    expect(records[0].description).assertEqual('description');
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
    let unifiedData = new UDMF.UnifiedData(html);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(1);
    expect(records[0].details.Key).assertEqual('html' + KEY_TEST_ELEMENT);
    expect(records[0].details.Value).assertEqual('html' + VALUE_TEST_ELEMENT);
    expect(records[0].htmlContent).assertEqual('htmlContent');
    expect(records[0].plainContent).assertEqual('plainContent');
    console.info("UdmfHtmlTest end")
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
    let unifiedData = new UDMF.UnifiedData(systemDefinedRecord);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(1);
    expect(records[0].details.recordKey1).assertEqual('systemDefinedRecord' + KEY_TEST_ELEMENT);
    expect(records[0].details.recordKey2).assertEqual(1);
    for (var i = 0; i < u8Array.length; i++) {
      expect(records[0].details.recordKey3[i]).assertEqual(u8Array[i]);
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
    let unifiedData = new UDMF.UnifiedData(systemDefinedPixelMap);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(1);
    expect(records[0].details.recordKey1).assertEqual('systemDefinedPixelMap' + KEY_TEST_ELEMENT);
    expect(records[0].details.recordKey2).assertEqual(1);
    for (var i = 0; i < u8Array.length; i++) {
      expect(records[0].details.recordKey3[i]).assertEqual(u8Array[i]);
    }
    for (var i = 0; i < u8Array.length; i++) {
      expect(records[0].rawData[i]).assertEqual(u8Array[i]);
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
    let unifiedData = new UDMF.UnifiedData(form);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(1);
    expect(records[0].details.formKey1).assertEqual(1);
    expect(records[0].details.formKey2).assertEqual('form' + VALUE_TEST_ELEMENT);
    for (var i = 0; i < u8Array.length; i++) {
      expect(records[0].details.formKey3[i]).assertEqual(u8Array[i]);
    }
    expect(records[0].formId).assertEqual(TEST_ID);
    expect(records[0].formName).assertEqual('MyFormName');
    expect(records[0].bundleName).assertEqual(TEST_BUNDLE_NAME);
    expect(records[0].abilityName).assertEqual(TEST_ABILITY_NAME);
    expect(records[0].module).assertEqual(TEST_MODULE);
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
    let unifiedData = new UDMF.UnifiedData(appItem);
    let records = unifiedData.getRecords();
    expect(records.length).assertEqual(1);
    expect(records[0].details.appItemKey1).assertEqual(1);
    expect(records[0].details.appItemKey2).assertEqual('appItem' + VALUE_TEST_ELEMENT);
    for (var i = 0; i < u8Array.length; i++) {
      expect(records[0].details.appItemKey3[i]).assertEqual(u8Array[i]);
    }
    expect(records[0].appId).assertEqual('MyAppId');
    expect(records[0].appName).assertEqual('MyAppName');
    expect(records[0].abilityName).assertEqual(TEST_ABILITY_NAME);
    expect(records[0].bundleName).assertEqual(TEST_BUNDLE_NAME);
    expect(records[0].appIconId).assertEqual('MyAppIconId');
    expect(records[0].appLabelId).assertEqual('MyAppLabelId');
    console.info("UdmfSystemDefinedAppItemTest end")
  })
})