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
import image from '@ohos.multimedia.image';
export var FormType;
(function (FormType) {
    FormType[FormType["TYPE_BIG"] = 0] = "TYPE_BIG";
    FormType[FormType["TYPE_MID"] = 1] = "TYPE_MID";
    FormType[FormType["TYPE_SMALL"] = 2] = "TYPE_SMALL";
})(FormType || (FormType = {}));
const i = 'udmf.ContentFormCard';
const j =
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
const m = 1.2;
const o = 0.8;
const t = 200;
const u = 200;
const a1 = 100;
const b1 = 100;
const c1 = 60;
const d1 = '#E6FFFFFF';
const e1 = '#1A999999';
const f1 = '#66000000';
const g1 = '#CCCCCC';
const h1 = {
    l1: 100,
    m1: 10,
    n1: 12,
    o1: 16,
    q1: 6.5,
    s1: 12,
    t1: 10,
    u1: 6
};
const i1 = {
    l1: 50,
    m1: 10,
    n1: 12,
    o1: 16,
    q1: 6.5,
    s1: 12,
    t1: 10,
    u1: 6
};
const j1 = {
    l1: 30,
    m1: 8,
    n1: 8,
    o1: 8,
    q1: 4,
    s1: 10,
    t1: 5,
    u1: 4
};

export class ContentFormCard extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.formType = FormType.TYPE_MID;
        this.contentFormData = undefined;
        this.formWidth = 0;
        this.formHeight = 0;
        this.formStyle = i1;
        this.v1 = new ObservedPropertyObjectPU(undefined, this, "defaultThumbImage");
        this.w1 = new ObservedPropertyObjectPU(undefined, this, "thumbImage");
        this.z1 = new ObservedPropertyObjectPU(undefined, this, "appImage");
        this.a2 = new ObservedPropertySimplePU(1, this, "cardScale");
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        if (params.formType !== undefined) {
            this.formType = params.formType;
        }
        if (params.contentFormData !== undefined) {
            this.contentFormData = params.contentFormData;
        }
        if (params.formWidth !== undefined) {
            this.formWidth = params.formWidth;
        }
        if (params.formHeight !== undefined) {
            this.formHeight = params.formHeight;
        }
        if (params.formStyle !== undefined) {
            this.formStyle = params.formStyle;
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
        if (params.cardScale !== undefined) {
            this.cardScale = params.cardScale;
        }
    }

    updateStateVars(params) {
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.v1.purgeDependencyOnElmtId(rmElmtId);
        this.w1.purgeDependencyOnElmtId(rmElmtId);
        this.z1.purgeDependencyOnElmtId(rmElmtId);
        this.a2.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.v1.aboutToBeDeleted();
        this.w1.aboutToBeDeleted();
        this.z1.aboutToBeDeleted();
        this.a2.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get defaultThumbImage() {
        return this.v1.get();
    }

    set defaultThumbImage(newValue) {
        this.v1.set(newValue);
    }

    get thumbImage() {
        return this.w1.get();
    }

    set thumbImage(newValue) {
        this.w1.set(newValue);
    }

    get appImage() {
        return this.z1.get();
    }

    set appImage(newValue) {
        this.z1.set(newValue);
    }

    get cardScale() {
        return this.a2.get();
    }

    set cardScale(newValue) {
        this.a2.set(newValue);
    }

    aboutToAppear() {
        this.initCardStyle();
        this.createPixelMap();
    }

    initCardScale(s1) {
        this.cardScale = s1;
        if (s1 > m) {
            this.cardScale = m;
        }
        if (s1 < o) {
            this.cardScale = o;
        }
    }

    initCardStyle() {
        if (this.formWidth === 0 && this.formHeight === 0) {
            if (this.formType === FormType.TYPE_BIG) {
                this.formWidth = t;
                this.formHeight = t;
            }
            if (this.formType === FormType.TYPE_MID) {
                this.formWidth = u;
                this.formHeight = a1;
            }
            if (this.formType === FormType.TYPE_SMALL) {
                this.formWidth = b1;
                this.formHeight = c1;
            }
        }
        let q1 = 1;
        switch (this.formType) {
            case FormType.TYPE_BIG:
                this.formStyle = h1;
                q1 = this.formWidth / t;
                this.initCardScale(q1);
                this.formWidth = t * this.cardScale;
                this.formHeight = t * this.cardScale;
                break;
            case FormType.TYPE_MID:
                this.formStyle = i1;
                q1 = this.formWidth / u;
                this.initCardScale(q1);
                this.formWidth = u * this.cardScale;
                this.formHeight = a1 * this.cardScale;
                break;
            case FormType.TYPE_SMALL:
                this.formStyle = j1;
                q1 = this.formWidth / b1;
                this.initCardScale(q1);
                this.formWidth = b1 * this.cardScale;
                this.formHeight = c1 * this.cardScale;
                break;
            default:
                break;
        }
        console.info(`${i}, cardScale: ${this.cardScale}`);
    }

    async getPixelMap(n1, callback) {
        let o1 = undefined;
        try {
            o1 = image.createImageSource(n1.buffer);
            let p1 = await o1?.createPixelMap();
            callback(p1);
        } catch (err) {
            let error = err;
            console.info(`${i}, Failed to create pixelMap, code is ${error.code}, message is ${error.message}`);
        }
    }

    transStringToUint8Array(l1) {
        const arr = l1.split(',');
        const m1 = new Uint8Array(arr.length);
        arr.forEach((value, index) => {
            m1[index] = parseInt(value);
        });
        return m1;
    }

    async createPixelMap() {
        let k1 = this.transStringToUint8Array(j);
        this.getPixelMap(k1, (pixelMap) => {
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

    ThumbImage(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create({ alignContent: Alignment.Bottom });
            Stack.width('100%');
            Stack.borderRadius({ topLeft: this.formStyle.o1, topRight: this.formStyle.o1 });
            Stack.layoutWeight(1);
            Stack.clip(true);
            Stack.backgroundColor(this.thumbImage ? d1 : g1);
        }, Stack);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.thumbImage) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(this.thumbImage);
                        Image.objectFit(ImageFit.Contain);
                        Image.width('100%');
                        Image.height('100%');
                    }, Image);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(this.defaultThumbImage);
                        Image.objectFit(ImageFit.Contain);
                        Image.width('100%');
                    }, Image);
                });
            }
        }, If);
        If.pop();
        Stack.pop();
    }

    CardDivider(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Divider.create();
            Divider.height(1);
            Divider.color(e1);
            Divider.padding({
                left: this.formStyle.s1 * this.cardScale,
                right: this.formStyle.s1 * this.cardScale
            });
        }, Divider);
    }

    AppView(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.width('100%');
            Row.padding({
                left: this.formStyle.s1 * this.cardScale,
                right: this.formStyle.s1 * this.cardScale,
                bottom: this.formStyle.t1 * this.cardScale,
                top: this.formStyle.u1 * this.cardScale
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.appImage);
            Image.width(this.formStyle.n1 * this.cardScale);
            Image.height(this.formStyle.n1 * this.cardScale);
            Image.objectFit(ImageFit.Fill);
            Image.alt({
                "id": -1,
                "type": 20000,
                params: ['sys.media.ohos_app_icon'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            });
        }, Image);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.contentFormData?.appName);
            Text.fontSize(this.formStyle.m1 * this.cardScale);
            Text.fontColor(f1);
            Text.maxLines(1);
            Text.margin({ left: this.formStyle.q1 * this.cardScale });
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
        }, Text);
        Text.pop();
        Row.pop();
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.borderRadius(this.formStyle.o1);
            Column.backgroundColor(d1);
            Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK,
                { colorMode: ThemeColorMode.LIGHT, adaptiveColor: AdaptiveColor.DEFAULT, scale: 1.0 });
            Column.shadow(ShadowStyle.OUTER_DEFAULT_SM);
            Column.size({ width: this.formWidth, height: this.formHeight });
            Column.onClick(() => {
                if (!this.contentFormData?.linkUri) {
                    console.warn(`${i}, linkUri is null`);
                    return;
                }
                try {
                    let context = getContext(this);
                    context.openLink(this.contentFormData?.linkUri, { appLinkingOnly: false, parameters: {} });
                } catch (err) {
                    let error = err;
                    console.error(`${i}, Failed to openLink, code is ${error.code}, message is ${error.message}`);
                }
            });
        }, Column);
        this.ThumbImage.bind(this)();
        this.CardDivider.bind(this)();
        this.AppView.bind(this)();
        Column.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export default { ContentFormCard, FormType };
