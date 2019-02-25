
# Software Requirements
- dotnet core version 2.2
- postgresql 10
    - You'll also need the npgsql driver, available through the dependency installer
- npm
<<<<<<< HEAD
=======
# Setup
## Database
- Make note of the port you set for the database (default is 5432)
- Also make note of the password you set for the default user
- Create the database and clientserver user. Open a terminal.
    - Login to postgres using the postgres user: 
        - `psql -U postgres`
        - Enter the password you set during the installation
    - Create the clientserver database: 
        - `CREATE DATABASE clientserver;`
        - (NOTE: You can change the username, database name and/or password. Just remain consistent, and modify `appsettings.json` as appropriate)
    - Create the clientserver user: 
        - `CREATE USER clientserver WITH ENCRYPTED PASSWORD 'password';`
    - Give privileges to the new user: 
        - `GRANT ALL PRIVILEGES ON DATABASE clientserver TO clientserver;`
    - Quit psql: 
        - `\q`
- Setup the tables. In a terminal, navigate to the `ClientServer` directory (the directory that contains this README). 
    - Create the Migrations model definitions: 
        - `dotnet ef migrations add InitialCreate`
    - Create the tables in the database: 
        - `dotnet ef database update`

## Angular App
- Trevor, fill this in
    

# Dotnet Core Helpful Links
- Base overview of how to structure the api:
    https://docs.microsoft.com/en-us/aspnet/core/web-api/?view=aspnetcore-2.2
- Querying Related Data:
    https://docs.microsoft.com/en-us/ef/core/querying/related-data
- HTTP Requests:
    https://docs.microsoft.com/en-us/aspnet/core/fundamentals/http-requests?view=aspnetcore-2.2

Base overview of how to structure the api:
    https://docs.microsoft.com/en-us/aspnet/core/web-api/?view=aspnetcore-2.2

Querying Related Data:
    https://docs.microsoft.com/en-us/ef/core/querying/related-data
=======
>>>>>>> 56a1269... Added a bunch of controllers. They'll need to be updated as we find out more of what we need.

# Setup
## Database
- Make note of the port you set for the database (default is 5432)
- Also make note of the password you set for the default user
- Create the database and clientserver user. Open a terminal.
    - Login to postgres using the postgres user: 
        - `psql -U postgres`
        - Enter the password you set during the installation
    - Create the clientserver database: 
        - `CREATE DATABASE clientserver;`
        - (NOTE: You can change the username, database name and/or password. Just remain consistent, and modify `appsettings.json` as appropriate)
    - Create the clientserver user: 
        - `CREATE USER clientserver WITH ENCRYPTED PASSWORD 'password';`
    - Give privileges to the new user: 
        - `GRANT ALL PRIVILEGES ON DATABASE clientserver TO clientserver;`
    - Quit psql: 
        - `\q`
- Setup the tables. In a terminal, navigate to the `ClientServer` directory (the directory that contains this README). 
    - Create the Migrations model definitions: 
        - `dotnet ef migrations add InitialCreate`
    - Create the tables in the database: 
        - `dotnet ef database update`
    

# Dotnet Core Helpful Links
- Base overview of how to structure the api:
    https://docs.microsoft.com/en-us/aspnet/core/web-api/?view=aspnetcore-2.2
- Querying Related Data:
    https://docs.microsoft.com/en-us/ef/core/querying/related-data
- HTTP Requests:
    https://docs.microsoft.com/en-us/aspnet/core/fundamentals/http-requests?view=aspnetcore-2.2

