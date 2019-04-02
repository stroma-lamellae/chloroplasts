import { Routes, RouterModule } from '@angular/router';

import { CourseComponent } from './modules/pages/course/course.component';
import { PackageComponent } from './modules/pages/package/package.component';
import { ResultComponent } from './modules/pages/result/result.component';
import { AuthGuard } from './core/guards/auth.guard';
import { DashboardComponent } from './modules/pages/dashboard/dashboard.component';
import { LoginComponent } from './modules/pages/login/login.component';
import { ArchivedCoursesComponent } from './modules/pages/archived-courses/archived-courses.component';
import { TestSubmissionComponent } from './modules/pages/test-submission/test-submission.component';

const appRoutes: Routes = [
  { path: '', component: DashboardComponent, canActivate: [AuthGuard] },
  { path: 'archived', component: ArchivedCoursesComponent, canActivate: [AuthGuard] },
  { path: 'login', component: LoginComponent },
  { path: 'course', component: CourseComponent, canActivate: [AuthGuard] },
  { path: 'package', component: PackageComponent, canActivate: [AuthGuard] },
  { path: 'result', component: ResultComponent, canActivate: [AuthGuard] },
  { path: 'test', component: TestSubmissionComponent },
  { path: '**', redirectTo: '/' }
];

export const routing = RouterModule.forRoot(appRoutes);
