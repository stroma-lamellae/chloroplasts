import { Component, OnInit } from '@angular/core';
import { CourseService } from '../course/course.service';
import { Course, Assignment } from '../course/course';
import { PackageService } from './package.service';
import { Package, PreviousAssignment } from './package';

@Component({
  selector: 'app-package',
  templateUrl: './package.component.html',
  styleUrls: ['./package.component.scss']
})
export class PackageComponent implements OnInit {
  courses: Course[];

  selectedCourse: Course;
  selectedCourseId: string;

  selectedAssignmentId: string;
  selectedAssignment: Assignment;

  addAssignment: boolean = false;

  supportingAssignments: Assignment[] = [];
  supportingCourse: Course;
  supportingCourseId: string;

  supportingAssignmentId: string;
  supportingAssignment: Assignment;

  constructor(private _courseService: CourseService, private _packageService: PackageService) { }

  ngOnInit() { 
    this._courseService.getCourses().subscribe(res => {
      this.courses = res;
    });
  }

  updateAssignments() {
    this.selectedCourse = this.courses.find(c => c.courseId.toString() == this.selectedCourseId);
    if (!this.selectedCourse.assignments) {
      this._courseService.getCourseAssignments(this.selectedCourse).subscribe(res => {
        this.selectedCourse = res;
      });
    }
  }

  selectAssignment() {
    this.selectedAssignment = this.selectedCourse.assignments.find(a => a.assignmentId.toString() == this.selectedAssignmentId);
  }

  addSupporting() {
    this.supportingCourse = null;
    this.supportingAssignment = null;
    this.addAssignment = true;
  }

  supportSelectCourse() {
    this.supportingCourse = this.courses.find(c => c.courseId.toString() == this.supportingCourseId);
    console.log(this.supportingCourse);
    if (!this.supportingCourse.assignments) {
      this._courseService.getCourseAssignments(this.supportingCourse).subscribe(res => {
        this.supportingCourse = res;
      });
    }
  }

  supportSelectAssignment() {
    this.supportingAssignment = this.supportingCourse.assignments.find(a => a.assignmentId.toString() == this.supportingAssignmentId);
  }

  addSupportingAssignment() {
    this.addAssignment = false;
    this.supportingAssignment.course = this.supportingCourse;
    this.supportingAssignments.push(this.supportingAssignment);
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

    this._packageService.uploadPackage(pack).subscribe(res => {
      console.log(res);
    });
  }
}
