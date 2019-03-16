import { UploadStatus } from "./upload-status.enum";
import { Submission } from "./submission";

export class FileUpload {
    public status: UploadStatus;
    public progress: number;

    constructor(public file: File, public submission: Submission) {
        this.status = UploadStatus.NotStarted;
        this.progress = 0;
    }

    public updateProgress(progress: number) {
        this.progress = progress;
        this.status = UploadStatus.Uploading;
    }

    public completed() {
        this.progress = 100;
        this.status = UploadStatus.Done;
    }

    public failed() {
        this.progress = 0;
        this.status = UploadStatus.Error;
    }

    get isWaitingForUpload(){
        return this.status === UploadStatus.NotStarted;
    }
}