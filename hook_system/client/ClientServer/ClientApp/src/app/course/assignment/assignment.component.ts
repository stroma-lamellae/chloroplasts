import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';
import { Assignment } from '../course';
import { CourseService } from '../course.service';
import { AssignmentService } from './assignment.service';

@Component({
  selector: 'app-assignment',
  templateUrl: './assignment.component.html',
  styleUrls: ['./assignment.component.scss']
})
export class AssignmentComponent implements OnInit {

  @Input() assignment: Assignment;
  @Output() assignmentChange: EventEmitter<Assignment> = new EventEmitter();
  showSubmission = false;

  constructor(private _assignmentService: AssignmentService) { }

  ngOnInit() { }

  update() {
    // Has an ID, so update it
    if (this.assignment.assignmentId) {
      this._assignmentService.updateAssignment(this.assignment).subscribe(res => {
        this.assignmentChange.emit(this.assignment);
      });
    } else {
      // No ID, so add the assignment
      this._assignmentService.addAssignment(this.assignment).subscribe(res => {
        this.assignment = res;
        this.assignmentChange.emit(res);
      })
    }
  }

  delete() {
    this._assignmentService.deleteAssignment(this.assignment).subscribe(res => {
      this.assignmentChange.emit(null);
    });
  }

  toggleSubmission() {
    this.showSubmission = !this.showSubmission;
  }

  submissionMade() {
    this.showSubmission = false;
  }
}
