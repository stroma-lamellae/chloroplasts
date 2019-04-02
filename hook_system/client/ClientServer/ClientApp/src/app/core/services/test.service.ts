import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class TestService {
  private _apiEndpoint = '/api/test';

  constructor(private _httpClient: HttpClient) { }

  uploadTestFile(file: File): Observable<any> {
    let formData = new FormData();
    formData.append("file", file);

    return this._httpClient.post(this._apiEndpoint, formData);
  }
}
