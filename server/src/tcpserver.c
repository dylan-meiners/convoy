#ifdef TESTING

#include <arpa/inet.h>
#include <signal.h>
#include "socketutil.h"

su_accept_resp* client;
int server;

void end();

int main() {

	//char y = '\0';
	//su_write(0, &y, 1);

    signal(SIGINT, end);
    signal(SIGPIPE, SIG_IGN);

    client = (su_accept_resp*)malloc(sizeof(su_accept_resp));

    server = su_socket(AF_INET, SOCK_STREAM, 0);
    su_bind(server, AF_INET, htonl(INADDR_ANY), 2542);
    su_listen(server, 1);

    char buf[256];
    memset(buf + 1, 0, 254);
    int c_fd;

    while (1) {

        client = su_accept(server);
        if (client != NULL) {

            char c_addr[INET_ADDRSTRLEN];
            memset(c_addr, 0, INET_ADDRSTRLEN * sizeof(char));
            inet_ntop(AF_INET, &client->c_addr->sin_addr, c_addr, INET_ADDRSTRLEN);
            printf("A client at %s:%d has connected to the server\n", c_addr, ntohs(client->c_addr->sin_port));
        }
        
        int c = 0;
        while (1) {
            
            buf[0] = 48 + c;
            if (c == 9) {

                buf[255] = '\n';
                c = 0;
            }
            else {

                buf[255] = ' ';
                c++;
            }
            //close(client->c_fd);
            if (su_connected(client->c_fd) == -1) {

            	printf("Socket disconnected\n");
            	break;
            }
            su_write(client->c_fd, buf, 256);
        }
        usleep(250000);
    }

    end();
    return 0;
}

void end() {

    su_shutdown(client->c_fd);
    su_close(client->c_fd);
    su_shutdown(server);
    su_close(server);
    printf("User interrupt. Exiting.\n");
    exit(-1);
}

#endif
