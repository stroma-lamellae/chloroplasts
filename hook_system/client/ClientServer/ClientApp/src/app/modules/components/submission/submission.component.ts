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
    this._submissionService.uploadSubmission(this.submission).subscribe(res => {
      this.submissionMade.emit(res);
    });
  }

  fileChange(event) {
    this.submission.files = event.target.files;
  }
}
