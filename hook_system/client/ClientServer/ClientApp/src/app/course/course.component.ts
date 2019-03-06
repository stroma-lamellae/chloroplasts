import { Component, OnInit } from '@angular/core';
import { CourseService } from './course.service';
import { Course } from './course';

@Component({
  selector: 'app-course',
  templateUrl: './course.component.html',
  styleUrls: ['./course.component.css']
})
export class CourseComponent implements OnInit {

  courses: Course[];

  constructor(private _courseService: CourseService) { }

  ngOnInit() {
    this._courseService.getCourses().subscribe(res => {
      console.log(res);
      if (res.length > 0) {
        console.log(res[0].courseCode);
      }
      this.courses = res;
    });
  }

  addCourse() {
    this.courses.push(new Course());
  }

  updateCourse(origCourse: Course, newCourse: Course) {
    if (newCourse == null) this.courses.splice(this.courses.indexOf(origCourse), 1);
    else origCourse = newCourse;
  }
}
