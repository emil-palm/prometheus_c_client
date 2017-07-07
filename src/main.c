#include "prometheus.h"
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <microhttpd.h>

#define PORT 8888
prom_collector_registry *reg;
prom_metric *requestCounter;

int answer_to_connection (void *cls, struct MHD_Connection *connection,
                          const char *url,
                          const char *method, const char *version,
                          const char *upload_data,
                          size_t *upload_data_size, void **con_cls) {
	struct MHD_Response *response;
	int ret;

	if ( strcmp("/metrics", url) == 0) {
    	prom_collector_registry_scrape(reg);
		char *resp;
		prom_text_exporter(reg, &resp);
		response = MHD_create_response_from_buffer(strlen(resp), resp, MHD_RESPMEM_MUST_FREE);
		ret = MHD_queue_response (connection, MHD_HTTP_OK, response);
	} else {
		
	 	response = MHD_create_response_from_buffer (1, "", MHD_RESPMEM_PERSISTENT);
		MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
	}
	MHD_destroy_response (response);


	return ret;
}

int main() {
    // Setup collector_registry
    reg = prom_collector_registry_setup(10);
	

	//prom_collector *collector = prom_create_collector();
	//collector->update_func = update_collector;
	//collector->metrics_func = metrics;

	//requestCounter = prom_counter_metric("Request counter", "Request counter of how many http requests we have gotten");
	

	struct MHD_Daemon *daemon;
	
  	daemon = MHD_start_daemon (MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                             &answer_to_connection, NULL, MHD_OPTION_END);
  	if (NULL == daemon) return 1;

 	getchar ();

  	MHD_stop_daemon (daemon);


    // Relase the collector_registry and its metrics;
    //prom_collector_registry_release(reg);
    return 0;
}

