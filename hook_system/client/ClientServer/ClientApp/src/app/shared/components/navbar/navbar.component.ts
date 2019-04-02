import { Component, OnInit, Input, Output } from '@angular/core';
import { EventEmitter } from '@angular/core';
import { AuthenticationService } from 'src/app/core/services/authentication.service';
import { Router } from '@angular/router';
@Component({
  selector: 'app-navbar',
  templateUrl: './navbar.component.html',
  styleUrls: ['./navbar.component.scss']
})
export class NavbarComponent implements OnInit {
  @Output() toggleNavigationEvent = new EventEmitter();

  constructor(
    private authenticationService: AuthenticationService,
    private router: Router
  ) {}
  toggleNavigation() {
    console.log('Emitted');
    this.toggleNavigationEvent.emit(null);
  }

  logout() {
    this.authenticationService.logout();
    this.router.navigate(['/login']);
  }
  ngOnInit() {}
}
