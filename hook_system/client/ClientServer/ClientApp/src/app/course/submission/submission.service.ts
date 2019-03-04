import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Submission } from './submission';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class SubmissionService {

  private _apiEndpoint = "/api/submission";

  constructor(private _httpClient: HttpClient) { }

  uploadSubmission(submission: Submission): Observable<any> {
    let formData = new FormData();

    for (let i = 0; i < submission.files.length; i++) {
      formData.append("Files", submission.files[i]);
    }

    formData.append("AssignmentId", submission.assignmentId.toString());
    formData.append("StudentNumber", submission.studentNumber);
    formData.append("StudentLastname", submission.studentLastname);
    formData.append("StudentFirstname", submission.studentFirstname);

    return this._httpClient.post(this._apiEndpoint, formData);
  }
}
