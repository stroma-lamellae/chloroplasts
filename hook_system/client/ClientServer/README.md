Base overview of how to structure the api:
    https://docs.microsoft.com/en-us/aspnet/core/web-api/?view=aspnetcore-2.2

Querying Related Data:
    https://docs.microsoft.com/en-us/ef/core/querying/related-data

HTTP Requests:
    https://docs.microsoft.com/en-us/aspnet/core/fundamentals/http-requests?view=aspnetcore-2.2


# Setup:
- Install dotnet core version 2.2
- `dotnet add package Microsoft.EntityFrameworkCore.Sqlite`
- `dotnet ef migrations add InitialCreate`
- `dotnet ef database update`