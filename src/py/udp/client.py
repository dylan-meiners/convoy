import sys, os
sys.path.append(os.path.dirname(os.path.dirname(os.path.realpath(__file__))))
import time
import socket
import ks
import socketutil
import serial
import logger
import struct
from mode import Modes

class Client:

    def __init__(self):
        self._log("init")
        #self.arduino = serial.Serial("/dev/ttyACM0", ks.SERIAL_BAUD, timeout=ks.SERIAL_TIMEOUT)
        #time.sleep(1) # I have no idea why, but if this isn't here EVERYTHING BREAKS
        #self._log("Initialized serial on: " + str(self.arduino.name) + " with baud: " + str(ks.SERIAL_BAUD) +  " and timeout: " + str(ks.SERIAL_TIMEOUT))

    def main(self):
        server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
        server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

        self._log("Attempting to bind to port: " + str(ks.PORT_INITIAL))
        socketutil.bind_forever(server, ks.HOST, ks.PORT_INITIAL)
        self._log("Bound to port: " + str(ks.PORT_INITIAL))

        mreq = struct.pack("4sL", socket.inet_aton(ks.HOST), socket.INADDR_ANY)
        server.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)

        while True:
            raw = server.recv(1024)
            chared = list(map(chr, raw))
            length = chared.index('>') - chared.index('<') - 1
            given_chk = raw[chared.index('>') + 1]
            # mode = "".join(chared[1:chared.index(' ')])
            # print(mode)
            if raw[0] != 1:
                self._log("Incoming data invalid: no SOH")
            elif raw[-1] != 4:
                self._log("Incoming data invalid: no EOT")
            elif length != given_chk:
                self._log(f"Incoming data invalid: checksum not valid. Got: {length} expected: {given_chk}")
            else:
                print("data good")
                # self.sendToArduino(bytes([raw[1]]) + bytes([given_chk]) + raw[3:chared.index('>')])


    def _log(self, msg):
        logger.log(msg, ["client", str(ks.PORT_INITIAL)])

    def sendToArduino(self, serialized_data):
        self.arduino.write(bytes([ks.ASCII_DATA_REQUEST_SEND]))
        ack = self.arduino.read()
        self._log(str(ack))
        if ack == bytes([]):
            self._log("Timeout waiting for ACK")
        elif ack[0] == ks.ASCII_ACK:
            self._log("Good ack")
            self.arduino.write(serialized_data)
            self._log("Data written to arduino")
        else:
            self._log("Bad ACK from arduino")

if __name__ == "__main__":
    Client().main()