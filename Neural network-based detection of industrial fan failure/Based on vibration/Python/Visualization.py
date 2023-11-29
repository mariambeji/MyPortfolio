# -*- coding: utf-8 -*-
"""
Created on Sun Jun  5 20:08:00 2022

@author: khalil&beji&taher&imed
"""

import pandas as pd 
import matplotlib.pyplot as plt


one_filename = r'\data\All\MOUNTING_20200629120748.csv'

new_df=pd.read_csv(one_filename)

new_df = new_df.drop(new_df.index[80:])
plt.plot(new_df['sequence'],new_df['AccelerometerX'],color='g',label='Accelero X')

plt.plot(new_df['sequence'],new_df['AccelerometerY'],color='r',label='Accelero Y')

plt.plot(new_df['sequence'],new_df['AccelerometerZ'],color='b',label='Accelero Z')

plt.plot(new_df['sequence'],new_df['GyroscopeX'],color='c',label='Gyro X')

plt.plot(new_df['sequence'],new_df['GyroscopeY'],color='m',label='Gyro Y')

plt.plot(new_df['sequence'],new_df['GyroscopeZ'],color='y',label='Gyro Z')

plt.legend()

plt.show()