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
const FONT_SYMBOL_COLOR: string = '#1A000000';
const FONT_SYMBOL_BACKGROUND: string = '#F0F0F0';

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

  async createPixelMap() {
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

  @Builder
  ThumbImageNull() {
    Text() {
      SymbolSpan($r('sys.symbol.ohos_photo'))
        .fontSize(this.formStyle.symbolSize * this.cardScale)
        .fontColor([FONT_SYMBOL_COLOR])
    }
    .textAlign(TextAlign.Center)
    .backgroundColor(FONT_SYMBOL_BACKGROUND)
    .thumbStyle()
  }

  @Builder
  Card2x1() {
    Column() {
      if (this.thumbImage) {
        Image(this.thumbImage)
          .objectFit(ImageFit.Fill)
          .thumbStyle()
      } else {
        this.ThumbImageNull()
      }
      this.CardDivider()
      this.AppView()
    }
    .size({ width: '100%', height: '100%' })
  }

  @Builder
  Card4x2() {
    Column() {
      if (this.contentFormData?.thumbData) {
        Image(this.thumbImage)
          .objectFit(ImageFit.Fill)
          .thumbStyle()
      } else {
        this.ThumbImageNull()
      }
      this.CardDivider()
      this.AppView()
    }
    .size({ width: '100%', height: '100%' })
  }

  @Builder
  Card4x4() {
    Column() {
      if (this.contentFormData?.thumbData) {
        Image(this.thumbImage)
          .objectFit(ImageFit.Fill)
          .thumbStyle()
      } else {
        this.ThumbImageNull()
      }
      this.CardDivider()
      this.AppView()
    }
    .size({ width: '100%', height: '100%' })
  }

  build() {
    Column() {
      if (this.formType === FormType.TYPE_BIG) {
        this.Card4x4();
      }

      if (this.formType === FormType.TYPE_MID) {
        this.Card4x2();
      }

      if (this.formType === FormType.TYPE_SMALL) {
        this.Card2x1();
      }
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