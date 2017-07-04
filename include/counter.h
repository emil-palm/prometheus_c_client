#include "prometheus.h"
#ifndef COUNTER_H
#define COUNTER_H

typedef struct {
	int counter;
} prom_counter;

extern prom_metric* prom_counter_metric(char *name, char *help);
extern int prom_counter_inc(prom_metric *metric);
extern int prom_counter_inc_double(prom_metric, double v);

#endif
