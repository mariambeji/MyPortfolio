# -*- coding: utf-8 -*-
"""
Created on Mon Aug 16 11:43:21 2021

@author: khalil&beji&taher&imed
"""

  

from torch.utils.data import Dataset
import pandas as pd
import torchaudio
import torch
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

class Fan(Dataset):

    def __init__(self, annotations_file,transformation,target_sample_rate,num_samples,device):
        self.annotations = pd.read_csv(annotations_file)
        self.device = device
        self.transformation = transformation.to(self.device)
        self.target_sample_rate = target_sample_rate
        self.num_samples = num_samples
        
        
        
    def __len__(self):
        return len(self.annotations)

    def __getitem__(self, index):
        audio_sample_path = self._get_audio_sample_path(index)
        label = self._get_audio_sample_label(index)
        signal, sr = torchaudio.load(audio_sample_path)
        signal = signal.to(self.device)
        
        
        signal = self._resample_if_necessary(signal,sr)
        
        signal = self._mix_down_if_necessary(signal)
        
        signal = self._cut_if_necessary(signal)
        signal = self._right_pad_if_necessary(signal)
        
        signal = self.transformation(signal)
        signal = torchaudio.functional.amplitude_to_DB(signal, multiplier=10, amin=1e-10, db_multiplier=0)
        return signal, label

    def _resample_if_necessary(self, signal, sr):
        if sr != self.target_sample_rate:
            resampler = torchaudio.transforms.Resample(sr, self.target_sample_rate)
            signal = resampler(signal)
        return signal

    def _mix_down_if_necessary(self, signal):
        if signal.shape[0] > 1:
            signal = torch.mean(signal, dim=0, keepdim=True)
        return signal
    
    def _cut_if_necessary(self, signal):
        if signal.shape[1] > self.num_samples:
            signal = signal[:, :self.num_samples]
        return signal

    def _right_pad_if_necessary(self, signal):
        length_signal = signal.shape[1]
        if length_signal < self.num_samples:
            num_missing_samples = self.num_samples - length_signal
            last_dim_padding = (0, num_missing_samples)
            signal = torch.nn.functional.pad(signal, last_dim_padding)
        return signal
    
    def _get_audio_sample_path(self, index):
        
        path = self.annotations.iloc[index, 1]
        return path

    def _get_audio_sample_label(self, index):
        return self.annotations.iloc[index, 2]


if __name__ == "__main__":
    ANNOTATIONS_FILE = "C:/Users/khalil/Desktop/Synth/Wevioo Stage/Py/outputfin.csv"
    
    SAMPLE_RATE = 16000
    NUM_SAMPLES = 160000
    
    if torch.cuda.is_available():
        device = "cuda"
    else:
        device = "cpu"    
    device = "cpu"
    print(f"using {device} device")
    
    mel_spectrogram = torchaudio.transforms.MelSpectrogram(sample_rate=SAMPLE_RATE,n_fft=1024,hop_length=512,n_mels=128,mel_scale="htk")
    #mel_spectrogram = torchaudio.transforms.MFCC(log_mels=True)
    Fan = Fan(ANNOTATIONS_FILE,mel_spectrogram,SAMPLE_RATE,NUM_SAMPLES,device)
    print(f"There are {len(Fan)} samples in the dataset.")
    
    
   
    for i in range(1):
        signal, label = Fan[100*i]
        plot_spectrogram(signal[0], title="MelSpectrogram - torchaudio", ylabel='mel freq')
        #plt.figure()
        #plt.imshow(  signal.permute(1, 2, 0)  )
#    metadata = torchaudio.info(path)
#    print(metadata)