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
const INVALID_TYPE1 = 'invalidUtdType';
const INVALID_TYPE2 = 123456;


describe('UdmfUtdJSTest', function () {

  /*
   * @tc.name UdmfTestTypeDescriptor001
   * @tc.desc Test Js Api input invalid string
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it ('UdmfTestTypeDescriptor001', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor001:';
    console.info(TAG, 'start');
    let typeObj = UTD.getTypeDescriptor('general.invalidType');
    console.info(TAG, 'typeDescriptor, ret= ' + typeObj);
    if (typeObj == null) {
      console.info(TAG, 'typeDescriptor, typeObj == null is true');
    }
    expect((typeObj == null)).assertEqual(true);
    console.info(TAG, 'end');
  });

  /*
   * @tc.name UdmfTestTypeDescriptor002
   * @tc.desc Test Js Api
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it ('UdmfTestTypeDescriptor002', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor002:';
    console.info(TAG, 'start');
    let typeObj = UTD.getTypeDescriptor('com.adobe.photoshop-image');
    let typeId = typeObj.typeId;
    let belonging = typeObj.belongingToTypes;
    let description = typeObj.description;
    let referenceURL = typeObj.referenceURL;
    let iconFile = typeObj.iconFile;
    let filenameExtensions = typeObj.filenameExtensions;
    let mimeTypes = typeObj.mimeTypes;
    console.info(TAG, ', typeId: ' + typeId + ', ' + Object.prototype.toString.call(typeId) +
      ', belongingToTypes: ' + belonging + ', ' + Object.prototype.toString.call(belonging));
    console.info(TAG, 'description: ' + typeObj.description + ', ' + Object.prototype.toString.call(description));
    console.info(TAG, 'referenceURL: ' + referenceURL + ', ' + Object.prototype.toString.call(referenceURL) +
      ', iconFile: ' + iconFile + ', ' + Object.prototype.toString.call(iconFile));
    expect(typeObj.typeId).assertEqual(UTD.UniformDataType.PHOTOSHOP_IMAGE);
    expect(typeObj.belongingToTypes[0]).assertEqual('general.image');
    expect(typeObj.description).assertEqual('Adobe Photoshop document.');
    let equalStr = 'https://gitee.com/openharmony/docs/blob/master/en/application-dev/reference/' +
      'apis/js-apis-data-uniformTypeDescriptor.md#uniformdatatype';
    expect(typeObj.referenceURL).assertEqual(equalStr);
    expect(typeObj.iconFile).assertEqual('sys.media.ohos_ic_normal_white_grid_image');
    expect(typeObj.filenameExtensions[0]).assertEqual('.psd');
    expect(typeObj.mimeTypes[0]).assertEqual('image/x-photoshop');
    console.info(TAG, 'end');
  });

  /*
   * @tc.name UdmfTestTypeDescriptor003
   * @tc.desc Test Js Api
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it ('UdmfTestTypeDescriptor003', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor003:';
    console.info(TAG, 'start');
    let typeObj = UTD.getTypeDescriptor('general.type-script');
    let typeObj2 = UTD.getTypeDescriptor('general.python-script');
    let typeObj3 = UTD.getTypeDescriptor('general.python-script');
    console.info(TAG, 'typeDescriptor, ret ' + typeObj);
    console.info(TAG, 'typeDescriptor, ret ' + typeObj2);
    let ret = typeObj.equals(typeObj2);
    console.info(TAG, 'typeObj equals with typeObj2 is ' + ret);
    expect(ret).assertEqual(false);
    ret = typeObj2.equals(typeObj3);
    console.info(TAG, 'typeObj2 equals with typeObj3 is ' + ret);
    expect(ret).assertEqual(true);
    console.info(TAG, 'end');
  });

  /*
   * @tc.name UdmfTestTypeDescriptor004
   * @tc.desc Test Js Api invalid para type
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it ('UdmfTestTypeDescriptor004', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor004:';
    console.info(TAG, 'start');
    try {
      let typeObj = UTD.getTypeDescriptor(null);
      console.info(TAG, 'typeDescriptor, ret ' + typeObj);
    } catch (e) {
      console.error(TAG, `get e. code is ${e.code},message is ${e.message} `);
      expect(e.code === ERROR_PARAMETER).assertTrue();
    }
    console.info(TAG, 'end');
  });

  /*
 * @tc.name UdmfTestTypeDescriptor005
 * @tc.desc Test Js Api
 * @tc.type: FUNC
 * @tc.require: issueNumber
 */
  it ('UdmfTestTypeDescriptor005', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor005:';
    console.info(TAG, 'start');
    let typeObj = UTD.getTypeDescriptor('com.adobe.photoshop-image', INVALID_TYPE1, INVALID_TYPE2);
    let typeId = typeObj.typeId;
    let belonging = typeObj.belongingToTypes;
    let description = typeObj.description;
    let referenceURL = typeObj.referenceURL;
    let iconFile = typeObj.iconFile;
    console.info(TAG, ', typeId: ' + typeId + ', ' + Object.prototype.toString.call(typeId) +
      ', belongingToTypes: ' + belonging + ', ' + Object.prototype.toString.call(belonging));
    console.info(TAG, 'description: ' + typeObj.description + ', ' + Object.prototype.toString.call(description));
    console.info(TAG, 'referenceURL: ' + referenceURL + ', ' + Object.prototype.toString.call(referenceURL) +
      ', iconFile: ' + iconFile + ', ' + Object.prototype.toString.call(iconFile));
    expect(typeObj.typeId).assertEqual(UTD.UniformDataType.PHOTOSHOP_IMAGE);
    expect(typeObj.belongingToTypes[0]).assertEqual('general.image');
    expect(typeObj.description).assertEqual('Adobe Photoshop document.');
    let equalStr = 'https://gitee.com/openharmony/docs/blob/master/en/application-dev/reference/' +
      'apis/js-apis-data-uniformTypeDescriptor.md#uniformdatatype';
    expect(typeObj.referenceURL).assertEqual(equalStr);
    expect(typeObj.iconFile).assertEqual('sys.media.ohos_ic_normal_white_grid_image');
    console.info(TAG, 'end');
  });

  /*
   * @tc.name UdmfTestTypeDescriptor007
   * @tc.desc Test Js Api foreach all UniformDataType
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it ('UdmfTestTypeDescriptor006', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor006:';
    console.info(TAG, 'start');
    for (let utdType in UTD.UniformDataType) {
      let typeObj = UTD.getTypeDescriptor(UTD.UniformDataType[utdType]);
      if (typeObj != null) {
        expect(typeObj.typeId).assertEqual(UTD.UniformDataType[utdType]);
      }
    }
    console.info(TAG, 'end');
  });

  /*
   * @tc.name UdmfTestTypeDescriptor007
   * @tc.desc Test Js Api getTypeDescriptor no para
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it ('UdmfTestTypeDescriptor007', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor007:';
    console.info(TAG, 'start');
    try {
      let typeObj = UTD.getTypeDescriptor();
      console.info(TAG, 'typeDescriptor, ret ' + typeObj);
    } catch (e) {
      console.error(TAG, `get e. code is ${e.code},message is ${e.message} `);
      expect(e.code === ERROR_PARAMETER).assertTrue();
    }
    console.info(TAG, 'end');
  });

  /*
   * @tc.name UdmfTestTypeDescriptor008
   * @tc.desc Test Js Api equals invalid para type
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it ('UdmfTestTypeDescriptor008', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor008:';
    console.info(TAG, 'start');
    let typeObj = UTD.getTypeDescriptor('general.type-script');
    console.info(TAG, 'typeDescriptor, ret ' + typeObj);
    try {
      typeObj.equals('1111');
      expect().assertFail();
    } catch (e) {
      console.error(TAG, `get e. code is ${e.code},message is ${e.message} `);
      expect(e.code === ERROR_PARAMETER).assertTrue();
    }
    console.info(TAG, 'end');
  });

  /*
   * @tc.name UdmfTestTypeDescriptor009
   * @tc.desc Test Js Api enum value judge part1
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it ('UdmfTestTypeDescriptor009', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor009:';
    console.info(TAG, 'start');
    expect(UTD.UniformDataType.TEXT).assertEqual('general.text');
    expect(UTD.UniformDataType.PLAIN_TEXT).assertEqual('general.plain-text');
    expect(UTD.UniformDataType.HTML).assertEqual('general.html');
    expect(UTD.UniformDataType.HYPERLINK).assertEqual('general.hyperlink');
    expect(UTD.UniformDataType.XML).assertEqual('general.xml');
    expect(UTD.UniformDataType.SOURCE_CODE).assertEqual('general.source-code');
    expect(UTD.UniformDataType.SCRIPT).assertEqual('general.script');
    expect(UTD.UniformDataType.SHELL_SCRIPT).assertEqual('general.shell-script');
    expect(UTD.UniformDataType.CSH_SCRIPT).assertEqual('general.csh-script');
    expect(UTD.UniformDataType.PERL_SCRIPT).assertEqual('general.perl-script');
    expect(UTD.UniformDataType.PHP_SCRIPT).assertEqual('general.php-script');
    expect(UTD.UniformDataType.PYTHON_SCRIPT).assertEqual('general.python-script');
    expect(UTD.UniformDataType.RUBY_SCRIPT).assertEqual('general.ruby-script');
    expect(UTD.UniformDataType.TYPE_SCRIPT).assertEqual('general.type-script');
    expect(UTD.UniformDataType.JAVA_SCRIPT).assertEqual('general.java-script');
    expect(UTD.UniformDataType.C_HEADER).assertEqual('general.c-header');
    expect(UTD.UniformDataType.C_SOURCE).assertEqual('general.c-source');
    expect(UTD.UniformDataType.C_PLUS_PLUS_HEADER).assertEqual('general.c-plus-plus-header');
    expect(UTD.UniformDataType.C_PLUS_PLUS_SOURCE).assertEqual('general.c-plus-plus-source');
    expect(UTD.UniformDataType.JAVA_SOURCE).assertEqual('general.java-source');
    expect(UTD.UniformDataType.EBOOK).assertEqual('general.ebook');
    expect(UTD.UniformDataType.EPUB).assertEqual('general.epub');
    expect(UTD.UniformDataType.AZW).assertEqual('com.amazon.azw');
    expect(UTD.UniformDataType.AZW3).assertEqual('com.amazon.azw3');
    expect(UTD.UniformDataType.KFX).assertEqual('com.amazon.kfx');
    expect(UTD.UniformDataType.MOBI).assertEqual('com.amazon.mobi');
    expect(UTD.UniformDataType.MEDIA).assertEqual('general.media');
    expect(UTD.UniformDataType.IMAGE).assertEqual('general.image');
    expect(UTD.UniformDataType.JPEG).assertEqual('general.jpeg');
    console.info(TAG, 'end');
  });

  /*
   * @tc.name UdmfTestTypeDescriptor010
   * @tc.desc Test Js Api enum value judge part2
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it ('UdmfTestTypeDescriptor010', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor010:';
    console.info(TAG, 'start');
    expect(UTD.UniformDataType.PNG).assertEqual('general.png');
    expect(UTD.UniformDataType.RAW_IMAGE).assertEqual('general.raw-image');
    expect(UTD.UniformDataType.TIFF).assertEqual('general.tiff');
    expect(UTD.UniformDataType.BMP).assertEqual('com.microsoft.bmp');
    expect(UTD.UniformDataType.ICO).assertEqual('com.microsoft.ico');
    expect(UTD.UniformDataType.PHOTOSHOP_IMAGE).assertEqual('com.adobe.photoshop-image');
    expect(UTD.UniformDataType.AI_IMAGE).assertEqual('com.adobe.illustrator.ai-image');
    expect(UTD.UniformDataType.WORD_DOC).assertEqual('com.microsoft.word.doc');
    expect(UTD.UniformDataType.EXCEL).assertEqual('com.microsoft.excel.xls');
    expect(UTD.UniformDataType.PPT).assertEqual('com.microsoft.powerpoint.ppt');
    expect(UTD.UniformDataType.PDF).assertEqual('com.adobe.pdf');
    expect(UTD.UniformDataType.POSTSCRIPT).assertEqual('com.adobe.postscript');
    expect(UTD.UniformDataType.ENCAPSULATED_POSTSCRIPT).assertEqual('com.adobe.encapsulated-postscript');
    expect(UTD.UniformDataType.VIDEO).assertEqual('general.video');
    expect(UTD.UniformDataType.AVI).assertEqual('general.avi');
    expect(UTD.UniformDataType.MPEG).assertEqual('general.mpeg');
    expect(UTD.UniformDataType.MPEG4).assertEqual('general.mpeg-4');
    expect(UTD.UniformDataType.VIDEO_3GPP).assertEqual('general.3gpp');
    expect(UTD.UniformDataType.VIDEO_3GPP2).assertEqual('general.3gpp2');
    expect(UTD.UniformDataType.WINDOWS_MEDIA_WM).assertEqual('com.microsoft.windows-media-wm');
    expect(UTD.UniformDataType.WINDOWS_MEDIA_WMV).assertEqual('com.microsoft.windows-media-wmv');
    expect(UTD.UniformDataType.WINDOWS_MEDIA_WMP).assertEqual('com.microsoft.windows-media-wmp');
    expect(UTD.UniformDataType.AUDIO).assertEqual('general.audio');
    expect(UTD.UniformDataType.AAC).assertEqual('general.aac');
    expect(UTD.UniformDataType.AIFF).assertEqual('general.aiff');
    expect(UTD.UniformDataType.ALAC).assertEqual('general.alac');
    expect(UTD.UniformDataType.FLAC).assertEqual('general.flac');
    expect(UTD.UniformDataType.MP3).assertEqual('general.mp3');
    expect(UTD.UniformDataType.OGG).assertEqual('general.ogg');
    expect(UTD.UniformDataType.PCM).assertEqual('general.pcm');
    console.info(TAG, 'end');
  });

  /*
   * @tc.name UdmfTestTypeDescriptor011
   * @tc.desc Test Js Api enum value judge part3
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it ('UdmfTestTypeDescriptor011', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor011:';
    console.info(TAG, 'start');
    expect(UTD.UniformDataType.WINDOWS_MEDIA_WMA).assertEqual('com.microsoft.windows-media-wma');
    expect(UTD.UniformDataType.WAVEFORM_AUDIO).assertEqual('com.microsoft.waveform-audio');
    expect(UTD.UniformDataType.WINDOWS_MEDIA_WMX).assertEqual('com.microsoft.windows-media-wmx');
    expect(UTD.UniformDataType.WINDOWS_MEDIA_WVX).assertEqual('com.microsoft.windows-media-wvx');
    expect(UTD.UniformDataType.WINDOWS_MEDIA_WAX).assertEqual('com.microsoft.windows-media-wax');
    expect(UTD.UniformDataType.FILE).assertEqual('general.file');
    expect(UTD.UniformDataType.DIRECTORY).assertEqual('general.directory');
    expect(UTD.UniformDataType.FOLDER).assertEqual('general.folder');
    expect(UTD.UniformDataType.SYMLINK).assertEqual('general.symlink');
    expect(UTD.UniformDataType.ARCHIVE).assertEqual('general.archive');
    expect(UTD.UniformDataType.BZ2_ARCHIVE).assertEqual('general.bz2-archive');
    expect(UTD.UniformDataType.DISK_IMAGE).assertEqual('general.disk-image');
    expect(UTD.UniformDataType.TAR_ARCHIVE).assertEqual('general.tar-archive');
    expect(UTD.UniformDataType.ZIP_ARCHIVE).assertEqual('general.zip-archive');
    expect(UTD.UniformDataType.JAVA_ARCHIVE).assertEqual('com.sun.java-archive');
    expect(UTD.UniformDataType.GNU_TAR_ARCHIVE).assertEqual('org.gnu.gnu-tar-archive');
    expect(UTD.UniformDataType.GNU_ZIP_ARCHIVE).assertEqual('org.gnu.gnu-zip-archive');
    expect(UTD.UniformDataType.GNU_ZIP_TAR_ARCHIVE).assertEqual('org.gnu.gnu-zip-tar-archive');
    expect(UTD.UniformDataType.CALENDAR).assertEqual('general.calendar');
    expect(UTD.UniformDataType.CONTACT).assertEqual('general.contact');
    expect(UTD.UniformDataType.DATABASE).assertEqual('general.database');
    expect(UTD.UniformDataType.MESSAGE).assertEqual('general.message');
    expect(UTD.UniformDataType.VCARD).assertEqual('general.vcard');
    expect(UTD.UniformDataType.NAVIGATION).assertEqual('general.navigation');
    expect(UTD.UniformDataType.LOCATION).assertEqual('general.location');
    expect(UTD.UniformDataType.OPENHARMONY_FORM).assertEqual('openharmony.form');
    expect(UTD.UniformDataType.OPENHARMONY_APP_ITEM).assertEqual('openharmony.app-item');
    expect(UTD.UniformDataType.OPENHARMONY_PIXEL_MAP).assertEqual('openharmony.pixel-map');
    expect(UTD.UniformDataType.OPENHARMONY_ATOMIC_SERVICE).assertEqual('openharmony.atomic-service');
    console.info(TAG, 'end');
  });

  /*
  * @tc.name UdmfTestTypeDescriptor012
  * @tc.desc Test Js Api belongsTo
  * @tc.type: FUNC
  * @tc.require: issueNumber
  */
  it ('UdmfTestTypeDescriptor012', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor012:';
    console.info(TAG, 'start');
    let typeObj = UTD.getTypeDescriptor('general.type-script');
    let ret = typeObj.belongsTo('general.plain-text');
    expect(ret === true).assertTrue();
    console.info(TAG, 'typeDescriptor, ret ' + typeObj);
    console.info(TAG, 'end');
  });

  /*
  * @tc.name UdmfTestTypeDescriptor013
  * @tc.desc Test Js Api isLowerLevelType
  * @tc.type: FUNC
  * @tc.require: issueNumber
  */
  it ('UdmfTestTypeDescriptor013', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor013:';
    console.info(TAG, 'start');
    let typeObj = UTD.getTypeDescriptor('general.type-script');
    let ret = typeObj.isLowerLevelType('general.plain-text');
    expect(ret === true).assertTrue();
    console.info(TAG, 'typeDescriptor, ret ' + ret);
    console.info(TAG, 'end');
  });

  /*
  * @tc.name UdmfTestTypeDescriptor014
  * @tc.desc Test Js Api isLowerLevelType
  * @tc.type: FUNC
  * @tc.require: issueNumber
  */
  it ('UdmfTestTypeDescriptor014', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor014:';
    console.info(TAG, 'start');
    let typeObj = UTD.getTypeDescriptor('general.plain-text');
    let ret = typeObj.isHigherLevelType('general.type-script');
    expect(ret === true).assertTrue();
    console.info(TAG, 'typeDescriptor, ret ' + typeObj);
    console.info(TAG, 'end');
  });

  /*
  * @tc.name UdmfTestTypeDescriptor015
  * @tc.desc Test Js Api getUniformDataTypeByFilenameExtension
  * @tc.type: FUNC
  * @tc.require: issueNumber
  */
  it ('UdmfTestTypeDescriptor015', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor015:';
    console.info(TAG, 'start');
    let typeId = UTD.getUniformDataTypeByFilenameExtension('.ts', 'general.plain-text');
    expect(typeId === 'general.type-script').assertTrue();
    console.info(TAG, 'typeDescriptor, ret ' + typeId);
    console.info(TAG, 'end');
  });

  /*
  * @tc.name UdmfTestTypeDescriptor016
  * @tc.desc Test Js Api getUniformDataTypeByMIMEType
  * @tc.type: FUNC
  * @tc.require: issueNumber
  */
  it ('UdmfTestTypeDescriptor016', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor016:';
    console.info(TAG, 'start');
    let typeId = UTD.getUniformDataTypeByMIMEType('application/vnd.ms-excel', 'general.object');
    expect(typeId === 'com.microsoft.excel.xls').assertTrue();
    console.info(TAG, 'typeDescriptor, ret ' + typeId);
    console.info(TAG, 'end');
  });

  /*
  * @tc.name UdmfTestTypeDescriptor017
  * @tc.desc Test Js Api getUniformDataTypeByMIMEType invalid para
  * @tc.type: FUNC
  * @tc.require: issueNumber
  */
  it('UdmfTestTypeDescriptor017', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor017:';
    console.info(TAG, 'start');
    try {
      let typeId = UTD.getUniformDataTypeByMIMEType('');
      console.error(TAG, 'getUniformDataTypeByMIMEType, ret ' + typeId);
      expect().assertFail();
    } catch (e) {
      console.info(TAG, `get e. code is ${e.code},message is ${e.message} `);
      expect(e.code === ERROR_PARAMETER).assertEqual(true);
      
    }
    console.info(TAG, 'end');
  });

  /*
  * @tc.name UdmfTestTypeDescriptor018
  * @tc.desc Test Js Api getUniformDataTypeByFilenameExtension invalid para
  * @tc.type: FUNC
  * @tc.require: issueNumber
  */
  it('UdmfTestTypeDescriptor018', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor018:';
    console.info(TAG, 'start');
    try {
      let typeId = UTD.getUniformDataTypeByFilenameExtension('');
      console.error(TAG, 'getUniformDataTypeByFilenameExtension, ret ' + typeId);
      expect().assertFail();
    } catch (e) {
      console.info(TAG, `get e. code is ${e.code},message is ${e.message} `);
      expect(e.code === ERROR_PARAMETER).assertEqual(true);
    }
    console.info(TAG, 'end');
  });

  /*
  * @tc.name UdmfTestTypeDescriptor019
  * @tc.desc Test Js Api belongsTo invalid para
  * @tc.type: FUNC
  * @tc.require: issueNumber
  */
  it('UdmfTestTypeDescriptor019', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor019:';
    console.info(TAG, 'start');
    let typeObj = UTD.getTypeDescriptor('general.type-script');
    console.info(TAG, 'typeDescriptor, ret ' + typeObj);
    try {
      typeObj.belongsTo('1111');
      expect().assertFail();
    } catch (e) {
      console.error(TAG, `get e. code is ${e.code},message is ${e.message} `);
      expect(e.code === ERROR_PARAMETER).assertTrue();
    }
    console.info(TAG, 'end');
  });

  /*
   * @tc.name UdmfTestTypeDescriptor020
   * @tc.desc Test Js Api equals invalid para type
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfTestTypeDescriptor020', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor020:';
    console.info(TAG, 'start');
    let typeObj = UTD.getTypeDescriptor('general.type-script');
    console.info(TAG, 'typeDescriptor, ret ' + typeObj);
    try {
      typeObj.isLowerLevelType('1111');
      expect().assertFail();
    } catch (e) {
      console.error(TAG, `get e. code is ${e.code},message is ${e.message} `);
      expect(e.code === ERROR_PARAMETER).assertTrue();
    }
    console.info(TAG, 'end');
  });

  /*
   * @tc.name UdmfTestTypeDescriptor021
   * @tc.desc Test Js Api isHigherLevelType invalid para type
   * @tc.type: FUNC
   * @tc.require: issueNumber
   */
  it('UdmfTestTypeDescriptor021', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor021:';
    console.info(TAG, 'start');
    let typeObj = UTD.getTypeDescriptor('general.type-script');
    console.info(TAG, 'typeDescriptor, ret ' + typeObj);
    try {
      typeObj.isHigherLevelType('1111');
      expect().assertFail();
    } catch (e) {
      console.error(TAG, `get e. code is ${e.code},message is ${e.message} `);
      expect(e.code === ERROR_PARAMETER).assertTrue();
    }
    console.info(TAG, 'end');
  });

  /*
  * @tc.name UdmfTestTypeDescriptor022
  * @tc.desc Test Js Api belongsTo invalid para
  * @tc.type: FUNC
  * @tc.require: issueNumber
  */
  it('UdmfTestTypeDescriptor022', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor022:';
    console.info(TAG, 'start');
    try {
      let typeId = UTD.getTypeDescriptor('general.type-script');
      console.info(TAG, 'typeDescriptor, ret ' + typeId);
      typeId.belongsTo();
      expect().assertFail();
    } catch (e) {
      console.error(TAG, `get e. code is ${e.code},message is ${e.message} `);
      expect(e.code === ERROR_PARAMETER).assertTrue();
    }
    console.info(TAG, 'end');
  });

  /*
  * @tc.name UdmfTestTypeDescriptor023
  * @tc.desc Test Js Api isLowerLevelType invalid para
  * @tc.type: FUNC
  * @tc.require: issueNumber
  */
  it('UdmfTestTypeDescriptor023', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor023:';
    console.info(TAG, 'start');
    try {
      let typeId = UTD.getTypeDescriptor('general.type-script');
      console.info(TAG, 'typeDescriptor, ret ' + typeId);
      typeId.isLowerLevelType();
      expect().assertFail();
    } catch (e) {
      console.error(TAG, `get e. code is ${e.code},message is ${e.message} `);
      expect(e.code === ERROR_PARAMETER).assertTrue();
    }
    console.info(TAG, 'end');
  });

  /*
  * @tc.name UdmfTestTypeDescriptor024
  * @tc.desc Test Js Api getUniformDataTypeByFilenameExtension invalid para
  * @tc.type: FUNC
  * @tc.require: issueNumber
  */
  it('UdmfTestTypeDescriptor024', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor024:';
    console.info(TAG, 'start');
    try {
      let typeId = UTD.getTypeDescriptor('general.type-script');
      console.info(TAG, 'typeDescriptor, ret ' + typeId);
      typeId.isHigherLevelType();
      expect().assertFail();
    } catch (e) {
      console.error(TAG, `get e. code is ${e.code},message is ${e.message} `);
      expect(e.code === ERROR_PARAMETER).assertTrue();
    }
    console.info(TAG, 'end');
  });

  /*
  * @tc.name UdmfTestTypeDescriptor025
  * @tc.desc Test Js Api getUniformDataTypeByMIMEType invalid para
  * @tc.type: FUNC
  * @tc.require: issueNumber
  */
  it('UdmfTestTypeDescriptor025', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor025:';
    console.info(TAG, 'start');
    try {
      let typeId = UTD.getUniformDataTypeByMIMEType();
      console.info(TAG, 'getUniformDataTypeByMIMEType, ret ' + typeId);
      expect().assertFail();
    } catch (e) {
      console.error(TAG, `get e. code is ${e.code},message is ${e.message} `);
      expect(e.code === ERROR_PARAMETER).assertTrue();
    }
    console.info(TAG, 'end');
  });

  /*
  * @tc.name UdmfTestTypeDescriptor026
  * @tc.desc Test Js Api getUniformDataTypeByFilenameExtension invalid para
  * @tc.type: FUNC
  * @tc.require: issueNumber
  */
  it('UdmfTestTypeDescriptor026', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor026:';
    console.info(TAG, 'start');
    try {
      let typeId = UTD.getUniformDataTypeByFilenameExtension();
      console.info(TAG, 'getUniformDataTypeByFilenameExtension, ret ' + typeId);
      expect().assertFail();
    } catch (e) {
      console.error(TAG, `get e. code is ${e.code},message is ${e.message} `);
      expect(e.code === ERROR_PARAMETER).assertTrue();
    }
    console.info(TAG, 'end');
  });

  /*
  * @tc.name UdmfTestTypeDescriptor027
  * @tc.desc Test Js Api getUniformDataTypeByFilenameExtension
  * @tc.type: FUNC
  * @tc.require: issueNumber
  */
  it('UdmfTestTypeDescriptor027', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor027:';
    console.info(TAG, 'start');
    let typeId = UTD.getUniformDataTypeByFilenameExtension('.ts');
    expect(typeId === 'general.type-script').assertTrue();
    console.info(TAG, 'getUniformDataTypeByFilenameExtension, ret ' + typeId);
    console.info(TAG, 'end');
  });

  /*
  * @tc.name UdmfTestTypeDescriptor028
  * @tc.desc Test Js Api getUniformDataTypeByMIMEType
  * @tc.type: FUNC
  * @tc.require: issueNumber
  */
  it('UdmfTestTypeDescriptor028', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor028:';
    console.info(TAG, 'start');
    let typeId = UTD.getUniformDataTypeByMIMEType('application/vnd.ms-excel');
    expect(typeId === 'com.microsoft.excel.xls').assertTrue();
    console.info(TAG, 'getUniformDataTypeByMIMEType, ret ' + typeId);
    console.info(TAG, 'end');
  });

  /*
  * @tc.name UdmfTestTypeDescriptor029
  * @tc.desc Test Js Api getUniformDataTypeByFilenameExtension
  * @tc.type: FUNC
  * @tc.require: issueNumber
  */
  it('UdmfTestTypeDescriptor029', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor029:';
    console.info(TAG, 'start');
    try {
      let flexibleType = UTD.getUniformDataTypeByFilenameExtension('.invalidFilenameExtension');
      console.info(TAG, 'getUniformDataTypeByFilenameExtension, ret ' + flexibleType);
      let flexibleTypeObj = UTD.getTypeDescriptor(flexibleType);
      console.info(TAG, 'UDMF,typeId:' + flexibleTypeObj.typeId);
      console.info(TAG, 'belongingToTypes:' + flexibleTypeObj.belongingToTypes);
      console.info(TAG, 'filenameExtension:' + flexibleTypeObj.filenameExtensions);
      console.info(TAG, 'mimeTypes:' + flexibleTypeObj.mimeTypes);
      expect(flexibleTypeObj.typeId).assertEqual(flexibleType);
      expect(flexibleTypeObj.belongingToTypes.length).assertEqual(0);
      expect(flexibleTypeObj.filenameExtensions[0]).assertEqual('.invalidfilenameextension');
      expect(flexibleTypeObj.mimeTypes.length).assertEqual(0);
    } catch (e) {
      console.error(TAG, `get e. code is ${e.code}, message is ${e.message} `);
      expect().assertFail();
    }
    console.info(TAG, 'end');
  });

  /*
  * @tc.name UdmfTestTypeDescriptor030
  * @tc.desc Test Js Api getUniformDataTypeByMIMEType
  * @tc.type: FUNC
  * @tc.require: issueNumber
  */
  it('UdmfTestTypeDescriptor030', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor030:';
    console.info(TAG, 'start');
    try {
      let flexibleType = UTD.getUniformDataTypeByMIMEType('invalidMIMEType');
      console.info(TAG, 'flexibleType=====>' + flexibleType);
      let flexibleTypeObj = UTD.getTypeDescriptor(flexibleType);
      console.info(TAG, 'typeId:' + flexibleTypeObj.typeId);
      console.info(TAG, 'belongingToTypes:' + flexibleTypeObj.belongingToTypes);
      console.info(TAG, 'filenameExtension:' + flexibleTypeObj.filenameExtensions);
      console.info(TAG, 'mimeTypes:' + flexibleTypeObj.mimeTypes);
      expect(flexibleTypeObj.typeId).assertEqual(flexibleType);
      expect(flexibleTypeObj.belongingToTypes.length).assertEqual(0);
      expect(flexibleTypeObj.mimeTypes[0]).assertEqual('invalidmimetype');
      expect(flexibleTypeObj.filenameExtensions.length).assertEqual(0);
    } catch (e) {
      console.error(TAG, `get e. code is ${e.code},message is ${e.message} `);
      expect().assertFail();
    }
    console.info(TAG, 'end');
  });

  /*
  * @tc.name UdmfTestTypeDescriptor031
  * @tc.desc Test Js Api belongsTo invalid para
  * @tc.type: FUNC
  * @tc.require: issueNumber
  */
  it('UdmfTestTypeDescriptor031', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor031:';
    console.info(TAG, 'start');
    let typeId = UTD.getTypeDescriptor('general.type-script');
    console.info(TAG, 'typeDescriptor, ret ' + typeId);
    let ret = typeId.belongsTo('general.type-script');
    expect(ret === true).assertTrue();
    console.info(TAG, 'end');
  });

  /*
  * @tc.name UdmfTestTypeDescriptor032
  * @tc.desc Test Js Api isLowerLevelType invalid para
  * @tc.type: FUNC
  * @tc.require: issueNumber
  */
  it('UdmfTestTypeDescriptor032', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor032:';
    console.info(TAG, 'start');
    let typeId = UTD.getTypeDescriptor('general.type-script');
    console.info(TAG, 'typeDescriptor, ret ' + typeId);
    let ret = typeId.isLowerLevelType('general.type-script');
    expect(ret === false).assertTrue();
    console.info(TAG, 'end');
  });

  /*
  * @tc.name UdmfTestTypeDescriptor033
  * @tc.desc Test Js Api getUniformDataTypeByFilenameExtension invalid para
  * @tc.type: FUNC
  * @tc.require: issueNumber
  */
  it('UdmfTestTypeDescriptor033', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor033:';
    console.info(TAG, 'start');
    let typeId = UTD.getTypeDescriptor('general.type-script');
    console.info(TAG, 'typeDescriptor, ret ' + typeId);
    let ret = typeId.isHigherLevelType('general.type-script');
    expect(ret === false).assertTrue();
    console.info(TAG, 'end');
  });

  /*
  * @tc.name UdmfTestTypeDescriptor032
  * @tc.desc Test Js Api getUniformDataTypeByFilenameExtension
  * @tc.type: FUNC
  * @tc.require: issueNumber
  */
  it('UdmfTestTypeDescriptor034', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor034:';
    console.info(TAG, 'start');
    try {
      let typeId = UTD.getUniformDataTypeByFilenameExtension('.ts', '');
      console.info(TAG, 'getUniformDataTypeByFilenameExtension, ret ' + typeId);
      expect().assertFail();
    } catch (e) {
      console.error(TAG, `get e. code is ${e.code},message is ${e.message} `);
      expect(e.code === ERROR_PARAMETER).assertTrue();
    }
    console.info(TAG, 'end');
  });

  /*
  * @tc.name UdmfTestTypeDescriptor035
  * @tc.desc Test Js Api getUniformDataTypeByMIMEType
  * @tc.type: FUNC
  * @tc.require: issueNumber
  */
  it('UdmfTestTypeDescriptor035', 0, function () {
    const TAG = 'UdmfTestTypeDescriptor035:';
    console.info(TAG, 'start');
    try {
      let typeId = UTD.getUniformDataTypeByMIMEType('video/3gpp2', '');
      console.info(TAG, 'getUniformDataTypeByMIMEType, ret ' + typeId);
      expect().assertFail();
    } catch (e) {
      console.error(TAG, `get e. code is ${e.code},message is ${e.message} `);
      expect(e.code === ERROR_PARAMETER).assertTrue();
    }
    console.info(TAG, 'end');
  });
});