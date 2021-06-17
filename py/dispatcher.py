import threading
import logger
import time
import socket
import ks
from contextlib import closing
import middleman
import errno
import socketutil

class Dispatcher:

    def __init__(self):
        self._log("init")

    def _log(self, msg):
        logger.log(msg, ["dispatcher"])

    def main(self):
        self._log("main")
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self._log("Waiting for dispatcher to bind...")
        socketutil.bind_forever(server, ks.HOST, ks.PORT_DISPATCHER)
        self._log("Dispatcher bound")
        server.listen()
        while True:
            client, addr = server.accept()
            with client:
                self._log("A client has connected on port " + str(addr[ks.INDEX_ADDR_PORT]))
                port = self.first_avail()
                self._log("First open port is: " + str(port))
                client.sendall(port.to_bytes(2, "big", signed=False))
                middleman_thread = threading.Thread(target=middleman.Middleman(port).main)
                middleman_thread.start()

    def port_is_open(self, port: int):
        with closing(socket.socket(socket.AF_INET, socket.SOCK_STREAM)) as s:
            try:
                s.bind((ks.HOST, port))
                return True
            except socket.error as error:
                self._log("Already bound on port: " + str(port) + " with error: " + str(error.errno))
                return False

    # TODO: This is probably a terrible way to do this... It could literally hang forever
    def first_avail(self):
        port = ks.PORT_CLIENT_BASE
        while True:
            if self.port_is_open(port):
                return port
            else:
                port = port + 1

    def get_next(self):
        pass