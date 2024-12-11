#ifndef ROUTER_H
#define ROUTER_H

typedef void (*handler_t)(void);

void register_route(const char *method, const char *path, handler_t handler);
void route_request(const char *method, const char *path);

#endif // ROUTER_H
