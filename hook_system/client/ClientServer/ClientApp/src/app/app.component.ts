import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

import { User } from './shared/models/user';
import { AuthenticationService } from './core/services/authentication.service';

@Component({
  selector: 'app',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss']
})
export class AppComponent{
  currentUser: User;
  hideNavigation: Boolean;
  loggedIn: Boolean;
  constructor(
    private router: Router,
    private authenticationService: AuthenticationService
  ) {
    this.authenticationService.currentUser.subscribe(
      x => (this.currentUser = x)
    );
  }

  logout() {
    this.authenticationService.logout();
    this.router.navigate(['/login']);
  }

  toggleNavigation(): void {
    this.hideNavigation = !this.hideNavigation;
  }
}
