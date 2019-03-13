import { Routes, RouterModule } from '@angular/router';

import { CourseComponent } from './modules/pages/course/course.component';
import { PackageComponent } from './modules/pages/package/package.component';
import { ResultComponent } from './modules/pages/result/result.component';
import { AuthGuard } from './core/guards/auth.guard';
import { DashboardComponent } from './modules/pages/dashboard/dashboard.component';
import { LoginComponent } from './modules/pages/login/login.component';

const appRoutes: Routes = [
  { path: '', component: DashboardComponent, canActivate: [AuthGuard] },
  { path: 'login', component: LoginComponent },
  { path: 'course', component: CourseComponent, canActivate: [AuthGuard] },
  { path: 'package', component: PackageComponent, canActivate: [AuthGuard] },
  { path: 'result', component: ResultComponent, canActivate: [AuthGuard] },
  { path: '**', redirectTo: '/' }
];

export const routing = RouterModule.forRoot(appRoutes);
