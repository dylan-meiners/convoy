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
        server.listen()
        while True:
            client, addr = server.accept()
            with client:
                self._log("A client has connected on port: " + str(addr[ks.INDEX_ADDR_PORT]))
                while True:
                    client.sendall(bytes([ks.ASCII_DATA_REQUEST_SEND]))
                    ack = client.recv(1)
                    if ack[0] == ks.ASCII_ACK:
                        self._log("Good ack")
                        client.sendall(ks.SAMPLE_256_BYTES)
                    else:
                        self._log("Bad ack")
                    time.sleep(5)

    def _log(self, msg):
        logger.log(msg, ["middleman", str(self._port)])