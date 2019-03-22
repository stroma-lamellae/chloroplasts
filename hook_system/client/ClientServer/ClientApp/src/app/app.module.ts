import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { HttpClientModule, HTTP_INTERCEPTORS } from '@angular/common/http';
import { routing } from './app.routing';

import { ErrorInterceptor } from './core/interceptors/error.interceptor';
import { JwtInterceptor } from './core/interceptors/jwt.interceptor';

import { AppComponent } from './app.component';
import { RootModule } from './modules/root.module';
import { NavbarComponent } from './shared/components/navbar/navbar.component';
import { UniquePipe } from './shared/pipes/unique.pipe';


@NgModule({
  declarations: [
    AppComponent,
    NavbarComponent,
	UniquePipe,
  ],
  imports: [
    BrowserModule.withServerTransition({ appId: 'ng-cli-universal' }),
    HttpClientModule,
    FormsModule,
    ReactiveFormsModule,
    RootModule,
    routing
  ],
  providers: [
    { provide: HTTP_INTERCEPTORS, useClass: JwtInterceptor, multi: true },
    { provide: HTTP_INTERCEPTORS, useClass: ErrorInterceptor, multi: true },
  ],
  export: [
	UniquePipe
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
