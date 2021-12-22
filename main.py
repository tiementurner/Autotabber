from ctypes import *
import pyaudio
import wave
import sys

ERROR_HANDLER_FUNC =  CFUNCTYPE(None, c_char_p, c_int, c_char_p, c_int, c_char_p)
def	py_error_handler(filename, line, function, err, fmt):
	pass
c_error_handler = ERROR_HANDLER_FUNC(py_error_handler)

ignore_alsa_errors = cdll.LoadLibrary('libasound.so')
ignore_alsa_errors.snd_lib_error_set_handler(c_error_handler)

if len(sys.argv) < 2:
	print("Give 1 single argument u damn idiot!")
	sys.exit(-1)

wf = wave.open(sys.argv[1], 'rb')

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