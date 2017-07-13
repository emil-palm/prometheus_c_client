#include "prometheus.h"

#ifndef HTTPD_H
#define HTTPD_H

extern void prom_httpd_setup();
extern int prom_httpd_add_registry(char *endpoint, 
                prom_collector_registry *reg);
extern int prom_httpd_del_registry(char *endpoint);
extern int prom_httpd_start(int port);
extern void prom_httpd_stop();
extern char** prom_httpd_endpoints();

#endif
