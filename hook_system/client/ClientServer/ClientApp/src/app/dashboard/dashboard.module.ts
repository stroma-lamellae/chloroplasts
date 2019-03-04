import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { HomeComponent } from './home/home.component';
import { RootComponent } from './root/root.component';

@NgModule({
  imports: [
    CommonModule
  ],
  declarations: [HomeComponent, RootComponent]
})
export class DashboardModule { }
