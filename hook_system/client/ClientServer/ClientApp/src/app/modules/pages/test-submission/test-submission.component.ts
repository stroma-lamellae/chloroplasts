import { Component, OnInit } from '@angular/core';
import { TestService } from 'src/app/core/services/test.service';

@Component({
  selector: 'app-test-submission',
  templateUrl: './test-submission.component.html',
  styleUrls: ['./test-submission.component.scss']
})
export class TestSubmissionComponent implements OnInit {

  testFile: File;

  constructor(private _testService: TestService) { }

  ngOnInit() { }

  uploadTest() {
    this._testService.uploadTestFile(this.testFile).subscribe(res => {
      console.log(res);
    });
  }

  fileChange(event) {
    this.testFile = event.target.files[0];
  }

}
