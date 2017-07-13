#include "collector.h"
#include <time.h>
// This is made for handling the "process_" type of data that we should implement
typedef struct {
    prom_metric *uptime;
} _default_collector_s;

_default_collector_s *_default_collector;
unsigned long _startTime;

prom_metrics* default_collector_metrics() {
    prom_metrics *metrics = prom_metrics_create();
    prom_metrics_add_metric(metrics, _default_collector->uptime);
    return metrics;
}

int default_collector_update() {
    prom_gauge_set(_default_collector->uptime, _startTime);
    return 0;
}

prom_collector* prom_default_collector() {
    if ( _default_collector  == NULL ) {
        _default_collector = malloc(sizeof(_default_collector_s));
        _default_collector->uptime = prom_gauge_metric("process_start_time_seconds", "Start time of the process since unix epoch in seconds.");
        _startTime = (unsigned long)time(NULL); 
    } 

    prom_collector *collector = malloc(sizeof(prom_collector*));
    collector->update = default_collector_update;
    collector->metrics = default_collector_metrics;

    return collector;
}

prom_collector* prom_create_collector() {
	return malloc(sizeof(prom_collector*));
}

