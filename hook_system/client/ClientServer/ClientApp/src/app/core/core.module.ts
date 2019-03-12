import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { ErrorInterceptor } from './interceptors/error.interceptor';
import { JwtInterceptor } from './interceptors/jwt.interceptor';
import { AuthGuard } from './guards/auth.guard';
import { AuthenticationService } from './services/authentication.service';

@NgModule({
  imports: [CommonModule],
  declarations: [
    ErrorInterceptor,
    JwtInterceptor,
    AuthGuard,
    AuthenticationService
  ]
})
export class CoreModule {}
