export class BusinessError<T = void> extends Error {
    code: number;
    data?: T;
    constructor() {
        super();
        this.code = 0;
    }
    constructor(code: number, error: Error) {
        super(error.name, error.message, new ErrorOptions(error.cause));
        this.code = code;
    }
    constructor(code: number, data: T, error: Error) {
        super(error.name, error.message, new ErrorOptions(error.cause));
        this.code = code;
        this.data = data;
    }
}
export type AsyncCallback<T, E = void> = (error: BusinessError<E>, data: T) => void;
