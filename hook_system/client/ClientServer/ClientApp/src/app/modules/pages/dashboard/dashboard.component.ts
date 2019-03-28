import { Component, OnInit } from '@angular/core';
import { CourseService } from 'src/app/core/services/course.service';
import { Course} from '../../../shared/models/course';

@Component({
  selector: 'app-dashboard',
  templateUrl: './dashboard.component.html',
  styleUrls: ['./dashboard.component.scss']
})
export class DashboardComponent implements OnInit {

  semester: string;

  courses: Course[];
  courseCodes: string[];

  currYear = (new Date().getFullYear().toString());
  currMonth = (new Date().getMonth());

  constructor(private courseService: CourseService) { }

  ngOnInit() {
    if (this.currMonth < 4) {
      this.semester = 'Winter';
    } else if (this.currMonth < 8) {
      this.semester = 'Summer';
    } else {
      this.semester = 'Fall';
    }

    this.getCourse();
  }

  getCourse(): void {

    let sem: number;

    if (this.currMonth < 4) {
      sem = 1;
    } else if (this.currMonth < 8) {
      sem = 2;
    } else {
      sem = 0;
    }

    this.courseService.getSemesterCourses(this.currYear, sem).subscribe(courses => this.courses = courses);
  }

}
