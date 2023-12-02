# -*- coding: utf-8 -*-
"""
Created on Sun Aug 15 19:50:12 2021

@author: khalil&beji&taher&imed
"""

    
import torch 
import torchaudio
from torch import nn
from torch.utils.data import DataLoader
import time
from Fan import Fan
from cnn import CNNNetwork


torch.cuda.empty_cache()

def train_one_epoch(model,data_loader,loss_fn,optimiser,device):
    # Create a loop and loop through all samples in the dataset 
    # each iteration gets a batch
    correct = 0
    total = 0
    for inputs,targets in data_loader:
        inputs,targets = inputs.to(device), targets.to(device)
        
        # Calculate loss
        predictions = model(inputs)
        loss = loss_fn (predictions, targets)        
        # Backpropagate loss and update weights 
        optimiser.zero_grad()
        loss.backward()  # Backpropagation
        optimiser.step() # updata weights 
        _,predicted = predictions.max(1)
        total += targets.size(0)
        correct += predicted.eq(targets).sum().item()
        
    print(f"Loss : {loss.item()}")    
    accu = 100. * correct / total 
    print(f"Accu : {accu}")

    

def train(model,data_loader,loss_fn,optimiser,device,epochs):
    for i in range(epochs):
        start = time.time()
        print(f"Epoch {i+1}")
        train_one_epoch(model, data_loader, loss_fn, optimiser, device)
        print("Time passed to train one epoch : ")
        stop = time.time()
        print(stop-start)
        print("------------")
    print("Training is Done ")
    

if __name__ == "__main__":
    # Choice of treatment unit according to availability 
    if torch.cuda.is_available():
        device = "cuda"
    else:
        device = "cpu"
    # Forcing the processing unit = CPU because of a bug
    device = "cpu"
    print(f"using {device} device")  
    
    # Path to the CSV file of the dataset
    ANNOTATIONS_FILE = "C:/Users/khalil/Desktop/Synth/Wevioo Stage/Py/DbTrain.csv"
    
    # sampling frequency, number of samples, batch size
    SAMPLE_RATE = 16000
    NUM_SAMPLES = 160000
    BATCH_SIZE = 256 
    
    # Configuration of the transformation to be performed ( Mel_Spectrogram with the following parameters )
    mel_spectrogram = torchaudio.transforms.MelSpectrogram(sample_rate=SAMPLE_RATE,
                                                           n_fft=1024,
                                                           hop_length=5100,
                                                           n_mels=30
                                                           )
    # Object of type Fan allowing to load the files
    Fan = Fan(ANNOTATIONS_FILE,
              mel_spectrogram,
              SAMPLE_RATE,
              NUM_SAMPLES,
              device
              )
    # DataLoader to split the dataset into batches and mix it 
    train_data_loader = DataLoader(Fan,
                                   batch_size = BATCH_SIZE,
                                   shuffle=True
                                   )
    
    
    # pass the model to the processing unit
    cnn = CNNNetwork().to(device)
    
    # start training 
    train(cnn,train_data_loader,nn.CrossEntropyLoss(),torch.optim.SGD(cnn.parameters(),lr=.001,weight_decay=1e-6,momentum=0.9,nesterov=True),device ,5)
    
    # export the model to a .pth file  
    torch.save(cnn.state_dict(),"cnn16.pth")
    print("Model trained and stored at cnn16.pth")
    
    
    