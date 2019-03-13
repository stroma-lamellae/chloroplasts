import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { PackageComponent } from './pages/package/package.component';
import { CourseComponent } from './pages/course/course.component';
import { ResultComponent } from './pages/result/result.component';
import { DashboardComponent } from './pages/dashboard/dashboard.component';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { AssignmentComponent } from './components/assignment/assignment.component';
import { SubmissionComponent } from './components/submission/submission.component';
import { CourseDetailComponent } from './components/course-detail/course-detail.component';
import { LoginComponent } from './pages/login/login.component';

@NgModule({
  imports: [CommonModule, FormsModule, ReactiveFormsModule],
  declarations: [
    PackageComponent,
    CourseComponent,
    ResultComponent,
    DashboardComponent,
    AssignmentComponent,
    CourseDetailComponent,
    SubmissionComponent,
    LoginComponent
  ]
})
export class RootModule {}
