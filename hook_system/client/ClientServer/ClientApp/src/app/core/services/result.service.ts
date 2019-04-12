import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';
import { ResultSet } from '../../shared/models/result-set';

@Injectable({
  providedIn: 'root'
})
export class ResultService {
  private _apiEndpoint = '/api/result';

  constructor(private _httpClient: HttpClient) { }

  getResultByPackageId(id: number): Observable<ResultSet> {
    return this._httpClient.get<ResultSet>(
      this._apiEndpoint + '/' + id + '/package'
    );
  }
}
