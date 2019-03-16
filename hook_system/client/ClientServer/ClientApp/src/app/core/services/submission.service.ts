import { Injectable } from '@angular/core';
import { HttpClient, HttpRequest, HttpEventType, HttpResponse, HttpErrorResponse } from '@angular/common/http';
import { Submission } from '../../shared/models/submission';
import { Observable, BehaviorSubject } from 'rxjs';
import { FileUpload } from '../../shared/models/file-upload';
import { finalize } from 'rxjs/operators';


// File upload stuff from:
//  https://medium.com/makonis/queue-multiple-files-for-uploading-with-angular-and-asp-net-core-2-1-e4aad2c52bf
@Injectable({
  providedIn: 'root'
})
export class SubmissionService {
  private _apiEndpoint = '/api/submission';
  
  private _isUploading: boolean;
  private _currentlyUploading: BehaviorSubject<boolean>;
  private _files: FileUpload[] = [];
  private _uploadQueue: BehaviorSubject<FileUpload[]>;

  constructor(private _httpClient: HttpClient) {
    this._isUploading = false;
    this._currentlyUploading = new BehaviorSubject(this._isUploading);
    this._uploadQueue = new BehaviorSubject([]);
  }

  get queue(): Observable<FileUpload[]> {
    return this._uploadQueue.asObservable();
  }

  addToQueue(file: File, submission: Submission) {
    const queuedUploadFile = new FileUpload(file, submission);
    this._files.push(queuedUploadFile);

    this._uploadQueue.next(this._files);

    this.checkAndUploadNextFile();
  }

  private checkAndUploadNextFile() {
    if (this._isUploading) {
      return;
    }

    let firstChoice = this._files.find(f => f.isWaitingForUpload);
    if (firstChoice) {
      this.upload(firstChoice);
    }
  }

  private upload(queuedUploadFile: FileUpload) {
    this.isUploading = true;
    queuedUploadFile.updateProgress(0);

    const request = this.createRequest(queuedUploadFile);
    this._httpClient.request(request)
      .pipe(
        finalize(() => {
          // Upload finished. Whether successful or failed.
          this.isUploading = false;
          this.checkAndUploadNextFile();
        })
      )
      .subscribe(event => {
        if (event.type === HttpEventType.UploadProgress) {
          const percentDone = Math.round(100 * event.loaded / event.total);
          queuedUploadFile.updateProgress(percentDone);
        } else if (event instanceof HttpResponse) {
          queuedUploadFile.completed();
        }

        this._uploadQueue.next(this._files);
      }, (err: HttpErrorResponse) => {
        if (err.error instanceof Error) {
          // A client-side or network error occurred. Handle it accordingly.
          queuedUploadFile.failed();
        } else {
          // The backend returned an unsuccessful response code.
          queuedUploadFile.failed();
        }

        this._uploadQueue.next(this._files);
      }, () => {
        console.info("completed!");
      });
  }

  private set isUploading(value: boolean) {
    this._isUploading = value;
    this._currentlyUploading.next(value);
  }

  private createRequest(queuedUploadFile: FileUpload) {
    const formData = new FormData();
    formData.append('files', queuedUploadFile.file);
    const uri = this._apiEndpoint + "/" + queuedUploadFile.submission.submissionId + "/files";
    const request = new HttpRequest('PUT', uri, formData, {
        reportProgress: true
      });
    return request;
  }

  uploadSubmission(submission: Submission): Observable<any> {
    let formData = new FormData();
    if (submission.files) {
      for (let i = 0; i < submission.files.length; i++) {
        formData.append('Files', submission.files[i]);
      }
    }

    formData.append('AssignmentId', submission.assignmentId.toString());
    formData.append('StudentNumber', submission.studentNumber);
    formData.append('StudentLastname', submission.studentLastname);
    formData.append('StudentFirstname', submission.studentFirstname);

    return this._httpClient.post(this._apiEndpoint, formData);
  }
}
