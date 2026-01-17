/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { AnimatorResult } from '@ohos.animator'
import { State, Watch, PropRef } from '@ohos.arkui.stateManagement'
import common from '@ohos.app.ability.common';
import I18n from '@ohos.i18n';
import { BusinessError } from '@ohos.base';
import image from '@ohos.multimedia.image';
import uniformDataStruct from '@ohos.data.uniformDataStruct';
import {
  Entry,
  Component,
  State,
  Column,
  Row,
  Text,
  Button,
  Margin,
  ImageFit,
  TextController,
  Image,
  Divider,
  RowOptions,
  $r,
  TextOverflow,
  FontWeight,
  HorizontalAlign,
  Direction,
  FlexAlign,
  LayoutManager,
  Area,
  ColumnOptions,
  Padding,
  VerticalAlign,
  BlurStyle,
  BackgroundBlurStyleOptions,
  ThemeColorMode,
  AdaptiveColor,
  ShadowStyle,
  ConstraintSizeOptions
} from '@kit.ArkUI';

export enum FormType {
  TYPE_BIG = 0,
  TYPE_MID = 1,
  TYPE_SMALL = 2
}

enum TextType {
  TITLE = 0,
  DESCRIPTION = 1,
  APP_NAME = 2
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
const MAX_CARD_SCALE: double = 1.2;
const MIN_CARD_SCALE: double = 0.8;
const SMALL_MIN_CARD_SCALE: double = 0.4;
const DEFAULT_BIG_CARD_SIZE: double = 200;
const DEFAULT_MID_CARD_WIDTH: double = 200;
const DEFAULT_MID_CARD_HEIGHT: double = 100;
const DEFAULT_SMALL_CARD_WIDTH: double = 137;
const DEFAULT_SMALL_CARD_HEIGHT: double = 83;
const DEFAULT_EMPTY_TITLE_WIDTH: double = 70;
const DEFAULT_EMPTY_APPNAME_WIDTH: double = 40;
const SMALL_EMPTY_TITLE_WIDTH: double = 50;
const SMALL_EMPTY_APPNAME_WIDTH: double = 30;
const DEFAULT_EMPTY_TEXT_RADIUS: double = 2;
const DEFAULT_EMPTY_DESCRIPTION_WIDTH: string = '100%';
const CARD_BACKGROUND: string = '#E6FFFFFF';
const TRANSLATE_BACKGROUND: string = '#00000000';
const APP_NAME_COLOR: string = '#99182431';
const DEFAULT_THUMB_BACKGROUND: string = '#CCCCCC';
const DEFAULT_FONT_BACKGROUND: string = '#55CCCCCC';
const TITLE_FONT_COLOR: string = '#ff182431';
const DESCRIPTION_FONT_COLOR: string = '#99182431';
const DEFAULT_MID_IMAGE_HEIGHT: double = 72; // 4x2卡片，图片默认高度
const DEFAULT_SMALL_IMAGE_HEIGHT: double = 59; // 2x1卡片，图片默认高度

interface CardStyle {
  thumbWidth: double,
  thumbHeight: double,
  thumbMarginLeft?: double,
  titleFontSize: double,
  titleFontLineHeight: double,
  titleFontMarginTop: double,
  descriptionFontSize: double,
  descriptionLineHeight: double,
  maxDescriptionFontSize?: double,
  maxDescriptionLineHeight?: double,
  descriptionMarginTop: double,
  dividerMarginTop: double,
  appNameFontSize: double,
  appIconSize: double,
  cardRadius: double,
  appNameMarginLeft: double,
  appNameLineHeight: double,
  cardPadding: double,
  cardPaddingBottom: double,
  cardPaddingTop: double
}

const BIG_CARD_STYLE: CardStyle = {
  thumbWidth: 200,
  thumbHeight: 120,
  titleFontSize: 14,
  titleFontLineHeight: 16,
  titleFontMarginTop: 10,
  descriptionFontSize: 14,
  descriptionLineHeight: 16,
  descriptionMarginTop: 4,
  dividerMarginTop: 5,
  appNameFontSize: 10,
  appNameLineHeight: 14,
  appIconSize: 12,
  cardRadius: 16,
  appNameMarginLeft: 6.5,
  cardPadding: 12,
  cardPaddingBottom: 10,
  cardPaddingTop: 5
}

const MID_CARD_STYLE: CardStyle = {
  thumbWidth: 36,
  thumbHeight: 48,
  thumbMarginLeft: 14,
  descriptionFontSize: 10,
  descriptionLineHeight: 12,
  maxDescriptionFontSize: 14,
  maxDescriptionLineHeight: 16,
  descriptionMarginTop: 10,
  titleFontSize: 14,
  titleFontLineHeight: 16,
  titleFontMarginTop: 14,
  dividerMarginTop: 5,
  appNameFontSize: 10,
  appNameLineHeight: 14,
  appIconSize: 12,
  cardRadius: 16,
  appNameMarginLeft: 6.5,
  cardPadding: 12,
  cardPaddingBottom: 10,
  cardPaddingTop: 5
}

const SMALL_CARD_STYLE: CardStyle = {
  thumbWidth: 24,
  thumbHeight: 24,
  thumbMarginLeft: 8,
  titleFontSize: 12,
  titleFontLineHeight: 14,
  titleFontMarginTop: 9,
  descriptionFontSize: 10,
  descriptionLineHeight: 12,
  maxDescriptionFontSize: 12,
  maxDescriptionLineHeight: 14,
  descriptionMarginTop: 4,
  dividerMarginTop: 5,
  appNameFontSize: 10,
  appIconSize: 12,
  cardRadius: 12,
  appNameMarginLeft: 4,
  appNameLineHeight: 12,
  cardPadding: 8,
  cardPaddingBottom: 8,
  cardPaddingTop: 4
}

@Component
export struct ContentFormCard {
  @PropRef @Watch('formTypeChange') formType: FormType = FormType.TYPE_MID;
  private contentFormData: uniformDataStruct.ContentForm | undefined = undefined;
  private formStyle: CardStyle = MID_CARD_STYLE;
  private controller: TextController = new TextController();
  @State cardScale: double = 1;
  @PropRef @Watch('formSizeChange') formWidth: double = 0.0;
  @PropRef @Watch('formSizeChange') formHeight: double = 0.0;
  @State cardWidth: double = 0;
  @State cardHeight: double = 0;
  @State defaultThumbImage: image.PixelMap | undefined = undefined;
  @State thumbImage: image.PixelMap | undefined = undefined;
  @State appImage: image.PixelMap | undefined = undefined;
  @State lineCount: int = 1;
  @State isMirrorLanguageType: boolean = false;
  private backAnimator: AnimatorResult | undefined = undefined;
  private widthEnd: double = 0;
  private handleOnClick: () => void = () => {
  };

  aboutToAppear(): void {
    this.initSystemLanguage();
    this.initCardStyle(this.formWidth, this.formHeight);
    this.createPixelMap();
  }

  aboutToDisappear(): void {
    this.contentFormData = undefined;
    this.thumbImage = undefined;
    this.appImage = undefined;
    this.backAnimator = undefined;
  }

  formTypeChange(value: string): void {
    switch (this.formType) {
      case FormType.TYPE_BIG:
        this.formWidth = DEFAULT_BIG_CARD_SIZE;
        break;
      case FormType.TYPE_MID:
        this.formWidth = DEFAULT_MID_CARD_WIDTH;
        break;
      default:
        this.formWidth = DEFAULT_SMALL_CARD_WIDTH;
        break;
    }
    this.initCardStyle(this.formWidth, NaN);
  }

  initAnimator() {
    let anima: AnimatorResult = this.getUIContext().createAnimator({
      duration: 300,
      easing: 'friction',
      delay: 0,
      fill: 'forwards',
      direction: 'normal',
      iterations: 1,
      begin: this.cardWidth,
      end: this.widthEnd
    });
    anima.onFrame = (value: double) => {
      this.initCardStyle(value, NaN);
    }
    this.backAnimator = anima;
  }

  formSizeChange(value: string): void {
    this.updateWidthEndValue();
    if (this.widthEnd === this.cardWidth) {
      return;
    }
    this.initAnimator();
    this.backAnimator?.play();
  }

  updateWidthEndValue(): void {
    let scale: double = 1;
    let defaultWidth: double = DEFAULT_SMALL_CARD_WIDTH;
    switch (this.formType) {
      case FormType.TYPE_BIG:
        scale = this.formWidth ? (this.formWidth / DEFAULT_BIG_CARD_SIZE) : this.formHeight / DEFAULT_BIG_CARD_SIZE;
        defaultWidth = DEFAULT_BIG_CARD_SIZE;
        break;
      case FormType.TYPE_MID:
        scale = this.formWidth ? (this.formWidth / DEFAULT_MID_CARD_WIDTH) : this.formHeight / DEFAULT_MID_CARD_HEIGHT;
        defaultWidth = DEFAULT_MID_CARD_WIDTH;
        break;
      default:
        scale = this.formWidth ?
          (this.formWidth / DEFAULT_SMALL_CARD_WIDTH) : this.formHeight / DEFAULT_SMALL_CARD_HEIGHT;
        break;
    }
    let minScale: double = this.formType === FormType.TYPE_SMALL ? SMALL_MIN_CARD_SCALE : MIN_CARD_SCALE;
    if (scale > MAX_CARD_SCALE) {
      scale = MAX_CARD_SCALE;
    } else if (scale < minScale) {
      scale = minScale;
    }
    this.widthEnd = scale * defaultWidth;
  }

  initCardScale(widthScale: double, defaultWidth: double, defaultHeight: double): void {
    let minScale = this.formType === FormType.TYPE_SMALL ? SMALL_MIN_CARD_SCALE : MIN_CARD_SCALE;
    if (widthScale > MAX_CARD_SCALE) {
      this.cardScale = MAX_CARD_SCALE;
    } else if (widthScale < minScale) {
      this.cardScale = minScale;
    } else {
      this.cardScale = widthScale;
    }
    this.cardWidth = defaultWidth * this.cardScale;
    this.cardHeight =
      (this.contentFormData?.title === '' && this.formHeight > 0) ? this.formHeight : defaultHeight * this.cardScale;
    console.info(`${TAG}, widthScale:${this.cardScale}, cardScale: ${this.cardScale}, ` +
      `cardWidth: ${this.cardWidth}, cardHeight: ${this.cardHeight}`);
  }

  initCardStyle(curWidth: double, curHeight: double): void {
    let scale: double = 1;
    if (this.lineCount !== 2) {
      this.lineCount = 1;
    }
    let defaultWidth: double = DEFAULT_SMALL_CARD_WIDTH;
    let defaultHeight: double = DEFAULT_SMALL_CARD_HEIGHT;
    switch (this.formType) {
      case FormType.TYPE_BIG:
        this.formStyle = BIG_CARD_STYLE;
        defaultWidth = DEFAULT_BIG_CARD_SIZE;
        defaultHeight = DEFAULT_BIG_CARD_SIZE;
        if (curHeight) {
          scale = curHeight / DEFAULT_BIG_CARD_SIZE;
        } else {
          scale = curWidth ? curWidth / DEFAULT_BIG_CARD_SIZE : 1;
        }
        break;
      case FormType.TYPE_MID:
        this.formStyle = MID_CARD_STYLE;
        defaultWidth = DEFAULT_MID_CARD_WIDTH;
        defaultHeight = DEFAULT_MID_CARD_HEIGHT;
        if (curHeight) {
          scale = curHeight / DEFAULT_MID_CARD_HEIGHT;
        } else {
          scale = curWidth ? curWidth / DEFAULT_MID_CARD_WIDTH : 1;
        }
        break;
      default:
        this.formStyle = SMALL_CARD_STYLE;
        if (curHeight) {
          scale = curHeight / DEFAULT_SMALL_CARD_HEIGHT;
        } else {
          scale = curWidth ? curWidth / DEFAULT_SMALL_CARD_WIDTH : 1;
        }
        break;
    }
    this.initCardScale(scale, defaultWidth, defaultHeight);
  }

  @Builder
  ThumbImage() {
    Column() {
      if (this.formHeight > 0) {
        Image(this.thumbImage ? this.thumbImage : this.defaultThumbImage)
          .objectFit(ImageFit.Contain)
          .width('100%')
          .layoutWeight(1)
          .draggable(false)
          .id('cardThumbImage')
      } else {
        Image(this.thumbImage ? this.thumbImage : this.defaultThumbImage)
          .objectFit(ImageFit.Contain)
          .width('100%')
          .aspectRatio(this.getAspectRatio())
          .draggable(false)
          .id('cardThumbImage')
      }
    }
    .size({ width: '100%' })
    .layoutWeight(this.formHeight > 0 ? 1 : 0)
    .backgroundColor(this.thumbImage ? CARD_BACKGROUND : DEFAULT_THUMB_BACKGROUND)
  }

  @Builder
  CardDivider() {
    Divider()
      .height(1)//.color(CARD_DIVIDER_COLOR)
      .opacity(0.5)
      .padding({
        left: this.formStyle.cardPadding * this.cardScale,
        right: this.formStyle.cardPadding * this.cardScale
      })
  }

  @Builder
  AppView() {
    Row({ space: this.formStyle.appNameMarginLeft * this.cardScale } as RowOptions) {
      Image(this.appImage)
        .width(this.formStyle.appIconSize * this.cardScale)
        .height(this.formStyle.appIconSize * this.cardScale)
        .objectFit(ImageFit.Fill)
        .alt($r('sys.media.ohos_app_icon'))
        .borderRadius($r('sys.float.corner_radius_level1'))
        .draggable(false)
        .id('cardAppIcon')
      Text(this.contentFormData?.appName ? this.contentFormData?.appName : ' ')
        .fontSize(this.formStyle.appNameFontSize * this.cardScale)
        .fontColor(APP_NAME_COLOR)
        .maxLines(1)
        .lineHeight(this.formStyle.appNameLineHeight * this.cardScale)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
        .constraintSize({ minWidth: this.getTextSize(TextType.APP_NAME, this.contentFormData?.appName) })
        .backgroundColor(this.getTextBackground(this.contentFormData?.appName))
        .fontWeight(FontWeight.Regular)
        .borderRadius(this.contentFormData?.title === '' ? 0 : DEFAULT_EMPTY_TEXT_RADIUS)
        .direction(this.isMirrorLanguageType ? Direction.Rtl : Direction.Ltr)
        .maxFontScale(1)
        .layoutWeight(1)
        .id('cardAppName')

    }
    .padding({
      left: this.formStyle.cardPadding * this.cardScale,
      right: this.formStyle.cardPadding * this.cardScale,
      top: this.formStyle.cardPaddingTop * this.cardScale,
      bottom: this.formStyle.cardPaddingBottom * this.cardScale,
    })
  }

  @Builder
  TitleText() {
    Text(this.contentFormData?.title)
      .fontSize(this.formStyle.titleFontSize * this.cardScale)
      .fontColor(TITLE_FONT_COLOR)
      .fontWeight(FontWeight.Bold)
      .maxLines(1)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .height(this.formStyle.titleFontLineHeight * this.cardScale)
      .margin({ top: this.formStyle.titleFontMarginTop * this.cardScale } as Margin)
      .constraintSize({ minWidth: this.getTextSize(TextType.TITLE, this.contentFormData?.title) })
      .backgroundColor(this.getTextBackground(this.contentFormData?.title))
      .borderRadius(this.contentFormData?.title === '' ? 0 : DEFAULT_EMPTY_TEXT_RADIUS)
      .direction(this.isMirrorLanguageType ? Direction.Rtl : Direction.Ltr)
      .maxFontScale(1)
      .id('cardTitleText')
  }

  @Builder
  Card4x4() {
    Column() {
      Image(this.thumbImage ? this.thumbImage : this.defaultThumbImage)
        .objectFit(ImageFit.Cover)
        .width('100%')
        .height(this.formStyle.thumbHeight * this.cardScale)
        .backgroundColor(this.thumbImage ? CARD_BACKGROUND : DEFAULT_THUMB_BACKGROUND)
        .draggable(false)
        .id('cardThumbImage')
      Column() {
        this.TitleText()
        Text(this.contentFormData?.description)
          .fontSize(this.formStyle.descriptionFontSize * this.cardScale)
          .fontColor(DESCRIPTION_FONT_COLOR)
          .fontWeight(FontWeight.Regular)
          .maxLines(1)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .constraintSize({ minWidth: this.getTextSize(TextType.DESCRIPTION, this.contentFormData?.description) })
          .height(this.formStyle.descriptionLineHeight * this.cardScale)
          .margin({ top: this.formStyle.descriptionMarginTop * this.cardScale } as Margin)
          .backgroundColor(this.getTextBackground(this.contentFormData?.description))
          .fontWeight(FontWeight.Regular)
          .borderRadius(this.contentFormData?.description ? 0 : DEFAULT_EMPTY_TEXT_RADIUS)
          .direction(this.isMirrorLanguageType ? Direction.Rtl : Direction.Ltr)
          .maxFontScale(1)
          .id('cardDescription')
      }
      .alignItems(HorizontalAlign.Start)
      .width('100%')
      .padding({
        left: this.formStyle.cardPadding * this.cardScale,
        right: this.formStyle.cardPadding * this.cardScale
      })
      .margin({ bottom: this.formStyle.dividerMarginTop * this.cardScale } as Margin)
      .justifyContent(FlexAlign.Center)

      this.CardDivider()
      this.AppView()
    }
    .size({ width: '100%', height: this.cardHeight })
  }

  @Builder
  DescriptionView() {
    Text(this.contentFormData?.description ? this.contentFormData?.description : ' ', { controller: this.controller })
      .fontColor(DESCRIPTION_FONT_COLOR)
      .fontWeight(FontWeight.Regular)
      .maxLines(2)
      .fontWeight(FontWeight.Regular)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .lineHeight((this.lineCount === 1 ?
        (this.formStyle.maxDescriptionLineHeight ? this.formStyle.maxDescriptionLineHeight as double :
          this.formStyle.descriptionLineHeight) : this.formStyle.descriptionLineHeight) * this.cardScale)
      .fontSize(this.getDescriptionFontSize() * this.cardScale)
      .constraintSize({ minWidth: this.getTextSize(TextType.DESCRIPTION, this.contentFormData?.description) })
      .backgroundColor(this.getTextBackground(this.contentFormData?.description))
      .borderRadius(this.contentFormData?.description ? 0 : DEFAULT_EMPTY_TEXT_RADIUS)
      .onAreaChange((oldValue: Area, newValue: Area) => {
        let layoutManager: LayoutManager | undefined = this.controller.getLayoutManager();
        if (layoutManager) {
          let line = layoutManager.getLineCount();
          if (line && line === 2) {
            this.lineCount = line;
          }
        }
      })
      .direction(this.isMirrorLanguageType ? Direction.Rtl : Direction.Ltr)
      .maxFontScale(1)
      .id('cardDescription')
  }

  @Builder
  Card4x2() {
    Column() {
      if (this.contentFormData?.title === '') { // show the card only thumbData
        this.ThumbImage()
      } else { // show the card has thumbData and title,description
        Row() {
          Column({ space: this.formStyle.descriptionMarginTop * this.cardScale } as ColumnOptions) {
            this.TitleText()
            this.DescriptionView()
          }
          .layoutWeight(1)
          .alignItems(HorizontalAlign.Start)

          if (this.thumbImage) {
            Image(this.thumbImage)
              .width(this.formStyle.thumbWidth * this.cardScale)
              .height(this.formStyle.thumbHeight * this.cardScale)
              .objectFit(this.thumbImage ? ImageFit.Cover : ImageFit.Contain)
              .borderRadius(4)
              .draggable(false)
              .margin({
                right: this.isMirrorLanguageType ? (this.formStyle.thumbMarginLeft as double * this.cardScale) : 0,
                left: this.isMirrorLanguageType ? 0 : (this.formStyle.thumbMarginLeft as double * this.cardScale),
                top: this.formStyle.titleFontMarginTop * this.cardScale
              } as Margin)
              .id('cardThumbImage')
          }
        }
        .width('100%')
        .padding({
          left: this.formStyle.cardPadding * this.cardScale,
          right: this.formStyle.cardPadding * this.cardScale
        } as Padding)
        .layoutWeight(1)
        .margin({ bottom: this.formStyle.dividerMarginTop * this.cardScale } as Margin)
        .alignItems(VerticalAlign.Top)
      }

      this.CardDivider();
      this.AppView();
    }
    .size({ width: '100%' })
    .constraintSize(this.getThumbViewConstraintSize())
  }

  @Builder
  Card2x1() {
    Column() {
      if (this.contentFormData?.title === '') { // show the card only thumbData
        this.ThumbImage()
      } else {
        Column() {
          this.TitleText()
          Row() {
            Column() {
              this.DescriptionView()
            }
            .layoutWeight(1)
            .alignItems(HorizontalAlign.Start)

            if (this.thumbImage) {
              Image(this.thumbImage)
                .objectFit(ImageFit.Cover)
                .borderRadius($r('sys.float.corner_radius_level2'))
                .width(this.formStyle.thumbWidth * this.cardScale)
                .height(this.formStyle.thumbHeight * this.cardScale)
                .draggable(false)
                .margin({
                  left: this.isMirrorLanguageType ? 0 : (this.formStyle.thumbMarginLeft as double * this.cardScale),
                  right: this.isMirrorLanguageType ? (this.formStyle.thumbMarginLeft as double * this.cardScale) : 0
                } as Margin)
                .id('cardThumbImage')
            }
          }
          .margin({ top: this.formStyle.descriptionMarginTop * this.cardScale } as Margin)
          .layoutWeight(1)
        }
        .width('100%')
        .padding({
          left: this.formStyle.cardPadding * this.cardScale,
          right: this.formStyle.cardPadding * this.cardScale
        })
        .layoutWeight(1)
        .alignItems(HorizontalAlign.Start)
        .margin({ bottom: this.formStyle.dividerMarginTop * this.cardScale } as Margin)
      }
      this.CardDivider()
      this.AppView()
    }
    .size({ width: '100%' })
    .constraintSize(this.getThumbViewConstraintSize())
  }

  build() {
    Column() {
      if (this.initSystemLanguage() && this.formType === FormType.TYPE_BIG) {
        this.Card4x4();
      } else if (this.formType === FormType.TYPE_MID) {
        this.Card4x2();
      } else {
        this.Card2x1();
      }
    }
    .borderRadius(this.formStyle.cardRadius * this.cardScale)
    .clip(true)
    .backgroundColor(CARD_BACKGROUND)
    .backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK,
      {
        colorMode: ThemeColorMode.LIGHT,
        adaptiveColor: AdaptiveColor.DEFAULT,
        scale: 1.0
      } as BackgroundBlurStyleOptions)
    .shadow(ShadowStyle.OUTER_DEFAULT_SM)
    .width(this.cardWidth)
    .onClick(() => {
      this.handleOnClick();
      if (!this.contentFormData?.linkUri) {
        console.warn(`${TAG}, linkUri is null`);
        return;
      }
      try {
        let context: common.UIAbilityContext = this.getUIContext().getHostContext() as common.UIAbilityContext;
        context.openLink(this.contentFormData?.linkUri as string, { appLinkingOnly: false, parameters: {} });
      } catch (err) {
        let error = err as BusinessError;
        console.error(`${TAG}, Failed to openLink, code is ${error.code}, message is ${error.message}`);
      }
    })
  }

  initSystemLanguage(): boolean {
    try {
      this.isMirrorLanguageType = I18n.isRTL(I18n.System.getSystemLanguage());
    } catch (err) {
      let error = err as BusinessError;
      console.error(`${TAG}, Failed to init system language, code is ${error.code}, message is ${error.message}`);
    }
    return true;
  }

  async getPixelMap(uint: Uint8Array, callback: (pixelMap: image.PixelMap) => void): Promise<void> {
    let imageResource: image.ImageSource | undefined = undefined;
    try {
      imageResource = image.createImageSource(uint.buffer);
      if (imageResource) {
        let pixelMapData = await imageResource.createPixelMap();
        if (pixelMapData) {
          callback(pixelMapData);
        }
      }
      imageResource?.release();
    } catch (err) {
      let error = err as BusinessError;
      console.error(`${TAG}, Failed to create pixelMap, code is ${error.code}, message is ${error.message}`);
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

  createPixelMap(): void {
    let defaultThumbData = this.transStringToUint8Array(defaultIcon);
    this.getPixelMap(defaultThumbData, (pixelMap: image.PixelMap) => {
      this.defaultThumbImage = pixelMap;
    })

    if (this.contentFormData && this.contentFormData?.thumbData) {
      if (!(this.contentFormData?.thumbData instanceof Uint8Array)) {
        console.error(`${TAG}, thumbData is not Uint8Array`);
        return;
      }
      this.getPixelMap(this.contentFormData?.thumbData as Uint8Array, (pixelMap: image.PixelMap) => {
        this.thumbImage = pixelMap;
      })
    }
    if (this.contentFormData && this.contentFormData?.appIcon) {
      if (!(this.contentFormData?.appIcon instanceof Uint8Array)) {
        console.error(`${TAG}, appIcon is not Uint8Array`);
        return;
      }
      this.getPixelMap(this.contentFormData?.appIcon as Uint8Array, (pixelMap: image.PixelMap) => {
        this.appImage = pixelMap;
      })
    }
  }

  getAspectRatio(): double {
    let iamgeSize = this.thumbImage?.getImageInfoSync().size;
    let defaultCardWidth = this.formType === FormType.TYPE_MID ? DEFAULT_MID_CARD_WIDTH : DEFAULT_SMALL_CARD_WIDTH;
    let defaultImageHeight =
      this.formType === FormType.TYPE_MID ? DEFAULT_MID_IMAGE_HEIGHT : DEFAULT_SMALL_IMAGE_HEIGHT;
    if (iamgeSize && this.thumbImage) {
      if ((iamgeSize.width / iamgeSize.height) > (defaultCardWidth / (defaultImageHeight * MIN_CARD_SCALE))) {
        return defaultCardWidth / (defaultImageHeight * MIN_CARD_SCALE);
      }
      if ((iamgeSize.width / iamgeSize.height) < (defaultCardWidth / (defaultImageHeight * MAX_CARD_SCALE))) {
        return defaultCardWidth / (defaultImageHeight * MAX_CARD_SCALE);
      }
      return iamgeSize.width / iamgeSize.height;
    }
    return defaultCardWidth / defaultImageHeight;
  }

  getTextBackground(text: string | undefined): string {
    if (text && text.length > 0) {
      return TRANSLATE_BACKGROUND;
    }
    return DEFAULT_FONT_BACKGROUND;
  }

  getTextSize(textType: TextType, text: string | undefined): double | string {
    if (textType === TextType.TITLE) {
      if (text === '' || text === undefined || text === null) {
        if (this.formType === FormType.TYPE_SMALL) {
          return SMALL_EMPTY_TITLE_WIDTH;
        }
        return DEFAULT_EMPTY_TITLE_WIDTH;
      }
      return DEFAULT_EMPTY_DESCRIPTION_WIDTH;
    }
    if (textType === TextType.APP_NAME) {
      if (text === '' || text === undefined || text === null) {
        if (this.formType === FormType.TYPE_SMALL) {
          return SMALL_EMPTY_APPNAME_WIDTH;
        }
        return DEFAULT_EMPTY_APPNAME_WIDTH;
      }
      return DEFAULT_EMPTY_DESCRIPTION_WIDTH;
    }
    return '100%'
  }

  getThumbViewConstraintSize(): ConstraintSizeOptions {
    if (this.contentFormData?.title !== '') {
      return { maxHeight: this.cardHeight, minHeight: this.cardHeight };
    } else {
      if (this.formHeight > 0) {
        return {
          maxHeight: this.formHeight,
          minHeight: this.formHeight
        };
      }
      return {
        maxHeight: this.cardHeight * MAX_CARD_SCALE,
        minHeight: this.cardHeight * MIN_CARD_SCALE
      };
    }
  }

  getDescriptionFontSize(): double {
    return this.lineCount === 1 ?
      (this.formStyle.maxDescriptionFontSize ? this.formStyle.maxDescriptionFontSize as double :
        this.formStyle.descriptionFontSize) : this.formStyle.descriptionFontSize;
  }
}
