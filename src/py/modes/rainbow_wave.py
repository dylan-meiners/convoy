import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.realpath(__file__))))

import logger
from mode import Mode

class RainbowWave(Mode):

    def __init__(self):
        self.wave_speed_scalar: float = 1.0
        self.should_reset = False

    def reset(self):
        self.should_reset = True

    def ident(self):
        return "rbw"

    def data(self) -> list[int]:
        if self.wave_speed_scalar < 0.0:
            logger.log("Speed scalar is less than 0.0, setting to 0.0", ["RainbowWave", "ERROR"])
            self.wave_speed_scalar = 0.0
        elif self.wave_speed_scalar > 2.0:
            logger.log("Speed scalar is greater than 2.0, setting to 2.0", ["RainbowWave", "ERROR"])
            self.wave_speed_scalar = 2.0
        data = [1 if self.should_reset else 0, int(self.wave_speed_scalar * 127.0)]
        self.should_reset = False
        return data