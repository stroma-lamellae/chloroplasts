import { Injectable, Inject } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Course, Assignment } from './course';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class CourseService {

  private _apiEndpoint = "/api/course";
  private _apiAssignmentEndpoint = "/api/assignment";

  constructor(private _httpClient: HttpClient, @Inject("BASE_URL") private baseUrl: string) { }

  getCourses(): Observable<Course[]> {
    return this._httpClient.get<Course[]>(this._apiEndpoint);
  }

  addCourse(course: Course): Observable<Course> {
    return this._httpClient.post<Course>(this._apiEndpoint, course);
  }

  updateCourse(course: Course): Observable<void> {
    return this._httpClient.put<void>(this._apiEndpoint + "/" + course.courseId, course);
  }

  deleteCourse(course: Course): Observable<void> {
    return this._httpClient.delete<void>(this._apiEndpoint + "/" + course.courseId);
  }

  getCourseAssignments(course: Course): Observable<Course> {
    return this._httpClient.get<Course>(this._apiEndpoint + "/" + course.courseId + "/assignments");
  }

  addAssignment(course: Course, assignment: Assignment): Observable<Assignment> {
    assignment.courseId = course.courseId;
    return this._httpClient.post<Assignment>(this._apiAssignmentEndpoint, assignment);
  }

  updateAssignment(assignment: Assignment): Observable<void> {
    return this._httpClient.put<void>(this._apiAssignmentEndpoint + "/" + assignment.assignmentId, assignment);
  }

  deleteAssignment(assignment: Assignment): Observable<void> {
    return this._httpClient.delete<void>(this._apiAssignmentEndpoint + "/" + assignment.assignmentId);
  }
}
