import { Routes, RouterModule } from '@angular/router';

import { HomeComponent } from './home/home.component';
import { LoginComponent } from './login/login.component';
import { AuthGuard } from './guards/auth.guard';
import { CourseComponent } from './course/course.component';
import { PackageComponent } from './package/package.component';
import { ResultComponent } from './result/result.component';

const appRoutes: Routes = [
  { path: '', component: HomeComponent, canActivate: [AuthGuard]},
  { path: 'login', component: LoginComponent },
  { path: 'course', component: CourseComponent, canActivate: [AuthGuard]},
  { path: 'package', component: PackageComponent, canActivate: [AuthGuard]},
  { path: 'result', component: ResultComponent, canActivate: [AuthGuard]},
  { path: '**', redirectTo: '/' }
];

export const routing = RouterModule.forRoot(appRoutes);
