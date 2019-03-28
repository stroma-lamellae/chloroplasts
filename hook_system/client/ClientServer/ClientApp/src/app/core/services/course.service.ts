import { Injectable, Inject } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Course, Assignment } from '../../shared/models/course';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class CourseService {

  private _apiEndpoint = '/api/course';

  constructor(private _httpClient: HttpClient) { }

  getCourses(): Observable<Course[]> {
    return this._httpClient.get<Course[]>(this._apiEndpoint);
  }

  getYearCourses(year): Observable<Course[]> {
    return this._httpClient.get<Course[]>(this._apiEndpoint + '/' + year);
  }

  getSemesterCourses(year, semester): Observable<Course[]> {
    return this._httpClient.get<Course[]>(this._apiEndpoint + '/' + year + '/' + semester);
  }

  addCourse(course: Course): Observable<Course> {
    return this._httpClient.post<Course>(this._apiEndpoint, course);
  }

  updateCourse(course: Course): Observable<void> {
    return this._httpClient.put<void>(this._apiEndpoint + '/' + course.courseId, course);
  }

  deleteCourse(course: Course): Observable<void> {
    return this._httpClient.delete<void>(this._apiEndpoint + '/' + course.courseId);
  }

  getCourseAssignments(course: Course): Observable<Course> {
    return this._httpClient.get<Course>(this._apiEndpoint + '/' + course.courseId + '/assignments');
  }

}
