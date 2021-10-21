import time
from numpy.fft import fft
import pyaudio
import wave
import json
import struct
import pyqtgraph as pg
import numpy as np
from scipy.ndimage import gaussian_filter
from scipy.interpolate import interp1d
from scipy import signal
import patsy
from sklearn.linear_model import LinearRegression

pw = pg.plot()
pw.setRange(yRange=[0, 14000])

CHUNK = 1024
# file = wave.open("/home/dylan/intentions.wav", "rb")
file = wave.open("/home/dylan/ucla.wav", "rb")
# file = wave.open("/home/dylan/440hz.wav", "rb")
print(file.getframerate())
p = pyaudio.PyAudio()
stream = p.open(format=pyaudio.get_format_from_width(file.getsampwidth()),
            channels=file.getnchannels(),
            rate=file.getframerate(),
            input=True,
            output=True,
            input_device_index=0,
            output_device_index=0,
            frames_per_buffer=CHUNK)
data = file.readframes(CHUNK)
while len(data) > 0:
    stream.write(data)
    data = file.readframes(CHUNK)
    # data = stream.read(CHUNK, exception_on_overflow=False)
    unpacked = struct.unpack(f"{CHUNK * file.getnchannels() * 2}B", data)
    fft_data = np.abs(np.fft.rfft(unpacked))[1:90] / 10.0
    # fft_data = gaussian_filter(fft_data, 1.0)
    # fft_data = signal.savgol_filter(fft_data, 5, 3)
    # fft_data = np.append(fft_data, 0)
    # fft_data[0] = 0
    # fft_data = np.multiply(20, np.log10(fft_data))
    # g = gaussian_filter1d(fft_data, sigma=1.0)
    # print(g)
    # x = np.fft.fftfreq(len(fft_data), 1.0 / 44100)
    x = np.arange(len(fft_data))
    #print(list(fft_data))
    # x_basis = patsy.cr(x, df=50)
    # model = LinearRegression().fit(x_basis, fft_data)
    # y_hat = model.predict(x_basis)

    #fft_data = interp1d(list(x), list(fft_data))

    pw.plot(x, fft_data, clear=True)
    pg.QtGui.QApplication.processEvents()


stream.stop_stream()
stream.close()
p.terminate()
file.close()