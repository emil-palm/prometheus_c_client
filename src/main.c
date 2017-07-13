#include "prometheus.h"
#include <signal.h>

#define PORT 8888
prom_collector_registry *reg;
prom_metric *requestCounter;

static volatile int keepRunning = 1;

void intHandler(int dummy) {
    keepRunning = 0;
}

int main() {
    // Setup collector_registry
    reg = prom_collector_registry_setup(10);

	requestCounter = prom_counter_metric("Request counter", "Request counter of how many http requests we have gotten");
    prom_collector_default_add_metric(requestCounter);
    prom_httpd_start(PORT);
    getchar();
    signal(SIGINT, intHandler);
    while (keepRunning) {
        getchar();
        prom_counter_inc(requestCounter);
    }

    prom_httpd_stop();

    // Relase the collector_registry and its metrics;
    //prom_collector_registry_release(reg);
    return 0;
}

