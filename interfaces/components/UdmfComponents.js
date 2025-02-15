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

export var FormType;
(function (FormType) {
    FormType[FormType["TYPE_BIG"] = 0] = "TYPE_BIG";
    FormType[FormType["TYPE_MID"] = 1] = "TYPE_MID";
    FormType[FormType["TYPE_SMALL"] = 2] = "TYPE_SMALL";
})(FormType || (FormType = {}));
const i = 'udmf.ContentFormCard';
const j = '82,73,70,70,60,3,0,0,87,69,66,80,86,80,56,32,48,3,0,0,144,67,0,157,1,42,36,2,76,1,62,145,72,161,76,37,164,163,34,3' +
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
const m = 1.2;
const o = 0.8;
const t = 200;
const u = 200;
const a1 = 100;
const b1 = 100;
const c1 = 60;
const d1 = 70;
const f3 = 40;
const g3 = 50;
const h3 = 30;
const i3 = 2;
const e1 = '100%';
const f1 = '#E6FFFFFF';
const g1 = '#1A999999';
const h1 = '#66000000';
const i1 = '#CCCCCC';
const j1 = '#55CCCCCC';
const l1 = '#E6000000';
const m1 = '#66000000';
const n1 = 120;
const o1 = 71;
const q1 = 42;
const s1 = {
    v1: 200,
    w1: 120,
    z1: 14,
    a2: 16,
    b2: 10,
    c2: 14,
    d2: 16,
    e2: 4,
    f2: 5,
    g2: 10,
    h2: 14,
    i2: 12,
    j2: 16,
    l2: 6.5,
    m2: 12,
    n2: 10,
    o2: 5
};
const t1 = {
    v1: 36,
    w1: 48,
    q2: 14,
    c2: 10,
    d2: 12,
    s2: 14,
    t2: 16,
    e2: 10,
    z1: 14,
    a2: 16,
    b2: 14,
    f2: 5,
    g2: 10,
    h2: 14,
    i2: 12,
    j2: 16,
    l2: 6.5,
    m2: 12,
    n2: 10,
    o2: 5
};
const u1 = {
    z1: 10,
    a2: 12,
    b2: 8,
    c2: 8,
    d2: 9,
    e2: 4,
    f2: 5,
    g2: 8,
    i2: 8,
    j2: 8,
    l2: 4,
    h2: 10,
    m2: 10,
    n2: 5,
    o2: 4
};
export class ContentFormCard extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.u2 = new SynchedPropertySimpleOneWayPU(params.formType, this, "formType");
        this.contentFormData = undefined;
        this.formStyle = t1;
        this.controller = new TextController();
        this.v2 = new ObservedPropertySimplePU(1, this, "cardScale");
        this.w2 = new SynchedPropertySimpleOneWayPU(params.formWidth, this, "formWidth");
        this.z2 = new ObservedPropertySimplePU(0, this, "cardWidth");
        this.a3 = new ObservedPropertySimplePU(0, this, "formHeight");
        this.b3 = new ObservedPropertyObjectPU(undefined, this, "defaultThumbImage");
        this.c3 = new ObservedPropertyObjectPU(undefined, this, "thumbImage");
        this.d3 = new ObservedPropertyObjectPU(undefined, this, "appImage");
        this.e3 = new ObservedPropertySimplePU(1, this, "lineCount");
        this.setInitiallyProvidedValue(params);
        this.declareWatch("formType", this.formTypeChange);
        this.declareWatch("formWidth", this.formWidthChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        if (params.formType === undefined) {
            this.u2.set(FormType.TYPE_MID);
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
            this.w2.set(0);
        }
        if (params.cardWidth !== undefined) {
            this.cardWidth = params.cardWidth;
        }
        if (params.formHeight !== undefined) {
            this.formHeight = params.formHeight;
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
    }
    updateStateVars(params) {
        this.u2.reset(params.formType);
        this.w2.reset(params.formWidth);
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.u2.purgeDependencyOnElmtId(rmElmtId);
        this.v2.purgeDependencyOnElmtId(rmElmtId);
        this.w2.purgeDependencyOnElmtId(rmElmtId);
        this.z2.purgeDependencyOnElmtId(rmElmtId);
        this.a3.purgeDependencyOnElmtId(rmElmtId);
        this.b3.purgeDependencyOnElmtId(rmElmtId);
        this.c3.purgeDependencyOnElmtId(rmElmtId);
        this.d3.purgeDependencyOnElmtId(rmElmtId);
        this.e3.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
        this.u2.aboutToBeDeleted();
        this.v2.aboutToBeDeleted();
        this.w2.aboutToBeDeleted();
        this.z2.aboutToBeDeleted();
        this.a3.aboutToBeDeleted();
        this.b3.aboutToBeDeleted();
        this.c3.aboutToBeDeleted();
        this.d3.aboutToBeDeleted();
        this.e3.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get formType() {
        return this.u2.get();
    }
    set formType(newValue) {
        this.u2.set(newValue);
    }
    get cardScale() {
        return this.v2.get();
    }
    set cardScale(newValue) {
        this.v2.set(newValue);
    }
    get formWidth() {
        return this.w2.get();
    }
    set formWidth(newValue) {
        this.w2.set(newValue);
    }
    get cardWidth() {
        return this.z2.get();
    }
    set cardWidth(newValue) {
        this.z2.set(newValue);
    }
    get formHeight() {
        return this.a3.get();
    }
    set formHeight(newValue) {
        this.a3.set(newValue);
    }
    get defaultThumbImage() {
        return this.b3.get();
    }
    set defaultThumbImage(newValue) {
        this.b3.set(newValue);
    }
    get thumbImage() {
        return this.c3.get();
    }
    set thumbImage(newValue) {
        this.c3.set(newValue);
    }
    get appImage() {
        return this.d3.get();
    }
    set appImage(newValue) {
        this.d3.set(newValue);
    }
    get lineCount() {
        return this.e3.get();
    }
    set lineCount(newValue) {
        this.e3.set(newValue);
    }
    aboutToAppear() {
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
                this.formWidth = t;
                break;
            case FormType.TYPE_MID:
                this.formWidth = u;
                break;
            default:
                this.formWidth = b1;
                break;
        }
        this.initCardStyle();
    }
    formWidthChange() {
        this.initCardStyle();
    }
    initCardScale(j2, k2, l2) {
        let m2 = j2;
        if (j2 > m) {
            m2 = m;
        }
        else if (j2 < o) {
            m2 = o;
        }
        this.cardWidth = k2 * m2;
        this.formHeight = l2 * m2;
        this.cardScale = m2;
        console.info(`${i}, ss1 widthScale:${this.cardScale}, cardScale: ${this.cardScale}, cardWidth: ${this.cardWidth}, formHeight: ${this.formHeight}`);
    }
    initCardStyle() {
        console.info(`${i}, ss0 cardScale: ${this.cardScale}, formType: ${this.formType},formWidth: ${this.formWidth}, formHeight: ${this.formHeight}`);
        let i2 = 1;
        switch (this.formType) {
            case FormType.TYPE_BIG:
                this.formStyle = s1;
                i2 = this.formWidth ? this.formWidth / t : 1;
                this.initCardScale(i2, t, t);
                break;
            case FormType.TYPE_MID:
                this.formStyle = t1;
                i2 = this.formWidth ? this.formWidth / u : 1;
                this.initCardScale(i2, u, a1);
                break;
            default:
                this.formStyle = u1;
                i2 = this.formWidth ? this.formWidth / b1 : 1;
                this.initCardScale(i2, b1, c1);
                break;
        }
    }
    ThumbImage(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.thumbImage) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(this.thumbImage);
                        Image.objectFit(ImageFit.Contain);
                        Image.width('100%');
                        Image.aspectRatio(this.getAspectRatio());
                    }, Image);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }
    CardDivider(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Divider.create();
            Divider.height(1);
            Divider.opacity(0.5);
            Divider.padding({
                left: this.formStyle.m2 * this.cardScale,
                right: this.formStyle.m2 * this.cardScale
            });
        }, Divider);
    }
    AppView(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.width('100%');
            Row.padding({
                left: this.formStyle.m2 * this.cardScale,
                right: this.formStyle.m2 * this.cardScale,
                top: this.formStyle.o2 * this.cardScale,
                bottom: this.formStyle.n2 * this.cardScale,
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.appImage);
            Image.width(this.formStyle.i2 * this.cardScale);
            Image.height(this.formStyle.i2 * this.cardScale);
            Image.objectFit(ImageFit.Fill);
            Image.alt({ "id": -1, "type": 20000, params: ['sys.media.ohos_app_icon'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.borderRadius(2);
        }, Image);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.contentFormData?.appName ? this.contentFormData?.appName : ' ');
            Text.fontSize(this.formStyle.g2 * this.cardScale);
            Text.fontColor(h1);
            Text.maxLines(1);
            Text.lineHeight(this.formStyle.h2 * this.cardScale);
            Text.margin({ left: this.formStyle.l2 * this.cardScale });
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.constraintSize({ minWidth: this.getTextSize('appName', this.contentFormData?.appName) });
            Text.backgroundColor(this.getTextBackground(this.contentFormData?.appName));
            Text.fontWeight(FontWeight.Regular);
            Text.borderRadius(this.contentFormData?.title === '' ? 0 : i3);
        }, Text);
        Text.pop();
        Row.pop();
    }
    TitleText(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.contentFormData?.title);
            Text.fontSize(this.formStyle.z1 * this.cardScale);
            Text.fontColor(l1);
            Text.fontWeight(FontWeight.Bold);
            Text.maxLines(1);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.height(this.formStyle.a2 * this.cardScale);
            Text.margin({ top: this.formStyle.b2 * this.cardScale });
            Text.constraintSize({ minWidth: this.getTextSize('title', this.contentFormData?.title) });
            Text.backgroundColor(this.getTextBackground(this.contentFormData?.title));
            Text.borderRadius(this.contentFormData?.title === '' ? 0 : i3);
        }, Text);
        Text.pop();
    }
    Card4x4(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.size({ width: '100%', height: this.formHeight });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.thumbImage ? this.thumbImage : this.defaultThumbImage);
            Image.objectFit(ImageFit.Cover);
            Image.width('100%');
            Image.height(this.formStyle.w1 ? this.formStyle.w1 * this.cardScale : n1);
            Image.backgroundColor(this.thumbImage ? f1 : i1);
        }, Image);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.alignItems(HorizontalAlign.Start);
            Column.width('100%');
            Column.padding({
                left: this.formStyle.m2 * this.cardScale,
                right: this.formStyle.m2 * this.cardScale
            });
            Column.margin({ bottom: this.formStyle.f2 * this.cardScale });
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.TitleText.bind(this)();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.contentFormData?.description);
            Text.fontSize(this.formStyle.c2 * this.cardScale);
            Text.fontColor(m1);
            Text.fontWeight(FontWeight.Regular);
            Text.maxLines(1);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.constraintSize({ minWidth: this.getTextSize('description', this.contentFormData?.description) });
            Text.height(this.formStyle.d2 * this.cardScale);
            Text.margin({ top: this.formStyle.e2 * this.cardScale });
            Text.backgroundColor(this.getTextBackground(this.contentFormData?.description));
            Text.fontWeight(FontWeight.Regular);
            Text.borderRadius(this.contentFormData?.description ? 0 : i3);
        }, Text);
        Text.pop();
        Column.pop();
        this.CardDivider.bind(this)();
        this.AppView.bind(this)();
        Column.pop();
    }
    DescriptionView(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.contentFormData?.description ? this.contentFormData?.description : ' ', { controller: this.controller });
            Text.fontColor(m1);
            Text.fontWeight(FontWeight.Regular);
            Text.maxLines(2);
            Text.fontWeight(FontWeight.Regular);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.lineHeight((this.lineCount === 1 ?
                (this.formStyle.t2 ? this.formStyle.t2 :
                    this.formStyle.d2) : this.formStyle.d2) * this.cardScale);
            Text.fontSize((this.lineCount === 1 ? (this.formStyle.s2 ? this.formStyle.s2 :
                this.formStyle.c2) : this.formStyle.c2) * this.cardScale);
            Text.constraintSize({ minWidth: this.getTextSize('description', this.contentFormData?.description) });
            Text.backgroundColor(this.getTextBackground(this.contentFormData?.description));
            Text.onAreaChange(() => {
                let h2 = this.controller.getLayoutManager();
                this.lineCount = h2.getLineCount();
            });
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
            }
            else if (this.thumbImage) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.width('100%');
                        Row.padding({
                            left: this.formStyle.m2 * this.cardScale,
                            right: this.formStyle.m2 * this.cardScale
                        });
                        Row.layoutWeight(1);
                        Row.margin({ bottom: this.formStyle.f2 * this.cardScale });
                        Row.alignItems(VerticalAlign.Top);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create({ space: this.formStyle.e2 * this.cardScale });
                        Column.layoutWeight(1);
                        Column.alignItems(HorizontalAlign.Start);
                    }, Column);
                    this.TitleText.bind(this)();
                    this.DescriptionView.bind(this)();
                    Column.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.width(this.formStyle.v1 ? this.formStyle.v1 * this.cardScale : 0);
                        Column.height(this.formStyle.w1 ? this.formStyle.w1 * this.cardScale : 0);
                        Column.margin({
                            left: this.formStyle.q2 ? this.formStyle.q2 * this.cardScale : 0,
                            top: this.formStyle.b2 * this.cardScale
                        });
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(this.thumbImage);
                        Image.width('100%');
                        Image.layoutWeight(1);
                        Image.objectFit(ImageFit.Cover);
                        Image.borderRadius(4);
                    }, Image);
                    Column.pop();
                    Row.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create({ space: this.formStyle.e2 * this.cardScale });
                        Column.width('100%');
                        Column.padding({
                            left: this.formStyle.m2 * this.cardScale,
                            right: this.formStyle.m2 * this.cardScale
                        });
                        Column.layoutWeight(1);
                        Column.alignItems(HorizontalAlign.Start);
                        Column.margin({ bottom: this.formStyle.f2 * this.cardScale });
                    }, Column);
                    this.TitleText.bind(this)();
                    this.DescriptionView.bind(this)();
                    Column.pop();
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
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.width('100%');
                        Column.padding({
                            left: this.formStyle.m2 * this.cardScale,
                            right: this.formStyle.m2 * this.cardScale
                        });
                        Column.layoutWeight(1);
                        Column.alignItems(HorizontalAlign.Start);
                        Column.margin({ bottom: this.formStyle.f2 * this.cardScale });
                    }, Column);
                    this.TitleText.bind(this)();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.contentFormData?.description);
                        Text.fontColor(m1);
                        Text.fontWeight(FontWeight.Regular);
                        Text.maxLines(1);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.height(this.formStyle.d2 * this.cardScale);
                        Text.margin({ top: this.formStyle.e2 * this.cardScale });
                        Text.fontSize(this.formStyle.c2 * this.cardScale);
                        Text.constraintSize({ minWidth: this.getTextSize('description', this.contentFormData?.description) });
                        Text.backgroundColor(this.getTextBackground(this.contentFormData?.description));
                        Text.fontWeight(FontWeight.Regular);
                    }, Text);
                    Text.pop();
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
            Column.borderRadius(this.formStyle.j2);
            Column.clip(true);
            Column.backgroundColor(f1);
            Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK, { colorMode: ThemeColorMode.LIGHT, adaptiveColor: AdaptiveColor.DEFAULT, scale: 1.0 });
            Column.shadow(ShadowStyle.OUTER_DEFAULT_SM);
            Column.width(this.cardWidth);
            Column.onClick(() => {
                if (!this.contentFormData?.linkUri) {
                    console.warn(`${i}, linkUri is null`);
                    return;
                }
                try {
                    let context = getContext(this);
                    context.openLink(this.contentFormData?.linkUri, { appLinkingOnly: false, parameters: {} });
                }
                catch (err) {
                    let error = err;
                    console.error(`${i}, Failed to openLink, code is ${error.code}, message is ${error.message}`);
                }
            });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.formType === FormType.TYPE_BIG) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.Card4x4.bind(this)();
                });
            }
            else if (this.formType === FormType.TYPE_MID) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.Card4x2.bind(this)();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.Card2x1.bind(this)();
                });
            }
        }, If);
        If.pop();
        Column.pop();
    }
    async getPixelMap(e2, callback) {
        let f2 = undefined;
        try {
            f2 = image.createImageSource(e2.buffer);
            let g2 = await f2?.createPixelMap();
            callback(g2);
        }
        catch (err) {
            let error = err;
            console.info(`${i}, Failed to create pixelMap, code is ${error.code}, message is ${error.message}`);
        }
    }
    transStringToUint8Array(c2) {
        const arr = c2.split(',');
        const d2 = new Uint8Array(arr.length);
        arr.forEach((value, index) => {
            d2[index] = parseInt(value);
        });
        return d2;
    }
    createPixelMap() {
        let b2 = this.transStringToUint8Array(j);
        this.getPixelMap(b2, (pixelMap) => {
            this.defaultThumbImage = pixelMap;
        });
        if (this.contentFormData && this.contentFormData?.thumbData) {
            if (!(this.contentFormData?.thumbData instanceof Uint8Array)) {
                console.error(`${i}, thumbData is not Uint8Array`);
                return;
            }
            this.getPixelMap(this.contentFormData?.thumbData, (pixelMap) => {
                this.thumbImage = pixelMap;
            });
        }
        if (this.contentFormData && this.contentFormData?.appIcon) {
            if (!(this.contentFormData?.appIcon instanceof Uint8Array)) {
                console.error(`${i}, appIcon is not Uint8Array`);
                return;
            }
            this.getPixelMap(this.contentFormData?.appIcon, (pixelMap) => {
                this.appImage = pixelMap;
            });
        }
    }
    getAspectRatio() {
        let w1 = this.thumbImage?.getImageInfoSync().size;
        let z1 = this.formType === FormType.TYPE_MID ? u : b1;
        let a2 = this.formType === FormType.TYPE_MID ? o1 : q1;
        if (w1) {
            if ((w1.width / w1.height) > (z1 / (a2 * o))) {
                return z1 / (a2 * o);
            }
            if ((w1.width / w1.height) < (z1 / (a2 * m))) {
                return z1 / (a2 * m);
            }
            return w1.width / w1.height;
        }
        return 1;
    }
    getTextBackground(text) {
        if (text && text.length > 0) {
            return f1;
        }
        return j1;
    }
    getTextSize(textType, text) {
        if (textType === 'title') {
            if (text === '' || text === undefined || text === null) {
                if (this.formType === FormType.TYPE_SMALL) {
                    return g3;
                }
                return d1;
            }
            return e1;
        }
        if (textType === 'appName') {
            if (text === '' || text === undefined || text === null) {
                if (this.formType === FormType.TYPE_SMALL) {
                    return h3;
                }
                return f3;
            }
            return e1;
        }
        return '100%';
    }
    getThumbViewConstraintSize() {
        if (this.contentFormData?.title !== '') {
            return { maxHeight: this.formHeight, minHeight: this.formHeight };
        }
        else {
            return {
                maxHeight: this.formHeight * m,
                minHeight: this.formHeight * o
            };
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}

export default { ContentFormCard, FormType };