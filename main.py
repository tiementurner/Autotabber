import alsa_error_ignore
import sys
from pydub import AudioSegment
import pyaudio
import wave
import scipy.io.wavfile as wavfile
import numpy as np
import pylab as pl
import matplotlib.pyplot as plt
import os

from pydub.utils import make_chunks

if len(sys.argv) < 2:
	print("1 argument expected!")
	sys.exit(-1)

frequency_list = []
with open('frequency') as frequency:
	for line in frequency:
		frequency_list.append(line)
print(frequency_list)

song = AudioSegment.from_file("E-note.wav", "wav")
segments = make_chunks(song, 1000)

for i, chunk in enumerate(segments):
	chunk.export("snippet.wav", format='wav')
	rate, data = wavfile.read("snippet.wav")
	power = 20*np.log10(np.abs(np.fft.rfft(data[:2048])))
	freq = np.linspace(0, rate/2.0, len(power))
	maxpower = np.abs(power)
	peak = np.max(maxpower)
	pos = np.argmax(maxpower)
	freqmax = freq[pos]
	print(freqmax)
	for i in frequency_list:
		
	os.remove("snippet.wav")
# pl.plot(freq,power)
# pl.xlabel("Freq")
# pl.ylabel("Power(dB)")
# pl.show()

