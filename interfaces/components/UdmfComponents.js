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

if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}

let image = requireNapi('multimedia.image');
let i = requireNapi('i18n');

export var FormType;
(function (FormType) {
    FormType[FormType["TYPE_BIG"] = 0] = "TYPE_BIG";
    FormType[FormType["TYPE_MID"] = 1] = "TYPE_MID";
    FormType[FormType["TYPE_SMALL"] = 2] = "TYPE_SMALL";
})(FormType || (FormType = {}));
var TextType;
(function (TextType) {
    TextType[TextType["TITLE"] = 0] = "TITLE";
    TextType[TextType["DESCRIPTION"] = 1] = "DESCRIPTION";
    TextType[TextType["APP_NAME"] = 2] = "APP_NAME";
})(TextType || (TextType = {}));
const j = 'udmf.ContentFormCard';
const m =
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
const o = 1.2;
const t = 0.8;
const u = 0.4;
const a1 = 200;
const b1 = 200;
const c1 = 100;
const d1 = 137;
const e1 = 83;
const f1 = 70;
const g1 = 40;
const h1 = 50;
const i1 = 30;
const j1 = 2;
const l1 = '100%';
const m1 = '#E6FFFFFF';
const n1 = '#00000000';
const o1 = '#99182431';
const q1 = '#CCCCCC';
const s1 = '#55CCCCCC';
const t1 = '#ff182431';
const u1 = '#99182431';
const v1 = 72;
const w1 = 59;
const z1 = 3.25;
const a2 = {
    d2: 200,
    e2: 120,
    f2: 14,
    g2: 16,
    h2: 10,
    i2: 14,
    j2: 16,
    l2: 4,
    m2: 5,
    n2: 10,
    o2: 14,
    q2: 12,
    s2: 16,
    t2: 6.5,
    u2: 12,
    v2: 10,
    w2: 5
};
const b2 = {
    d2: 36,
    e2: 48,
    z2: 14,
    i2: 10,
    j2: 12,
    a3: 14,
    b3: 16,
    l2: 10,
    f2: 14,
    g2: 16,
    h2: 14,
    m2: 5,
    n2: 10,
    o2: 14,
    q2: 12,
    s2: 16,
    t2: 6.5,
    u2: 12,
    v2: 10,
    w2: 5
};
const c2 = {
    d2: 24,
    e2: 24,
    z2: 8,
    f2: 12,
    g2: 14,
    h2: 9,
    i2: 10,
    j2: 12,
    a3: 12,
    b3: 14,
    l2: 4,
    m2: 5,
    n2: 10,
    q2: 12,
    s2: 12,
    t2: 4,
    o2: 12,
    u2: 8,
    v2: 8,
    w2: 4
};

export class ContentFormCard extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.__formType = new SynchedPropertySimpleOneWayPU(params.formType, this, "formType");
        this.contentFormData = undefined;
        this.formStyle = b2;
        this.controller = new TextController();
        this.__cardScale = new ObservedPropertySimplePU(1, this, "cardScale");
        this.__formWidth = new SynchedPropertySimpleOneWayPU(params.formWidth, this, "formWidth");
        this.__formHeight = new SynchedPropertySimpleOneWayPU(params.formHeight, this, "formHeight");
        this.__cardWidth = new ObservedPropertySimplePU(0, this, "cardWidth");
        this.__cardHeight = new ObservedPropertySimplePU(0, this, "cardHeight");
        this.__defaultThumbImage = new ObservedPropertyObjectPU(undefined, this, "defaultThumbImage");
        this.__thumbImage = new ObservedPropertyObjectPU(undefined, this, "thumbImage");
        this.__appImage = new ObservedPropertyObjectPU(undefined, this, "appImage");
        this.__lineCount = new ObservedPropertySimplePU(1, this, "lineCount");
        this.__isMirrorLanguageType = new ObservedPropertySimplePU(false, this, "isMirrorLanguageType");
        this.handleOnClick = () => {
        };
        this.setInitiallyProvidedValue(params);
        this.declareWatch("formType", this.formTypeChange);
        this.declareWatch("formWidth", this.formSizeChange);
        this.declareWatch("formHeight", this.formSizeChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        if (params.formType === undefined) {
            this.__formType.set(FormType.TYPE_MID);
        }
        if (params.contentFormData !== undefined) {
            this.contentFormData = params.contentFormData;
        }
        if (params.formStyle !== undefined) {
            this.formStyle = params.formStyle;
        }
        if (params.controller !== undefined) {
            this.controller = params.controller;
        }
        if (params.cardScale !== undefined) {
            this.cardScale = params.cardScale;
        }
        if (params.formWidth === undefined) {
            this.__formWidth.set(0);
        }
        if (params.formHeight === undefined) {
            this.__formHeight.set(0);
        }
        if (params.cardWidth !== undefined) {
            this.cardWidth = params.cardWidth;
        }
        if (params.cardHeight !== undefined) {
            this.cardHeight = params.cardHeight;
        }
        if (params.defaultThumbImage !== undefined) {
            this.defaultThumbImage = params.defaultThumbImage;
        }
        if (params.thumbImage !== undefined) {
            this.thumbImage = params.thumbImage;
        }
        if (params.appImage !== undefined) {
            this.appImage = params.appImage;
        }
        if (params.lineCount !== undefined) {
            this.lineCount = params.lineCount;
        }
        if (params.isMirrorLanguageType !== undefined) {
            this.isMirrorLanguageType = params.isMirrorLanguageType;
        }
        if (params.handleOnClick !== undefined) {
            this.handleOnClick = params.handleOnClick;
        }
    }

    updateStateVars(params) {
        this.__formType.reset(params.formType);
        this.__formWidth.reset(params.formWidth);
        this.__formHeight.reset(params.formHeight);
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__formType.purgeDependencyOnElmtId(rmElmtId);
        this.__cardScale.purgeDependencyOnElmtId(rmElmtId);
        this.__formWidth.purgeDependencyOnElmtId(rmElmtId);
        this.__formHeight.purgeDependencyOnElmtId(rmElmtId);
        this.__cardWidth.purgeDependencyOnElmtId(rmElmtId);
        this.__cardHeight.purgeDependencyOnElmtId(rmElmtId);
        this.__defaultThumbImage.purgeDependencyOnElmtId(rmElmtId);
        this.__thumbImage.purgeDependencyOnElmtId(rmElmtId);
        this.__appImage.purgeDependencyOnElmtId(rmElmtId);
        this.__lineCount.purgeDependencyOnElmtId(rmElmtId);
        this.__isMirrorLanguageType.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.__formType.aboutToBeDeleted();
        this.__cardScale.aboutToBeDeleted();
        this.__formWidth.aboutToBeDeleted();
        this.__formHeight.aboutToBeDeleted();
        this.__cardWidth.aboutToBeDeleted();
        this.__cardHeight.aboutToBeDeleted();
        this.__defaultThumbImage.aboutToBeDeleted();
        this.__thumbImage.aboutToBeDeleted();
        this.__appImage.aboutToBeDeleted();
        this.__lineCount.aboutToBeDeleted();
        this.__isMirrorLanguageType.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get formType() {
        return this.__formType.get();
    }

    set formType(newValue) {
        this.__formType.set(newValue);
    }

    get cardScale() {
        return this.__cardScale.get();
    }

    set cardScale(newValue) {
        this.__cardScale.set(newValue);
    }

    get formWidth() {
        return this.__formWidth.get();
    }

    set formWidth(newValue) {
        this.__formWidth.set(newValue);
    }

    get formHeight() {
        return this.__formHeight.get();
    }

    set formHeight(newValue) {
        this.__formHeight.set(newValue);
    }

    get cardWidth() {
        return this.__cardWidth.get();
    }

    set cardWidth(newValue) {
        this.__cardWidth.set(newValue);
    }

    get cardHeight() {
        return this.__cardHeight.get();
    }

    set cardHeight(newValue) {
        this.__cardHeight.set(newValue);
    }

    get defaultThumbImage() {
        return this.__defaultThumbImage.get();
    }

    set defaultThumbImage(newValue) {
        this.__defaultThumbImage.set(newValue);
    }

    get thumbImage() {
        return this.__thumbImage.get();
    }

    set thumbImage(newValue) {
        this.__thumbImage.set(newValue);
    }

    get appImage() {
        return this.__appImage.get();
    }

    set appImage(newValue) {
        this.__appImage.set(newValue);
    }

    get lineCount() {
        return this.__lineCount.get();
    }

    set lineCount(newValue) {
        this.__lineCount.set(newValue);
    }

    get isMirrorLanguageType() {
        return this.__isMirrorLanguageType.get();
    }

    set isMirrorLanguageType(newValue) {
        this.__isMirrorLanguageType.set(newValue);
    }

    aboutToAppear() {
        this.initSystemLanguage();
        this.initCardStyle();
        this.createPixelMap();
    }

    aboutToDisappear() {
        this.contentFormData = undefined;
        this.thumbImage = undefined;
        this.appImage = undefined;
    }

    formTypeChange() {
        switch (this.formType) {
            case FormType.TYPE_BIG:
                this.formWidth = a1;
                break;
            case FormType.TYPE_MID:
                this.formWidth = b1;
                break;
            default:
                this.formWidth = d1;
                break;
        }
        this.initCardStyle();
    }

    formSizeChange() {
        this.initCardStyle();
    }

    initCardScale(o2, q2, r2) {
        let s2 = this.formType === FormType.TYPE_SMALL ? u : t;
        if (o2 > o) {
            this.cardScale = o;
        } else if (o2 < s2) {
            this.cardScale = s2;
        } else {
            this.cardScale = o2;
        }
        this.cardWidth = q2 * this.cardScale;
        this.cardHeight =
            (this.contentFormData?.title === '' && this.formHeight > 0) ? this.formHeight : r2 * this.cardScale;
        console.info(`${j}, widthScale:${this.cardScale}, cardScale: ${this.cardScale}, ` +
            `cardWidth: ${this.cardWidth}, cardHeight: ${this.cardHeight}`);
    }

    initCardStyle() {
        let n2 = 1;
        this.lineCount = 2;
        switch (this.formType) {
            case FormType.TYPE_BIG:
                this.formStyle = a2;
                n2 = this.formWidth ? this.formWidth / a1 : 1;
                this.initCardScale(n2, a1, a1);
                break;
            case FormType.TYPE_MID:
                this.formStyle = b2;
                n2 = this.formWidth ? this.formWidth / b1 : 1;
                this.initCardScale(n2, b1, c1);
                break;
            default:
                this.formStyle = c2;
                n2 = this.formWidth ? this.formWidth / d1 : 1;
                this.initCardScale(n2, d1, e1);
                break;
        }
    }

    ThumbImage(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.size({ width: '100%' });
            Column.layoutWeight(this.formHeight > 0 ? 1 : 0);
            Column.backgroundColor(this.thumbImage ? m1 : q1);
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.formHeight > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    if (!If.canRetake('cardThumbImage')) {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            Image.create(this.thumbImage ? this.thumbImage : this.defaultThumbImage);
                            Image.objectFit(ImageFit.Contain);
                            Image.width('100%');
                            Image.layoutWeight(1);
                            Image.draggable(false);
                            Image.id('cardThumbImage');
                        }, Image);
                    }
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    if (!If.canRetake('cardThumbImage')) {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            Image.create(this.thumbImage ? this.thumbImage : this.defaultThumbImage);
                            Image.objectFit(ImageFit.Contain);
                            Image.width('100%');
                            Image.aspectRatio(this.getAspectRatio());
                            Image.draggable(false);
                            Image.id('cardThumbImage');
                        }, Image);
                    }
                });
            }
        }, If);
        If.pop();
        Column.pop();
    }

    CardDivider(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Divider.create();
            Divider.height(1);
            Divider.opacity(0.5);
            Divider.padding({
                left: this.formStyle.u2 * this.cardScale,
                right: this.formStyle.u2 * this.cardScale
            });
        }, Divider);
    }

    AppView(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create({ space: this.formStyle.t2 * this.cardScale });
            Row.padding({
                left: this.formStyle.u2 * this.cardScale,
                right: this.formStyle.u2 * this.cardScale,
                top: this.formStyle.w2 * this.cardScale,
                bottom: this.formStyle.v2 * this.cardScale,
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.appImage);
            Image.width(this.formStyle.q2 * this.cardScale);
            Image.height(this.formStyle.q2 * this.cardScale);
            Image.objectFit(ImageFit.Fill);
            Image.alt({
                "id": -1,
                "type": 20000,
                params: ['sys.media.ohos_app_icon'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            });
            Image.borderRadius({
                "id": -1,
                "type": 10002,
                params: ['sys.float.corner_radius_level1'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            });
            Image.draggable(false);
            Image.id('cardAppIcon');
        }, Image);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.contentFormData?.appName ? this.contentFormData?.appName : ' ');
            Text.fontSize(this.formStyle.n2 * this.cardScale);
            Text.fontColor(o1);
            Text.maxLines(1);
            Text.lineHeight(this.formStyle.o2 * this.cardScale);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.constraintSize({ minWidth: this.getTextSize(TextType.APP_NAME, this.contentFormData?.appName) });
            Text.backgroundColor(this.getTextBackground(this.contentFormData?.appName));
            Text.fontWeight(FontWeight.Regular);
            Text.borderRadius(this.contentFormData?.title === '' ? 0 : j1);
            Text.direction(this.isMirrorLanguageType ? Direction.Rtl : Direction.Ltr);
            Text.maxFontScale(1);
            Text.layoutWeight(1);
            Text.id('cardAppName');
        }, Text);
        Text.pop();
        Row.pop();
    }

    TitleText(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.contentFormData?.title);
            Text.fontSize(this.formStyle.f2 * this.cardScale);
            Text.fontColor(t1);
            Text.fontWeight(FontWeight.Bold);
            Text.maxLines(1);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.height(this.formStyle.g2 * this.cardScale);
            Text.margin({ top: this.formStyle.h2 * this.cardScale });
            Text.constraintSize({ minWidth: this.getTextSize(TextType.TITLE, this.contentFormData?.title) });
            Text.backgroundColor(this.getTextBackground(this.contentFormData?.title));
            Text.borderRadius(this.contentFormData?.title === '' ? 0 : j1);
            Text.direction(this.isMirrorLanguageType ? Direction.Rtl : Direction.Ltr);
            Text.maxFontScale(1);
            Text.id('cardTitleText');
        }, Text);
        Text.pop();
    }

    Card4x4(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.size({ width: '100%', height: this.cardHeight });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.thumbImage ? this.thumbImage : this.defaultThumbImage);
            Image.objectFit(ImageFit.Cover);
            Image.width('100%');
            Image.height(this.formStyle.e2 * this.cardScale);
            Image.backgroundColor(this.thumbImage ? m1 : q1);
            Image.draggable(false);
            Image.id('cardThumbImage');
        }, Image);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.alignItems(HorizontalAlign.Start);
            Column.width('100%');
            Column.padding({
                left: this.formStyle.u2 * this.cardScale,
                right: this.formStyle.u2 * this.cardScale
            });
            Column.margin({ bottom: this.formStyle.m2 * this.cardScale });
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.TitleText.bind(this)();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.contentFormData?.description);
            Text.fontSize(this.formStyle.i2 * this.cardScale);
            Text.fontColor(u1);
            Text.fontWeight(FontWeight.Regular);
            Text.maxLines(1);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.constraintSize({
                minWidth: this.getTextSize(TextType.DESCRIPTION, this.contentFormData?.description)
            });
            Text.height(this.formStyle.j2 * this.cardScale);
            Text.margin({ top: this.formStyle.l2 * this.cardScale });
            Text.backgroundColor(this.getTextBackground(this.contentFormData?.description));
            Text.fontWeight(FontWeight.Regular);
            Text.borderRadius(this.contentFormData?.description ? 0 : j1);
            Text.direction(this.isMirrorLanguageType ? Direction.Rtl : Direction.Ltr);
            Text.maxFontScale(1);
            Text.id('cardDescription');
        }, Text);
        Text.pop();
        Column.pop();
        this.CardDivider.bind(this)();
        this.AppView.bind(this)();
        Column.pop();
    }

    DescriptionView(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.contentFormData?.description ? this.contentFormData?.description : ' ',
                { controller: this.controller });
            Text.fontColor(u1);
            Text.fontWeight(FontWeight.Regular);
            Text.maxLines(2);
            Text.fontWeight(FontWeight.Regular);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.lineHeight((this.lineCount === 1 ?
                (this.formStyle.b3 ? this.formStyle.b3 :
                this.formStyle.j2) : this.formStyle.j2) * this.cardScale);
            Text.fontSize(this.getDescriptionFontSize());
            Text.constraintSize({
                minWidth: this.getTextSize(TextType.DESCRIPTION, this.contentFormData?.description)
            });
            Text.backgroundColor(this.getTextBackground(this.contentFormData?.description));
            Text.borderRadius(this.contentFormData?.description ? 0 : j1);
            Text.onAreaChange(() => {
                let m2 = this.controller.getLayoutManager();
                if (m2.getLineCount() === 2) {
                    this.lineCount = 2;
                }
            });
            Text.direction(this.isMirrorLanguageType ? Direction.Rtl : Direction.Ltr);
            Text.maxFontScale(1);
            Text.id('cardDescription');
        }, Text);
        Text.pop();
    }

    Card4x2(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.size({ width: '100%' });
            Column.constraintSize(this.getThumbViewConstraintSize());
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.contentFormData?.title === '') {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.ThumbImage.bind(this)();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.width('100%');
                        Row.padding({
                            left: this.formStyle.u2 * this.cardScale,
                            right: this.formStyle.u2 * this.cardScale
                        });
                        Row.layoutWeight(1);
                        Row.margin({ bottom: this.formStyle.m2 * this.cardScale });
                        Row.alignItems(VerticalAlign.Top);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create({ space: this.formStyle.l2 * this.cardScale });
                        Column.layoutWeight(1);
                        Column.alignItems(HorizontalAlign.Start);
                    }, Column);
                    this.TitleText.bind(this)();
                    this.DescriptionView.bind(this)();
                    Column.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.thumbImage) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                if (!If.canRetake('cardThumbImage')) {
                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                        Image.create(this.thumbImage);
                                        Image.width(this.formStyle.d2 * this.cardScale);
                                        Image.height(this.formStyle.e2 * this.cardScale);
                                        Image.objectFit(this.thumbImage ? ImageFit.Cover : ImageFit.Contain);
                                        Image.borderRadius(4);
                                        Image.draggable(false);
                                        Image.margin({
                                            right: this.isMirrorLanguageType ? (this.formStyle.z2 * this.cardScale) : 0,
                                            left: this.isMirrorLanguageType ? 0 : (this.formStyle.z2 * this.cardScale),
                                            top: this.formStyle.h2 * this.cardScale
                                        });
                                        Image.id('cardThumbImage');
                                    }, Image);
                                }
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    Row.pop();
                });
            }
        }, If);
        If.pop();
        this.CardDivider.bind(this)();
        this.AppView.bind(this)();
        Column.pop();
    }

    Card2x1(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.size({ width: '100%' });
            Column.constraintSize(this.getThumbViewConstraintSize());
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.contentFormData?.title === '') {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.ThumbImage.bind(this)();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.width('100%');
                        Column.padding({
                            left: this.formStyle.u2 * this.cardScale,
                            right: this.formStyle.u2 * this.cardScale
                        });
                        Column.layoutWeight(1);
                        Column.alignItems(HorizontalAlign.Start);
                        Column.margin({ bottom: this.formStyle.m2 * this.cardScale });
                    }, Column);
                    this.TitleText.bind(this)();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.margin({ top: this.formStyle.l2 * this.cardScale });
                        Row.layoutWeight(1);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.layoutWeight(1);
                        Column.alignItems(HorizontalAlign.Start);
                    }, Column);
                    this.DescriptionView.bind(this)();
                    Column.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.thumbImage) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                if (!If.canRetake('cardThumbImage')) {
                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                        Image.create(this.thumbImage);
                                        Image.objectFit(ImageFit.Cover);
                                        Image.borderRadius({
                                            "id": -1,
                                            "type": 10002,
                                            params: ['sys.float.corner_radius_level2'],
                                            "bundleName": "__harDefaultBundleName__",
                                            "moduleName": "__harDefaultModuleName__"
                                        });
                                        Image.width(this.formStyle.d2 * this.cardScale);
                                        Image.height(this.formStyle.e2 * this.cardScale);
                                        Image.draggable(false);
                                        Image.margin({
                                            left: this.isMirrorLanguageType ? 0 : (this.formStyle.z2 * this.cardScale),
                                            right: this.isMirrorLanguageType ? (this.formStyle.z2 * this.cardScale) : 0
                                        });
                                        Image.id('cardThumbImage');
                                    }, Image);
                                }
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    Row.pop();
                    Column.pop();
                });
            }
        }, If);
        If.pop();
        this.CardDivider.bind(this)();
        this.AppView.bind(this)();
        Column.pop();
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.borderRadius(this.formStyle.s2 * this.cardScale);
            Column.clip(true);
            Column.backgroundColor(m1);
            Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK,
                { colorMode: ThemeColorMode.LIGHT, adaptiveColor: AdaptiveColor.DEFAULT, scale: 1.0 });
            Column.shadow(ShadowStyle.OUTER_DEFAULT_SM);
            Column.width(this.cardWidth);
            Column.onClick(() => {
                this.handleOnClick();
                if (!this.contentFormData?.linkUri) {
                    console.warn(`${j}, linkUri is null`);
                    return;
                }
                try {
                    let context = getContext(this);
                    context.openLink(this.contentFormData?.linkUri, { appLinkingOnly: false, parameters: {} });
                } catch (err) {
                    let error = err;
                    console.error(`${j}, Failed to openLink, code is ${error.code}, message is ${error.message}`);
                }
            });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.initSystemLanguage() && this.formType === FormType.TYPE_BIG) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.Card4x4.bind(this)();
                });
            } else if (this.formType === FormType.TYPE_MID) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.Card4x2.bind(this)();
                });
            } else {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.Card2x1.bind(this)();
                });
            }
        }, If);
        If.pop();
        Column.pop();
    }

    initSystemLanguage() {
        try {
            this.isMirrorLanguageType = i.isRTL(i.System.getSystemLanguage());
        } catch (err) {
            let error = err;
            console.error(`${j}, Failed to init system language, code is ${error.code}, message is ${error.message}`);
        }
        return true;
    }

    async getPixelMap(j2, callback) {
        let k2 = undefined;
        try {
            k2 = image.createImageSource(j2.buffer);
            let l2 = await k2?.createPixelMap();
            callback(l2);
            k2.release();
        } catch (err) {
            let error = err;
            console.error(`${j}, Failed to create pixelMap, code is ${error.code}, message is ${error.message}`);
        }
    }

    transStringToUint8Array(h2) {
        const arr = h2.split(',');
        const i2 = new Uint8Array(arr.length);
        arr.forEach((value, index) => {
            i2[index] = parseInt(value);
        });
        return i2;
    }

    createPixelMap() {
        let g2 = this.transStringToUint8Array(m);
        this.getPixelMap(g2, (pixelMap) => {
            this.defaultThumbImage = pixelMap;
        });
        if (this.contentFormData && this.contentFormData?.thumbData) {
            if (!(this.contentFormData?.thumbData instanceof Uint8Array)) {
                console.error(`${j}, thumbData is not Uint8Array`);
                return;
            }
            this.getPixelMap(this.contentFormData?.thumbData, (pixelMap) => {
                this.thumbImage = pixelMap;
            });
        }
        if (this.contentFormData && this.contentFormData?.appIcon) {
            if (!(this.contentFormData?.appIcon instanceof Uint8Array)) {
                console.error(`${j}, appIcon is not Uint8Array`);
                return;
            }
            this.getPixelMap(this.contentFormData?.appIcon, (pixelMap) => {
                this.appImage = pixelMap;
            });
        }
    }

    getAspectRatio() {
        let d2 = this.thumbImage?.getImageInfoSync().size;
        let e2 = this.formType === FormType.TYPE_MID ? b1 : d1;
        let f2 = this.formType === FormType.TYPE_MID ? v1 : w1;
        if (d2 && this.thumbImage) {
            if ((d2.width / d2.height) > (e2 / (f2 * t))) {
                return e2 / (f2 * t);
            }
            if ((d2.width / d2.height) < (e2 / (f2 * o))) {
                return e2 / (f2 * o);
            }
            return d2.width / d2.height;
        }
        return e2 / f2;
    }

    getTextBackground(text) {
        if (text && text.length > 0) {
            return n1;
        }
        return s1;
    }

    getTextSize(textType, text) {
        if (textType === TextType.TITLE) {
            if (text === '' || text === undefined || text === null) {
                if (this.formType === FormType.TYPE_SMALL) {
                    return h1;
                }
                return f1;
            }
            return l1;
        }
        if (textType === TextType.APP_NAME) {
            if (text === '' || text === undefined || text === null) {
                if (this.formType === FormType.TYPE_SMALL) {
                    return i1;
                }
                return g1;
            }
            return l1;
        }
        return '100%';
    }

    getThumbViewConstraintSize() {
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
                maxHeight: this.cardHeight * o,
                minHeight: this.cardHeight * t
            };
        }
    }

    getDescriptionFontSize() {
        return this.lineCount === 1 ? (this.formStyle.a3 ? this.formStyle.a3 :
        this.formStyle.i2) : (this.formStyle.i2 * this.cardScale);
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export default { ContentFormCard, FormType };