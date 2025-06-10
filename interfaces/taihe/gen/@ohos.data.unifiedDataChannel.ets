import {AsyncCallback} from '@ohos.base';
import {BusinessError} from '@ohos.base';
import Want from '@ohos.app.ability.Want';
import image from '@ohos.multimedia.image';
export namespace unifiedDataChannel {

    static { loadLibrary("udmf_taihe_native.z") }
    native function CreateSummary_inner(): Summary;
    native function CreateUnifiedData_inner(): UnifiedData;
    native function CreateUnifiedDataWithParams_inner(unifiedRecord: AllRecords): UnifiedData;
    native function CreateUnifiedRecord_inner(): UnifiedRecord;
    native function CreateUnifiedRecordWithParams_inner(type: string, value: ValueType): UnifiedRecord;
    native function CreateUnifiedFile_inner(): File;
    native function CreateFolder_inner(): Folder;
    native function CreateAudio_inner(): Audio;
    native function CreateVideo_inner(): Video;
    native function CreateImage_inner(): Image;
    native function CreateText_inner(): Text;
    native function CreateHtml_inner(): HTML;
    native function CreateHyperlink_inner(): Hyperlink;
    native function CreatePlainText_inner(): PlainText;
    native function CreateSystemDefinedRecord_inner(): SystemDefinedRecord;
    native function CreateSystemDefinedForm_inner(): SystemDefinedForm;
    native function CreateSystemDefinedAppItem_inner(): SystemDefinedAppItem;
    native function CreateSystemDefinedPixelMap_inner(): SystemDefinedPixelMap;
    native function InsertDataSync_inner(options: Options, data: UnifiedData): void;
    native function QueryDataSync_inner(options: Options): Array<UnifiedData>;
    export function createSummary(): Summary {
        return CreateSummary_inner();
    }
    export function insertDataSync(options: Options, data: UnifiedData): void {
        return InsertDataSync_inner(options, data);
    }
    export function insertData(options: Options, data: UnifiedData): Promise<void> {
        return new Promise<void>((resolve, reject): void => {
            taskpool.execute((): void => {
                return InsertDataSync_inner(options, data);
            })
            .then((ret: NullishType): void => {
                resolve(ret as undefined);
            })
            .catch((ret: NullishType): void => {
                reject(ret as Error);
            });
        });
    }
    export function insertData(options: Options, data: UnifiedData, callback: AsyncCallback<void>): void {
        taskpool.execute((): void => {
            return InsertDataSync_inner(options, data);
        })
        .then((ret: NullishType): void => {
            callback(new BusinessError(), ret as undefined);
        })
        .catch((ret: NullishType): void => {
            let data: undefined;
            callback(ret as BusinessError, data);
        });
    }
    export function queryDataSync(options: Options): Array<UnifiedData> {
        return QueryDataSync_inner(options);
    }
    export function queryData(options: Options): Promise<Array<UnifiedData>> {
        return new Promise<Array<UnifiedData>>((resolve, reject): void => {
            taskpool.execute((): Array<UnifiedData> => {
                return QueryDataSync_inner(options);
            })
            .then((ret: NullishType): void => {
                resolve(ret as Array<UnifiedData>);
            })
            .catch((ret: NullishType): void => {
                reject(ret as Error);
            });
        });
    }
    export function queryData(options: Options, callback: AsyncCallback<Array<UnifiedData>>): void {
        taskpool.execute((): Array<UnifiedData> => {
            return QueryDataSync_inner(options);
        })
        .then((ret: NullishType): void => {
            callback(new BusinessError(), ret as Array<UnifiedData>);
        })
        .catch((ret: NullishType): void => {
            let data: Array<UnifiedData>;
            callback(ret as BusinessError, data);
        });
    }
    export enum Intention {
        DATA_HUB = "DataHub",
        DRAG = "Drag",
    }
    export enum ProgressIndicator {
        NONE = 0,
        DEFAULT = 1,
    }
    export enum ListenerStatus {
        FINISHED = 0,
        PROCESSING = 1,
        CANCELED = 2,
        INNER_ERROR = 200,
        INVALID_PARAMETERS = 201,
        DATA_NOT_FOUND = 202,
        SYNC_FAILED = 203,
        COPY_FILE_FAILED = 204,
    }
    export enum FileConflictOptions {
        OVERWRITE = 0,
        SKIP = 1,
    }
    export type ValueType = double | string | boolean | ArrayBuffer | null | undefined | (image.PixelMap | Want | object);
    export type DetailsValue = double | string | Uint8Array;
    export type AllRecords = File | UnifiedRecord;
    export type UnifiedDataOrNull = UnifiedData | null;
    export interface Options {
        intention: (Intention | undefined);
        key: (string | undefined);
    }
    export interface ProgressInfo {
        progress: double;
        status: ListenerStatus;
    }
    export interface GetDataParams {
        progressIndicator: ProgressIndicator;
        dataProgressListener: ((arg_0: ProgressInfo, arg_1: UnifiedDataOrNull) => void);
        destUri: (string | undefined);
        fileConflictOptions: (FileConflictOptions | undefined);
    }
    class Options_inner implements Options {
        intention: (Intention | undefined);
        key: (string | undefined);
        constructor(intention: (Intention | undefined), key: (string | undefined)) {
            this.intention = intention;
            this.key = key;
        }
    }
    export class Summary {
        summary: Record<string, double>;
        totalSize: double;
        constructor(summary: Record<string, double>, totalSize: double) {
            this.summary = summary;
            this.totalSize = totalSize;
        }
    }
    class ProgressInfo_inner implements ProgressInfo {
        progress: double;
        status: ListenerStatus;
        constructor(progress: double, status: ListenerStatus) {
            this.progress = progress;
            this.status = status;
        }
    }
    class GetDataParams_inner implements GetDataParams {
        progressIndicator: ProgressIndicator;
        dataProgressListener: ((arg_0: ProgressInfo, arg_1: UnifiedDataOrNull) => void);
        destUri: (string | undefined);
        fileConflictOptions: (FileConflictOptions | undefined);
        constructor(progressIndicator: ProgressIndicator, dataProgressListener: ((arg_0: ProgressInfo, arg_1: UnifiedDataOrNull) => void), destUri: (string | undefined), fileConflictOptions: (FileConflictOptions | undefined)) {
            this.progressIndicator = progressIndicator;
            this.dataProgressListener = dataProgressListener;
            this.destUri = destUri;
            this.fileConflictOptions = fileConflictOptions;
        }
    }
    export class UnifiedData {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { UnifiedData._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            UnifiedData._registry.register(this, this._data_ptr)
        }
        constructor() {
            let temp = CreateUnifiedData_inner() as UnifiedData;
            this._data_ptr = temp._data_ptr;
            this._vtbl_ptr = temp._vtbl_ptr;
        }
        constructor(unifiedRecord: AllRecords) {
            let temp = CreateUnifiedDataWithParams_inner(unifiedRecord) as UnifiedData;
            this._data_ptr = temp._data_ptr;
            this._vtbl_ptr = temp._vtbl_ptr;
        }
        native AddRecord_inner(unifiedRecord: AllRecords): void;
        native GetRecords_inner(): Array<AllRecords>;
        native GetInner_inner(): long;
        addRecord(unifiedRecord: AllRecords): void {
            return this.AddRecord_inner(unifiedRecord);
        }
        getRecords(): Array<AllRecords> {
            return this.GetRecords_inner();
        }
        getInner(): long {
            return this.GetInner_inner();
        }
    }
    export class UnifiedRecord {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { UnifiedRecord._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            UnifiedRecord._registry.register(this, this._data_ptr)
        }
        constructor() {
            let temp = CreateUnifiedRecord_inner() as UnifiedRecord;
            this._data_ptr = temp._data_ptr;
            this._vtbl_ptr = temp._vtbl_ptr;
        }
        constructor(type: string, value: ValueType) {
            let temp = CreateUnifiedRecordWithParams_inner(type, value) as UnifiedRecord;
            this._data_ptr = temp._data_ptr;
            this._vtbl_ptr = temp._vtbl_ptr;
        }
        native GetType_inner(): string;
        native GetValue_inner(): ValueType;
        native GetInner_inner(): long;
        getType(): string {
            return this.GetType_inner();
        }
        getValue(): ValueType {
            return this.GetValue_inner();
        }
        getInner(): long {
            return this.GetInner_inner();
        }
    }
    export class File {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { File._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            File._registry.register(this, this._data_ptr)
        }
        constructor() {
            let temp = CreateUnifiedFile_inner() as File;
            this._data_ptr = temp._data_ptr;
            this._vtbl_ptr = temp._vtbl_ptr;
        }
        native GetType_inner(): string;
        native GetValue_inner(): ValueType;
        native GetUri_inner(): string;
        native SetUri_inner(uri: string): void;
        native GetDetails_inner(): (Record<string, string> | undefined);
        native SetDetails_inner(details: Record<string, string>): void;
        native GetInner_inner(): long;
        getType(): string {
            return this.GetType_inner();
        }
        getValue(): ValueType {
            return this.GetValue_inner();
        }
        get uri(): string {
            return this.GetUri_inner();
        }
        set uri(uri: string) {
            return this.SetUri_inner(uri);
        }
        get details(): (Record<string, string> | undefined) {
            return this.GetDetails_inner();
        }
        set details(details: Record<string, string>) {
            return this.SetDetails_inner(details);
        }
        getInner(): long {
            return this.GetInner_inner();
        }
    }
    export class Folder {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { Folder._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            Folder._registry.register(this, this._data_ptr)
        }
        constructor() {
            let temp = CreateFolder_inner() as Folder;
            this._data_ptr = temp._data_ptr;
            this._vtbl_ptr = temp._vtbl_ptr;
        }
        native GetType_inner(): string;
        native GetValue_inner(): ValueType;
        native GetUri_inner(): string;
        native SetUri_inner(uri: string): void;
        native GetDetails_inner(): (Record<string, string> | undefined);
        native SetDetails_inner(details: Record<string, string>): void;
        native GetFolderUri_inner(): string;
        native SetFolderUri_inner(folderUri: string): void;
        native GetInner_inner(): long;
        getType(): string {
            return this.GetType_inner();
        }
        getValue(): ValueType {
            return this.GetValue_inner();
        }
        get uri(): string {
            return this.GetUri_inner();
        }
        set uri(uri: string) {
            return this.SetUri_inner(uri);
        }
        get details(): (Record<string, string> | undefined) {
            return this.GetDetails_inner();
        }
        set details(details: Record<string, string>) {
            return this.SetDetails_inner(details);
        }
        get folderUri(): string {
            return this.GetFolderUri_inner();
        }
        set folderUri(folderUri: string) {
            return this.SetFolderUri_inner(folderUri);
        }
        getInner(): long {
            return this.GetInner_inner();
        }
    }
    export class Audio {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { Audio._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            Audio._registry.register(this, this._data_ptr)
        }
        constructor() {
            let temp = CreateAudio_inner() as Audio;
            this._data_ptr = temp._data_ptr;
            this._vtbl_ptr = temp._vtbl_ptr;
        }
        native GetType_inner(): string;
        native GetValue_inner(): ValueType;
        native GetUri_inner(): string;
        native SetUri_inner(uri: string): void;
        native GetDetails_inner(): (Record<string, string> | undefined);
        native SetDetails_inner(details: Record<string, string>): void;
        native GetAudioUri_inner(): string;
        native SetAudioUri_inner(audioUri: string): void;
        native GetInner_inner(): long;
        getType(): string {
            return this.GetType_inner();
        }
        getValue(): ValueType {
            return this.GetValue_inner();
        }
        get uri(): string {
            return this.GetUri_inner();
        }
        set uri(uri: string) {
            return this.SetUri_inner(uri);
        }
        get details(): (Record<string, string> | undefined) {
            return this.GetDetails_inner();
        }
        set details(details: Record<string, string>) {
            return this.SetDetails_inner(details);
        }
        get audioUri(): string {
            return this.GetAudioUri_inner();
        }
        set audioUri(audioUri: string) {
            return this.SetAudioUri_inner(audioUri);
        }
        getInner(): long {
            return this.GetInner_inner();
        }
    }
    export class Video {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { Video._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            Video._registry.register(this, this._data_ptr)
        }
        constructor() {
            let temp = CreateVideo_inner() as Video;
            this._data_ptr = temp._data_ptr;
            this._vtbl_ptr = temp._vtbl_ptr;
        }
        native GetType_inner(): string;
        native GetValue_inner(): ValueType;
        native GetUri_inner(): string;
        native SetUri_inner(uri: string): void;
        native GetDetails_inner(): (Record<string, string> | undefined);
        native SetDetails_inner(details: Record<string, string>): void;
        native GetVideoUri_inner(): string;
        native SetVideoUri_inner(videoUri: string): void;
        native GetInner_inner(): long;
        getType(): string {
            return this.GetType_inner();
        }
        getValue(): ValueType {
            return this.GetValue_inner();
        }
        get uri(): string {
            return this.GetUri_inner();
        }
        set uri(uri: string) {
            return this.SetUri_inner(uri);
        }
        get details(): (Record<string, string> | undefined) {
            return this.GetDetails_inner();
        }
        set details(details: Record<string, string>) {
            return this.SetDetails_inner(details);
        }
        get videoUri(): string {
            return this.GetVideoUri_inner();
        }
        set videoUri(videoUri: string) {
            return this.SetVideoUri_inner(videoUri);
        }
        getInner(): long {
            return this.GetInner_inner();
        }
    }
    export class Image {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { Image._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            Image._registry.register(this, this._data_ptr)
        }
        constructor() {
            let temp = CreateImage_inner() as Image;
            this._data_ptr = temp._data_ptr;
            this._vtbl_ptr = temp._vtbl_ptr;
        }
        native GetType_inner(): string;
        native GetValue_inner(): ValueType;
        native GetUri_inner(): string;
        native SetUri_inner(uri: string): void;
        native GetDetails_inner(): (Record<string, string> | undefined);
        native SetDetails_inner(details: Record<string, string>): void;
        native GetImageUri_inner(): string;
        native SetImageUri_inner(imageUri: string): void;
        native GetInner_inner(): long;
        getType(): string {
            return this.GetType_inner();
        }
        getValue(): ValueType {
            return this.GetValue_inner();
        }
        get uri(): string {
            return this.GetUri_inner();
        }
        set uri(uri: string) {
            return this.SetUri_inner(uri);
        }
        get details(): (Record<string, string> | undefined) {
            return this.GetDetails_inner();
        }
        set details(details: Record<string, string>) {
            return this.SetDetails_inner(details);
        }
        get imageUri(): string {
            return this.GetImageUri_inner();
        }
        set imageUri(imageUri: string) {
            return this.SetImageUri_inner(imageUri);
        }
        getInner(): long {
            return this.GetInner_inner();
        }
    }
    export class Text {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { Text._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            Text._registry.register(this, this._data_ptr)
        }
        constructor() {
            let temp = CreateText_inner() as Text;
            this._data_ptr = temp._data_ptr;
            this._vtbl_ptr = temp._vtbl_ptr;
        }
        native GetType_inner(): string;
        native GetValue_inner(): ValueType;
        native GetDetails_inner(): (Record<string, string> | undefined);
        native SetDetails_inner(details: Record<string, string>): void;
        native GetInner_inner(): long;
        getType(): string {
            return this.GetType_inner();
        }
        getValue(): ValueType {
            return this.GetValue_inner();
        }
        get details(): (Record<string, string> | undefined) {
            return this.GetDetails_inner();
        }
        set details(details: Record<string, string>) {
            return this.SetDetails_inner(details);
        }
        getInner(): long {
            return this.GetInner_inner();
        }
    }
    export class HTML {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { HTML._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            HTML._registry.register(this, this._data_ptr)
        }
        constructor() {
            let temp = CreateHtml_inner() as HTML;
            this._data_ptr = temp._data_ptr;
            this._vtbl_ptr = temp._vtbl_ptr;
        }
        native GetType_inner(): string;
        native GetValue_inner(): ValueType;
        native GetDetails_inner(): (Record<string, string> | undefined);
        native SetDetails_inner(details: Record<string, string>): void;
        native SetHtmlContent_inner(htmlContent: string): void;
        native GetHtmlContent_inner(): string;
        native SetPlainContent_inner(plainContent: string): void;
        native GetPlainContent_inner(): string;
        native GetInner_inner(): long;
        getType(): string {
            return this.GetType_inner();
        }
        getValue(): ValueType {
            return this.GetValue_inner();
        }
        get details(): (Record<string, string> | undefined) {
            return this.GetDetails_inner();
        }
        set details(details: Record<string, string>) {
            return this.SetDetails_inner(details);
        }
        set htmlContent(htmlContent: string) {
            return this.SetHtmlContent_inner(htmlContent);
        }
        get htmlContent(): string {
            return this.GetHtmlContent_inner();
        }
        set plainContent(plainContent: string) {
            return this.SetPlainContent_inner(plainContent);
        }
        get plainContent(): string {
            return this.GetPlainContent_inner();
        }
        getInner(): long {
            return this.GetInner_inner();
        }
    }
    export class Hyperlink {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { Hyperlink._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            Hyperlink._registry.register(this, this._data_ptr)
        }
        constructor() {
            let temp = CreateHyperlink_inner() as Hyperlink;
            this._data_ptr = temp._data_ptr;
            this._vtbl_ptr = temp._vtbl_ptr;
        }
        native GetType_inner(): string;
        native GetValue_inner(): ValueType;
        native GetDetails_inner(): (Record<string, string> | undefined);
        native SetDetails_inner(details: Record<string, string>): void;
        native SetUrl_inner(url: string): void;
        native GetUrl_inner(): string;
        native SetDescription_inner(description: string): void;
        native GetDescription_inner(): string;
        native GetInner_inner(): long;
        getType(): string {
            return this.GetType_inner();
        }
        getValue(): ValueType {
            return this.GetValue_inner();
        }
        get details(): (Record<string, string> | undefined) {
            return this.GetDetails_inner();
        }
        set details(details: Record<string, string>) {
            return this.SetDetails_inner(details);
        }
        set url(url: string) {
            return this.SetUrl_inner(url);
        }
        get url(): string {
            return this.GetUrl_inner();
        }
        set description(description: string) {
            return this.SetDescription_inner(description);
        }
        get description(): string {
            return this.GetDescription_inner();
        }
        getInner(): long {
            return this.GetInner_inner();
        }
    }
    export class PlainText {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { PlainText._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            PlainText._registry.register(this, this._data_ptr)
        }
        constructor() {
            let temp = CreatePlainText_inner() as PlainText;
            this._data_ptr = temp._data_ptr;
            this._vtbl_ptr = temp._vtbl_ptr;
        }
        native GetType_inner(): string;
        native GetValue_inner(): ValueType;
        native GetDetails_inner(): (Record<string, string> | undefined);
        native SetDetails_inner(details: Record<string, string>): void;
        native SetTextContent_inner(textContent: string): void;
        native GetTextContent_inner(): string;
        native SetAbstract1_inner(abstract1: string): void;
        native GetAbstract1_inner(): string;
        native GetInner_inner(): long;
        getType(): string {
            return this.GetType_inner();
        }
        getValue(): ValueType {
            return this.GetValue_inner();
        }
        get details(): (Record<string, string> | undefined) {
            return this.GetDetails_inner();
        }
        set details(details: Record<string, string>) {
            return this.SetDetails_inner(details);
        }
        set textContent(textContent: string) {
            return this.SetTextContent_inner(textContent);
        }
        get textContent(): string {
            return this.GetTextContent_inner();
        }
        set abstract1(abstract1: string) {
            return this.SetAbstract1_inner(abstract1);
        }
        get abstract1(): string {
            return this.GetAbstract1_inner();
        }
        getInner(): long {
            return this.GetInner_inner();
        }
    }
    export class SystemDefinedRecord {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { SystemDefinedRecord._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            SystemDefinedRecord._registry.register(this, this._data_ptr)
        }
        constructor() {
            let temp = CreateSystemDefinedRecord_inner() as SystemDefinedRecord;
            this._data_ptr = temp._data_ptr;
            this._vtbl_ptr = temp._vtbl_ptr;
        }
        native GetType_inner(): string;
        native GetValue_inner(): ValueType;
        native GetDetails_inner(): (Record<string, DetailsValue> | undefined);
        native SetDetails_inner(details: Record<string, DetailsValue>): void;
        native GetInner_inner(): long;
        getType(): string {
            return this.GetType_inner();
        }
        getValue(): ValueType {
            return this.GetValue_inner();
        }
        get details(): (Record<string, DetailsValue> | undefined) {
            return this.GetDetails_inner();
        }
        set details(details: Record<string, DetailsValue>) {
            return this.SetDetails_inner(details);
        }
        getInner(): long {
            return this.GetInner_inner();
        }
    }
    export class SystemDefinedForm {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { SystemDefinedForm._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            SystemDefinedForm._registry.register(this, this._data_ptr)
        }
        constructor() {
            let temp = CreateSystemDefinedForm_inner() as SystemDefinedForm;
            this._data_ptr = temp._data_ptr;
            this._vtbl_ptr = temp._vtbl_ptr;
        }
        native GetType_inner(): string;
        native GetValue_inner(): ValueType;
        native GetDetails_inner(): (Record<string, DetailsValue> | undefined);
        native SetDetails_inner(details: Record<string, DetailsValue>): void;
        native GetFormId_inner(): double;
        native SetFormId_inner(formId: double): void;
        native GetFormName_inner(): string;
        native SetFormName_inner(formName: string): void;
        native GetBundleName_inner(): string;
        native SetBundleName_inner(bundleName: string): void;
        native GetAbilityName_inner(): string;
        native SetAbilityName_inner(abilityName: string): void;
        native GetModule_inner(): string;
        native SetModule_inner(module: string): void;
        native GetInner_inner(): long;
        getType(): string {
            return this.GetType_inner();
        }
        getValue(): ValueType {
            return this.GetValue_inner();
        }
        get details(): (Record<string, DetailsValue> | undefined) {
            return this.GetDetails_inner();
        }
        set details(details: Record<string, DetailsValue>) {
            return this.SetDetails_inner(details);
        }
        get formId(): double {
            return this.GetFormId_inner();
        }
        set formId(formId: double) {
            return this.SetFormId_inner(formId);
        }
        get formName(): string {
            return this.GetFormName_inner();
        }
        set formName(formName: string) {
            return this.SetFormName_inner(formName);
        }
        get bundleName(): string {
            return this.GetBundleName_inner();
        }
        set bundleName(bundleName: string) {
            return this.SetBundleName_inner(bundleName);
        }
        get abilityName(): string {
            return this.GetAbilityName_inner();
        }
        set abilityName(abilityName: string) {
            return this.SetAbilityName_inner(abilityName);
        }
        get module(): string {
            return this.GetModule_inner();
        }
        set module(module: string) {
            return this.SetModule_inner(module);
        }
        getInner(): long {
            return this.GetInner_inner();
        }
    }
    export class SystemDefinedAppItem {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { SystemDefinedAppItem._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            SystemDefinedAppItem._registry.register(this, this._data_ptr)
        }
        constructor() {
            let temp = CreateSystemDefinedAppItem_inner() as SystemDefinedAppItem;
            this._data_ptr = temp._data_ptr;
            this._vtbl_ptr = temp._vtbl_ptr;
        }
        native GetType_inner(): string;
        native GetValue_inner(): ValueType;
        native GetDetails_inner(): (Record<string, DetailsValue> | undefined);
        native SetDetails_inner(details: Record<string, DetailsValue>): void;
        native GetAppId_inner(): string;
        native SetAppId_inner(appId: string): void;
        native GetAppName_inner(): string;
        native SetAppName_inner(appName: string): void;
        native GetAppIconId_inner(): string;
        native SetAppIconId_inner(appIconId: string): void;
        native GetAppLabelId_inner(): string;
        native SetAppLabelId_inner(appLabelId: string): void;
        native GetBundleName_inner(): string;
        native SetBundleName_inner(bundleName: string): void;
        native GetAbilityName_inner(): string;
        native SetAbilityName_inner(abilityName: string): void;
        native GetInner_inner(): long;
        getType(): string {
            return this.GetType_inner();
        }
        getValue(): ValueType {
            return this.GetValue_inner();
        }
        get details(): (Record<string, DetailsValue> | undefined) {
            return this.GetDetails_inner();
        }
        set details(details: Record<string, DetailsValue>) {
            return this.SetDetails_inner(details);
        }
        get appId(): string {
            return this.GetAppId_inner();
        }
        set appId(appId: string) {
            return this.SetAppId_inner(appId);
        }
        get appName(): string {
            return this.GetAppName_inner();
        }
        set appName(appName: string) {
            return this.SetAppName_inner(appName);
        }
        get appIconId(): string {
            return this.GetAppIconId_inner();
        }
        set appIconId(appIconId: string) {
            return this.SetAppIconId_inner(appIconId);
        }
        get appLabelId(): string {
            return this.GetAppLabelId_inner();
        }
        set appLabelId(appLabelId: string) {
            return this.SetAppLabelId_inner(appLabelId);
        }
        get bundleName(): string {
            return this.GetBundleName_inner();
        }
        set bundleName(bundleName: string) {
            return this.SetBundleName_inner(bundleName);
        }
        get abilityName(): string {
            return this.GetAbilityName_inner();
        }
        set abilityName(abilityName: string) {
            return this.SetAbilityName_inner(abilityName);
        }
        getInner(): long {
            return this.GetInner_inner();
        }
    }
    export class SystemDefinedPixelMap {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { SystemDefinedPixelMap._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            SystemDefinedPixelMap._registry.register(this, this._data_ptr)
        }
        constructor() {
            let temp = CreateSystemDefinedPixelMap_inner() as SystemDefinedPixelMap;
            this._data_ptr = temp._data_ptr;
            this._vtbl_ptr = temp._vtbl_ptr;
        }
        native GetType_inner(): string;
        native GetValue_inner(): ValueType;
        native GetDetails_inner(): (Record<string, DetailsValue> | undefined);
        native SetDetails_inner(details: Record<string, DetailsValue>): void;
        native GetRawData_inner(): (Uint8Array | undefined);
        native SetRawData_inner(rawData: Uint8Array): void;
        native GetInner_inner(): long;
        getType(): string {
            return this.GetType_inner();
        }
        getValue(): ValueType {
            return this.GetValue_inner();
        }
        get details(): (Record<string, DetailsValue> | undefined) {
            return this.GetDetails_inner();
        }
        set details(details: Record<string, DetailsValue>) {
            return this.SetDetails_inner(details);
        }
        get rawData(): (Uint8Array | undefined) {
            return this.GetRawData_inner();
        }
        set rawData(rawData: Uint8Array) {
            return this.SetRawData_inner(rawData);
        }
        getInner(): long {
            return this.GetInner_inner();
        }
    }
    function __fromArrayBufferToBigInt(arr: ArrayBuffer): BigInt {
        let res: BigInt = 0n;
        for (let i: int = 0; i < arr.getByteLength(); i++) {
            res |= BigInt(arr.at(i) as long & 0xff) << BigInt(i * 8);
        }
        let m: int = arr.getByteLength();
        if (arr.at(m - 1) < 0) {
            res |= -1n << BigInt(m * 8 - 1);
        }
        return res;
    }
    function __fromBigIntToArrayBuffer(val: BigInt, blk: int): ArrayBuffer {
        let n_7 = BigInt(blk * 8 - 1);
        let n_8 = BigInt(blk * 8);
        let ocp: BigInt = val;
        let n: int = 0;
        while (true) {
            n += blk;
            let t_7 = ocp >> n_7;
            let t_8 = ocp >> n_8;
            if (t_7 == t_8) {
                break;
            }
            ocp = t_8;
        }
        let buf = new ArrayBuffer(n);
        for (let i: int = 0; i < n; i++) {
            buf.set(i, (val & 255n).getLong() as byte)
            val >>= 8n;
        }
        return buf;
    }
}
function __fromArrayBufferToBigInt(arr: ArrayBuffer): BigInt {
    let res: BigInt = 0n;
    for (let i: int = 0; i < arr.getByteLength(); i++) {
        res |= BigInt(arr.at(i) as long & 0xff) << BigInt(i * 8);
    }
    let m: int = arr.getByteLength();
    if (arr.at(m - 1) < 0) {
        res |= -1n << BigInt(m * 8 - 1);
    }
    return res;
}
function __fromBigIntToArrayBuffer(val: BigInt, blk: int): ArrayBuffer {
    let n_7 = BigInt(blk * 8 - 1);
    let n_8 = BigInt(blk * 8);
    let ocp: BigInt = val;
    let n: int = 0;
    while (true) {
        n += blk;
        let t_7 = ocp >> n_7;
        let t_8 = ocp >> n_8;
        if (t_7 == t_8) {
            break;
        }
        ocp = t_8;
    }
    let buf = new ArrayBuffer(n);
    for (let i: int = 0; i < n; i++) {
        buf.set(i, (val & 255n).getLong() as byte)
        val >>= 8n;
    }
    return buf;
}
