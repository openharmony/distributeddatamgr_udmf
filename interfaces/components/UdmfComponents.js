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
const u = 0.6;
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
const n3 = '#00000000';
const n1 = '#99182431';
const o1 = '#CCCCCC';
const q1 = '#55CCCCCC';
const s1 = '#ff182431';
const t1 = '#99182431';
const u1 = 72;
const v1 = 59;
const w1 = 3.25;
const z1 = {
    c2: 200,
    d2: 120,
    e2: 14,
    f2: 16,
    g2: 10,
    h2: 14,
    i2: 16,
    j2: 4,
    l2: 5,
    m2: 10,
    n2: 14,
    o2: 12,
    q2: 16,
    s2: 6.5,
    t2: 12,
    u2: 10,
    v2: 5
};
const a2 = {
    c2: 36,
    d2: 48,
    w2: 14,
    h2: 10,
    i2: 12,
    z2: 14,
    a3: 16,
    j2: 10,
    e2: 14,
    f2: 16,
    g2: 14,
    l2: 5,
    m2: 10,
    n2: 14,
    o2: 12,
    q2: 16,
    s2: 6.5,
    t2: 12,
    u2: 10,
    v2: 5
};
const b2 = {
    c2: 24,
    d2: 24,
    w2: 8,
    e2: 12,
    f2: 14,
    g2: 9,
    h2: 10,
    i2: 12,
    z2: 12,
    a3: 14,
    j2: 4,
    l2: 5,
    m2: 10,
    o2: 12,
    q2: 12,
    s2: 4,
    n2: 12,
    t2: 8,
    u2: 8,
    v2: 4
};

export class ContentFormCard extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.b3 = new SynchedPropertySimpleOneWayPU(params.formType, this, "formType");
        this.contentFormData = undefined;
        this.formStyle = a2;
        this.controller = new TextController();
        this.c3 = new ObservedPropertySimplePU(1, this, "cardScale");
        this.d3 = new SynchedPropertySimpleOneWayPU(params.formWidth, this, "formWidth");
        this.e3 = new SynchedPropertySimpleOneWayPU(params.formHeight, this, "formHeight");
        this.f3 = new ObservedPropertySimplePU(0, this, "cardWidth");
        this.g3 = new ObservedPropertySimplePU(0, this, "cardHeight");
        this.h3 = new ObservedPropertyObjectPU(undefined, this, "defaultThumbImage");
        this.i3 = new ObservedPropertyObjectPU(undefined, this, "thumbImage");
        this.j3 = new ObservedPropertyObjectPU(undefined, this, "appImage");
        this.l3 = new ObservedPropertySimplePU(1, this, "lineCount");
        this.m3 = new ObservedPropertySimplePU(false, this, "isMirrorLanguageType");
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
            this.b3.set(FormType.TYPE_MID);
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
            this.d3.set(0);
        }
        if (params.formHeight === undefined) {
            this.e3.set(0);
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
        this.b3.reset(params.formType);
        this.d3.reset(params.formWidth);
        this.e3.reset(params.formHeight);
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.b3.purgeDependencyOnElmtId(rmElmtId);
        this.c3.purgeDependencyOnElmtId(rmElmtId);
        this.d3.purgeDependencyOnElmtId(rmElmtId);
        this.e3.purgeDependencyOnElmtId(rmElmtId);
        this.f3.purgeDependencyOnElmtId(rmElmtId);
        this.g3.purgeDependencyOnElmtId(rmElmtId);
        this.h3.purgeDependencyOnElmtId(rmElmtId);
        this.i3.purgeDependencyOnElmtId(rmElmtId);
        this.j3.purgeDependencyOnElmtId(rmElmtId);
        this.l3.purgeDependencyOnElmtId(rmElmtId);
        this.m3.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.b3.aboutToBeDeleted();
        this.c3.aboutToBeDeleted();
        this.d3.aboutToBeDeleted();
        this.e3.aboutToBeDeleted();
        this.f3.aboutToBeDeleted();
        this.g3.aboutToBeDeleted();
        this.h3.aboutToBeDeleted();
        this.i3.aboutToBeDeleted();
        this.j3.aboutToBeDeleted();
        this.l3.aboutToBeDeleted();
        this.m3.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get formType() {
        return this.b3.get();
    }

    set formType(newValue) {
        this.b3.set(newValue);
    }

    get cardScale() {
        return this.c3.get();
    }

    set cardScale(newValue) {
        this.c3.set(newValue);
    }

    get formWidth() {
        return this.d3.get();
    }

    set formWidth(newValue) {
        this.d3.set(newValue);
    }

    get formHeight() {
        return this.e3.get();
    }

    set formHeight(newValue) {
        this.e3.set(newValue);
    }

    get cardWidth() {
        return this.f3.get();
    }

    set cardWidth(newValue) {
        this.f3.set(newValue);
    }

    get cardHeight() {
        return this.g3.get();
    }

    set cardHeight(newValue) {
        this.g3.set(newValue);
    }

    get defaultThumbImage() {
        return this.h3.get();
    }

    set defaultThumbImage(newValue) {
        this.h3.set(newValue);
    }

    get thumbImage() {
        return this.i3.get();
    }

    set thumbImage(newValue) {
        this.i3.set(newValue);
    }

    get appImage() {
        return this.j3.get();
    }

    set appImage(newValue) {
        this.j3.set(newValue);
    }

    get lineCount() {
        return this.l3.get();
    }

    set lineCount(newValue) {
        this.l3.set(newValue);
    }

    get isMirrorLanguageType() {
        return this.m3.get();
    }

    set isMirrorLanguageType(newValue) {
        this.m3.set(newValue);
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

    initCardScale(n2, o2, q2) {
        let r2 = this.formType === FormType.TYPE_SMALL ? u : t;
        if (n2 > o) {
            this.cardScale = o;
        } else if (n2 < r2) {
            this.cardScale = r2;
        } else {
            this.cardScale = n2;
        }
        this.cardWidth = o2 * this.cardScale;
        this.cardHeight =
            (this.contentFormData?.title === '' && this.formHeight > 0) ? this.formHeight : q2 * this.cardScale;
        console.info(`${j}, widthScale:${this.cardScale}, cardScale: ${this.cardScale}, ` +
            `cardWidth: ${this.cardWidth}, cardHeight: ${this.cardHeight}`);
    }

    initCardStyle() {
        let m2 = 1;
        switch (this.formType) {
            case FormType.TYPE_BIG:
                this.formStyle = z1;
                m2 = this.formWidth ? this.formWidth / a1 : 1;
                this.initCardScale(m2, a1, a1);
                break;
            case FormType.TYPE_MID:
                this.formStyle = a2;
                m2 = this.formWidth ? this.formWidth / b1 : 1;
                this.initCardScale(m2, b1, c1);
                break;
            default:
                this.formStyle = b2;
                m2 = this.formWidth ? this.formWidth / d1 : 1;
                this.initCardScale(m2, d1, e1);
                break;
        }
    }

    ThumbImage(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.size({ width: '100%' });
            Column.layoutWeight(this.formHeight > 0 ? 1 : 0);
            Column.backgroundColor(this.thumbImage ? m1 : o1);
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.formHeight > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(this.thumbImage ? this.thumbImage : this.defaultThumbImage);
                        Image.objectFit(ImageFit.Contain);
                        Image.width('100%');
                        Image.layoutWeight(1);
                        Image.draggable(false);
                    }, Image);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(this.thumbImage ? this.thumbImage : this.defaultThumbImage);
                        Image.objectFit(ImageFit.Contain);
                        Image.width('100%');
                        Image.aspectRatio(this.getAspectRatio());
                        Image.draggable(false);
                    }, Image);
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
                left: this.formStyle.t2 * this.cardScale,
                right: this.formStyle.t2 * this.cardScale
            });
        }, Divider);
    }

    AppView(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create({ space: this.formStyle.s2 * this.cardScale });
            Row.padding({
                left: this.formStyle.t2 * this.cardScale,
                right: this.formStyle.t2 * this.cardScale,
                top: this.formStyle.v2 * this.cardScale,
                bottom: this.formStyle.u2 * this.cardScale,
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.appImage);
            Image.width(this.formStyle.o2 * this.cardScale);
            Image.height(this.formStyle.o2 * this.cardScale);
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
        }, Image);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.contentFormData?.appName ? this.contentFormData?.appName : ' ');
            Text.fontSize(this.formStyle.m2 * this.cardScale);
            Text.fontColor(n1);
            Text.maxLines(1);
            Text.lineHeight(this.formStyle.n2 * this.cardScale);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.constraintSize({ minWidth: this.getTextSize(TextType.APP_NAME, this.contentFormData?.appName) });
            Text.backgroundColor(this.getTextBackground(this.contentFormData?.appName));
            Text.fontWeight(FontWeight.Regular);
            Text.borderRadius(this.contentFormData?.title === '' ? 0 : j1);
            Text.direction(this.isMirrorLanguageType ? Direction.Rtl : Direction.Ltr);
            Text.maxFontScale(1);
            Text.layoutWeight(1);
        }, Text);
        Text.pop();
        Row.pop();
    }

    TitleText(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.contentFormData?.title);
            Text.fontSize(this.formStyle.e2 * this.cardScale);
            Text.fontColor(s1);
            Text.fontWeight(FontWeight.Bold);
            Text.maxLines(1);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.height(this.formStyle.f2 * this.cardScale);
            Text.margin({ top: this.formStyle.g2 * this.cardScale });
            Text.constraintSize({ minWidth: this.getTextSize(TextType.TITLE, this.contentFormData?.title) });
            Text.backgroundColor(this.getTextBackground(this.contentFormData?.title));
            Text.borderRadius(this.contentFormData?.title === '' ? 0 : j1);
            Text.direction(this.isMirrorLanguageType ? Direction.Rtl : Direction.Ltr);
            Text.maxFontScale(1);
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
            Image.height(this.formStyle.d2 * this.cardScale);
            Image.backgroundColor(this.thumbImage ? m1 : o1);
            Image.draggable(false);
        }, Image);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.alignItems(HorizontalAlign.Start);
            Column.width('100%');
            Column.padding({
                left: this.formStyle.t2 * this.cardScale,
                right: this.formStyle.t2 * this.cardScale
            });
            Column.margin({ bottom: this.formStyle.l2 * this.cardScale });
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.TitleText.bind(this)();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.contentFormData?.description);
            Text.fontSize(this.formStyle.h2 * this.cardScale);
            Text.fontColor(t1);
            Text.fontWeight(FontWeight.Regular);
            Text.maxLines(1);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.constraintSize({
                minWidth: this.getTextSize(TextType.DESCRIPTION, this.contentFormData?.description)
            });
            Text.height(this.formStyle.i2 * this.cardScale);
            Text.margin({ top: this.formStyle.j2 * this.cardScale });
            Text.backgroundColor(this.getTextBackground(this.contentFormData?.description));
            Text.fontWeight(FontWeight.Regular);
            Text.borderRadius(this.contentFormData?.description ? 0 : j1);
            Text.direction(this.isMirrorLanguageType ? Direction.Rtl : Direction.Ltr);
            Text.maxFontScale(1);
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
            Text.fontColor(t1);
            Text.fontWeight(FontWeight.Regular);
            Text.maxLines(2);
            Text.fontWeight(FontWeight.Regular);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.lineHeight((this.lineCount === 1 ?
                (this.formStyle.a3 ? this.formStyle.a3 :
                this.formStyle.i2) : this.formStyle.i2) * this.cardScale);
            Text.fontSize(this.getDescriptionFontSize());
            Text.constraintSize({
                minWidth: this.getTextSize(TextType.DESCRIPTION, this.contentFormData?.description)
            });
            Text.backgroundColor(this.getTextBackground(this.contentFormData?.description));
            Text.borderRadius(this.contentFormData?.description ? 0 : j1);
            Text.onAreaChange(() => {
                let l2 = this.controller.getLayoutManager();
                this.lineCount = l2.getLineCount();
            });
            Text.direction(this.isMirrorLanguageType ? Direction.Rtl : Direction.Ltr);
            Text.maxFontScale(1);
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
                            left: this.formStyle.t2 * this.cardScale,
                            right: this.formStyle.t2 * this.cardScale
                        });
                        Row.layoutWeight(1);
                        Row.margin({ bottom: this.formStyle.l2 * this.cardScale });
                        Row.alignItems(VerticalAlign.Top);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create({ space: this.formStyle.j2 * this.cardScale });
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
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Image.create(this.thumbImage);
                                    Image.width(this.formStyle.c2 * this.cardScale);
                                    Image.height(this.formStyle.d2 * this.cardScale);
                                    Image.objectFit(this.thumbImage ? ImageFit.Cover : ImageFit.Contain);
                                    Image.borderRadius(4);
                                    Image.draggable(false);
                                    Image.margin({
                                        right: this.isMirrorLanguageType ? (this.formStyle.w2 * this.cardScale) : 0,
                                        left: this.isMirrorLanguageType ? 0 : (this.formStyle.w2 * this.cardScale),
                                        top: this.formStyle.g2 * this.cardScale
                                    });
                                }, Image);
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
                            left: this.formStyle.t2 * this.cardScale,
                            right: this.formStyle.t2 * this.cardScale
                        });
                        Column.layoutWeight(1);
                        Column.alignItems(HorizontalAlign.Start);
                        Column.margin({ bottom: this.formStyle.l2 * this.cardScale });
                    }, Column);
                    this.TitleText.bind(this)();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.margin({ top: this.formStyle.j2 * this.cardScale });
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
                                    Image.width(this.formStyle.c2 * this.cardScale);
                                    Image.height(this.formStyle.d2 * this.cardScale);
                                    Image.draggable(false);
                                    Image.margin({
                                        left: this.isMirrorLanguageType ? 0 : (this.formStyle.w2 * this.cardScale),
                                        right: this.isMirrorLanguageType ? (this.formStyle.w2 * this.cardScale) : 0
                                    });
                                }, Image);
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
            Column.borderRadius(this.formStyle.q2 * this.cardScale);
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

    async getPixelMap(i2, callback) {
        let j2 = undefined;
        try {
            j2 = image.createImageSource(i2.buffer);
            let k2 = await j2?.createPixelMap();
            callback(k2);
            j2.release();
        } catch (err) {
            let error = err;
            console.error(`${j}, Failed to create pixelMap, code is ${error.code}, message is ${error.message}`);
        }
    }

    transStringToUint8Array(g2) {
        const arr = g2.split(',');
        const h2 = new Uint8Array(arr.length);
        arr.forEach((value, index) => {
            h2[index] = parseInt(value);
        });
        return h2;
    }

    createPixelMap() {
        let f2 = this.transStringToUint8Array(m);
        this.getPixelMap(f2, (pixelMap) => {
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
        let c2 = this.thumbImage?.getImageInfoSync().size;
        let d2 = this.formType === FormType.TYPE_MID ? b1 : d1;
        let e2 = this.formType === FormType.TYPE_MID ? u1 : v1;
        if (c2 && this.thumbImage) {
            if ((c2.width / c2.height) > (d2 / (e2 * t))) {
                return d2 / (e2 * t);
            }
            if ((c2.width / c2.height) < (d2 / (e2 * o))) {
                return d2 / (e2 * o);
            }
            return c2.width / c2.height;
        }
        return d2 / e2;
    }

    getTextBackground(text) {
        if (text && text.length > 0) {
            return n3;
        }
        return q1;
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
        return this.lineCount === 1 ? (this.formStyle.z2 ? this.formStyle.z2 :
        this.formStyle.h2) : (this.formStyle.h2 * this.cardScale);
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export default { ContentFormCard, FormType };