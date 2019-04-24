import { Component, OnInit, Input, Output, EventEmitter, HostListener } from '@angular/core';
import { SubmissionService } from 'src/app/core/services/submission.service';
import { Course, Assignment } from '../../../shared/models/course';
import { CourseService } from 'src/app/core/services/course.service';
import { Router } from '@angular/router';

@Component({
  selector: 'app-upload',
  templateUrl: './upload.component.html',
  styleUrls: ['./upload.component.scss']
})
export class UploadComponent implements OnInit {
  @Input() bulkSubmissionFile: File;
  @Input() selectedAssignmentId: number;
  @Output() submissionMade: EventEmitter<any> = new EventEmitter();

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
    private _submissionService: SubmissionService,
    private _courseService: CourseService,
    private _router: Router
  ) { }

  ngOnInit() {
    this._courseService.getCourses().subscribe(courses => this.courses = courses);
  }

  uploadSubmission() {
    this._submissionService.uploadBulkSubmission(this.bulkSubmissionFile, this.selectedAssignmentId).subscribe(res => {
      this.submissionMade.emit(res);
    });

    // redirect the page to the ViewStatus page
    this._router.navigate(['/dashboard']);
  }

  fileChange(event) {
    this.bulkSubmissionFile = event.target.files[0];
  }

  removeFile() {
    this.bulkSubmissionFile = null;
  }

  @HostListener('dragover', ['$event'])
  public onDragOver($event: DragEvent): void {
    $event.preventDefault();
    this.fileHover = true;
  }

  @HostListener('dragleave', ['$event'])
  public onDragLeave($event: DragEvent): void {
    $event.preventDefault();
    this.fileHover = false;
  }

  @HostListener('drop', ['$event'])
  public onDrop($event: DragEvent): void {
    $event.preventDefault();
    const files = $event.dataTransfer.files;
    this.fileHover = false;
    this.bulkSubmissionFile = files[0];
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
