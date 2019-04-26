import { Component, OnInit } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { Submission } from '../../../shared/models/submission';
import { ResultService } from '../../../core/services/result.service';
import { ResultSet } from '../../../shared/models/result-set';
import { PackageService } from '../../../core/services/package.service';
import { Package } from '../../../shared/models/package';

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
  package: Package;
  loading = true;

  constructor(
    private _resultService: ResultService,
    private route: ActivatedRoute,
    private _packageService: PackageService
  ) {}

  ngOnInit() {
    this.submissions = [];
    this.sub = this.route.params.subscribe(params => {
      this.id = +params['id'];
    });
    this._packageService.getPackage(this.id).subscribe(res => {
      this.package = res;
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
        this.result.matches[i].maxPercentage = "0";
        this.result.matches[i].maxLines = 0;
        for (let j = 0; j < this.result.matches[i].lines.length; j++) {
          const path = this.result.matches[i].lines[j].filePath;
          const submissionId = this.result.matches[i].lines[j].submissionId;
          let line = this.result.matches[i].lines[j];
          line.viewFile = this.result.files.find(
            f => f.submissionId == submissionId && f.filePath == path
          );
          // Find out how much of the file this match is
          line.percentage = (((line.lineEnd - line.lineStart) / line.viewFile.lines.length)*100).toFixed(0);
          line.numLines = line.lineEnd - line.lineStart;
          // Save the highest percentage into the match
          if (parseInt(line.percentage) > parseInt(this.result.matches[i].maxPercentage)) {
            this.result.matches[i].maxPercentage = line.percentage;
          }
          if (line.numLines > this.result.matches[i].maxLines) {
            this.result.matches[i].maxLines = line.numLines;
          }

          // Try and fix test naming, so that the TA doesn't get confused by
          //  the file name
          // TODO: Remove after Stage 3 is done
          if (line.submission.studentFirstname.includes("ThisIsTestData")) {
            line.submission.studentFirstname = "";
            line.submission.studentLastname = "Folder";
            line.submission.studentNumber = line.submission.studentNumber.replace(this.result.assignmentName, "");
            while (line.submission.studentNumber.includes("&underscore&")) {
              line.submission.studentNumber = line.submission.studentNumber.replace("&underscore&", "_");
            }
            
          }
        }
      }
      this.result.matches.sort((a,b) => {
        return b.maxLines - a.maxLines;
      });
      this.loading = false;
    }, err => {
      this.loading = false;
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
