import sys, os
sys.path.append(os.path.dirname(os.path.dirname(os.path.realpath(__file__))))
import socket
import ks
import socketutil
import time
import logger
from modes.rainbow_wave import RainbowWave

class Commander:

    def __init__(self):
        self._log("init")

    def _log(self, msg):
        logger.log(msg, ["commander"])

    def main(self):
        self._log("main")
        server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
        server.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, 2)
        while True:
            server.sendto(RainbowWave().serialize(), (ks.HOST, ks.PORT_INITIAL))
            self._log("Sent to socket")
            time.sleep(1)