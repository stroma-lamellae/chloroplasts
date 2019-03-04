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
}
