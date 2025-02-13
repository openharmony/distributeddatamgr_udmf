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
import common from '@ohos.app.ability.common';
import image from '@ohos.multimedia.image';
import uniformDataStruct from '@ohos.data.uniformDataStruct';
import { BusinessError } from '@kit.BasicServicesKit';

export enum FormType {
  TYPE_BIG = 0,
  TYPE_MID = 1,
  TYPE_SMALL = 2
}

const TAG: string = 'udmf.ContentFormCard';
const defaultIcon: string =
  '82,73,70,70,60,3,0,0,87,69,66,80,86,80,56,32,48,3,0,0,144,67,0,157,1,42,36,2,76,1,62,145,72,161,76,37,164,163,34,3' +
  '4,151,40,24,176,18,9,105,110,225,117,81,27,243,141,167,87,231,251,1,151,228,76,129,74,56,124,143,240,134,221,17,24' +
  '5,145,49,195,251,155,103,15,145,254,16,219,162,62,178,38,56,127,115,108,225,242,63,194,27,116,71,214,68,199,15,238' +
  ',109,156,62,71,248,67,110,136,250,200,152,225,253,205,179,135,200,255,8,109,209,31,89,19,28,63,185,182,112,249,31,' +
  '225,13,186,35,235,34,99,135,247,54,206,31,35,252,33,183,68,125,100,76,112,254,230,217,195,228,75,0,41,63,219,242,2' +
  '38,77,44,240,251,18,157,13,186,35,235,34,99,135,247,54,206,31,35,249,8,172,169,162,121,152,235,226,174,0,65,245,14' +
  '5,49,195,251,155,103,15,145,254,16,219,50,4,52,148,102,170,225,73,64,87,161,183,68,125,100,76,112,254,230,217,195,' +
  '228,71,209,214,155,210,69,175,155,95,117,236,130,111,176,161,115,26,13,253,205,179,135,200,255,8,109,209,31,89,19,' +
  '28,63,185,182,112,248,134,3,147,196,80,183,60,143,240,134,221,17,245,145,49,195,251,155,103,9,153,121,194,183,243,' +
  '118,43,147,107,248,164,83,185,180,54,232,143,172,137,142,31,220,219,56,124,136,157,203,110,159,181,177,87,164,132,' +
  '51,246,217,120,189,13,186,35,235,34,99,134,241,245,180,72,132,116,112,254,7,167,195,150,227,244,98,234,67,237,155,' +
  '35,135,102,236,204,223,23,161,183,68,125,100,75,176,70,248,207,116,46,59,232,218,137,15,41,225,38,20,162,105,88,3,' +
  '59,221,52,249,17,46,76,68,130,195,148,187,103,15,145,253,241,76,10,132,82,146,126,208,179,241,65,64,84,151,15,193,' +
  '27,58,174,246,254,217,195,225,201,8,103,237,178,241,122,27,116,71,210,161,106,19,234,133,230,77,60,101,201,227,55,' +
  '59,2,148,71,237,122,200,152,222,202,193,86,94,164,111,28,63,185,180,88,205,133,69,41,39,237,156,62,237,252,33,183,' +
  '68,126,68,34,111,88,1,159,60,108,76,112,252,104,245,218,227,1,255,172,137,142,31,220,219,56,124,143,239,99,182,153' +
  ',157,89,206,237,156,41,135,174,215,24,15,76,90,90,193,245,145,49,195,251,155,103,15,145,18,140,226,36,22,28,165,21' +
  '8,7,174,215,23,217,167,25,36,48,125,100,76,112,254,230,217,195,196,106,61,255,30,253,149,0,0,254,254,226,128,0,0,0' +
  ',0,0,8,43,156,5,139,91,64,214,164,5,157,168,214,71,99,143,63,110,129,210,71,53,1,30,120,20,41,161,99,5,167,202,76,' +
  '251,103,189,240,128,146,208,198,255,248,206,215,46,193,53,91,227,66,219,241,255,4,235,164,113,76,186,21,195,174,10' +
  ',72,252,102,101,0,19,200,26,224,13,190,145,249,137,208,169,128,196,203,52,114,184,23,26,103,126,29,119,157,143,214' +
  ',115,91,208,138,148,47,18,132,3,189,65,160,138,162,129,225,223,121,199,68,111,66,131,240,170,9,87,178,109,244,143,' +
  '204,78,245,205,43,87,181,148,112,162,163,53,27,128,197,247,165,165,55,37,6,212,240,48,76,139,191,173,182,51,61,7,1' +
  '38,70,81,93,158,178,96,58,63,135,99,61,33,123,114,106,17,205,205,245,73,209,248,208,230,67,84,83,67,62,174,199,125' +
  ',7,42,68,205,119,254,54,95,35,146,246,87,229,105,194,49,134,23,113,205,13,105,146,10,231,32,0,26,210,69,47,127,104' +
  ',73,141,205,245,214,23,231,110,132,188,27,13,88,8,43,145,225,60,68,0,42,15,95,85,238,25,204,75,166,163,127,0,0';
const MAX_CARD_SCALE: number = 1.2;
const MIN_CARD_SCALE: number = 0.8;
const DEFAULT_BIG_CARD_SIZE: number = 200;
const DEFAULT_MID_CARD_WIDTH: number = 200;
const DEFAULT_MID_CARD_HEIGHT: number = 100;
const DEFAULT_SMALL_CARD_WIDTH: number = 100;
const DEFAULT_SMALL_CARD_HEIGHT: number = 60;
const CARD_BACKGROUND: string = '#E6FFFFFF';
const CARD_DIVIDER_COLOR: string = '#1A999999';
const APP_NAME_COLOR: string = '#66000000';
const DEFAULT_THUMB_BACKGROUND: string = '#CCCCCC';

interface CardStyle {
  symbolSize: number,
  appNameFontSize: number,
  appIconSize: number,
  cardRadius: number,
  textLeft: number,
  bottomPadding: number,
  bottomPaddingBottom: number,
  bottomPaddingTop: number
}

const BIG_CARD_STYLE: CardStyle = {
  symbolSize: 100,
  appNameFontSize: 10,
  appIconSize: 12,
  cardRadius: 16,
  textLeft: 6.5,
  bottomPadding: 12,
  bottomPaddingBottom: 10,
  bottomPaddingTop: 6
}

const MID_CARD_STYLE: CardStyle = {
  symbolSize: 50,
  appNameFontSize: 10,
  appIconSize: 12,
  cardRadius: 16,
  textLeft: 6.5,
  bottomPadding: 12,
  bottomPaddingBottom: 10,
  bottomPaddingTop: 6
}

const SMALL_CARD_STYLE: CardStyle = {
  symbolSize: 30,
  appNameFontSize: 8,
  appIconSize: 8,
  cardRadius: 8,
  textLeft: 4,
  bottomPadding: 10,
  bottomPaddingBottom: 5,
  bottomPaddingTop: 4
}

@Preview
@Component
export struct ContentFormCard {
  private formType: FormType = FormType.TYPE_MID;
  private contentFormData: uniformDataStruct.ContentForm | undefined = undefined;
  private formWidth: number = 0;
  private formHeight: number = 0;
  private formStyle: CardStyle = MID_CARD_STYLE;
  @State defaultThumbImage: image.PixelMap | undefined = undefined;
  @State thumbImage: image.PixelMap | undefined = undefined;
  @State appImage: image.PixelMap | undefined = undefined;
  @State cardScale: number = 1;

  aboutToAppear(): void {
    this.initCardStyle();
    this.createPixelMap();
  }

  initCardScale(widthScale: number) {
    this.cardScale = widthScale;
    if (widthScale > MAX_CARD_SCALE) {
      this.cardScale = MAX_CARD_SCALE;
    }
    if (widthScale < MIN_CARD_SCALE) {
      this.cardScale = MIN_CARD_SCALE;
    }
  }

  initCardStyle(): void {
    if (this.formWidth === 0 && this.formHeight === 0) {
      if (this.formType === FormType.TYPE_BIG) {
        this.formWidth = DEFAULT_BIG_CARD_SIZE;
        this.formHeight = DEFAULT_BIG_CARD_SIZE;
      }
      if (this.formType === FormType.TYPE_MID) {
        this.formWidth = DEFAULT_MID_CARD_WIDTH;
        this.formHeight = DEFAULT_MID_CARD_HEIGHT;
      }
      if (this.formType === FormType.TYPE_SMALL) {
        this.formWidth = DEFAULT_SMALL_CARD_WIDTH;
        this.formHeight = DEFAULT_SMALL_CARD_HEIGHT;
      }
    }
    let widthScale = 1;
    switch (this.formType) {
      case FormType.TYPE_BIG:
        this.formStyle = BIG_CARD_STYLE;
        widthScale = this.formWidth / DEFAULT_BIG_CARD_SIZE;
        this.initCardScale(widthScale);
        this.formWidth = DEFAULT_BIG_CARD_SIZE * this.cardScale;
        this.formHeight = DEFAULT_BIG_CARD_SIZE * this.cardScale;
        break;
      case FormType.TYPE_MID:
        this.formStyle = MID_CARD_STYLE;
        widthScale = this.formWidth / DEFAULT_MID_CARD_WIDTH;
        this.initCardScale(widthScale);
        this.formWidth = DEFAULT_MID_CARD_WIDTH * this.cardScale;
        this.formHeight = DEFAULT_MID_CARD_HEIGHT * this.cardScale;
        break;
      case FormType.TYPE_SMALL:
        this.formStyle = SMALL_CARD_STYLE;
        widthScale = this.formWidth / DEFAULT_SMALL_CARD_WIDTH;
        this.initCardScale(widthScale);
        this.formWidth = DEFAULT_SMALL_CARD_WIDTH * this.cardScale;
        this.formHeight = DEFAULT_SMALL_CARD_HEIGHT * this.cardScale;
        break;
      default:
        break;
    }
    console.info(`${TAG}, cardScale: ${this.cardScale}`);
  }

  async getPixelMap(uint: Uint8Array, callback: Function): Promise<void> {
    let imageResource: image.ImageSource | undefined = undefined;
    try {
      imageResource = image.createImageSource(uint.buffer);
      let pixelMapData = await imageResource?.createPixelMap();
      callback(pixelMapData);
    } catch (err) {
      let error = err as BusinessError;
      console.info(`${TAG}, Failed to create pixelMap, code is ${error.code}, message is ${error.message}`);
    }
  }

  transStringToUint8Array(srcData: string): Uint8Array {
    const arr: string[] = srcData.split(',');
    const uint8Array = new Uint8Array(arr.length);
    arr.forEach((value, index) => {
      uint8Array[index] = parseInt(value);
    })
    return uint8Array;
  }

  async createPixelMap() {
    let defaultThumbData = this.transStringToUint8Array(defaultIcon);
    this.getPixelMap(defaultThumbData, (pixelMap: image.PixelMap) => {
      this.defaultThumbImage = pixelMap;
    })

    if (this.contentFormData && this.contentFormData?.thumbData) {
      if (!(this.contentFormData?.thumbData instanceof Uint8Array)) {
        console.error(`${TAG}, thumbData is not Uint8Array`);
        return;
      }
      this.getPixelMap(this.contentFormData?.thumbData, (pixelMap: image.PixelMap) => {
        this.thumbImage = pixelMap;
      })
    }
    if (this.contentFormData && this.contentFormData?.appIcon) {
      if (!(this.contentFormData?.appIcon instanceof Uint8Array)) {
        console.error(`${TAG}, appIcon is not Uint8Array`);
        return;
      }
      this.getPixelMap(this.contentFormData?.appIcon, (pixelMap: image.PixelMap) => {
        this.appImage = pixelMap;
      })
    }
  }

  @Styles
  thumbStyle() {
    .width('100%')
    .borderRadius({ topLeft: this.formStyle.cardRadius, topRight: this.formStyle.cardRadius })
    .layoutWeight(1)
    .clip(true)
  }

  @Builder
  ThumbImage() {
    Stack({ alignContent: Alignment.Bottom }) {
      if (this.thumbImage) {
        Image(this.thumbImage)
          .objectFit(ImageFit.Contain)
          .width('100%')
          .height('100%')
      } else {
        Image(this.defaultThumbImage)
          .objectFit(ImageFit.Contain)
          .width('100%')
      }
    }
    .thumbStyle()
    .backgroundColor(this.thumbImage ? CARD_BACKGROUND: DEFAULT_THUMB_BACKGROUND)
  }

  @Builder
  CardDivider() {
    Divider()
      .height(1)
      .color(CARD_DIVIDER_COLOR)
      .padding({
        left: this.formStyle.bottomPadding * this.cardScale,
        right: this.formStyle.bottomPadding * this.cardScale
      })
  }

  @Builder
  AppView() {
    Row() {
      Image(this.appImage)
        .width(this.formStyle.appIconSize * this.cardScale)
        .height(this.formStyle.appIconSize * this.cardScale)
        .objectFit(ImageFit.Fill)
        .alt($r('sys.media.ohos_app_icon'))
      Text(this.contentFormData?.appName)
        .fontSize(this.formStyle.appNameFontSize * this.cardScale)
        .fontColor(APP_NAME_COLOR)
        .maxLines(1)
        .margin({ left: this.formStyle.textLeft * this.cardScale })
        .textOverflow({ overflow: TextOverflow.Ellipsis })
    }
    .width('100%')
    .padding({
      left: this.formStyle.bottomPadding * this.cardScale,
      right: this.formStyle.bottomPadding * this.cardScale,
      bottom: this.formStyle.bottomPaddingBottom * this.cardScale,
      top: this.formStyle.bottomPaddingTop * this.cardScale
    })
  }

  build() {
    Column() {
      this.ThumbImage()
      this.CardDivider()
      this.AppView()
    }
    .borderRadius(this.formStyle.cardRadius)
    .backgroundColor(CARD_BACKGROUND)
    .backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK,
      { colorMode: ThemeColorMode.LIGHT, adaptiveColor: AdaptiveColor.DEFAULT, scale: 1.0 })
    .shadow(ShadowStyle.OUTER_DEFAULT_SM)
    .size({ width: this.formWidth, height: this.formHeight })
    .onClick(() => {
      if (!this.contentFormData?.linkUri) {
        console.warn(`${TAG}, linkUri is null`);
        return;
      }
      try {
        let context = getContext(this) as common.UIAbilityContext;
        context.openLink(this.contentFormData?.linkUri, { appLinkingOnly: false, parameters: {} });
      } catch (err) {
        let error = err as BusinessError;
        console.error(`${TAG}, Failed to openLink, code is ${error.code}, message is ${error.message}`);
      }
    })
  }
}