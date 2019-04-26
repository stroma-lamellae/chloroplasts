import {
  Component,
  OnInit,
  Input,
  OnChanges,
  SimpleChanges,
  SimpleChange
} from '@angular/core';
import { SubmissionService } from 'src/app/core/services/submission.service';
import { Submission } from 'src/app/shared/models/submission';

@Component({
  selector: 'app-submission-display',
  templateUrl: './submission-display.component.html',
  styleUrls: ['./submission-display.component.scss']
})
export class SubmissionDisplayComponent implements OnInit, OnChanges {
  @Input() assignmentId: number;
  private _assignmentId: number;
  private _submissions: Submission[];
  private _selectedSubmission: Submission;
  private _fileList: string[];
  private _selectedFile: string[];
  private _selectedFileIndex: number;
  private studentIsSelected: boolean;
  constructor(private _submissionService: SubmissionService) {
    this._fileList = [];
    this._selectedFile = [];
    this.studentIsSelected = false;
  }

  ngOnInit() {  }

  ngOnChanges(changes: SimpleChanges): void {
    const assignmentId: SimpleChange = changes.assignmentId;
    this._assignmentId = assignmentId.currentValue;
    console.log(changes);
    if(this._assignmentId !== undefined && this.assignmentId !== null && this.assignmentId !== -1) {
      this._submissionService
        .getSubmissionsForAssignment(this._assignmentId)
        .subscribe(res => {
          this._submissions = res;
        });
    }
  }

  selectSubmission(submission: Submission){
    this._selectedSubmission = submission;
    this._submissionService
    .getFolderListing(this._selectedSubmission.submissionId)
    .subscribe( res => {
      this._fileList = res;
    });
    this.studentIsSelected = true;
  }

  selectFile(filename: string, index: number){
    this._submissionService
    .getFileContents(filename, this._selectedSubmission.submissionId)
    .subscribe( res => {
      this._selectedFile = res;
    });
    this._selectedFileIndex = index;
  }

  goBack(){
    this.studentIsSelected = false;
    this._selectedFile = [];
  }


}
