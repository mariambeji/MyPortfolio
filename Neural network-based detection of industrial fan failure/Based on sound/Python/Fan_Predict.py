# -*- coding: utf-8 -*-
"""
Created on Tue Aug 17 09:00:03 2021

@author: khalil&beji&taher&imed
"""


import torch 
import torchaudio
from Fan import Fan
from cnn import CNNNetwork

# output class names 
class_mapping = [
    "Normal" , "Abnormal"
    ]

# prediction function :
def predict(model,input,target,class_mapping):
    model.eval()
    with torch.no_grad():
        predictions = model(input)
        # Tensor (numbre of samples passed = 1, number of classes trying to predict = 10)
        predicted_index = predictions[0].argmax()
        predicted = class_mapping [predicted_index]
        expected = class_mapping[target]
    return predicted,expected

if __name__ ==  "__main__":
    n = 0
    # Load back the model :
    cnn = CNNNetwork()               # Load model structure
    state_dict = torch.load("cnn16.pth")     # Load Characteristic Values (Coefs)
    cnn.load_state_dict(state_dict)      # Assign coefficients to the model

    device="cpu"
    print(f"using {device} device")    
    
    ANNOTATIONS_FILE = "C:/Users/khalil/Desktop/Synth/Wevioo Stage/Py/DbTest.csv"
    SAMPLE_RATE = 16000
    NUM_SAMPLES = 160000
    mel_spectrogram = torchaudio.transforms.MelSpectrogram(sample_rate=SAMPLE_RATE,n_fft=1024,hop_length=5100,n_mels=30)
    Fan = Fan(ANNOTATIONS_FILE,mel_spectrogram,SAMPLE_RATE,NUM_SAMPLES,device)
    
    
    # Perform prediction for 950 files 
    for ii in range(950):
        input,target = Fan[ii][0],Fan[ii][1]
        input.unsqueeze_(0)
        predicted,expected = predict(cnn,input,target,class_mapping)
        if(predicted==expected):
            print(f"for file {ii} , predicted = expected = {predicted}")
            n = n + 1
    
    # Show percentage
    print("---------")
    print((n/949)*100)
