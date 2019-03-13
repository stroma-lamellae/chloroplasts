import { Component, OnInit, Input, Output } from '@angular/core';
import { EventEmitter } from '@angular/core';

@Component({
  selector: 'app-navbar',
  templateUrl: './navbar.component.html',
  styleUrls: ['./navbar.component.scss']
})
export class NavbarComponent implements OnInit {
  @Output() toggleNavigationEvent = new EventEmitter();

  toggleNavigation() {
    console.log('Emitted');
    this.toggleNavigationEvent.emit(null);
  }

  constructor() {}
  ngOnInit() {}
}
