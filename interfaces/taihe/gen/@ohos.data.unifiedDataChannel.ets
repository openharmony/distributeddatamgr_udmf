import {AsyncCallback} from '@ohos.base';
import {BusinessError} from '@ohos.base';
import Want from '@ohos.app.ability.Want';
import image from '@ohos.multimedia.image';
export namespace unifiedDataChannel {

    static { loadLibrary("udmf_taihe_native.z") }


    export class UnifiedData {
      inner: UnifiedDataInner;
      constructor() {
        this.inner = CreateUnifiedData_inner();
      }
      constructor(inner: UnifiedDataInner) {
        this.inner = inner;
      }
      constructor(unifiedRecord: UnifiedRecord) {
        if (unifiedRecord instanceof Folder) {
          this.inner = CreateUnifiedDataWithParams_inner((unifiedRecord as Folder).inner);
        } else if (unifiedRecord instanceof Audio) {
          this.inner = CreateUnifiedDataWithParams_inner((unifiedRecord as Audio).inner);
        } else if (unifiedRecord instanceof Video) {
          this.inner = CreateUnifiedDataWithParams_inner((unifiedRecord as Video).inner);
        } else if (unifiedRecord instanceof Image) {
          this.inner = CreateUnifiedDataWithParams_inner((unifiedRecord as Image).inner);
        } else if (unifiedRecord instanceof PlainText) {
          this.inner = CreateUnifiedDataWithParams_inner((unifiedRecord as PlainText).inner);
        } else if (unifiedRecord instanceof HTML) {
          this.inner = CreateUnifiedDataWithParams_inner((unifiedRecord as HTML).inner);
        } else if (unifiedRecord instanceof Hyperlink) {
          this.inner = CreateUnifiedDataWithParams_inner((unifiedRecord as Hyperlink).inner);
        } else if (unifiedRecord instanceof SystemDefinedForm) {
          this.inner = CreateUnifiedDataWithParams_inner((unifiedRecord as SystemDefinedForm).inner);
        } else if (unifiedRecord instanceof SystemDefinedAppItem) {
          this.inner = CreateUnifiedDataWithParams_inner((unifiedRecord as SystemDefinedAppItem).inner);
        } else if (unifiedRecord instanceof SystemDefinedPixelMap) {
          this.inner = CreateUnifiedDataWithParams_inner((unifiedRecord as SystemDefinedPixelMap).inner);
        } else if (unifiedRecord instanceof Text) {
          this.inner = CreateUnifiedDataWithParams_inner((unifiedRecord as Text).inner);
        } else if (unifiedRecord instanceof File) {
          this.inner = CreateUnifiedDataWithParams_inner((unifiedRecord as File).inner);
        } else if (unifiedRecord instanceof SystemDefinedRecord) {
          this.inner = CreateUnifiedDataWithParams_inner((unifiedRecord as SystemDefinedRecord).inner);
        } else if (unifiedRecord instanceof UnifiedRecord) {
          this.inner = CreateUnifiedDataWithParams_inner((unifiedRecord as UnifiedRecord).inner);
        }
      }
      addRecord(unifiedRecord: UnifiedRecord) {
        if (unifiedRecord instanceof Folder) {
          this.inner.addRecord((unifiedRecord as Folder).inner);
        } else if (unifiedRecord instanceof Audio) {
          this.inner.addRecord((unifiedRecord as Audio).inner);
        } else if (unifiedRecord instanceof Video) {
          this.inner.addRecord((unifiedRecord as Video).inner);
        } else if (unifiedRecord instanceof Image) {
          this.inner.addRecord((unifiedRecord as Image).inner);
        } else if (unifiedRecord instanceof PlainText) {
          this.inner.addRecord((unifiedRecord as PlainText).inner);
        } else if (unifiedRecord instanceof HTML) {
          this.inner.addRecord((unifiedRecord as HTML).inner);
        } else if (unifiedRecord instanceof Hyperlink) {
          this.inner.addRecord((unifiedRecord as Hyperlink).inner);
        } else if (unifiedRecord instanceof SystemDefinedForm) {
          this.inner.addRecord((unifiedRecord as SystemDefinedForm).inner);
        } else if (unifiedRecord instanceof SystemDefinedAppItem) {
          this.inner.addRecord((unifiedRecord as SystemDefinedAppItem).inner);
        } else if (unifiedRecord instanceof SystemDefinedPixelMap) {
          this.inner.addRecord((unifiedRecord as SystemDefinedPixelMap).inner);
        } else if (unifiedRecord instanceof Text) {
          this.inner.addRecord((unifiedRecord as Text).inner);
        } else if (unifiedRecord instanceof File) {
          this.inner.addRecord((unifiedRecord as File).inner);
        } else if (unifiedRecord instanceof SystemDefinedRecord) {
          this.inner.addRecord((unifiedRecord as SystemDefinedRecord).inner);
        } else if (unifiedRecord instanceof UnifiedRecord) {
          this.inner.addRecord((unifiedRecord as UnifiedRecord).inner);
        }
      }
      getRecords(): Array<UnifiedRecord> {
        let records = this.inner.getRecords();
        let arr: Array<UnifiedRecord> = new Array<UnifiedRecord>();
        for (let i = 0; i < records.length; i++ ) {
          if (records[i] instanceof UnifiedRecordInner) {
            arr.push(new UnifiedRecord(records[i] as UnifiedRecordInner));
          } else if (records[i] instanceof FileInner) {
            arr.push(new File(records[i] as FileInner));
          } else if (records[i] instanceof FolderInner) {
            arr.push(new Folder(records[i] as FolderInner));
          } else if (records[i] instanceof AudioInner) {
            arr.push(new Audio(records[i] as AudioInner));
          } else if (records[i] instanceof VideoInner) {
            arr.push(new Video(records[i] as VideoInner));
          } else if (records[i] instanceof ImageInner) {
            arr.push(new Image(records[i] as ImageInner));
          } else if (records[i] instanceof TextInner) {
            arr.push(new Text(records[i] as TextInner));
          } else if (records[i] instanceof PlainTextInner) {
            arr.push(new PlainText(records[i] as PlainTextInner));
          } else if (records[i] instanceof HTMLInner) {
            arr.push(new HTML(records[i] as HTMLInner));
          } else if (records[i] instanceof HyperlinkInner) {
            arr.push(new Hyperlink(records[i] as HyperlinkInner));
          } else if (records[i] instanceof SystemDefinedRecordInner) {
            arr.push(new SystemDefinedRecord(records[i] as SystemDefinedRecordInner));
          } else if (records[i] instanceof SystemDefinedFormInner) {
            arr.push(new SystemDefinedForm(records[i] as SystemDefinedFormInner));
          } else if (records[i] instanceof SystemDefinedAppItemInner) {
            arr.push(new SystemDefinedAppItem(records[i] as SystemDefinedAppItemInner));
          } else if (records[i] instanceof SystemDefinedPixelMapInner) {
            arr.push(new SystemDefinedPixelMap(records[i] as SystemDefinedPixelMapInner));
          }
        }
        return arr;
      }
    }

    export class UnifiedRecord {
      inner: UnifiedRecordInner;
      constructor() {
        this.inner = CreateUnifiedRecord_inner();
      }
      constructor(inner: UnifiedRecordInner) {
        this.inner = inner;
      }

      constructor(type: string, value: ValueType) {
        this.inner = CreateUnifiedRecordWithParams_inner(type, value);
      }
      getType(): string {
        return this.inner.getType();
      }
      getValue(): ValueType {
        return this.inner.getValue();
      }
    }

    export class File extends UnifiedRecord {
      inner: FileInner;
      constructor() {
        this.inner = CreateUnifiedFile_inner();
      }
      constructor(inner: FileInner) {
        this.inner = inner;
      }
      getValue(): ValueType {
        return this.inner.getValue();
      }
      getType(): string {
        return this.inner.getType();
      }
      get uri(): string {
        return this.inner.uri;
      }
      set uri(uri: string) {
        this.inner.uri = uri;
      }
    }

    export class Folder extends File {
      inner: FolderInner;
      constructor() {
        this.inner = CreateUnifiedFolder_inner();
      }
      constructor(inner: FolderInner) {
        this.inner = inner;
      }
      getType(): string {
        return this.inner.getType();
      }
      getValue(): ValueType {
        return this.inner.getValue();
      }
      get uri(): string {
        return this.inner.uri;
      }
      set uri(uri: string) {
        this.inner.uri = uri;
      }
      get details(): Record<String, String> | undefined {
        return this.inner.details;
      }
      set details(details: Record<String, String>) {
        this.inner.details = details;
      }
      get folderUri(): string {
        return this.inner.folderUri;
      }
      set folderUri(folderUri: string) {
        this.inner.folderUri = folderUri;
      }
    }

    export class Audio extends File {
      inner: AudioInner;
      constructor() {
        this.inner = CreateUnifiedAudio_inner();
      }
      constructor(inner: AudioInner) {
        this.inner = inner;
      }
      getType(): string {
        return this.inner.getType();
      }
      getValue(): ValueType {
        return this.inner.getValue();
      }
      get uri(): string {
        return this.inner.uri;
      }
      set uri(uri: string) {
        this.inner.uri = uri;
      }
      get details(): Record<String, String> | undefined {
        return this.inner.details;
      }
      set details(details: Record<String, String>) {
        this.inner.details = details;
      }
      get audioUri(): string {
        return this.inner.audioUri;
      }
      set audioUri(audioUri: string) {
        this.inner.audioUri = audioUri;
      }
    }

    export class Video extends File {
      inner: VideoInner;
      constructor() {
        this.inner = CreateUnifiedVideo_inner();
      }
      constructor(inner: VideoInner) {
        this.inner = inner;
      }
      getType(): string {
        return this.inner.getType();
      }
      getValue(): ValueType {
        return this.inner.getValue();
      }
      get uri(): string {
        return this.inner.uri;
      }
      set uri(uri: string) {
        this.inner.uri = uri;
      }
      get details(): Record<String, String> | undefined {
        return this.inner.details;
      }
      set details(details: Record<String, String>) {
        this.inner.details = details;
      }
      get videoUri(): string {
        return this.inner.videoUri;
      }
      set videoUri(videoUri: string) {
        this.inner.videoUri = videoUri;
      }
    }

    export class Image extends File {
      inner: ImageInner;
      constructor() {
        this.inner = CreateUnifiedImage_inner();
      }
      constructor(inner: ImageInner) {
        this.inner = inner;
      }
      getType(): string {
        return this.inner.getType();
      }
      getValue(): ValueType {
        return this.inner.getValue();
      }
      get uri(): string {
        return this.inner.uri;
      }
      set uri(uri: string) {
        this.inner.uri = uri;
      }
      get details(): Record<String, String> | undefined {
        return this.inner.details;
      }
      set details(details: Record<String, String>) {
        this.inner.details = details;
      }
      get imageUri(): string {
        return this.inner.imageUri;
      }
      set imageUri(imageUri: string) {
        this.inner.imageUri = imageUri;
      }
    }

    export class Text extends UnifiedRecord {
      inner: TextInner;
      constructor() {
        this.inner = CreateText_inner();
      }
      constructor(inner: TextInner) {
        this.inner = inner;
      }
      getType(): string {
        return this.inner.getType();
      }
      getValue(): ValueType {
        return this.inner.getValue();
      }
      get details(): Record<string, string>| undefined {
        return this.inner.details;
      }
      set details(info: Record<string, string>) {
        this.inner.details = info;
      }
    }

    export class PlainText extends Text {
      inner: PlainTextInner;
      constructor() {
        this.inner = CreatePlainText_inner();
      }
      constructor(inner: PlainTextInner) {
        this.inner = inner;
      }
      get details(): Record<string, string>| undefined {
        return this.inner.details;
      }
      set details(info: Record<string, string>) {
        this.inner.details = info;
      }
      get textContent(): string {
        return this.inner.textContent;
      }
      set textContent(text: string) {
        this.inner.textContent = text;
      }
      getType(): string {
        return this.inner.getType();
      }
      getValue(): ValueType {
        return this.inner.getValue();
      }
    }

    export class HTML extends Text {
      inner: HTMLInner;
      constructor() {
        this.inner = CreateHtml_inner();
      }
      constructor(inner: HTMLInner) {
        this.inner = inner;
      }
      get details(): Record<string, string>| undefined {
        return this.inner.details;
      }
      set details(info: Record<string, string>) {
        this.inner.details = info;
      }
      get htmlContent(): string {
        return this.inner.htmlContent;
      }
      set htmlContent(html: string) {
        this.inner.htmlContent = html;
      }
      get plainContent(): string {
        return this.inner.plainContent;
      }
      set plainContent(plain: string) {
        this.inner.plainContent = plain;
      }
      getType(): string {
        return this.inner.getType();
      }
      getValue(): ValueType {
        return this.inner.getValue();
      }
    }

    export class Hyperlink extends Text {
      inner: HyperlinkInner;
      constructor() {
        this.inner = CreateHyperlink_inner();
      }
      constructor(inner: HyperlinkInner) {
        this.inner = inner;
      }
      get details(): Record<string, string>| undefined {
        return this.inner.details;
      }
      set details(info: Record<string, string>) {
        this.inner.details = info;
      }
      get url(): string {
        return this.inner.url;
      }
      set url(url: string) {
        this.inner.url = url;
      }
      get description(): string {
        return this.inner.description;
      }
      set description(description: string) {
        this.inner.description = description;
      }
      getType(): string {
        return this.inner.getType();
      }
      getValue(): ValueType {
        return this.inner.getValue();
      }
    }

    export class SystemDefinedRecord extends UnifiedRecord {
      inner: SystemDefinedRecordInner;
      constructor() {
        this.inner = CreateSystemDefinedRecord_inner();
      }
      constructor(inner: SystemDefinedRecordInner) {
        this.inner = inner;
      }
      getType(): string {
        return this.inner.getType();
      }
      getValue(): ValueType {
        return this.inner.getValue();
      }
      get details(): Record<String, DetailsValue> | undefined {
        return this.inner.details;
      }
      set details(details: Record<String, DetailsValue>) {
        this.inner.details = details;
      }
    }

    export class SystemDefinedForm extends SystemDefinedRecord {
      inner: SystemDefinedFormInner;
      constructor() {
        this.inner = CreateSystemDefinedForm_inner();
      }
      constructor(inner: SystemDefinedFormInner) {
        this.inner = inner;
      }
      getType(): string {
        return this.inner.getType();
      }
      getValue(): ValueType {
        return this.inner.getValue();
      }
      get details(): Record<String, DetailsValue> | undefined {
        return this.inner.details;
      }
      set details(details: Record<String, DetailsValue>) {
        this.inner.details = details;
      }
      get formId(): number {
        return this.inner.formId;
      }
      set formId(formId: number) {
        this.inner.formId = formId;
      }
      get formName(): String {
        return this.inner.formName;
      }
      set formName(formName: String) {
        this.inner.formName = formName;
      }
      get bundleName(): String {
        return this.inner.bundleName;
      }
      set bundleName(bundleName: String) {
        this.inner.bundleName = bundleName;
      }
      get abilityName(): String {
        return this.inner.abilityName;
      }
      set abilityName(abilityName: String) {
        this.inner.abilityName = abilityName;
      }
      get module(): String {
        return this.inner.module;
      }
      set module(module: String) {
        this.inner.module = module;
      }
    }

    export class SystemDefinedAppItem extends SystemDefinedRecord {
      inner: SystemDefinedAppItemInner;
      constructor() {
        this.inner = CreateSystemDefinedAppItem_inner();
      }
      constructor(inner: SystemDefinedAppItemInner) {
        this.inner = inner;
      }
      getType(): string {
        return this.inner.getType();
      }
      getValue(): ValueType {
        return this.inner.getValue();
      }
      get details(): Record<String, DetailsValue> | undefined {
        return this.inner.details;
      }
      set details(details: Record<String, DetailsValue>) {
        this.inner.details = details;
      }
      get appId(): String {
        return this.inner.appId;
      }
      set appId(appId: String) {
        this.inner.appId = appId;
      }
      get appName(): String {
        return this.inner.appName;
      }
      set appName(appName: String) {
        this.inner.appName = appName;
      }
      get appIconId(): String {
        return this.inner.appIconId;
      }
      set appIconId(appIconId: String) {
        this.inner.appIconId = appIconId;
      }
      get appLabelId(): String {
        return this.inner.appLabelId;
      }
      set appLabelId(appLabelId: String) {
        this.inner.appLabelId = appLabelId;
      }
      get bundleName(): String {
        return this.inner.bundleName;
      }
      set bundleName(bundleName: String) {
        this.inner.bundleName = bundleName;
      }
      get abilityName(): String {
        return this.inner.abilityName;
      }
      set abilityName(abilityName: String) {
        this.inner.abilityName = abilityName;
      }
    }

    export class SystemDefinedPixelMap extends SystemDefinedRecord {
      inner: SystemDefinedPixelMapInner;
      constructor() {
        this.inner = CreateSystemDefinedPixelMap_inner();
      }
      constructor(inner: SystemDefinedPixelMapInner) {
        this.inner = inner;
      }
      getType(): string {
        return this.inner.getType();
      }
      getValue(): ValueType {
        return this.inner.getValue();
      }
      get details(): Record<String, DetailsValue> | undefined {
        return this.inner.details;
      }
      set details(details: Record<String, DetailsValue>) {
        this.inner.details = details;
      }
      get rawData(): Uint8Array | undefined {
        return this.inner.rawData;
      }
      set rawData(rawData: Uint8Array) {
        this.inner.rawData = rawData;
      }
    }

    export function insertData(options: Options, data: UnifiedData): Promise<string> {
    return new Promise<string>((resolve, reject): void => {
        taskpool.execute((): string => {
            return InsertDataSync_inner(options, data.inner);
        })
        .then((ret: NullishType): void => {
            resolve(ret as string);
        })
        .catch((ret: NullishType): void => {
            reject(ret as Error);
        });
    });
    }
    export function insertData(options: Options, data: UnifiedData, callback: AsyncCallback<string>): void {
    taskpool.execute((): string => {
        return InsertDataSync_inner(options, data.inner);
    })
    .then((ret: NullishType): void => {
        callback(new BusinessError(), ret as string);
    })
    .catch((ret: NullishType): void => {
        let data: string;
        callback(ret as BusinessError, data);
    });
    }

    export function queryData(options: Options): Promise<Array<UnifiedData>> {
        return new Promise<Array<UnifiedData>>((resolve, reject): void => {
            taskpool.execute((): Array<UnifiedData> => {
                let dataArray = QueryDataSync_inner(options);
                let arr: Array<UnifiedData> = new Array<UnifiedData>();
                for (let i = 0; i < dataArray.length; i++ ) {
                  arr.push(new UnifiedData(dataArray[i]))
                }
                return arr;
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
            let dataArray = QueryDataSync_inner(options);
            let arr: Array<UnifiedData> = new Array<UnifiedData>();
            for (let i = 0; i < dataArray.length; i++ ) {
              arr.push(new UnifiedData(dataArray[i]))
            }
            return arr;
        })
        .then((ret: NullishType): void => {
            callback(new BusinessError(), ret as Array<UnifiedData>);
        })
        .catch((ret: NullishType): void => {
            let data: Array<UnifiedData>;
            callback(ret as BusinessError, data);
        });
    }
    native function CreateSummary_inner(): Summary;
    native function CreateUnifiedData_inner(): UnifiedDataInner;
    native function CreateUnifiedDataWithParams_inner(unifiedRecord: AllRecords): UnifiedDataInner;
    native function CreateUnifiedRecord_inner(): UnifiedRecordInner;
    native function CreateUnifiedRecordWithParams_inner(type: string, value: ValueType): UnifiedRecordInner;
    native function CreateUnifiedFile_inner(): FileInner;
    native function CreateUnifiedFolder_inner(): FolderInner;
    native function CreateUnifiedAudio_inner(): AudioInner;
    native function CreateUnifiedVideo_inner(): VideoInner;
    native function CreateUnifiedImage_inner(): ImageInner;
    native function CreateText_inner(): TextInner;
    native function CreateHtml_inner(): HTMLInner;
    native function CreateHyperlink_inner(): HyperlinkInner;
    native function CreatePlainText_inner(): PlainTextInner;
    native function CreateSystemDefinedRecord_inner(): SystemDefinedRecordInner;
    native function CreateSystemDefinedForm_inner(): SystemDefinedFormInner;
    native function CreateSystemDefinedAppItem_inner(): SystemDefinedAppItemInner;
    native function CreateSystemDefinedPixelMap_inner(): SystemDefinedPixelMapInner;
    native function InsertDataSync_inner(options: Options, data: UnifiedDataInner): string;
    native function QueryDataSync_inner(options: Options): Array<UnifiedDataInner>;
    export function createSummary(): Summary {
        return CreateSummary_inner();
    }
    export function createUnifiedData(): UnifiedDataInner {
        return CreateUnifiedData_inner();
    }
    export function createUnifiedDataWithParams(unifiedRecord: AllRecords): UnifiedDataInner {
        return CreateUnifiedDataWithParams_inner(unifiedRecord);
    }
    export function createUnifiedRecord(): UnifiedRecordInner {
        return CreateUnifiedRecord_inner();
    }
    export function createUnifiedRecordWithParams(type: string, value: ValueType): UnifiedRecordInner {
        return CreateUnifiedRecordWithParams_inner(type, value);
    }
    export function createUnifiedFile(): FileInner {
        return CreateUnifiedFile_inner();
    }
    export function createUnifiedFolder(): FolderInner {
        return CreateUnifiedFolder_inner();
    }
    export function createUnifiedAudio(): AudioInner {
        return CreateUnifiedAudio_inner();
    }
    export function createUnifiedVideo(): VideoInner {
        return CreateUnifiedVideo_inner();
    }
    export function createUnifiedImage(): ImageInner {
        return CreateUnifiedImage_inner();
    }
    export function createText(): TextInner {
        return CreateText_inner();
    }
    export function createHtml(): HTMLInner {
        return CreateHtml_inner();
    }
    export function createHyperlink(): HyperlinkInner {
        return CreateHyperlink_inner();
    }
    export function createPlainText(): PlainTextInner {
        return CreatePlainText_inner();
    }
    export function createSystemDefinedRecord(): SystemDefinedRecordInner {
        return CreateSystemDefinedRecord_inner();
    }
    export function createSystemDefinedForm(): SystemDefinedFormInner {
        return CreateSystemDefinedForm_inner();
    }
    export function createSystemDefinedAppItem(): SystemDefinedAppItemInner {
        return CreateSystemDefinedAppItem_inner();
    }
    export function createSystemDefinedPixelMap(): SystemDefinedPixelMapInner {
        return CreateSystemDefinedPixelMap_inner();
    }
    export function insertDataSync(options: Options, data: UnifiedDataInner): string {
        return InsertDataSync_inner(options, data);
    }
    export function queryDataSync(options: Options): Array<UnifiedDataInner> {
        return QueryDataSync_inner(options);
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
    export type AllRecords = FileInner | FolderInner | AudioInner | VideoInner | ImageInner | TextInner | PlainTextInner | HTMLInner | HyperlinkInner | SystemDefinedRecordInner | SystemDefinedFormInner | SystemDefinedAppItemInner | SystemDefinedPixelMapInner | UnifiedRecordInner;
    export type UnifiedDataOrNull = UnifiedDataInner | null;
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
    export class UnifiedDataInner {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { UnifiedDataInner._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            UnifiedDataInner._registry.register(this, this._data_ptr)
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
    export class UnifiedRecordInner {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { UnifiedRecordInner._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            UnifiedRecordInner._registry.register(this, this._data_ptr)
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
    export class FileInner {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { FileInner._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            FileInner._registry.register(this, this._data_ptr)
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
    export class FolderInner {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { FolderInner._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            FolderInner._registry.register(this, this._data_ptr)
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
    export class AudioInner {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { AudioInner._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            AudioInner._registry.register(this, this._data_ptr)
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
    export class VideoInner {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { VideoInner._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            VideoInner._registry.register(this, this._data_ptr)
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
    export class ImageInner {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { ImageInner._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            ImageInner._registry.register(this, this._data_ptr)
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
    export class TextInner {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { TextInner._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            TextInner._registry.register(this, this._data_ptr)
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
    export class HTMLInner {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { HTMLInner._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            HTMLInner._registry.register(this, this._data_ptr)
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
    export class HyperlinkInner {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { HyperlinkInner._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            HyperlinkInner._registry.register(this, this._data_ptr)
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
    export class PlainTextInner {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { PlainTextInner._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            PlainTextInner._registry.register(this, this._data_ptr)
        }
        native GetType_inner(): string;
        native GetValue_inner(): ValueType;
        native GetDetails_inner(): (Record<string, string> | undefined);
        native SetDetails_inner(details: Record<string, string>): void;
        native SetTextContent_inner(textContent: string): void;
        native GetTextContent_inner(): string;
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
        getInner(): long {
            return this.GetInner_inner();
        }
    }
    export class SystemDefinedRecordInner {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { SystemDefinedRecordInner._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            SystemDefinedRecordInner._registry.register(this, this._data_ptr)
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
    export class SystemDefinedFormInner {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { SystemDefinedFormInner._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            SystemDefinedFormInner._registry.register(this, this._data_ptr)
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
    export class SystemDefinedAppItemInner {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { SystemDefinedAppItemInner._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            SystemDefinedAppItemInner._registry.register(this, this._data_ptr)
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
    export class SystemDefinedPixelMapInner {
        private _vtbl_ptr: long;
        private _data_ptr: long;
        private static native _finalize(data_ptr: long): void;
        private static _registry = new FinalizationRegistry<long>((data_ptr: long) => { SystemDefinedPixelMapInner._finalize(data_ptr); });
        private constructor(_vtbl_ptr: long, _data_ptr: long) {
            this._vtbl_ptr = _vtbl_ptr;
            this._data_ptr = _data_ptr;
            SystemDefinedPixelMapInner._registry.register(this, this._data_ptr)
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
