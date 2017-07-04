#include "prometheus.h"
#ifndef METRIC_H
#define METRIC_H

typedef struct prom_metric prom_metric;

typedef char* (*prom_metric_export_function)(prom_metric *collector);

typedef struct {
	prom_metric **list;
	int length;
} prom_metrics;

extern int prom_metrics_add_metric(prom_metrics *metrics, prom_metric *metric);

struct prom_metric {
    prom_metric_export_function export_func;
    void* data;
	char *name;
	char *help;
	prom_labels *labels;
    void* collectorCount;
};

extern prom_metric* prom_metric_setup(char *name, char *help);
extern char* prom_metric_export(prom_metric *collector);

#endif
