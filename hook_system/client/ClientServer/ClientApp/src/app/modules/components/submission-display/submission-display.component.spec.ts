import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { SubmissionDisplayComponent } from './submission-display.component';

describe('SubmissionDisplayComponent', () => {
  let component: SubmissionDisplayComponent;
  let fixture: ComponentFixture<SubmissionDisplayComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ SubmissionDisplayComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(SubmissionDisplayComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
