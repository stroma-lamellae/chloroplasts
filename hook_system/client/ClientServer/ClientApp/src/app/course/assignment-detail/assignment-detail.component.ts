import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';
import { Assignment } from '../course';

@Component({
  selector: 'app-assignment-detail',
  templateUrl: './assignment-detail.component.html',
  styleUrls: ['./assignment-detail.component.css']
})
export class AssignmentDetailComponent implements OnInit {

  @Input() assignment: Assignment;
  @Output() assignmentChange: EventEmitter<Assignment> = new EventEmitter();

  constructor() { }

  ngOnInit() { }

  update() {
    this.assignmentChange.emit(this.assignment);
  }

  delete() {
    this.assignmentChange.emit(null);
  }
}
