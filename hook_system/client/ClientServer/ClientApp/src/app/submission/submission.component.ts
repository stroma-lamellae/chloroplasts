import { Component, OnInit } from '@angular/core';
import { SubmissionService } from './submission.service';
import { Submission } from './submission';

@Component({
  selector: 'app-submission',
  templateUrl: './submission.component.html',
  styleUrls: ['./submission.component.css']
})
export class SubmissionComponent implements OnInit {
  private _submission: Submission;

  constructor(private _submissionService: SubmissionService) { }

  ngOnInit() { 
    this._submission = new Submission();
  }

  uploadSubmission(): void {
    this._submission.AssignmentId = 1;
    this._submissionService.uploadSubmission(this._submission).subscribe(res => {
      console.log(res);
    });
  }

  fileChange(event): void {
    this._submission.Files = event.target.files;
  }
}
