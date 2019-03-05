import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Package } from './package';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class PackageService {

  private _apiEndpoint = "/api/package";

  constructor(private _httpClient: HttpClient) { }

  uploadPackage(pack: Package): Observable<any> {
    return this._httpClient.post(this._apiEndpoint, pack);
  }

  getPackages(): Observable<Package[]> {
    return this._httpClient.get<Package[]>(this._apiEndpoint);
  }

  requestResults(pack: Package): Observable<Package> {
    return this._httpClient.get<Package>(this._apiEndpoint + "/" + pack.packageId + "/results");
  }
}
