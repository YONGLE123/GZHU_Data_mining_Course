import pandas as pd
import numpy as np
from pandas import DataFrame as df
import matplotlib.pyplot as plt
import math
df=pd.read_table('sorted.txt',header=None,sep=",") #读取txt文件

#量化Constitution数据
def quantization(y):
    for i in range(y.size):
        if y[i]=='excellent':
            y[i]=100
        elif y[i]=='good':
            y[i]=90
        elif y[i]=='general':
            y[i]=80
        elif y[i]=='bad':
            y[i]=70
        else:
            y[i]=60
#均值
def Mean(y):
    num = 0
    for i in range(y.size):
        num += y[i]
    return num/y.size

#标准差
def std(y,u):
    nu=0
    for j in range(y.size):
        nu+=(y[j]-u)**2
    return  math.sqrt(nu/y.size)
#z_socre
def z_score(y,u,std):
    for i in range(y.size):
        if std==0:
            y[i]=0
        else:
            y[i]=(y[i]-u)/std

if __name__ == '__main__':
    quantization(df[15].values)
    for i in range(5,16):
        z_score(df[i].values,Mean(df[i].values),std(df[i].values,Mean(df[i].values)))
    df.to_csv('z-score_Data.csv',index=False)


