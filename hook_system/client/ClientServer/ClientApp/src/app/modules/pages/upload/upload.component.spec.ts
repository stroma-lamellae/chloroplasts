import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { UniquePipe } from '../../../shared/pipes/unique.pipe';
import { UploadComponent } from './upload.component';
import { FormsModule } from '@angular/forms';
import { CourseService } from '../../../core/services/course.service';
import { HttpClient, HttpHandler } from '@angular/common/http';
import { RouterTestingModule } from '@angular/router/testing';

describe('UploadComponent', () => {
  let component: UploadComponent;
  let fixture: ComponentFixture<UploadComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ UploadComponent, UniquePipe ],
      imports: [FormsModule, RouterTestingModule],
      providers: [CourseService, HttpClient, HttpHandler]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(UploadComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
