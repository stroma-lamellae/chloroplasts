import { Pipe, PipeTransform } from '@angular/core';

@Pipe({name: 'unique'})

export class UniquePipe implements PipeTransform {
    transform(value: any): any {
        return value + '-unique';
    }
}
