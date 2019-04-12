import { Injectable } from '@angular/core';
import { HttpInterceptor, HttpRequest, HttpEvent, HttpHandler } from '@angular/common/http';
import { Observable, throwError } from 'rxjs';
import { catchError } from 'rxjs/operators';
import { ToastrService } from 'ngx-toastr';

@Injectable()
export class ToastInterceptor implements HttpInterceptor {
    constructor(private toastr: ToastrService) { }

    intercept(request: HttpRequest<any>, next: HttpHandler): Observable<HttpEvent<any>> {
        return next.handle(request).pipe(catchError(err => {
            let error = ""; 
            if (err.status == 500) {
                error = "Internal Server Error. Please contact the System Administrator.";
            } else {
                if (err.error) {
                    error = err.error.title || err.error.login_failure || err.error || err.statusText;
                } else {
                    error = err.error || err.statusText;
                }
            }
            this.toastr.error(error, "Error", {
                onActivateTick: true
            });
            return throwError(err);
        }));
    }
}
