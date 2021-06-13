import socket
import logger
import time
import ks

class Middleman:

    def __init__(self, port) -> None:
        self._port = port
        self._log("init")

    def main(self):
        self._log("main")
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server.bind((ks.HOST, self._port))
        while True:
            time.sleep(1)

    def _log(self, msg):
        logger.log(msg, ["middleman", str(self._port)])