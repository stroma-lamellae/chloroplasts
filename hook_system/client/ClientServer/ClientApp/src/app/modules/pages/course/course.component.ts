import { Component, OnInit } from '@angular/core';
import { CourseService } from '../../../core/services/course.service';
import { Course } from '../../../shared/models/course';
import { ActivatedRoute } from '@angular/router';
import { FormGroup, FormControl } from '@angular/forms';

@Component({
  selector: 'app-course',
  templateUrl: './course.component.html',
  styleUrls: ['./course.component.scss']
})
export class CourseComponent implements OnInit {

  newCourseForm: FormGroup;

  course: Course;
  id: number;
  private sub: any;

  currYear = (new Date().getFullYear().toString());

  selectedYear: string = this.currYear;

  constructor(
    private _courseService: CourseService, 
    private route: ActivatedRoute
  ) {}

  ngOnInit() {
    this.sub  = this.route.params.subscribe(params => {
      this.id = + params['id'];
    });

    if (isNaN(this.id)) {
      this.course = new Course();
    } else {
      this._courseService.getCourse(this.id).subscribe(res => {
        this.course = res;
      });
    }

    this.newCourseForm = new FormGroup({
      year: new FormControl(),
      semester: new FormControl(),
      program: new FormControl(),
      course: new FormControl()
    });
  }

  // TODO: Make this do something
  updateCourse(item1, item2) {
    
  }
}
