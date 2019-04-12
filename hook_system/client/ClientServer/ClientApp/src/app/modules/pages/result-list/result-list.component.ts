import { Component, OnInit } from '@angular/core';
import { Package } from '../../../shared/models/package';
import { PackageService } from '../../../core/services/package.service';

@Component({
  selector: 'app-result-list',
  templateUrl: './result-list.component.html',
  styleUrls: ['./result-list.component.scss']
})
export class ResultListComponent implements OnInit {
  packages: Package[] = [];

  constructor(private _packageService: PackageService) {}

  ngOnInit() {
    this._packageService.getPackages().subscribe(res => {
      this.packages = res;
    });
  }

  getResults(pack: Package) {
    console.log(pack);
    if (!pack.result) {
      this._packageService.requestResults(pack).subscribe(res => {
        console.log(res);
        this.packages[this.packages.indexOf(pack)] = res;
      });
    }
  }
}
