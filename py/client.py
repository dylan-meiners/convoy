import socket
import logger
import ks

class Client:

    def __init__(self):
        self._port = None
        self._log("init")
        self._server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self._server.connect((ks.HOST, ks.PORT_DISPATCHER))
        port_raw = self._server.recv(2)
        self._port = int.from_bytes(port_raw, "big", signed=False)
        self._log("Bound on port: " + (str(self._port)))

    def main(self):
        while True:
            data = self._server.recv(2)
            if data == bytes(map(ord, ['G', 'O'])):
                self._server.sendall(bytes([ord('L')]))
                data = self._server.recv(256)
                good = True
                for i in range(256):
                    if data[i] != bytes([i]):
                        good = False
                        break
                if good:
                    self.__log("Good data")
                else:
                    self.__log("Bad data")

    def _log(self, msg):
        logger.log(msg, ["client", str(self._port)])

if __name__ == "__main__":
    Client().main()