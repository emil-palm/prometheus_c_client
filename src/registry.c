#include "prometheus.h"

prom_collector_registry* prom_collector_registry_setup(int maxCollectors) {
    prom_collector_registry *reg = malloc(sizeof(prom_collector_registry));
    reg->collectors = malloc(sizeof(prom_collector)*maxCollectors);
    reg->count = 0;

    // Setup the default collector, this should be moved deeper inside the library
    prom_collector *default_collector = prom_default_collector();
    prom_collector_registry_register(reg, default_collector);

    prom_httpd_setup();
    prom_httpd_add_registry("/metrics", reg);

    return reg;
}

int prom_collector_registry_register(prom_collector_registry *reg, prom_collector *collector) {
    reg->collectors[reg->count] = collector;
    reg->count++;
    return 0;
}

int prom_collector_registry_unregister(prom_collector_registry *reg, prom_collector *collector) {
    free(reg->collectors);
    free(reg);
    return 0;
}


int prom_collector_registry_scrape(prom_collector_registry *reg) {
 	for(int i=0; i < reg->count; i++) {
        int return_value = reg->collectors[i]->update();
        if ( return_value != 0 ) {
            return return_value;
        }   
    }
    return 0;
}
