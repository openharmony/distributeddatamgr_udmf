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
import image from "@ohos.multimedia.image";
import Want from "@ohos.app.ability.Want";

type ValueType = number | string | boolean | image.PixelMap | Want | ArrayBuffer | object | null | undefined;

 export default namespace unifiedDataChannel {

    export class UnifiedRecord {
        static { loadLibrary("unifieddatachannel_ani") }

        constructor(type?: string, value?: ValueType) {
            if (type == undefined || value == undefined) {
                this.init("default", 0)
            } else {
                this.init(type, value)
            }
        }

        setNativePtr(context: long) {
            this.nativePtr = context
        }

        native init(type: string, value: ValueType): void;
        private nativePtr: long = 0;
    }

    export class UnifiedData {
        static { loadLibrary("unifieddatachannel_ani") }
        constructor(record?: UnifiedRecord) {
            if (record == undefined) {
                this.initData(new UnifiedRecord("default", 0))
            } else {
                this.initData(record)
            }
        }

        native initData(record: UnifiedRecord): void;
        native getRecords(): Array<UnifiedRecord>;

        getNativePtr(): long {
            return this.nativePtr;
        }

        private nativePtr: long = 0;
    }
}


