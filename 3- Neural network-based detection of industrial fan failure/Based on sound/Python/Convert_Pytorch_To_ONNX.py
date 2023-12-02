# -*- coding: utf-8 -*-
"""
Created on Fri Aug 20 10:54:04 2021

@author: khalil&beji&taher&imed
"""

import torch 
import torchaudio
from Fan import Fan
from cnn import CNNNetwork



cnn = CNNNetwork()               # Load model structure
state_dict = torch.load("cnn16.pth")     # Load Characteristic Values (Coefs)
cnn.load_state_dict(state_dict)      # Assign coefficients to the model

# select the "CPU" processing unit
device="cpu"

# Path to the CSV file of the dataset 
ANNOTATIONS_FILE = "C:/Users/khalil/Desktop/Synth/Wevioo Stage/Py/DbTest.csv"

# sampling frequency and number of samples
SAMPLE_RATE = 16000
NUM_SAMPLES = 160000

# define the transformation to apply to the signal (log mel spectrogram)
mel_spectrogram = torchaudio.transforms.MelSpectrogram(sample_rate=SAMPLE_RATE,n_fft=1024,hop_length=5100,n_mels=30)
# load an object of class Fan 
Fan = Fan(ANNOTATIONS_FILE,mel_spectrogram,SAMPLE_RATE,NUM_SAMPLES,device)
input = Fan[0][0]
input.unsqueeze_(0)

# export ONNX file
torch.onnx.export(cnn, input, "Cnn_Embedded8.onnx")

