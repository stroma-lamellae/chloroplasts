import { Component, OnInit, Input, EventEmitter, Output } from '@angular/core';
import { Course, Assignment } from '../course';
import { CourseService } from '../course.service';
import { Observable } from 'rxjs';
import { AssignmentComponent } from '../assignment/assignment.component';

@Component({
  selector: 'app-course-detail',
  templateUrl: './course-detail.component.html',
  styleUrls: ['./course-detail.component.scss']
})
export class CourseDetailComponent implements OnInit {

  @Input() course: Course;
  @Output() courseChange: EventEmitter<Course> = new EventEmitter();
  showAssignments: boolean = false;

  constructor(private _courseService: CourseService) { 
    this.course = new Course();
  }

  ngOnInit() { }

  submit() {
    if (!this.course.courseId) {
      this._courseService.addCourse(this.course).subscribe(res => {
        this.course = res;
        this.courseChange.emit(this.course);
      });
    } else {
      this._courseService.updateCourse(this.course).subscribe(res => {
        this.courseChange.emit(this.course);
      });
    }
  }

  delete() {
    this._courseService.deleteCourse(this.course).subscribe(res => {
      this.courseChange.emit(null);
    });
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
      this.courseChange.emit(this.course);
    } else if (!origAssignment.assignmentId) {
      this.course.assignments[this.course.assignments.indexOf(origAssignment)] = assignment;
      this.courseChange.emit(this.course);
    } else if (origAssignment.assignmentId) {
      this.course.assignments[this.course.assignments.indexOf(origAssignment)] = assignment;
      this.courseChange.emit(this.course);
    }
  }
}
