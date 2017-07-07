#include "prometheus.h"

#define LABEL_START_SIZE 10

prom_label* prom_label_create(char *name, char *value) {
    prom_label *label = malloc(sizeof(prom_label));
    label->name = name;
    label->value = value;
    return label;
}

int prom_labels_add(prom_labels *labels, prom_label *label) {
    labels->list[labels->length] = label;
    labels->length++;
    if (labels->length % LABEL_START_SIZE == 0) {
        prom_label **new_labels = realloc(labels->list, labels->length+LABEL_START_SIZE);
        if (new_labels  == NULL) {
            log_error("Couldnt reallocate memory for labels from %d to %d", labels->length, labels->length+LABEL_START_SIZE);
            return 0;
        } 
        labels->list = new_labels;
    }

    return labels->length;
}

int prom_labels_create_label(prom_labels *labels, char *name, char *value) {
    prom_label *label = prom_label_create(name, value);
    return prom_labels_add(labels, label);
}

prom_labels* prom_labels_create() {
    prom_labels *labels = malloc(sizeof(prom_labels));
    labels->list = malloc(sizeof(prom_labels)*LABEL_START_SIZE);
	labels->length = 0;
    return labels;
}
