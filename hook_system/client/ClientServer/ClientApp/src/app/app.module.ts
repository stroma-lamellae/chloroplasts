import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { HttpClientModule } from '@angular/common/http';
import { RouterModule } from '@angular/router';

import { AppComponent } from './app.component';
import { NavMenuComponent } from './nav-menu/nav-menu.component';
import { HomeComponent } from './home/home.component';
import { CounterComponent } from './counter/counter.component';
import { FetchDataComponent } from './fetch-data/fetch-data.component';

import { SubmissionComponent } from './course/submission/submission.component';
import { CourseComponent } from './course/course.component';
import { CourseService } from './course/course.service';
import { CourseDetailComponent } from './course/course-detail/course-detail.component';
import { AssignmentComponent } from './course/assignment/assignment.component';
import { PackageComponent } from './package/package.component';
import { PackageService } from './package/package.service';
import { SubmissionService } from './course/submission/submission.service';
import { AssignmentService } from './course/assignment/assignment.service';

@NgModule({
  declarations: [
    AppComponent,
    NavMenuComponent,
    HomeComponent,
    CounterComponent,
    FetchDataComponent,
    SubmissionComponent,
    CourseComponent,
    CourseDetailComponent,
    AssignmentComponent,
    PackageComponent
  ],
  imports: [
    BrowserModule.withServerTransition({ appId: 'ng-cli-universal' }),
    HttpClientModule,
    FormsModule,
    RouterModule.forRoot([
      { path: '', component: HomeComponent, pathMatch: 'full' },
      { path: 'counter', component: CounterComponent },
      { path: 'fetch-data', component: FetchDataComponent },
      { path: 'course', component: CourseComponent},
      { path: 'package', component: PackageComponent}
    ])
  ],
  providers: [CourseService, PackageService, SubmissionService, AssignmentService],
  bootstrap: [AppComponent]
})
export class AppModule { }
