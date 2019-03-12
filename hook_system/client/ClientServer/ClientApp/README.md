# ClientServer

This project was generated with .NET project generator with angular configurations

## Development server

Development server can be made by running `dotnet watch run` in the dotnet project directory.

## Code scaffolding

Run `ng generate component component-name --spec=false` to generate a new component. You can also use `ng generate directive|pipe|service|class|guard|interface|enum|module`. Always add the `--spec=false` flag so that it doesn't generate spec files in the objects.

## Build

Run `ng build` to build the project. The build artifacts will be stored in the `dist/` directory. Use the `--prod` flag for a production build.

## Running unit tests

Run `ng test` to execute the unit tests via [Karma](https://karma-runner.github.io).

## Running end-to-end tests

Run `ng e2e` to execute the end-to-end tests via [Protractor](http://www.protractortest.org/).

## Further help

To get more help on the Angular CLI use `ng help` or go check out the [Angular CLI README](https://github.com/angular/angular-cli/blob/master/README.md).

## Project structure
```
|-- app
    |-- modules
    |-- home
        |-- components
            |-- [+] package
            |-- [+] assignment
            |-- [+] course-detail
            |-- [+] submission
        |-- pages
            |-- course
                |-- course.component.html
                |-- course.component.scss
                |-- course.component.ts
            |-- [+] dashboard
            |-- [+] result
        |-- root.module.ts
    |-- core
    |-- [+] authentication
    |-- [+] footer
    |-- [+] guards
    |-- [+] http
    |-- [+] interceptors
    |-- [+] mocks
    |-- [+] services
    |-- [+] header
    |-- core.module.ts
    |
    |-- shared
        |-- components
            |-- button.component.html
            |-- button.component.scss
            |-- button.component.ts
        |-- [+] directives
        |-- [+] pipes
        |-- [+] models
    |
    |-- [+] configs
    |-- app.component.html
    |-- app.component.scss
    |-- app.component.ts
    |-- app.module.ts
    |-- app.server.module.ts
|-- assets
    |-- [+] images
    |-- icons 
        |-- favicon.ico
        |-- check.png
```
- Structure from [itnext.io](https://itnext.io/choosing-a-highly-scalable-folder-structure-in-angular-d987de65ec7)