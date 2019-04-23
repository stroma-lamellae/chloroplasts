import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';
import { SubmissionService } from 'src/app/core/services/submission.service';
import { Course, Assignment } from '../../../shared/models/course';
import { CourseService } from 'src/app/core/services/course.service';

@Component({
  selector: 'app-upload',
  templateUrl: './upload.component.html',
  styleUrls: ['./upload.component.scss']
})
export class UploadComponent implements OnInit {
  @Output() submissionMade: EventEmitter<any> = new EventEmitter();
  @Input() assignmentId: number;
  bulkSubmissionFile: File;

  courses: Course[];

  filteredYearCourses: Course[];
  filteredSemCourses: Course[];
  filteredProgramCourses: Course[];
  filteredSupportYearCourses: Course[];
  filteredSupportSemCourses: Course[];
  filteredSupportProgramCourses: Course[];

  selectedCourse: Course;
  selectedCourseCode: string;
  selectedProgramCode: string;
  selectedSemester: string;
  selectedYear: string;

  selectedAssignmentId: number;
  selectedAssignment: Assignment;

  constructor(
    private _submissionService: SubmissionService,
    private _courseService: CourseService,
  ) { }

  ngOnInit() {
    this._courseService.getCourses().subscribe(courses => this.courses = courses);
  }

  uploadSubmission() {
    this._submissionService.uploadBulkSubmission(this.bulkSubmissionFile, this.selectedAssignmentId).subscribe(res => {
      this.submissionMade.emit(res);
    });
  }

  yearUpdate() {
    this.filteredYearCourses = this.courses.filter(
      c => c.year.toString() === this.selectedYear
    );

    this.selectedSemester = null;
    this.selectedProgramCode = null;
    this.selectedCourse = null;
    this.selectedAssignmentId = null;

    this.filteredSemCourses = null;
    this.filteredProgramCourses = null;
  }

  semesterUpdate() {
    this.filteredSemCourses = this.filteredYearCourses.filter(
      c => c.semester.toString() === this.selectedSemester
    );

    this.selectedProgramCode = null;
    this.selectedCourse = null;
    this.selectedAssignmentId = null;
    this.filteredProgramCourses = null;
  }

  programUpdate() {
    this.filteredProgramCourses = this.filteredSemCourses.filter(
      c => c.programCode.toString() === this.selectedProgramCode
    );
    this.selectedCourse = null;
    this.selectedAssignmentId = null;
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
  }

  selectAssignment() {
    this.selectedAssignment = this.selectedCourse.assignments.find(
      a => a.assignmentId.toString() === this.selectedAssignmentId.toString()
    );
  }

}
