#include "prometheus.h"

#ifndef EXPORTER_H
#define EXPORTER_H


extern int prom_text_exporter(prom_collector_registry *reg, char **buffer);

#endif
