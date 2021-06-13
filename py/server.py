import threading
import dispatcher
import logger
import time

def main():
    _log("init")
    _log("main")
    # format = "[%(asctime)s][%(thread)-12s] %(message)s"
    # logging.basicConfig(format=format, level=logging.INFO, datefmt="%H:%M:%S")
    # logging.getLogger("main")
    # logging.info("Welcome")
    disp = dispatcher.Dispatcher()
    disp_thread = threading.Thread(target=disp.main)
    disp_thread.start()

    while True:
        time.sleep(1)
        # Appparently, "while True:\n\tpass" ABSOLUTELY DESTROYS THE CPU

def _log(msg):
    logger.log(msg, ["main"])

if __name__ == "__main__":
    main()