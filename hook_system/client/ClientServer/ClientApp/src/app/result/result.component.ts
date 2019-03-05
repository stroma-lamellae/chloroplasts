import { Component, OnInit } from '@angular/core';
import { PackageService } from '../package/package.service';
import { Package } from '../package/package';

@Component({
  selector: 'app-result',
  templateUrl: './result.component.html',
  styleUrls: ['./result.component.css']
})
export class ResultComponent implements OnInit {

  packages: Package[] = [];

  constructor(private _packageService: PackageService) { }

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
