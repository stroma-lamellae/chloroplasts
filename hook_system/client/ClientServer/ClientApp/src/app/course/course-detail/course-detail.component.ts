import { Component, OnInit, Input, EventEmitter, Output } from '@angular/core';
import { Course, Assignment } from '../course';
import { CourseService } from '../course.service';
import { Observable } from 'rxjs';

@Component({
  selector: 'app-course-detail',
  templateUrl: './course-detail.component.html',
  styleUrls: ['./course-detail.component.css']
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
    this.course.assignments.push(new Assignment());
  }

  updateAssignment(origAssignment: Assignment, assignment: Assignment) {
    if (assignment == null) {
      this._courseService.deleteAssignment(origAssignment).subscribe(res => {
        this.course.assignments.splice(this.course.assignments.indexOf(origAssignment), 1);
        this.courseChange.emit(this.course);
      });
    } else if (!assignment.assignmentId) {
      this._courseService.addAssignment(this.course, assignment).subscribe(res => {
        this.course.assignments[this.course.assignments.indexOf(origAssignment)] = res;
        this.courseChange.emit(this.course);
      });
    } else if (assignment.assignmentId) {
      this._courseService.updateAssignment(assignment).subscribe(res => {
        this.course.assignments[this.course.assignments.indexOf(origAssignment)] = assignment;
        this.courseChange.emit(this.course);
      });
    }
  }
}
