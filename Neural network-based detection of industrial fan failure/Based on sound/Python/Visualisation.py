# -*- coding: utf-8 -*-
"""
Created on Tue Aug 17 11:10:21 2021

@author: khalil&beji&taher&imed
"""
import torch
import torchaudio
import matplotlib.pyplot as plt
import librosa


def plot_spectrogram(spec, title=None, ylabel='freq_bin', aspect='auto', xmax=None):
  fig, axs = plt.subplots(1, 1)
  axs.set_title(title or 'Spectrogram (db)')
  axs.set_ylabel(ylabel)
  axs.set_xlabel('frame')
  im = axs.imshow(spec, origin='lower', aspect=aspect)
  if xmax:
    axs.set_xlim((0, xmax))
  fig.colorbar(im, ax=axs)
  plt.show(block=False)


# Importer un fichier du dataset

# filename contains the path to a WAV file of the dataset
filename = "00000000.wav"
# function that returns the waveform and the sampling rate 
waveform, sample_rate = torchaudio.load(filename)


# Display the curve as a function of the sample number
print("Shape of waveform: {}".format(waveform.size()))
print("Sample rate of waveform: {}".format(sample_rate))
plt.figure()
plt.plot(waveform.t().numpy())


# Mix the 8 channels of the microphone array
waveform = torch.mean(waveform, dim=0, keepdim=True)

# Display the curve of the new mixed signal
print("Shape of waveform: {}".format(waveform.size()))
print("Sample rate of waveform: {}".format(sample_rate))
plt.figure()
plt.plot(waveform.t().numpy())

# Extract the spectrogram log-mel and display it
"""
# Based on torchaudio
specgram = torchaudio.transforms.MelSpectrogram(sample_rate=16000,n_fft=1024,hop_length=5100,n_mels=30,mel_scale="htk")(waveform)
specgram = librosa.power_to_db(specgram)
plot_spectrogram(specgram[0], title="MelSpectrogram - torchaudio", ylabel='mel freq')
"""
# Based on librosa 
y = librosa.load('00000000.wav', sr=None)[0] # keep the initial sampling rate of the file
specgram2 = librosa.feature.melspectrogram(y, sr=16000, n_mels=30, n_fft=1024, hop_length=5100, center=False)
specgram2 = librosa.power_to_db(specgram2)
plot_spectrogram(specgram2, title="MelSpectrogram - torchaudio", ylabel='mel freq')
