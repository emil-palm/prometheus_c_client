#include "gauge.h"

prom_metric* prom_gauge_metric(char *name, char *help) {
	prom_metric *metric = prom_metric_setup(name, help);
    metric->type = PROM_METRIC_GAUGE_TYPE;
    prom_gauge *guage = malloc(sizeof(prom_gauge));
    guage->value = 0;
	metric->data = guage;
	return metric;
}

int prom_gauge_inc(prom_metric *metric) {
    prom_gauge *g = (prom_gauge *)metric->data;
    g->value++;
	return 0;
}

int prom_gauge_inc_double(prom_metric *metric, double v) {
    prom_gauge *g = (prom_gauge *)metric->data;
    g->value += v;
	return 0;
}

int prom_gauge_dec(prom_metric *metric) {
    prom_gauge *g = (prom_gauge *)metric->data;
    g->value--;
    return 0;
}

int prom_gauge_dec_double(prom_metric *metric, double v) {
    prom_gauge *g = (prom_gauge *)metric->data;
    g->value -= v;
    return 0;
}

int prom_gauge_set(prom_metric *metric, double v) {
    prom_gauge *g = (prom_gauge *)metric->data;
    g->value = v;
    return 0;
}

