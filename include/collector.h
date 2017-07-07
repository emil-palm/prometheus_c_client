#include "prometheus.h"
#include "metric.h"
#ifndef COLLECTOR_H
#define COLLECTOR_H

typedef int (*prom_collector_update_func)();


typedef prom_metrics* (*prom_collector_metrics_func)();

typedef struct {
    prom_collector_update_func update;
    prom_collector_metrics_func metrics;
} prom_collector;

extern prom_collector* prom_create_collector();
extern prom_collector* prom_default_collector();

#endif
