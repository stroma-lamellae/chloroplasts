import { Component, OnInit } from '@angular/core';
import { CourseService } from 'src/app/core/services/course.service';
import { Course } from '../../../shared/models/course';
import { FormBuilder, FormGroup, ReactiveFormsModule, FormControl } from '@angular/forms';

@Component({
  selector: 'app-archived-courses',
  templateUrl: './archived-courses.component.html',
  styleUrls: ['./archived-courses.component.scss']
})

export class ArchivedCoursesComponent implements OnInit {

  courseForm: FormGroup;
  allCourses: Course[];
  searchedSemCourses: Course[];
  searchedProgramCourses: Course[];
  searchedCourseCourses: Course[];

  academicYear: string;
  currYear1: any;
  currYear2: any;

  selectedYear: any;
  selectedSemester: any;
  selectedProgram: any;
  selectedCourse: any;

  yearSelected = false;
  semesterSelected = false;
  programSelected = false;
  courseSelected = false;

  currYear = (new Date().getFullYear());
  currMonth = (new Date().getMonth());

  constructor(
    private courseService: CourseService,
    private formBuilder: FormBuilder
  ) { }

  ngOnInit() {
    if (this.currMonth < 8) {
      this.currYear1 = this.currYear - 1;
      this.currYear2 = this.currYear;
    } else {
      this.currYear1 = this.currYear;
      this.currYear2 = this.currYear + 1;
    }

    this.academicYear = (this.currYear1) + '/' + (this.currYear2);
    this.getAllCourses();

    this.courseForm = new FormGroup({
      year: new FormControl(),
      semester: new FormControl(),
      program: new FormControl(),
      course: new FormControl()
    });

  }

  getAllCourses(): void {
    this.courseService.getCourses().subscribe(allCourses => this.allCourses = allCourses);
  }

  // convenience getter for easy access to form fields
  get f() {
    return this.courseForm.controls;
  }

  yearChange(): void {
    if (this.f.year.value === '') {
      this.yearSelected = false;
      this.semesterSelected = false;
      this.programSelected = false;
      this.courseSelected = false;

      this.selectedYear = '';
      this.selectedSemester = '';
      this.selectedProgram = '';
      this.selectedCourse = '';
    } else {
      this.yearSelected = true;
      this.selectedYear = this.f.year.value;
    }

  }

  semesterChange(): void {
    if (this.f.semester.value === '') {
      this.semesterSelected = false;
      this.programSelected = false;
      this.courseSelected = false;

      this.selectedSemester = '';
      this.selectedProgram = '';
      this.selectedCourse = '';
    } else {
      this.semesterSelected = true;
      this.selectedSemester = this.f.semester.value;
    }

    this.courseService.getSemesterCourses(this.selectedYear, this.selectedSemester)
    .subscribe(allCourses => this.searchedSemCourses = allCourses);
  }

  programChange(): void {
    if (this.f.program.value === '') {
      this.programSelected = false;
      this.courseSelected = false;

      this.selectedProgram = '';
      this.selectedCourse = '';
    } else {
      this.programSelected = true;
      this.selectedProgram = this.f.program.value;
    }

    this.searchedProgramCourses = this.searchedSemCourses.filter(c => c.programCode.toString() === this.f.program.value);

  }

  courseChange(): void {
    if (this.f.course.value === '') {
      this.courseSelected = false;
      this.selectedCourse = '';
    } else {
      this.courseSelected = true;
      this.selectedCourse = this.f.course.value;
    }

    this.searchedCourseCourses = this.searchedProgramCourses.filter(c => c.courseCode.toString() === this.f.course.value);

  }

}
