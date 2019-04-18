import { Component, OnInit } from '@angular/core';
import { CourseService } from '../../../core/services/course.service';
import { Course } from '../../../shared/models/course';
import { ActivatedRoute } from '@angular/router';

@Component({
  selector: 'app-course',
  templateUrl: './course.component.html',
  styleUrls: ['./course.component.scss']
})
export class CourseComponent implements OnInit {

  course: Course;
  id: number;
  private sub: any;

  title: string;

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
      this.title = 'Add a New Course';
    } else {
      this._courseService.getCourse(this.id).subscribe(res => {
        this.course = res;
      });
      this.title = 'Update Course';
    }
  }

  // TODO: Make this do something
  // updateCourse(item1, item2) {
    
  // }
}
