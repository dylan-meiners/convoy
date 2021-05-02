#include <pthread.h>
#include <errno.h>
#include "error.h"
#include "dispatcher.h"

int main(void) {

	pthread_t dispatcher_t;
	if (pthread_create(&dispatcher_t, NULL, dispatcher_main, NULL) < 0) {

		error("pthread_create", errno, 1);
	}

	while (1);

	return 0;
}
