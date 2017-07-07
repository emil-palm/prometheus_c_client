#include "prometheus.h"
#ifndef METRIC_H
#define METRIC_H

#define PROM_METRIC_COUNTER_TYPE    0x000000001
#define PROM_METRIC_GAUGE_TYPE      0x000000002
#define PROM_METRIC_SUMMARY_TYPE    0x000000004
#define PROM_METRIC_HISTOGRAM_TYPE  0x000000008 // 0x000000010 (is the nxt)

typedef struct prom_metric prom_metric;

typedef struct {
	prom_metric **list;
	int length;
} prom_metrics;

extern int prom_metrics_add_metric(prom_metrics *metrics, prom_metric *metric);

struct prom_metric {
    u_int64_t type;
    void* data;
	char *name;
	char *help;
	prom_labels *labels;
    void* collectorCount;
};

extern prom_metric* prom_metric_setup(char *name, char *help);
extern char* prom_metric_export(prom_metric *collector);
extern prom_metrics* prom_metrics_create();

#endif
