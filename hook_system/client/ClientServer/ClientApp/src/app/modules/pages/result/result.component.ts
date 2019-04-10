import { Component, OnInit } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { FileService } from '../../../core/services/file.service';
import { Submission } from '../../../shared/models/submission';
import { ResultService } from '../../../core/services/result.service';
import { ResultSet } from '../../../shared/models/result-set';

@Component({
  selector: 'app-result',
  templateUrl: './result.component.html',
  styleUrls: ['./result.component.scss']
})
export class ResultComponent implements OnInit {
  private sub: any;
  id: number;
  result: ResultSet;
  submissions: Submission[];

  constructor(
    private _resultService: ResultService,
    private _fileService: FileService,
    private route: ActivatedRoute
  ) {}

  ngOnInit() {
    this.submissions = [];
    this.sub = this.route.params.subscribe(params => {
      this.id = +params['id'];
    });

    this._resultService.getResultByPackageId(this.id).subscribe(res => {
      this.result = res;
      for (let i = 0; i < this.result.matches.length; i++) {
        for (let j = 0; j < this.result.matches[i].lines.length; j++) {
          const path = this.result.matches[i].lines[j].filePath;
          this.result.matches[i].lines[j].viewFile =
            this.result.files.find(f => f.filePath === path);
        }
      }
    });
  }
}
