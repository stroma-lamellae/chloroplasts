import { Component, OnInit } from '@angular/core';
import { TestService } from 'src/app/core/services/test.service';
import { Package } from 'src/app/shared/models/package';
import { PackageService } from 'src/app/core/services/package.service';

@Component({
  selector: 'app-test-submission',
  templateUrl: './test-submission.component.html',
  styleUrls: ['./test-submission.component.scss']
})
export class TestSubmissionComponent implements OnInit {

  testFile: File;
  testName = '';
  package: Package;
  packageWithResults: Package;

  constructor(private _testService: TestService, private _packageService: PackageService) { }

  ngOnInit() { }

  uploadTest() {
    this._testService.uploadTestFile(this.testFile, this.testName).subscribe(res => {
      this.package = res;
    });
  }

  getResults() {
    this._packageService.requestResults(this.package).subscribe(res => {
      this.packageWithResults = res;
    });
  }

  reset() {
    this.package = null;
    this.packageWithResults = null;
    this.testFile = null;
    this.testName = '';
  }

  fileChange(event) {
    this.testFile = event.target.files[0];
  }

}
