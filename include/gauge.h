#include "prometheus.h"
#ifndef GAUAGE_H
#define GAUAGE_H

typedef struct {
	double value;
} prom_gauge;

extern prom_metric* prom_gauge_metric(char *name, char *help);
extern int prom_gauge_inc(prom_metric *metric);
extern int prom_gauge_inc_double(prom_metric *metric, double v);
extern int prom_gauge_dec(prom_metric *metric);
extern int prom_gauge_dec_double(prom_metric *metric, double v);
extern int prom_gauge_set(prom_metric *metric, double v);

#endif
