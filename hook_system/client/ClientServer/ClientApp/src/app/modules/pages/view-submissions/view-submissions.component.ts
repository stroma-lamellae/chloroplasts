import { Component, OnInit, Input } from '@angular/core';
import { Course, Assignment } from 'src/app/shared/models/course';
import { CourseService } from 'src/app/core/services/course.service';
import { Router } from '@angular/router';

@Component({
  selector: 'app-view-submissions',
  templateUrl: './view-submissions.component.html',
  styleUrls: ['./view-submissions.component.scss']
})
export class ViewSubmissionsComponent implements OnInit {
  @Input() selectedAssignmentId: number;

  Semester = ['Fall', 'Winter', 'Summer'];

  courses: Course[];

  filteredYearCourses: Course[];
  filteredSemCourses: Course[];
  filteredProgramCourses: Course[];

  selectedCourse: Course;
  selectedCourseCode: string;
  selectedProgramCode: string;
  selectedSemester: string;
  selectedYear: string;

  selectedAssignment: Assignment;

  fileHover = false;

  constructor(
    private _courseService: CourseService,
    private _router: Router
  ) { }

  ngOnInit() {
    this._courseService.getCourses().subscribe(courses => this.courses = courses);
  }

  yearUpdate() {
    this.filteredYearCourses = this.courses.filter(
      c => c.year.toString() === this.selectedYear
    );

    this.selectedSemester = null;
    this.selectedProgramCode = null;
    this.selectedCourse = null;
    this.selectedCourseCode = null;
    this.selectedAssignmentId = null;
    this.selectedAssignment = null;

    this.filteredSemCourses = null;
    this.filteredProgramCourses = null;
  }

  semesterUpdate() {
    this.filteredSemCourses = this.filteredYearCourses.filter(
      c => c.semester.toString() === this.selectedSemester
    );

    this.selectedProgramCode = null;
    this.selectedCourse = null;
    this.selectedCourseCode = null;
    this.selectedAssignmentId = null;
    this.selectedAssignment = null;

    this.filteredProgramCourses = null;
  }

  programUpdate() {
    this.filteredProgramCourses = this.filteredSemCourses.filter(
      c => c.programCode.toString() === this.selectedProgramCode
    );
    this.selectedCourse = null;
    this.selectedCourseCode = null;
    this.selectedAssignmentId = null;
    this.selectedAssignment = null;
  }

  updateAssignments() {
    this.selectedCourse = this.filteredProgramCourses.find(
      c => c.courseCode.toString() === this.selectedCourseCode
    );
    if (this.selectedCourse.assignments) {
      this._courseService
        .getCourseAssignments(this.selectedCourse)
        .subscribe(res => {
          this.selectedCourse = res;
        });
    }
    this.selectedAssignmentId = null;
    this.selectedAssignment = null;
  }

  selectAssignment() {
    this.selectedAssignment = this.selectedCourse.assignments.find(
      a => a.assignmentId.toString() === this.selectedAssignmentId.toString()
    );
  }

}
