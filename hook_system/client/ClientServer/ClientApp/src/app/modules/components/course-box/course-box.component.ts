import { Component, OnInit, Input, EventEmitter, Output } from '@angular/core';
import { Course, Assignment } from '../../../shared/models/course';
import { Observable } from 'rxjs';

@Component({
  selector: 'app-course-box',
  templateUrl: './course-box.component.html',
  styleUrls: ['./course-box.component.scss']
})
export class CourseBoxComponent implements OnInit {

  @Input() course: Course[];

  constructor() {
  }

  ngOnInit() { }

}
