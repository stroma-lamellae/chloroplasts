import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { PackageComponent } from './components/package/package.component';
import { CourseComponent } from './pages/course/course.component';
import { ResultComponent } from './pages/result/result.component';
import { DashboardComponent } from './pages/dashboard/dashboard.component';
import { FormsModule } from '@angular/forms';
import { AssignmentComponent } from './pages/course/assignment/assignment.component';
import { CourseDetailComponent } from './pages/course/course-detail/course-detail.component';
import { SubmissionComponent } from './pages/course/submission/submission.component';

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
