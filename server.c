#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    read(client_socket, buffer, BUFFER_SIZE);
    printf("Received request:\n%s\n", buffer);

    // Simple HTTP response
    const char *response = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 13\r\n"
        "\r\n"
        "Hello, World!";
    
    write(client_socket, response, strlen(response));
    close(client_socket);
}

void start_server(int port) {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Attach socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Bind the socket to the address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 10) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", port);

    // Accept and handle client connections
    while (1) {
        if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("Accept failed");
            continue;
        }

        handle_client(client_fd);
    }
}

''' add static file to servet'''

void serve_static_file(int client_socket, const char *file_path) {
    int fd = open(file_path, O_RDONLY);
    if (fd < 0) {
        const char *not_found = "HTTP/1.1 404 Not Found\r\n\r\nFile not found.";
        write(client_socket, not_found, strlen(not_found));
        return;
    }

    char buffer[1024];
    int bytes_read;
    write(client_socket, "HTTP/1.1 200 OK\r\n\r\n", 19);
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        write(client_socket, buffer, bytes_read);
    }
    close(fd);
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    read(client_socket, buffer, BUFFER_SIZE);
    
    // Check for the /docs path
    if (strncmp(buffer, "GET /docs", 9) == 0) {
        serve_static_file(client_socket, "swagger/index.html");
    } else {
        const char *response = "HTTP/1.1 404 Not Found\r\n\r\nPage not found.";
        write(client_socket, response, strlen(response));
    }

    close(client_socket);
}