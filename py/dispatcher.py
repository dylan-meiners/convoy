import threading
import logger
import time
import socket
import ks

class Dispatcher:

    def __init__(self):
        self._log("init")
        pass

    def _log(self, msg):
        logger.log(msg, ["dispatcher"])

    def main(self):
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server.bind((ks.HOST, ks.PORT_DISPATCHER))
        server.listen()
        while True:
            client, addr = server.accept()
            with client:
                self._log("A client has connected on port " + str(addr[ks.INDEX_ADDR_PORT]))
                while True:
                    client.sendall([0])

    def get_next(self):
        pass