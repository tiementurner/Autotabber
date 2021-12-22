from ctypes import *
import pyaudio
import wave
import sys
import scipy.io.wavfile as wavfile
import numpy as np
import pylab as pl

ERROR_HANDLER_FUNC =  CFUNCTYPE(None, c_char_p, c_int, c_char_p, c_int, c_char_p)
def	py_error_handler(filename, line, function, err, fmt):
	pass
c_error_handler = ERROR_HANDLER_FUNC(py_error_handler)

ignore_alsa_errors = cdll.LoadLibrary('libasound.so')
ignore_alsa_errors.snd_lib_error_set_handler(c_error_handler)

if len(sys.argv) < 2:
	print("Give 1 single argument u damn idiot!")
	sys.exit(-1)

rate, data = wavfile.read(sys.argv[1])

p = 20*np.log10(np.abs(np.fft.rfft(data[:2048])))
f = np.linspace(0, rate/2.0, len(p))
pl.plot(f,p)
pl.xlabel("Freq")
pl.ylabel("Power(dB)")
pl.show()

"""
p = pyaudio.PyAudio()

stream = p.open(format = p.get_format_from_width(wf.getsampwidth()),
				channels = wf.getnchannels(),
				rate=wf.getframerate(),
				output = True)

data = wf.readframes(1024)

while len(data) > 0:
	stream.write(data)
	data = wf.readframes(1024)

stream.stop_stream()
stream.close()

p.terminate()
"""