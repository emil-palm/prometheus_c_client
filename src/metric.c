#include "metric.h"
#include <limits.h>

#define METRIC_START_SIZE 10

prom_metric* prom_metric_setup(char *name, char *help) {
  	prom_metric *metric = malloc(sizeof(prom_metric));
	metric->name = name;
    metric->help = help;
    metric->labels = prom_labels_create();
    return metric;
}



prom_metrics* prom_metrics_create() {
    prom_metrics *metrics = malloc(sizeof(prom_metrics));
    metrics->list = malloc(sizeof(prom_metric)*METRIC_START_SIZE);
	metrics->length = 0;
    return metrics;
}


int prom_metrics_add_metric(prom_metrics *metrics, prom_metric *metric) {
    metrics->list[metrics->length] = metric;
    metrics->length++;
    if (metrics->length % METRIC_START_SIZE == 0) {
        prom_metric **new_metrics = realloc(metrics->list, metrics->length+METRIC_START_SIZE);
        if (new_metrics  == NULL) {
            log_error("Couldnt reallocate memory for metrics from %d to %d", metrics->length, metrics->length+METRIC_START_SIZE);
            return 0;
        } 
        metrics->list = new_metrics;
    }
    return metrics->length;
}
