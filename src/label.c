#include "prometheus.h"

#define LABEL_START_SIZE 10

prom_label* prom_label_create(char *name, char *value) {
    prom_label *label = malloc(sizeof(prom_label));
    label->name = name;
    label->value = value;
    return label;
}

char* prom_label_export(prom_label *label) {
    char buf[9000];
    size_t length = snprintf(buf, 9000, "%s=\"%s\"", label->name, label->value);
    char *buffer = malloc(sizeof(char)*length);
    strcpy(buf, buffer);
    return buffer;
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
    return labels;
}

char * prom_labels_export(prom_labels *labels) {
    char buffer[9000];
    size_t length;
    for(int i=0; i < labels->length; i++) {
        if (i != 0) {
            length += snprintf(buffer, 9000, "%s,%s", buffer, prom_label_export(labels->list[i]));
        } else {
            length += snprintf(buffer, 9000, "%s", prom_label_export(labels->list[i]));
        }
    }
    char *buff = malloc(sizeof(char) * length);
    strcpy(buff, buffer);
    return buff;
}
