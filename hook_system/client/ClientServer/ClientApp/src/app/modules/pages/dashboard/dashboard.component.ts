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
  semesters: any[];

  courses: Course[];

  currYear = (new Date().getFullYear().toString());
  currMonth = (new Date().getMonth());

  constructor(private courseService: CourseService) { }

  ngOnInit() {
    this.semesters = ['Winter', 'Winter', 'Winter', 'Winter', 'Summer', 'Summer', 'Summer', 'Summer', 'Fall', 'Fall', 'Fall', 'Fall'];
    this.semester = this.semesters[(new Date().getMonth())];

    this.getCourse();
  }

  getCourse(): void {

    let sem: any;

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
