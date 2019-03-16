import { Component, OnInit, Output, EventEmitter, Input } from '@angular/core';
import { Submission } from '../../../shared/models/submission';
import { SubmissionService } from '../../../core/services/submission.service';

@Component({
  selector: 'app-submission',
  templateUrl: './submission.component.html',
  styleUrls: ['./submission.component.scss']
})
export class SubmissionComponent implements OnInit {

  submission: Submission;
  @Output() submissionMade: EventEmitter<Submission> = new EventEmitter();
  @Input() assignmentId: number;

  constructor(private _submissionService: SubmissionService) { 
    this.submission = new Submission();
  }

  ngOnInit() { }

  uploadSubmission() {
    this.submission.assignmentId = this.assignmentId;
    const submissionFiles = this.submission.files;
    // Set to null to prevent a bulk upload in one request
    this.submission.files = null; 
    // Upload the submission, then upload all the files
    this._submissionService.uploadSubmission(this.submission).subscribe(res => {
      this.submissionMade.emit(res);
      for (const key in submissionFiles) {
        this._submissionService.addToQueue(submissionFiles[key], res);
      }
    });
  }

  fileChange(event) {
    this.submission.files = event.target.files;
  }
}
