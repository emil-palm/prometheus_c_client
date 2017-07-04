#include "prometheus.h"

#ifndef REGISTRY_H
#define REGISTRY_H

typedef struct {
   prom_collector** collectors;
   int count;
} prom_collector_registry;


extern prom_collector_registry* prom_collector_registry_setup(int maxCollectors);
extern int prom_collector_registry_register(prom_collector_registry *reg, prom_collector *collector);
extern int prom_collector_registry_unregister(prom_collector_registry *reg, prom_collector *collector);
extern int prom_collector_registry_scrape(prom_collector_registry *reg);
//extern char* prom_collector_registry_export(prom_collector_registry *reg);

#endif
