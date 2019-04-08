import { Routes, RouterModule } from '@angular/router';

import { PackageComponent } from './modules/pages/package/package.component';
import { ResultComponent } from './modules/pages/result/result.component';
import { AuthGuard } from './core/guards/auth.guard';
import { DeauthGuard } from './core/guards/deauth.guard';
import { DashboardComponent } from './modules/pages/dashboard/dashboard.component';
import { LoginComponent } from './modules/pages/login/login.component';
import { ArchivedCoursesComponent } from './modules/pages/archived-courses/archived-courses.component';
import { ViewSubmissionsComponent } from './modules/pages/view-submissions/view-submissions.component';
import { UploadComponent } from './modules/pages/upload/upload.component';
import { CourseComponent } from './modules/pages/course/course.component';
import { TestSubmissionComponent } from './modules/pages/test-submission/test-submission.component';

const appRoutes: Routes = [
  { path: 'login', component: LoginComponent, canActivate: [DeauthGuard] },
  { path: 'courses', component: DashboardComponent, canActivate: [AuthGuard] },
  { path: 'search', component: ArchivedCoursesComponent, canActivate: [AuthGuard] },
  { path: 'submissions', component: ViewSubmissionsComponent, canActivate: [AuthGuard] },
  { path: 'package', component: PackageComponent, canActivate: [AuthGuard] },
  { path: 'upload', component: UploadComponent, canActivate: [AuthGuard] },
  { path: 'results', component: ResultComponent, canActivate: [AuthGuard] },
  { path: 'test', component: TestSubmissionComponent },
  //Temp remove later
  { path: 'course/:id', component: CourseComponent, canActivate: [AuthGuard]},
  { path: 'newcourse', component: CourseComponent, canActivate: [AuthGuard]},
  { path: '**', redirectTo: '/courses' }
];

export const routing = RouterModule.forRoot(appRoutes);
