#include <errno.h>
#include "error.h"
#include "socketutil.h"
#include "ks.h"

int main(void) {

    int server = su_socket(AF_INET, SOCK_STREAM, 0);
	su_connect(server, AF_INET, htonl(INADDR_ANY), DISPATCHER_PORT, 1);

	char port;
	su_read(server, &port, sizeof(port));
	printf("Recieved from dispatcher: %d\n", (int)port);
	su_close(server);

	server = su_socket(AF_INET, SOCK_STREAM, 0);
	while (su_connect(server, AF_INET, htonl(INADDR_ANY), CLIENT_PORT_BASE + port, 0) < 0);

	const char l = 'l';
	char ready[2];
	char data[256];
	while (1) {
	
		su_read(server, ready, 2);
		if (ready[0] == 'g' && ready[1] == 'o') {

			su_write(server, &l, 1);
			su_read(server, data, 256);
			int searching = 1;
			for (int i = 0; searching == 1 && i < 256; i++) {

				searching = data[i] == 'f' ? 1 : 0;
			}
			_log("client", port + CLIENT_PORT_BASE, searching == 1 ? "Data good" : "Data bad");
		}
	}
	
	su_close(server);
    return 0;
}
