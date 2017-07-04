#include "counter.h"

char *prom_counter_export(prom_metric *metric) {
	char buffer[9000];
	size_t length = (size_t)snprintf(buffer, 9000, "# TYPE %s counter\n", metric->name);
	char *buf = malloc(sizeof(char)*length);
	strcpy(buf, buffer);
	return buf;	
}

prom_metric* prom_counter_metric(char *name, char *help) {
	prom_metric *metric = prom_metric_setup(name, help);
	metric->data = malloc(sizeof(prom_counter));
	metric->export_func = prom_counter_export;
	return metric;
}

int prom_counter_inc(prom_metric *metric) {
	return 0;
}

int prom_counter_inc_double(prom_metric metric, double v) {
	return 0;
}

