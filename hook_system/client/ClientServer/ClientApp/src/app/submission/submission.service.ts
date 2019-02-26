import { Injectable, Inject } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Observable } from 'rxjs';
import { Submission } from './submission';

@Injectable({
  providedIn: 'root'
})
export class SubmissionService {
  private _httpUploadOptions = {
    headers: new HttpHeaders({ "Content-Type": "multipart/form-data", "Accept": "application/json" })
  };

  private _apiEndpoint = "/api/submission";

  constructor(private _httpClient: HttpClient, @Inject("BASE_URL") private baseUrl: string) { }

  uploadSubmission(submission: Submission): Observable<any> {
    let formData = new FormData();

    for (let i = 0; i < submission.Files.length; i++) {
      formData.append("Files", submission.Files[i]);
    }

    formData.append("AssignmentId", submission.AssignmentId.toString());

    return this._httpClient.post(this._apiEndpoint, formData);
  }
}
