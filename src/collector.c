#include "collector.h"

typedef struct {
    prom_metric* counter;
} _default_collector_s;

_default_collector_s *_default_collector;

prom_metrics* default_collector_metrics() {
    prom_metrics *metrics = malloc(sizeof(prom_metrics));
    prom_metrics_add_metric(metrics, _default_collector->counter);
    return metrics;
}

int default_collector_update() {
    prom_metric *metric = prom_counter_metric("requests_total","Requests.");
    prom_counter_inc(metric);
    return 0;
}

prom_collector* prom_default_collector() {
    if ( _default_collector  == NULL ) {
        _default_collector = malloc(sizeof(_default_collector_s));
    } 

    prom_collector *collector = malloc(sizeof(prom_collector*));
    collector->update = default_collector_update;
    collector->metrics = default_collector_metrics;

    return collector;
}

