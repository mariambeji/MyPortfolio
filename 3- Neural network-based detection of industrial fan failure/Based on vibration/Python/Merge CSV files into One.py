# -*- coding: utf-8 -*-
"""
Created on Tue May 31 15:29:58 2022

@author: khalil&beji&taher&imed
"""
import pandas as pd 
import glob

# Create an empty list
all_dfs = []

# See all the csv files
for one_filename in glob.glob(r'C:\Users\khalil\Desktop\IIA 4\PFA\Python\*.csv'):
    print(f'loading {one_filename}')
    # Open the csv file
    new_df=pd.read_csv(one_filename)
    # Store the dataframe in a list
    all_dfs.append(new_df)

# Concatenation of the dataframe present in the list
final = pd.concat(all_dfs)

# Delete the column named sequence 
final = final.drop('sequence',1)


#export as CSV file for future use
final.to_csv('Combined Dataset.csv', index=False)


