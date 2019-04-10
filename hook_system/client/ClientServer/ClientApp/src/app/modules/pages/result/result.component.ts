import { Component, OnInit } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { Package, Result } from '../../../shared/models/package';
import { PackageService } from '../../../core/services/package.service';
import { File } from '../../../shared/models/file';
import { FileService } from '../../../core/services/file.service';
import { Submission } from '../../../shared/models/submission';

@Component({
  selector: 'app-result',
  templateUrl: './result.component.html',
  styleUrls: ['./result.component.scss']
})
export class ResultComponent implements OnInit {
  private sub: any;
  id: number;
  package: Package;
  result: Result;
  submissions: Submission[];

  constructor(
    private _packageService: PackageService,
    private _fileService: FileService,
    private route: ActivatedRoute
  ) {}

  ngOnInit() {
    this.submissions = [];
    this.sub = this.route.params.subscribe(params => {
      this.id = +params['id'];
    });

    this._packageService.requestResultsById(this.id).subscribe(packageData => {
      this.package = packageData;
      this.result = this.package.result;
      this.result.matches.forEach(res => {
        res.lines.forEach(line => {
          if (!this.submissions.some(s => s.submissionId === line.submissionId)) {
            this.submissions.push(line.submission);
          }
          const index = this.submissions.indexOf(this.submissions.find(s => s.submissionId === line.submissionId));
          this.submissions[index].viewFiles = [];

          if (!this.submissions[index].viewFiles.some(f => f.filePath === line.filePath)) {
            this._fileService.getFile(line.submissionId, line.filePath).subscribe(fileData => {
              this.submissions[index].viewFiles.push(fileData);
              line.viewFile = fileData;
            });
          } else {
            line.viewFile = this.submissions[index].viewFiles.find(f => f.filePath === line.filePath);
          }
        });
      });
    });

  }
}
