import socket
import logger
import ks
import socketutil
import serial

class Client:

    def __init__(self):
        self._log("init")
        arduino = serial.Serial("/dev/ttyACM0", ks.SERIAL_BAUD, timeout=ks.SERIAL_TIMEOUT)
        self._log("Initialized serial on: " + str(arduino.name) + " with baud: " + str(ks.SERIAL_BAUD) +  " and timeout: " + str(ks.SERIAL_TIMEOUT))
        
        self._port = None
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server.connect((ks.HOST, ks.PORT_DISPATCHER))
        port_raw = server.recv(2)
        self._port = int.from_bytes(port_raw, "big", signed=False)
        self._log("Received redirect to port: " + str(self._port))
        self._log("Disconnecting from dispatcher")
        server.close()

    def main(self):
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self._log("Attempting to connect to port: " + str(self._port))
        socketutil.connect_forever(server, ks.HOST, self._port)
        self._log("Connected to port: " + str(self._port))

        while True:
            data = server.recv(1)
            if data[0] == ks.ASCII_DATA_REQUEST_SEND:
                server.sendall(bytes([ks.ASCII_ACK]))
                data = server.recv(256)
                good = True
                for i in range(256):
                    if data[i] != i:
                        good = False
                        break
                if good:
                    self._log("Good data")
                else:
                    self._log("Bad data")

    def _log(self, msg):
        logger.log(msg, ["client", str(self._port)])

if __name__ == "__main__":
    Client().main()