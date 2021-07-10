import socket
import ks
import logger
import time

def connect_forever(server, host: str, port: int):
    connected = False
    while not connected:
        try:
            server.connect((host, port))
            connected = True
        except socket.error as error:
            # logger.log("Unable to connect, but the error ")
            pass
        time.sleep(.1)

def bind_forever(server, host: str, port: int):
    bound = False
    while not bound:
        try:
            server.bind((host, port))
            bound = True
        except socket.error as error:
            if error.errno != 98:
                logger.log("Unable to bind dispatcher port, but the error is not 98", ["bind_forever"])
        time.sleep(.1)