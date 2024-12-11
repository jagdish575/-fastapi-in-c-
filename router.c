#include "router.h"
#include <stdio.h>
#include <string.h>

#define MAX_ROUTES 100

typedef struct {
    char method[10];
    char path[100];
    handler_t handler;
} Route;

static Route routes[MAX_ROUTES];
static int route_count = 0;

void register_route(const char *method, const char *path, handler_t handler) {
    if (route_count < MAX_ROUTES) {
        strncpy(routes[route_count].method, method, sizeof(routes[route_count].method));
        strncpy(routes[route_count].path, path, sizeof(routes[route_count].path));
        routes[route_count].handler = handler;
        route_count++;
    } else {
        printf("Maximum number of routes reached\n");
    }
}

void route_request(const char *method, const char *path) {
    for (int i = 0; i < route_count; i++) {
        if (strcmp(routes[i].method, method) == 0 && strcmp(routes[i].path, path) == 0) {
            routes[i].handler();
            return;
        }
    }
    printf("No route found for %s %s\n", method, path);
}
