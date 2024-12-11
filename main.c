#include "server.h"
#include "router.h"
#include <stdio.h>

// Sample handler function
void hello_handler() {
    printf("Hello, World Handler Invoked\n");
}

int main() {
    // Register routes
    register_route("GET", "/hello", hello_handler);

    // Start the server on port 8080
    start_server(8080);

    return 0;
}
