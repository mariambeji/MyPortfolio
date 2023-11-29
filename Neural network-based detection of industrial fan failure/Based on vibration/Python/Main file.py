# -*- coding: utf-8 -*-
"""
Created on Tue May 31 15:43:18 2022

@author: khalil&beji&taher&imed
"""

import tensorflow as tf
from tensorflow.keras import Sequential
from tensorflow.keras.layers import Flatten, Dense, Dropout, BatchNormalization
from tensorflow.keras.layers import Conv2D, MaxPool2D
from tensorflow.keras.optimizers import Adam
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler, LabelEncoder
import scipy.stats as stats
from mlxtend.plotting import plot_confusion_matrix
from sklearn.metrics import confusion_matrix


# Show the learning curve
def plot_learningCurve(history, epochs):
  # Plot training & validation accuracy values
  epoch_range = range(1, epochs+1)
  plt.plot(epoch_range, history.history['accuracy'])
  plt.plot(epoch_range, history.history['val_accuracy'])
  plt.title('Model accuracy')
  plt.ylabel('Accuracy')
  plt.xlabel('Epoch')
  plt.legend(['Train', 'Val'], loc='upper left')
  plt.show()

  # Plot training & validation loss values
  plt.plot(epoch_range, history.history['loss'])
  plt.plot(epoch_range, history.history['val_loss'])
  plt.title('Model loss')
  plt.ylabel('Loss')
  plt.xlabel('Epoch')
  plt.legend(['Train', 'Val'], loc='upper left')
  plt.show()
  
#separate the dataset into frames of frame_size measures
def get_frames(df, frame_size, hop_size):

    N_FEATURES = 6

    frames = []
    labels = []
    for i in range(0, len(df) - frame_size, hop_size):
        a = df['AccelerometerX'].values[i: i + frame_size]
        b = df['AccelerometerY'].values[i: i + frame_size]
        c = df['AccelerometerZ'].values[i: i + frame_size]
        d = df['GyroscopeX'].values[i: i + frame_size]
        e = df['GyroscopeY'].values[i: i + frame_size]
        f = df['GyroscopeZ'].values[i: i + frame_size]


        
        # Retrieve the most often used label in this segment
        label = stats.mode(df['label'][i: i + frame_size])[0][0]
        frames.append([a, b, c, d, e, f])
        labels.append(label)

    # Bring the segments into a better shape
    frames = np.asarray(frames).reshape(-1, frame_size, N_FEATURES)
    labels = np.asarray(labels)

    return frames, labels

# View our version of TensorFlow
print(tf.__version__)

# Import the contents of the CSV file
df = pd.read_csv('Combined Dataset.csv')

# Conversion of accelerometer and gyroscope values to float
df['AccelerometerX']=df['AccelerometerX'].astype('float')
df['AccelerometerY']=df['AccelerometerY'].astype('float')
df['AccelerometerZ']=df['AccelerometerZ'].astype('float')

df['GyroscopeX']=df['GyroscopeX'].astype('float')
df['GyroscopeY']=df['GyroscopeY'].astype('float')
df['GyroscopeZ']=df['GyroscopeZ'].astype('float')


# Calculate the number of states in the dataset 
states = df['state'].value_counts().index

# Count the number of rows for each state
df['state'].value_counts()

# Take the same number of rows from each state to balance the dataset
On = df[df['state']=='On'].head(116280).copy()
Blocking = df[df['state']=='Blocking'].head(116280).copy()
Off = df[df['state']=='Off'].head(116280).copy()
Tapping = df[df['state']=='Tapping'].head(116280).copy()
Fan_Guards = df[df['state']=='Fan Guards'].head(116280).copy()
Blade_Fault = df[df['state']=='Blade_Fault'].head(116280).copy()
Mounting = df[df['state']=='Mounting'].head(116280).copy()


# Create a balanced dataset
balanced_data = pd.DataFrame()
balanced_data = balanced_data.append([On, Blocking, Off, Tapping, Fan_Guards, Blade_Fault,Mounting])

# Encode labels
label = LabelEncoder()
balanced_data['label'] = label.fit_transform(balanced_data['state'])

# Extract X and Y (in our case X are the accelerometer and gyro data and Y the label indicating the fan status)
X = balanced_data[['AccelerometerX', 'AccelerometerY', 'AccelerometerZ','GyroscopeX','GyroscopeY','GyroscopeZ']]
y = balanced_data['label']

# Scaling the values of X (z = (x - mean) / standard deviation) 
scaler = StandardScaler()
X = scaler.fit_transform(X)

# Creation of a variable containing the scaled values of X
scaled_X = pd.DataFrame(data = X, columns = ['AccelerometerX', 'AccelerometerY', 'AccelerometerZ','GyroscopeX','GyroscopeY','GyroscopeZ'])
scaled_X['label'] = y.values

# Determining the grouping parameters of the table rows
Fs = 20
frame_size = Fs*4 # 80
hop_size = Fs*2 # 40

# Group the rows to give them as input to the model 
# In our case we will take groups of 80 measures 
X, y = get_frames(scaled_X, frame_size, hop_size)

# Preparation of the training and validation dataset
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.2, random_state = 0, stratify = y)


# Change the shape of the training and validation X's 
X_train = X_train.reshape(16277, 80, 6, 1)
X_test = X_test.reshape(4070, 80, 6, 1)


# Creating a model
model = Sequential()
model.add(Conv2D(16, (2, 2), activation = 'relu', input_shape = X_train[0].shape))
model.add(Dropout(0.1))
model.add(Conv2D(32, (2, 2), activation='relu'))
model.add(Dropout(0.2))
model.add(Flatten())
model.add(Dense(64, activation = 'relu'))
model.add(Dropout(0.5))
model.add(Dense(7, activation='softmax'))

# Compiling the model
model.compile(optimizer=Adam(learning_rate = 0.001), loss = 'sparse_categorical_crossentropy', metrics = ['accuracy'])

# Model training
history = model.fit(X_train, y_train, epochs = 10, validation_data= (X_test, y_test), verbose=1)

# Show the learning curve
plot_learningCurve(history, 10)

# Extract predictions for validation X
y_pred = model.predict_classes(X_test)

# Display the correlation matrix
mat = confusion_matrix(y_test, y_pred)
plot_confusion_matrix(conf_mat=mat, class_names=label.classes_, show_normed=True, figsize=(7,7))

# Saving the model
model.save('model.h5')


