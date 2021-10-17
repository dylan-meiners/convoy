from abc import ABC, abstractmethod
from enum import Enum

class Modes(Enum):
    TestMode    = 0,
    RainbowWave = 1,
    GreenPulse  = 2,
    Flow        = 3,
    Driving     = 4,
    Warning     = 5

class Mode(ABC):

    def __init__(self):
        pass

    def serialize(self):
        ascii_arr = []
        ascii_arr.append('\x01')
        ascii_arr.append(1)
        ascii_arr.append('<')
        data = self.data()
        ascii_arr += data
        ascii_arr.append('>')
        ascii_arr.append(len(data))
        ascii_arr.append('\x04')
        return bytes(ord(b) if not isinstance(b, int) else b for b in ascii_arr)

    @property
    @abstractmethod
    def ident(self):
        return ""

    @abstractmethod
    def data(self) -> list[int]:
        return ""