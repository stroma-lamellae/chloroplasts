import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Course, Assignment } from '../course';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class AssignmentService {

  private _apiEndpoint = "/api/assignment";

  constructor(private _httpClient: HttpClient) { }

  addAssignment(assignment: Assignment): Observable<Assignment> {
    return this._httpClient.post<Assignment>(this._apiEndpoint, assignment);
  }

  updateAssignment(assignment: Assignment): Observable<void> {
    return this._httpClient.put<void>(this._apiEndpoint + "/" + assignment.assignmentId, assignment);
  }

  deleteAssignment(assignment: Assignment): Observable<void> {
    return this._httpClient.delete<void>(this._apiEndpoint + "/" + assignment.assignmentId);
  }
}
