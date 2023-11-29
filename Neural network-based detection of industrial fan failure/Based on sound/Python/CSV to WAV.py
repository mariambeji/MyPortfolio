# -*- coding: utf-8 -*-
"""
Created on Thu Aug 26 12:05:32 2021

@author: khalil&beji&taher&imed
"""

import csv
import scipy.io.wavfile as wavf
import numpy as np
from matplotlib import pyplot as plt

# CSV file path 

filename = 'mytest2.csv'

with open(filename, 'rU') as p:
        # converts the csv file into a list of lists 
        my_list = [list(map(int,rec)) for rec in csv.reader(p, delimiter=',')]
        

plt.plot(my_list[0])
plt.show()

arr = np.array(my_list[0])
n=(arr).astype(np.int16)
fs = 16000
out_f = 'out.wav'
wavf.write(out_f, fs, n)