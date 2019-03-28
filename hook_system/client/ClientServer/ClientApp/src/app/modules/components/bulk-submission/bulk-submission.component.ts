import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';
import { SubmissionService } from 'src/app/core/services/submission.service';
import { Submission } from 'src/app/shared/models/submission';

@Component({
  selector: 'app-bulk-submission',
  templateUrl: './bulk-submission.component.html',
  styleUrls: ['./bulk-submission.component.scss']
})
export class BulkSubmissionComponent implements OnInit {
  @Output() submissionMade: EventEmitter<any> = new EventEmitter();
  @Input() assignmentId: number;
  bulkSubmissionFile: File;

  constructor(private _submissionService: SubmissionService) { }

  ngOnInit() { }

  uploadSubmission() {
    this._submissionService.uploadBulkSubmission(this.bulkSubmissionFile, this.assignmentId).subscribe(res => {
      this.submissionMade.emit(res);
    })
  }

  fileChange(event) {
    this.bulkSubmissionFile = event.target.files[0];
  }

}
