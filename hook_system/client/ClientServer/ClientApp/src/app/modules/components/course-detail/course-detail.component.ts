import { Component, OnInit, Input, EventEmitter, Output } from '@angular/core';
import { Course, Assignment } from '../../../shared/models/course';
import { CourseService } from '../../../core/services/course.service';
import { Observable } from 'rxjs';
import { AssignmentComponent } from '../assignment/assignment.component';

@Component({
  selector: 'app-course-detail',
  templateUrl: './course-detail.component.html',
  styleUrls: ['./course-detail.component.scss']
})
export class CourseDetailComponent implements OnInit {
  @Input() course: Course;
  showAssignments: boolean = false;

  constructor(private _courseService: CourseService) { 
    this.course = new Course();
  }

  ngOnInit() { }

  submit() {
    if (!this.course.courseId) {
      this._courseService.addCourse(this.course).subscribe(res => {
        this.course = res;
      });
    } else {
      this._courseService.updateCourse(this.course);
    }
  }

  delete() {
    this._courseService.deleteCourse(this.course);
  }

  toggleAssignments() {
    this.showAssignments = !this.showAssignments;
    this._courseService.getCourseAssignments(this.course).subscribe(res => {
      this.course = res;
    });
  }

  addAssignment() {
    let assignment = new Assignment();
    assignment.courseId = this.course.courseId;
    this.course.assignments.push(assignment);
  }

  updateAssignment(origAssignment: Assignment, assignment: Assignment) {
    // Updates the assignment with the output of the AssignmentComponent
    // Needs to update differently based on what was returned
    if (assignment == null) {
      this.course.assignments.splice(this.course.assignments.indexOf(origAssignment), 1);
    } else if (!origAssignment.assignmentId) {
      this.course.assignments[this.course.assignments.indexOf(origAssignment)] = assignment;
    } else if (origAssignment.assignmentId) {
      this.course.assignments[this.course.assignments.indexOf(origAssignment)] = assignment;
    }
  }
}
