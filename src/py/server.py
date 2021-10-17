from modes.rainbow_wave import RainbowWave
import threading
import logger
import time
from enum import Enum
from configparser import ConfigParser
import tcp.dispatcher as dispatcher
import udp.commander as commander

def main():
    _log("init")
    _log("main")
    # format = "[%(asctime)s][%(thread)-12s] %(message)s"
    # logging.basicConfig(format=format, level=logging.INFO, datefmt="%H:%M:%S")
    # logging.getLogger("main")
    # logging.info("Welcome")

    config = ConfigParser()
    config.optionxform = str
    config.read("config.cfg")
    method = config["Settings"]["CommunicationProtocol"]

    if method == "TCP":
        disp = dispatcher.Dispatcher()
        disp_thread = threading.Thread(target=disp.main)
        disp_thread.start()
    elif method == "UDP":
        commando = commander.Commander()
        commando_thread = threading.Thread(target=commando.main)
        commando_thread.start()
    else:
        _log("Communicaiton method is not a valid choice. Valid choices include: \"TCP\" and \"UDP\"")
        exit(-1)

    while True:
        time.sleep(1)
        # Appparently, "while True:\n\tpass" ABSOLUTELY DESTROYS THE CPU

def _log(msg):
    logger.log(msg, ["main"])

if __name__ == "__main__":
    main()