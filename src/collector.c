#include "collector.h"
#include <time.h>
// This is made for handling the "process_" type of data that we should implement
typedef struct {
    prom_metrics *user_metrics;
    prom_metric *uptime;
} _default_collector_s;

_default_collector_s *_default_collector;

prom_metrics* default_collector_metrics() {
    prom_metrics *metrics = prom_metrics_create();
    prom_metrics_add_metric(metrics, _default_collector->uptime);
    for(int i=0; i < _default_collector->user_metrics->length; i++) {
        prom_metrics_add_metric(metrics, _default_collector->user_metrics->list[i]);
    }
    return metrics;
}

int default_collector_update() {
    return 0;
}

prom_collector* prom_default_collector() {
    if ( _default_collector  == NULL ) {
        _default_collector = malloc(sizeof(_default_collector_s));
        _default_collector->user_metrics = prom_metrics_create();
        _default_collector->uptime = prom_gauge_metric("process_start_time_seconds", "Start time of the process since unix epoch in seconds.");
        prom_gauge_set(_default_collector->uptime, (unsigned long)time(NULL));
    } 

    prom_collector *collector = malloc(sizeof(prom_collector*));
    collector->update = default_collector_update;
    collector->metrics = default_collector_metrics;

    return collector;
}

prom_collector* prom_create_collector() {
	return malloc(sizeof(prom_collector*));
}

int prom_collector_default_add_metric(prom_metric *metric) {
    return prom_metrics_add_metric(_default_collector->user_metrics, metric);
}

