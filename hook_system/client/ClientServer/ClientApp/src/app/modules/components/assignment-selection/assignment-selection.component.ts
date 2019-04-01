import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';
import { Course, Assignment } from '../../../shared/models/course';
import { CourseService } from 'src/app/core/services/course.service';
import { Observable } from 'rxjs';

@Component({
  selector: 'app-assignment-selection',
  templateUrl: './assignment-selection.component.html',
  styleUrls: ['./assignment-selection.component.scss']
})
export class AssignmentSelectionComponent implements OnInit {

  @Input() courses: Course[];
  // @Output() previousCourses = new EventEmitter<Course[]>();

  selectedCourse: Course;
  selectedCourseId: string;

  constructor(private _courseService: CourseService) {
  }

  ngOnInit() { }

  updateAssignments() {
    this.selectedCourse = this.courses.find(
      c => c.courseId.toString() === this.selectedCourseId
    );
    if (this.selectedCourse.assignments) {
      this._courseService
        .getCourseAssignments(this.selectedCourse)
        .subscribe(res => {
          this.selectedCourse = res;
        });
    }
  }

}
