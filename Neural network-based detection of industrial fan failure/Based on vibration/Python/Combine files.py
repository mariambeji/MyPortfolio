# -*- coding: utf-8 -*-
"""
Created on Mon May 30 12:13:50 2022

@author: khalil&beji&taher&imed
"""

import pandas as pd 
import numpy as np
import glob


# Creating an empty list 
all_dfs = []

# Browse for files containing Tapping in their names
for one_filename in glob.glob(r'\data\All\TAPPING*.csv'):
    print(f'loading {one_filename}')
    # Open the CSV file
    new_df=pd.read_csv(one_filename)
    # Store the dataframe in a list
    all_dfs.append(new_df)

# Concatenation of the dataframe present in the liste
Blade_fault = pd.concat(all_dfs)

# creation of a column vector containing the string 'Tapping'
a =np.full(( Blade_fault.shape[0],1),'Tapping')

# Adding the column
Blade_fault = Blade_fault.assign(state = a)

#export as CSV file for future use
Blade_fault.to_csv('Tapping.csv', index=False)

test=pd.read_csv('Tapping.csv')

