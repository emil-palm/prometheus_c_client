#include "httpd.h"
#include <microhttpd.h>

typedef struct {
    char *endpoint;
    prom_collector_registry *reg;
} prom_httpd_endpoint_s;

typedef struct {
    int length;
    prom_httpd_endpoint_s **entries;
} prom_httpd_endpoints_s;

prom_httpd_endpoints_s *endpoints;

struct MHD_Daemon *httpd_daemon;

extern int prom_httpd_handle_connection (void *cls, struct MHD_Connection *connection,
                          const char *url,
                          const char *method, const char *version,
                          const char *upload_data,
                          size_t *upload_data_size, void **con_cls);

#define ENDPOINTS_START_SIZE 10

void prom_httpd_setup() {
    endpoints = malloc(sizeof(prom_httpd_endpoints_s));
    endpoints->length = 0;
    endpoints->entries = malloc(sizeof(prom_httpd_endpoint_s)*ENDPOINTS_START_SIZE);
}

int prom_httpd_add_registry(char *endpoint, prom_collector_registry *reg) {
    // Lets check that we dont have a registered endpoint already
    for(int i=0; i < endpoints->length; i++) {
        if(endpoints->entries[i]->endpoint == endpoint) {
            log_warn("Could not add %s to httpd since there is already a endpoint with the same name added", endpoint);
            return 1;
        }
    }

    // Okay so we are ready to append the endpoint to the list
    prom_httpd_endpoint_s *entry = malloc(sizeof(prom_httpd_endpoint_s));
    entry->endpoint = endpoint;
    entry->reg = reg;

    endpoints->entries[endpoints->length] = entry;
    endpoints->length++;


    if (endpoints->length % ENDPOINTS_START_SIZE == 0) {
        prom_httpd_endpoint_s **new_endpoints = realloc(endpoints->entries, endpoints->length+ENDPOINTS_START_SIZE);
        if (new_endpoints  == NULL) {
            log_error("Couldnt reallocate memory for endpoints from %d to %d", endpoints->length, endpoints->length+ENDPOINTS_START_SIZE);
            return 0;
        } 
        endpoints->entries = new_endpoints;
    }

    return 0;
}

int prom_httpd_del_registry(char *endpoint) {
    // Lets check that we do have this endpoint added.
    int removed = 0;
    for(int i=0; i < endpoints->length; i++) {
        if ( removed == 1 ) {
            // So we should now move everyone up one index
            endpoints->entries[i-1] = endpoints->entries[i];
        }

        if(endpoints->entries[i]->endpoint == endpoint) {
            removed = 1;
            endpoints->entries[i] = NULL;
        }
    }

    if ( removed == 1 ) {
        endpoints->length--;
        return 0;
    } else {
        // Endpoint doesnt exist.

        log_warn("Could not remove %s from httpd since there is no such endpoint", endpoint);
        return 1;
    }
}

int prom_httpd_start(int port) {
	
  	httpd_daemon = MHD_start_daemon (MHD_USE_SELECT_INTERNALLY, port, NULL, NULL,
                             &prom_httpd_handle_connection, NULL, MHD_OPTION_END);

  	if (NULL == httpd_daemon) {
        return 1;
    }

    return 0;


}

void prom_httpd_stop() {
  	MHD_stop_daemon (httpd_daemon);
}

char** prom_httpd_endpoints() {
    char **endpoints = malloc(sizeof(char*)*10);
    return endpoints;
}


/* Internal functions */
int prom_httpd_handle_connection (void *cls, struct MHD_Connection *connection,
                          const char *url,
                          const char *method, const char *version,
                          const char *upload_data,
                          size_t *upload_data_size, void **con_cls) {
	struct MHD_Response *response;
	int ret;

    prom_collector_registry *reg = NULL;

    for(int i=0; i < endpoints->length; i++) {
        if( strcmp(endpoints->entries[i]->endpoint,url) == 0 ) {
            reg = endpoints->entries[i]->reg;
        }
    }


    if ( reg == 0 ) {
	    response = MHD_create_response_from_buffer (strlen(""), "", MHD_RESPMEM_MUST_COPY);
		ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
    } else {
	    prom_collector_registry_scrape(reg);
		char *resp;
		prom_text_exporter(reg, &resp);
		response = MHD_create_response_from_buffer(strlen(resp), resp, MHD_RESPMEM_MUST_FREE);
		ret = MHD_queue_response (connection, MHD_HTTP_OK, response);
    }
	MHD_destroy_response (response);


	return ret;
}

