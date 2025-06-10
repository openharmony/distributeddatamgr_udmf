import {AsyncCallback} from '@ohos.base';
import {BusinessError} from '@ohos.base';
export namespace uniformTypeDescriptor {
    native function getUniformDataTypeByFilenameExtension_inner(filenameExtension: string, belongsTo: (string | undefined)): string;
    export function getUniformDataTypeByFilenameExtension(filenameExtension: string, belongsTo: (string | undefined)): string {
        return getUniformDataTypeByFilenameExtension_inner(filenameExtension, belongsTo);
    }
    export enum UniformDataType {
        OPENHARMONY_PIXEL_MAP = "openharmony.pixel-map",
        FOLDER = "general.folder",
        FILE = "general.file",
        AUDIO = "general.audio",
        VIDEO = "general.video",
        IMAGE = "general.image",
        HYPERLINK = "general.hyperlink",
        HTML = "general.html",
        PLAIN_TEXT = "general.plain-text",
        TEXT = "general.text",
        JPEG = "general.jpeg",
        PNG = "general.png",
        MPEG4 = "general.mpeg-4",
        OPENHARMONY_ATOMIC_SERVICE = "openharmony.atomic-service",
        PDF = "com.adobe.pdf",
        OPENHARMONY_APP_ITEM = "openharmony.app-item",
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
