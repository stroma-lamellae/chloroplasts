import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';
import { File } from '../../shared/models/file';

@Injectable({
  providedIn: 'root'
})
export class FileService {
  private _apiEndpoint = 'api/file';

  constructor(private _httpClient: HttpClient) { }

  getFile(submissionId: number, filePath: string): Observable<File> {
    return this._httpClient.get<File>(
      this._apiEndpoint + '/' + submissionId + "?filePath="+filePath
    );
  }

}
