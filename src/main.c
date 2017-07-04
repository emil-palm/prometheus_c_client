#include "prometheus.h"

int main() {
    // Setup collector_registry
    prom_collector_registry *reg = prom_collector_registry_setup(10);

    prom_collector *default_collector = prom_default_collector();

    prom_collector_registry_register(reg, default_collector);

    prom_collector_registry_scrape(reg);

    // Create a metric
    //prom_metric *metric = prom_counter_metric("requests_total","Requests.");

    // Register the collector
    //prom_collector_registry_add_collector(reg, collector);

    // Increase the counter
    //prom_counter_inc(metric);

    // Dump the output
    //printf("%s", prom_collector_registry_export(reg));

    // Relase the collector_registry and its metrics;
    //prom_collector_registry_release(reg);
    return 0;
}

