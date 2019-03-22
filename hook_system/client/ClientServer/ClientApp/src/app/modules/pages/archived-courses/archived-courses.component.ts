import { Component, OnInit } from '@angular/core';
import { CourseService } from 'src/app/core/services/course.service';
import { Course } from '../../../shared/models/course';
import { FormBuilder, FormGroup, ReactiveFormsModule, FormControl } from '@angular/forms';
import { analyzeAndValidateNgModules } from '@angular/compiler';
import { getEffectiveTypeRoots } from 'typescript';

@Component({
  selector: 'app-archived-courses',
  templateUrl: './archived-courses.component.html',
  styleUrls: ['./archived-courses.component.scss']
})

export class ArchivedCoursesComponent implements OnInit {

  courseForm: FormGroup;
  allCourses: Course[];

  academicYear: string;
  currYear1: any;
  currYear2: any;

  selectedYear: any;
  selectedSemester: any;

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
      semester: new FormControl()
    });

    // this.getPrevCourse();

  }

  // getPrevCourse(): void {
  //   // this.submitted = true;
  //   this.selectedYear = 2019;//this.f.selectedYear.value;
  //   this.selectedSemester = 1;//this.f.selectedSemester.value;
  //   this.courseService.getSemesterCourses(this.selectedYear, this.selectedSemester)
  //     .subscribe(prevCourses => this.prevCourses = prevCourses);
  // }

  getAllCourses(): void {
    this.courseService.getCourses().subscribe(allCourses => this.allCourses = allCourses);
  }

  // convenience getter for easy access to form fields
  get f() {
    return this.courseForm.controls;
  }

  submit(): void {
    this.selectedSemester = this.f.semester.value;
    this.selectedYear = this.f.year.value;
  }

}
