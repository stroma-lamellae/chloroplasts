import { Routes, RouterModule } from '@angular/router';

import { CourseComponent } from './modules/pages/course/course.component';
import { PackageComponent } from './modules/pages/package/package.component';
import { ResultComponent } from './modules/pages/result/result.component';
import { AuthGuard } from './core/guards/auth.guard';
import { DeauthGuard } from './core/guards/deauth.guard';
import { DashboardComponent } from './modules/pages/dashboard/dashboard.component';
import { LoginComponent } from './modules/pages/login/login.component';
import { ArchivedCoursesComponent } from './modules/pages/archived-courses/archived-courses.component';
import { BulkSubmissionComponent } from './modules/components/bulk-submission/bulk-submission.component';
import { SubmissionComponent } from './modules/components/submission/submission.component';

const appRoutes: Routes = [
  { path: '', component: DashboardComponent, canActivate: [AuthGuard] },
  {
    path: 'archived',
    component: ArchivedCoursesComponent,
    canActivate: [AuthGuard]
  },
  { path: 'login', component: LoginComponent, canActivate: [DeauthGuard] },
  { path: 'course', component: CourseComponent, canActivate: [AuthGuard] },
  // Change to SearchComponent
  { path: 'search', component: DashboardComponent, canActivate: [AuthGuard] },
  { path: 'submission', component: SubmissionComponent, canActivate: [AuthGuard] },
  { path: 'package', component: PackageComponent, canActivate: [AuthGuard] },
  { path: 'upload', component: BulkSubmissionComponent, canActivate: [AuthGuard] },
  { path: 'result', component: ResultComponent, canActivate: [AuthGuard] },
  { path: '**', redirectTo: '/' }
];

export const routing = RouterModule.forRoot(appRoutes);
