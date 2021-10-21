import time
from numpy.fft import fft
import pyaudio
import struct
import pyqtgraph as pg
import numpy as np
from scipy.ndimage import gaussian_filter

CHUNK = 1024
MAX_Y = 7000
GAUSS_SIG = 2.0
N_CHANNELS = 2

pw = pg.plot()
pw.setRange(yRange=[0, MAX_Y])

p = pyaudio.PyAudio()
stream = p.open(format=pyaudio.paInt16,
            channels=N_CHANNELS,
            rate=44100,
            input=True,
            input_device_index=2,
            frames_per_buffer=CHUNK)
while True:
    data = stream.read(CHUNK, exception_on_overflow=False)
    unpacked = struct.unpack(f"{CHUNK * N_CHANNELS * 2}B", data)
    fft_data = np.abs(np.fft.rfft(unpacked))[1:90] / 10.0
    fft_data = gaussian_filter(fft_data, GAUSS_SIG)
    x = np.arange(len(fft_data))

    pw.plot(x, fft_data, clear=True)
    pg.QtGui.QApplication.processEvents()


stream.stop_stream()
stream.close()
p.terminate()
file.close()