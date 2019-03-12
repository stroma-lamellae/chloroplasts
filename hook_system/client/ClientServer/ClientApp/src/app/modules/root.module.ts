import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { PackageComponent } from './components/package/package.component';
import { CourseComponent } from './pages/course/course.component';
import { ResultComponent } from './pages/result/result.component';
import { DashboardComponent } from './pages/dashboard/dashboard.component';
import { FormsModule } from '@angular/forms';
import { AssignmentComponent } from './components/assignment/assignment.component';
import { SubmissionComponent } from './components/submission/submission.component';
import { CourseDetailComponent } from './components/course-detail/course-detail.component';

@NgModule({
  imports: [CommonModule, FormsModule],
  declarations: [
    PackageComponent,
    CourseComponent,
    ResultComponent,
    DashboardComponent,
    AssignmentComponent,
    CourseDetailComponent,
    SubmissionComponent
  ]
})
export class RootModule {}
