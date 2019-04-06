import { Component, OnInit, Input } from '@angular/core';
import { Course, Assignment } from '../../../shared/models/course';
import { Observable } from 'rxjs';
import { RouterLink } from '@angular/router';

@Component({
  selector: 'app-course-box',
  templateUrl: './course-box.component.html',
  styleUrls: ['./course-box.component.scss']
})
export class CourseBoxComponent implements OnInit {

  @Input() course: Course;

  constructor() {
  }

  ngOnInit() { }

}
