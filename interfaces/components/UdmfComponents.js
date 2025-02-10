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
const e2 = 1.2;
const f2 = 0.8;
const j = 200;
const m = 200;
const o = 100;
const t = 100;
const u = 60;
const s1 = '#E6FFFFFF';
const t1 = '#1A999999';
const u1 = '#66000000';
const v1 = '#1A000000';
const w1 = '#F0F0F0';
const a1 = {
    z1: 100,
    g1: 10,
    l1: 12,
    m1: 16,
    a2: 6.5,
    b2: 12,
    c2: 10,
    d2: 6
};
const b1 = {
    z1: 50,
    g1: 10,
    l1: 12,
    m1: 16,
    a2: 6.5,
    b2: 12,
    c2: 10,
    d2: 6
};
const c1 = {
    z1: 30,
    g1: 8,
    l1: 8,
    m1: 8,
    a2: 4,
    b2: 10,
    c2: 5,
    d2: 4
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
        this.formStyle = b1;
        this.n1 = new ObservedPropertyObjectPU(undefined, this, "thumbImage");
        this.o1 = new ObservedPropertyObjectPU(undefined, this, "appImage");
        this.q1 = new ObservedPropertySimplePU(1, this, "cardScale");
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
        this.n1.purgeDependencyOnElmtId(rmElmtId);
        this.o1.purgeDependencyOnElmtId(rmElmtId);
        this.q1.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.n1.aboutToBeDeleted();
        this.o1.aboutToBeDeleted();
        this.q1.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get thumbImage() {
        return this.n1.get();
    }

    set thumbImage(newValue) {
        this.n1.set(newValue);
    }

    get appImage() {
        return this.o1.get();
    }

    set appImage(newValue) {
        this.o1.set(newValue);
    }

    get cardScale() {
        return this.q1.get();
    }

    set cardScale(newValue) {
        this.q1.set(newValue);
    }

    aboutToAppear() {
        this.initCardStyle();
        this.createPixelMap();
    }

    initCardScale(g2) {
        this.cardScale = g2;
        if (g2 > e2) {
            this.cardScale = e2;
        }
        if (g2 < f2) {
            this.cardScale = f2;
        }
    }

    initCardStyle() {
        if (this.formWidth === 0 && this.formHeight === 0) {
            if (this.formType === FormType.TYPE_BIG) {
                this.formWidth = j;
                this.formHeight = j;
            }
            if (this.formType === FormType.TYPE_MID) {
                this.formWidth = m;
                this.formHeight = o;
            }
            if (this.formType === FormType.TYPE_SMALL) {
                this.formWidth = t;
                this.formHeight = u;
            }
        }
        let g1 = 1;
        switch (this.formType) {
            case FormType.TYPE_BIG:
                this.formStyle = a1;
                g1 = this.formWidth / j;
                this.initCardScale(g1);
                this.formWidth = j * this.cardScale;
                this.formHeight = j * this.cardScale;
                break;
            case FormType.TYPE_MID:
                this.formStyle = b1;
                g1 = this.formWidth / m;
                this.initCardScale(g1);
                this.formWidth = m * this.cardScale;
                this.formHeight = o * this.cardScale;
                break;
            case FormType.TYPE_SMALL:
                this.formStyle = c1;
                g1 = this.formWidth / t;
                this.initCardScale(g1);
                this.formWidth = t * this.cardScale;
                this.formHeight = u * this.cardScale;
                break;
            default:
                break;
        }
        console.info(`${i}, cardScale: ${this.cardScale}`);
    }

    async getPixelMap(d1, callback) {
        let e1 = undefined;
        try {
            e1 = image.createImageSource(d1.buffer);
            let f1 = await e1?.createPixelMap();
            callback(f1);
        } catch (err) {
            let error = err;
            console.info(`${i}, Failed to create pixelMap, code is ${error.code}, message is ${error.message}`);
        }
    }

    async createPixelMap() {
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

    CardDivider(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Divider.create();
            Divider.height(1);
            Divider.color(t1);
            Divider.padding({
                left: this.formStyle.b2 * this.cardScale,
                right: this.formStyle.b2 * this.cardScale
            });
        }, Divider);
    }

    AppView(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.width('100%');
            Row.padding({
                left: this.formStyle.b2 * this.cardScale,
                right: this.formStyle.b2 * this.cardScale,
                bottom: this.formStyle.c2 * this.cardScale,
                top: this.formStyle.d2 * this.cardScale
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.appImage);
            Image.width(this.formStyle.l1 * this.cardScale);
            Image.height(this.formStyle.l1 * this.cardScale);
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
            Text.fontSize(this.formStyle.g1 * this.cardScale);
            Text.fontColor(u1);
            Text.maxLines(1);
            Text.margin({ left: this.formStyle.a2 * this.cardScale });
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
        }, Text);
        Text.pop();
        Row.pop();
    }

    ThumbImageNull(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create();
            Text.textAlign(TextAlign.Center);
            Text.backgroundColor(w1);
            Text.width('100%');
            Text.borderRadius({ topLeft: this.formStyle.m1, topRight: this.formStyle.m1 });
            Text.layoutWeight(1);
        }, Text);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolSpan.create({
                "id": -1,
                "type": 40000,
                params: ['sys.symbol.ohos_photo'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            });
            SymbolSpan.fontSize(this.formStyle.z1 * this.cardScale);
            SymbolSpan.fontColor([v1]);
        }, SymbolSpan);
        Text.pop();
    }

    Card2x1(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.size({ width: '100%', height: '100%' });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.thumbImage) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(this.thumbImage);
                        Image.objectFit(ImageFit.Fill);
                        Image.width('100%');
                        Image.borderRadius({ topLeft: this.formStyle.m1, topRight: this.formStyle.m1 });
                        Image.layoutWeight(1);
                    }, Image);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.ThumbImageNull.bind(this)();
                });
            }
        }, If);
        If.pop();
        this.CardDivider.bind(this)();
        this.AppView.bind(this)();
        Column.pop();
    }

    Card4x2(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.size({ width: '100%', height: '100%' });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.contentFormData?.thumbData) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(this.thumbImage);
                        Image.objectFit(ImageFit.Fill);
                        Image.width('100%');
                        Image.borderRadius({ topLeft: this.formStyle.m1, topRight: this.formStyle.m1 });
                        Image.layoutWeight(1);
                    }, Image);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.ThumbImageNull.bind(this)();
                });
            }
        }, If);
        If.pop();
        this.CardDivider.bind(this)();
        this.AppView.bind(this)();
        Column.pop();
    }

    Card4x4(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.size({ width: '100%', height: '100%' });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.contentFormData?.thumbData) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(this.thumbImage);
                        Image.objectFit(ImageFit.Fill);
                        Image.width('100%');
                        Image.borderRadius({ topLeft: this.formStyle.m1, topRight: this.formStyle.m1 });
                        Image.layoutWeight(1);
                    }, Image);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.ThumbImageNull.bind(this)();
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
            Column.borderRadius(this.formStyle.m1);
            Column.backgroundColor(s1);
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.formType === FormType.TYPE_BIG) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.Card4x4.bind(this)();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.formType === FormType.TYPE_MID) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.Card4x2.bind(this)();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.formType === FormType.TYPE_SMALL) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.Card2x1.bind(this)();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Column.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export default { ContentFormCard, FormType };