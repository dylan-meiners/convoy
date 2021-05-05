#include <pthread.h>
#include <arpa/inet.h>
#include <signal.h>
#include "socketutil.h"
#include "middleman.h"
#include "ks.h"
#include "error.h"

int first_avail(int);

void* dispatcher_main(void* args) {

	_log("dispatcher", -1, "Checking in.");

	/*if (pthread_detach(pthread_self()) < 0) {

		error("pthread_detach", errno, 1);
	}*/

	su_accept_resp* client;
	int server = su_socket(AF_INET, SOCK_STREAM, 0);
	su_bind(server, AF_INET, htonl(INADDR_ANY), DISPATCHER_PORT, 1);
	su_listen(server, 1);

	while (1) {

		client = su_accept(server);
		char* addr = su_addrtos(AF_INET, &client->c_addr->sin_addr);
		_log("dispatcher", -1, "Client connected with an address of: %s", addr != NULL ? addr : "NULL?");
		
		int target_port_offset = first_avail(AF_INET) - CLIENT_PORT_BASE;
		if (target_port_offset < 0 || target_port_offset > 255) {

			fprintf(stderr, "ERROR: Could not find an available port\n");
		}
		else {
			
			_log("dispatcher", -1, "First available: %d", target_port_offset + CLIENT_PORT_BASE);
			char p = (char)target_port_offset;
			su_write(client->c_fd, &p, sizeof(p));
			pthread_t middleman;
			if (pthread_create(&middleman, NULL, middleman_main, &p) < 0) {

				error("pthread_create", errno, 1);
			}
		}

	}	
	
	return NULL;
}

int first_avail(int af) {

	for (int i = CLIENT_PORT_BASE; i < 300; i++) {

		if (su_avail(af, i) == 0) {

			return i;
		}
	}
	return -1;
}
