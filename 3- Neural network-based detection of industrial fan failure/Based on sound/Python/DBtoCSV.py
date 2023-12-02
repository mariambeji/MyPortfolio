# -*- coding: utf-8 -*-
"""
Created on Mon Aug 16 16:43:38 2021

@author: khalil&beji&taher&imed
"""
import glob
import pandas as pd




path_abnormal =r"D:\fan\Train\Abnormal\*.wav"
path_normal=r"D:\fan\Train\Normal\*.wav"


abnormal = glob.glob(path_abnormal)
normal = glob.glob(path_normal)
ones = [1] * len(abnormal)
zeros = [0] * len(normal)
Features=ones+zeros

Class = ["Abnormal"] * len(abnormal) + ["Normal"] * len(normal)
# Path , Class ID , Class
test = {'Path' : abnormal + normal ,'Class ID' : Features, 'Class' : Class }
df_test = pd.DataFrame(test)

df_test.to_csv("DbTrain.csv")



path_abnormal =r"D:\fan\Validation\Abnormal\*.wav"
path_normal=r"D:\fan\Validation\Normal\*.wav"


abnormal = glob.glob(path_abnormal)
normal = glob.glob(path_normal)
ones = [1] * len(abnormal)
zeros = [0] * len(normal)
Features=ones+zeros

Class = ["Abnormal"] * len(abnormal) + ["Normal"] * len(normal)
# Path , Class ID , Class
test = {'Path' : abnormal + normal ,'Class ID' : Features, 'Class' : Class }
df_test = pd.DataFrame(test)

df_test.to_csv("DbTest.csv")





