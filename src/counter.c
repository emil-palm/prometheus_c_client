#include "counter.h"

prom_metric* prom_counter_metric(char *name, char *help) {
	prom_metric *metric = prom_metric_setup(name, help);
    if ( metric != NULL ) {
        metric->type = PROM_METRIC_COUNTER_TYPE;
        prom_counter *cnt = malloc(sizeof(prom_counter));
        cnt->value = 0;
    	metric->data = cnt;
    }
	return metric;
}

int prom_counter_inc(prom_metric *metric) {
    prom_counter *cnt = (prom_counter*)metric->data;
    cnt->value++;
	return 0;
}

int prom_counter_inc_double(prom_metric *metric, double v) {
    prom_counter *cnt = metric->data;
    cnt->value += v;
	return 0;
}

