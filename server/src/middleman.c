#include <pthread.h>
#include <errno.h>
#include <stdarg.h>
#include "middleman.h"
#include "socketutil.h"
#include "error.h"
#include "ks.h"

void* middleman_main(void* args) {

	char* port_offset = (char*)args;
	int port = (int)*port_offset + CLIENT_PORT_BASE;
	_log("middleman", port, "Checking in");

	/*if (pthread_detach(pthread_self()) < 0) {

		error("pthread_detach", errno, 1);
	}*/

	int server = su_socket(AF_INET, SOCK_STREAM, 0);
	su_bind(server, AF_INET, htonl(INADDR_ANY), port, 1);
	su_listen(server, 1);

	char fs[256];
	memset(fs, 'f', 256);

	su_accept_resp* client;
	while (1) {

		client = su_accept(server);
		char* addr = su_addrtos(AF_INET, &client->c_addr->sin_addr);
		_log("middleman", port, "Client connected with an address of: %s", addr != NULL ? addr : "NULL?");

		while (1) {

			if (su_connected(client->c_fd) == -1) {

				_log("middleman", port, "Client disconnected");
				su_close(client->c_fd);
				break;
			}

			const char go[2] = { 'g', 'o' };
			su_write(client->c_fd, go, 2);
			char ack = '\0';
			su_read(client->c_fd, &ack, 1);
			if (ack == 'l') {

				su_write(client->c_fd, fs, 256);
				_log("middleman", port, "Good ack");
			}
			else {

				_log("middleman", port, "Bad ack");
			}
		}
		_log("middleman", port, "Exiting thread");
		break;
	}
	
	su_close(server);
	return NULL;
}
