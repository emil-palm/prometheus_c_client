#include "prometheus.h"
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <microhttpd.h>

#define PORT 8888
prom_collector_registry *reg;
prom_metric *requestCounter;

int main() {
    // Setup collector_registry
    reg = prom_collector_registry_setup(10);

	//prom_collector *collector = prom_create_collector();
	//collector->update_func = update_collector;
	//collector->metrics_func = metrics;

	//requestCounter = prom_counter_metric("Request counter", "Request counter of how many http requests we have gotten");
	

    prom_httpd_start(PORT);
    getchar();
    prom_httpd_stop();

    // Relase the collector_registry and its metrics;
    //prom_collector_registry_release(reg);
    return 0;
}

