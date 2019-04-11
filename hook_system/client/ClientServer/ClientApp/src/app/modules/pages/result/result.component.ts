import { Component, OnInit } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { FileService } from '../../../core/services/file.service';
import { Submission } from '../../../shared/models/submission';
import { ResultService } from '../../../core/services/result.service';
import { ResultSet } from '../../../shared/models/result-set';
import { Line } from '../../../shared/models/package';

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
  toggles: boolean[];
  leftToggles: boolean[];
  rightToggles: boolean[];
  leftChoices: number[];
  rightChoices: number[];

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
      this.toggles = new Array(this.result.matches.length);
      this.leftChoices  = new Array(this.result.matches.length);
      this.rightChoices  = new Array(this.result.matches.length);
      this.leftToggles  = new Array(this.result.matches.length);
      this.rightToggles  = new Array(this.result.matches.length);
      this.toggles.fill(false);
      this.leftChoices.fill(0);
      this.rightChoices.fill(1);
      this.leftToggles.fill(false);
      this.rightToggles.fill(false);
      for (let i = 0; i < this.result.matches.length; i++) {
        for (let j = 0; j < this.result.matches[i].lines.length; j++) {
          const path = this.result.matches[i].lines[j].filePath;
          this.result.matches[i].lines[j].viewFile = this.result.files.find(
            f => f.filePath === path
          );
        }
      }
    });
  }

  toggleMatch(index: number) {
    this.toggles[index] = !this.toggles[index];
  }

  toggleLeftNames(index: number){
    this.leftToggles[index] =  !this.leftToggles[index];
  }

  toggleRightNames(index: number){
    this.rightToggles[index] =  !this.rightToggles[index];
  }

  updateLeftChoice(matchIndex: number, choiceIndex: number){
    this.leftChoices[matchIndex] = choiceIndex;
  }

  updateRightChoice(matchIndex: number, choiceIndex: number){
    this.rightChoices[matchIndex] = choiceIndex;
  }
}
