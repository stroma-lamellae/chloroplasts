import { Component, OnInit } from '@angular/core';
import { PackageService } from '../../../core/services/package.service';
import { Package, PreviousAssignment } from '../../../shared/models/package';
import { Course, Assignment } from '../../../shared/models/course';
import { CourseService } from 'src/app/core/services/course.service';
import { FormGroup, FormControl } from '@angular/forms';
import { Input, HostListener, Output, EventEmitter } from '@angular/core';

@Component({
  selector: 'app-package',
  templateUrl: './package.component.html',
  styleUrls: ['./package.component.scss']
})
export class PackageComponent implements OnInit {
  @Input() message = 'Select files or drag here';
  fileHover: boolean;
  @Output('fileListChange') fileList: EventEmitter<File[]>;
  @Input('fileList') files: File[] = [];

  packageForm: FormGroup;
  supportForm: FormGroup;

  courses: Course[];

  filteredSemCourses: Course[];
  filteredProgramCourses: Course[];
  filteredSupportSemCourses: Course[];
  filteredSupportProgramCourses: Course[];

  selectedCourse: Course;
  selectedCourseCode: string;
  selectedProgramCode: string;
  selectedSemester: string;
  selectedYear: string;

  selectedSupportYear: string;
  selectedSupportSemester: string;
  selectedSupportProgramCode: string;
  selectedSupportCourseCode: string;

  selectedAssignmentId: string;
  selectedAssignment: Assignment;

  addAssignment = false;

  supportingAssignments: Assignment[] = [];
  supportingCourse: Course;

  supportingAssignmentId: string;
  supportingAssignment: Assignment;

  currYear = (new Date().getFullYear());

  constructor(
    private _courseService: CourseService,
    private _packageService: PackageService
  ) {
    this.fileList = new EventEmitter();
  }

  ngOnInit() {
    this._courseService.getCourses().subscribe(courses => this.courses = courses);

    this.packageForm = new FormGroup({
      year: new FormControl(),
      semester: new FormControl(),
      program: new FormControl(),
      course: new FormControl(),
      assignment: new FormControl()
    });

    this.supportForm = new FormGroup({
      supportYear: new FormControl(),
      supportSemester: new FormControl(),
      supportProgram: new FormControl(),
      supportCourse: new FormControl(),
      supportAssignment: new FormControl()
    });

    this.fileHover = false;
  }

  // convenience getter for easy access to form fields
  get f() {
    return this.packageForm.controls;
  }

  get supportf() {
    return this.supportForm.controls;
  }

  semesterUpdate() {
    this.filteredSemCourses = this.courses.filter(c => c.year.toString() === this.selectedYear)
      .filter(c => c.semester.toString() === this.selectedSemester);
  }

  programUpdate() {
    this.filteredProgramCourses = this.filteredSemCourses.filter(c => c.programCode.toString() === this.selectedProgramCode);
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
  }

  selectAssignment() {
    this.selectedAssignment = this.selectedCourse.assignments.find(
      a => a.assignmentId.toString() === this.selectedAssignmentId
    );
  }

  addSupporting() {
    this.supportingCourse = null;
    this.supportingAssignment = null;
    this.addAssignment = true;
  }

  removeSupportingAssignment(a: Assignment) {
    let removeIndex;
    removeIndex = this.supportingAssignments.indexOf(a);
    this.supportingAssignments.splice(removeIndex, 1);
  }

  supportSemesterUpdate() {
    this.filteredSupportSemCourses = this.courses.filter(c => c.year.toString() === this.selectedSupportYear)
      .filter(c => c.semester.toString() === this.selectedSupportSemester);
  }

  supportProgramUpdate() {
    this.filteredSupportProgramCourses = this.filteredSupportSemCourses.filter(
      c => c.programCode.toString() === this.selectedSupportProgramCode
    );
  }

  supportSelectCourse() {
    this.supportingCourse = this.filteredSupportProgramCourses.find(
      c => c.courseCode.toString() === this.selectedSupportCourseCode
    );
    console.log(this.supportingCourse);
    if (!this.supportingCourse.assignments) {
      this._courseService
        .getCourseAssignments(this.supportingCourse)
        .subscribe(res => {
          this.supportingCourse = res;
        });
    }
  }

  supportSelectAssignment() {
    this.supportingAssignment = this.supportingCourse.assignments.find(
      a => a.assignmentId.toString() === this.supportingAssignmentId
    );
  }

  addSupportingAssignment() {
    this.addAssignment = false;
    this.supportingAssignment.course = this.supportingCourse;
    this.supportingAssignments.push(this.supportingAssignment);

    this.selectedSupportYear = null;
    this.selectedSupportSemester = null;
    this.selectedSupportProgramCode = null;
    this.selectedSupportCourseCode = null;
    this.supportingAssignmentId = null;

    this.supportingCourse = null;

    this.filteredSupportProgramCourses = null;
    this.filteredSupportSemCourses = null;
  }

  @HostListener('dragover', ['$event'])
  public onDragOver($event: DragEvent): void {
    $event.preventDefault();
    this.fileHover= true;
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
    for (let i = 0; i < files.length; i++) {
      this.files.push(files.item(i));
    }
    this.fileList.emit(this.files);
  }

  public removeFile(file: File): void {
    this.files.splice(this.files.indexOf(file), 1);
    this.fileList.emit(this.files);
  }

  submit() {
    console.log(this.supportingAssignments);
    let pack = new Package();
    pack.assignmentId = parseInt(this.selectedAssignmentId);
    pack.previousAssignments = [];
    for (let i = 0; i < this.supportingAssignments.length; i++) {
      let prevAssignment = new PreviousAssignment();
      prevAssignment.assignmentId = this.supportingAssignments[i].assignmentId;
      pack.previousAssignments.push(prevAssignment);
    }
    pack.exclusions = [];
    for(let i = 0; i < this.files.length; i++) {
      pack.exclusions.push(this.files[i]);
    }
    this._packageService.uploadPackage(pack).subscribe(res => {
      console.log(res);
    });

    //reset the page
    this.files = [];

    this.filteredSemCourses = null;
    this.filteredProgramCourses = null;
    this.filteredSupportSemCourses = null;
    this.filteredSupportProgramCourses = null;

    this.selectedCourse = null;
    this.selectedCourseCode = null;
    this.selectedProgramCode = null;
    this.selectedSemester = null;
    this.selectedYear = null;

    this.selectedSupportYear = null;
    this.selectedSupportSemester = null;
    this.selectedSupportProgramCode = null;
    this.selectedSupportCourseCode = null;

    this.selectedAssignmentId = null;
    this.selectedAssignment = null;

    this.addAssignment = false;

    this.supportingAssignments = [];
    this.supportingCourse = null;

    this.supportingAssignmentId = null;
    this.supportingAssignment = null;
  }
}
