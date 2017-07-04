#include "prometheus.h"

prom_collector_registry* prom_collector_registry_setup(int maxCollectors) {
    prom_collector_registry *reg = malloc(sizeof(prom_collector_registry));
    reg->collectors = malloc(sizeof(prom_collector)*maxCollectors);
    reg->count = 0;
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

/*
char* prom_collector_registry_export(prom_collector_registry *reg) {
	char buffer[9000];
	size_t totalSize = 0;
 	for(int i=0; i < reg->count; i++) {
		char *buf = prom_collector_export(reg->collectors[i]);
		totalSize += (size_t)snprintf(buffer, 9000, "%s%s", buffer, buf);
	}
	char *resizedBuffer = malloc(sizeof(char)*totalSize);
	strcpy(resizedBuffer, buffer);
	return resizedBuffer;
}*/
