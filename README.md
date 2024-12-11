FastAPI-Like Framework in C
A lightweight, FastAPI-inspired web framework built in C for handling HTTP requests with high performance, concurrency, and customizable middleware.

Features
Routing: Easily register and handle routes for different HTTP methods.
Concurrency: Uses POSIX threads to handle multiple client requests concurrently.
Middleware: Support for adding middleware for tasks like logging, authentication, and validation.
Static File Serving: Serve static assets such as CSS, JS, images, and HTML.
OpenAPI Documentation:
Dynamic generation of openapi.json based on registered routes.
Integration with Swagger UI to visualize and interact with the API.
Error Handling: Improved error responses and logging for better debugging and maintenance.


Project Structure

FastAPI-C/
│-- Makefile
│-- server.c
│-- router.c
│-- router.h
│-- server.h
│-- static/
│   ├── index.html
│   ├── swagger-ui.css
│   └── swagger-ui.js
└-- README.md
Getting Started
Requirements
GCC compiler
POSIX threads (pthread library)
Build the Project
Run the following command to compile the code:


make
Run the Server

./server
By default, the server runs on port 8080.

Routes
Registering Routes
In router.c, you can register new routes like this:


add_route("GET", "/hello", hello_handler);
add_route("POST", "/submit", submit_handler);
Middleware
Middleware functions can be added for logging, authentication, and validation. Examples include:

Logging Middleware: Logs all incoming requests.
Auth Middleware: Checks authentication for protected routes.
Validation Middleware: Validates requests based on method and path.
OpenAPI Documentation
The framework automatically generates an openapi.json based on registered routes and serves a Swagger UI for interactive API documentation.

Swagger UI is accessible at: http://localhost:8080/docs
Static Files
Static assets for Swagger UI (CSS, JS) are served from the static/ directory.

Concurrency
The server uses POSIX threads to handle multiple clients concurrently. Each incoming request is processed in a separate thread to ensure high performance.

Error Handling
Improved error handling includes:

Logging detailed error messages.
Returning appropriate HTTP status codes for errors.
Example Requests
Valid Route
bash
Copy code
curl http://localhost:8080/hello
Secure Route (Fails Authentication)

curl http://localhost:8080/secure
Unsupported Method

curl -X POST http://localhost:8080/hello
Future Enhancements
Request Parsing: Support for parsing JSON payloads.
More Middleware: Add more advanced middleware for rate-limiting and CORS.
Database Integration: Connect with databases for dynamic data handling.
License
This project is licensed under the MIT License.

Contributing
Contributions are welcome! Feel free to open issues or submit pull requests.

