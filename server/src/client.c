#include <errno.h>
#include "error.h"
#include "socketutil.h"
#include "ks.h"

int main(void) {

    int server = su_socket(AF_INET, SOCK_STREAM, DISPATCHER_PORT);


    return 0;
}