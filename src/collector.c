#include "collector.h"

// This is made for handling the "process_" type of data that we should implement
typedef struct {
} _default_collector_s;

_default_collector_s *_default_collector;

prom_metrics* default_collector_metrics() {
    prom_metrics *metrics = prom_metrics_create();
    return metrics;
}

int default_collector_update() {
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

prom_collector* prom_create_collector() {
	return malloc(sizeof(prom_collector*));
}

