#include "exporter.h"
#include<stdarg.h>


int sprintf_realloc(char **buffer, char *fmt, ...) {
    va_list argptr;
    va_start(argptr, fmt);
    char tBuf[1000];
    size_t length = (size_t)vsprintf(tBuf, fmt, argptr);
    va_end(argptr);

    *buffer = realloc(*buffer, (length * sizeof(char)) + strlen(*buffer));
    if ( buffer ) {
        strcat(*buffer, tBuf);
    } else {
        log_warn("Failed to reallocate memory for text export");
        return 1;
    }
    return 0;
}

char * format_labels(prom_labels *labels) {
    char *buff = malloc(1*sizeof(char));
    if (labels != NULL && labels->length > 0) {
        char *labelsBuff = malloc(1*sizeof(char));

        for(int i=0; i<labels->length; i++) {
            prom_label *label = labels->list[i];
            char *fmt = calloc(7, sizeof(char));
            if ( i == 0 ) {
                strcpy(fmt, "%s=\"%s\"");
            } else {
                strcpy(fmt, ",%s=\"%s\"");
            }
            sprintf_realloc(&labelsBuff, fmt, label->name, label->value);
        }
        sprintf_realloc(&buff, "{%s}", labelsBuff);
    }
    return buff;
}

int prom_text_exporter(prom_collector_registry *reg, char **buffer) {
    *buffer = (char*)malloc(1*sizeof(*buffer));
    for(int i=0; i<reg->count; i++) {
         prom_metrics *metrics = reg->collectors[i]->metrics();
         for(int j=0; j<metrics->length; j++) {
            prom_metric *metric = metrics->list[j];

            // Lets start with exporting the information about this metric
            sprintf_realloc(buffer, "# HELP %s %s\n", metric->name, metric->help);
            // Since export the labels for each metric
            char *labels = format_labels(metric->labels);

            // Depending on the type we export them differently.
            switch(metric->type) {
                case PROM_METRIC_COUNTER_TYPE: {
                    prom_counter *cnt = (prom_counter *)metric->data;
                	sprintf_realloc(buffer, "# TYPE %s counter\n%s%s %f\n", metric->name, metric->name, labels, cnt->value);
                } break;
                case PROM_METRIC_GAUGE_TYPE: {
                    prom_gauge *cnt = (prom_gauge *)metric->data;
                	sprintf_realloc(buffer, "# TYPE %s guage\n%s%s %f\n", metric->name, metric->name, labels, cnt->value);

                } break;
                case PROM_METRIC_HISTOGRAM_TYPE:
                    log_warn("Histogram: %x", metric);
                    break;
                case PROM_METRIC_SUMMARY_TYPE:
                    log_warn("Summary: %x", metric);
                    break;
            }
            free(labels);
        }
    }

    return 0;
}
