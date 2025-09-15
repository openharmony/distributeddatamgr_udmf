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
    export class Cleaner {
        static { loadLibraryWithPermissionCheck("unifieddatachannel_ani", "@ohos.data.unifiedDataChannel") }
        static callback(cleaner: Cleaner): void {
            cleaner.clean()
        }
        constructor(targetPtr: long) {
            this.targetPtr = targetPtr
        }

        native clean(): void

        private targetPtr: long = 0
    }
    class FinalizationAgent<T extends Object> {
        constructor(obj: T, ptr: long) {
            this.register(obj, ptr);
        }

        register(obj: T, ptr: long): void {
            this.unregisterToken = {};
            this.cleaner = new Cleaner(ptr);
            finalizer.register(obj, this.cleaner!, this.unregisterToken);
        }

        unregister(): void {
            finalizer.unregister(this.unregisterToken);
        }

        private cleaner: Cleaner | null = null;
        private unregisterToken: object;
    }

    let finalizer = new FinalizationRegistry<Cleaner>(Cleaner.callback)
    export class UnifiedRecord {
        static { loadLibraryWithPermissionCheck("unifieddatachannel_ani", "@ohos.data.unifiedDataChannel") }

        constructor(type?: string, value?: ValueType) {
            if (type == undefined) {
                this.initRecordWithOutTypeValue();
            } else {
                this.init(type, value);
            }
            this.registerCleaner();
        }

        registerCleaner(): void {
            this.fzAgent = new FinalizationAgent<UnifiedRecord>(this, this.nativePtr);
        }

        unregisterCleaner(): void {
            this.fzAgent.unregister();
        }
        setNativePtr(context: long) {
            this.nativePtr = context;
        }

        private fzAgent: FinalizationAgent<UnifiedRecord>;
        native init(type: string, value: ValueType): void;
        native initRecordWithOutTypeValue(): void;
        private nativePtr: long = 0;
    }

    export class UnifiedData {
        static { loadLibraryWithPermissionCheck("unifieddatachannel_ani", "@ohos.data.unifiedDataChannel") }
        constructor(record?: UnifiedRecord) {
            if (record == undefined) {
                this.initDataWithOutRecord();
            } else {
                this.initData(record);
            }
            this.registerCleaner();
        }

        registerCleaner(): void {
            this.fzAgent = new FinalizationAgent<UnifiedData>(this, this.nativePtr);
        }

        unregisterCleaner(): void {
            this.fzAgent.unregister();
        }
        native initData(record: UnifiedRecord): void;
        native initDataWithOutRecord(): void;
        native getRecords(): Array<UnifiedRecord>;

        getNativePtr(): long {
            return this.nativePtr;
        }

        private fzAgent: FinalizationAgent<UnifiedData>;
        private nativePtr: long = 0;
    }
}