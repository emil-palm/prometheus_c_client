#include "metric.h"
#include <limits.h>

#define METRIC_START_SIZE 10

prom_metric* prom_metric_setup(char *name, char *help) {
  	prom_metric *collector = malloc(sizeof(prom_metric));
	collector->name = name;
    collector->help = help;
    return collector;
}

char* prom_metric_export(prom_metric *collector) {
	char buf[9000];
	int j = snprintf(buf, INT_MAX, "# HELP %s %s\n%s", collector->name, collector->help, collector->export_func(collector));
	char *resizedBuffer = malloc(sizeof(char)*j);
	strcpy(resizedBuffer, buf);
	return resizedBuffer;
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
