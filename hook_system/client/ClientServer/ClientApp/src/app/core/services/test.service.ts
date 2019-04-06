import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class TestService {
  private _apiEndpoint = '/api/test';

  constructor(private _httpClient: HttpClient) { }

  uploadTestFile(file: File, testName: string): Observable<any> {
    let formData = new FormData();
    formData.append("File", file);
    formData.append("TestName", testName);
    formData.append("Email", "myEmail");

    return this._httpClient.post(this._apiEndpoint, formData);
  }
}
