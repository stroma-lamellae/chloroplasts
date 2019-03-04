import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { HttpClientModule, HTTP_INTERCEPTORS } from '@angular/common/http';
import { routing } from './app.routing';

import { AppComponent } from './app.component';
import { HomeComponent } from './home/home.component';
import { LoginComponent } from './login/login.component';
import { ErrorInterceptor } from './shared/helpers/error.interceptor';
import { JwtInterceptor } from './shared/helpers/jwt.interceptor';

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
    HomeComponent,
    LoginComponent,
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
    ReactiveFormsModule,
    routing
  ],
  providers: [
    { provide: HTTP_INTERCEPTORS, useClass: JwtInterceptor, multi: true },
    { provide: HTTP_INTERCEPTORS, useClass: ErrorInterceptor, multi: true },
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
