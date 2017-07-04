#include "prometheus.h"
#ifndef LABEL_H
#define LABEL_H

typedef struct { 
	char *name;
	char *value;
} prom_label;

typedef struct {
	prom_label **list;
	int length;
} prom_labels;

extern prom_label* prom_label_create(char *name, char *value);
extern int prom_labels_add(prom_labels *labels, prom_label *label);
extern int prom_labels_create_label(prom_labels *labels, char *name, char *value);
extern prom_labels* prom_labels_create();

#endif
