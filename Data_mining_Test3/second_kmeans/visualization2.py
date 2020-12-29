import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import math
from sklearn.cluster import KMeans
from mpl_toolkits.axisartist.axislines import Subplot

plt.rcParams['font.sans-serif']=['SimHei'] #显示中文标签
plt.rcParams['axes.unicode_minus']=False   #这两行需要手动设置

df2=pd.read_table('test.txt',index_col=None,header=None,sep=",") #读取txt文件数据
n=2     # 聚类数

def km():
    # 由于数据没有列名， 所以先给每个列取个名字。
    df2.columns = ['one', 'two']

    # 聚类
    kmeans = KMeans(n)
    kmeans.fit(df2[['one','two']])

    #挑选出前两个维度作为x轴和y轴
    x_axis = df2['one']
    y_axis = df2['two']

    #预测全部数据
    all_predictions = kmeans.predict(df2.values)

    #打印出来数据的聚类散点图
    plt.title('Kmeans聚类散点图')
    plt.scatter(x_axis, y_axis, c=all_predictions)
    plt.savefig("kmeans_TEST.jpg")
    plt.show()
    #获取聚类中心
    centers = kmeans.cluster_centers_
    return centers

def center(centers):
    sum=[0,0]
    for i in centers:#计算加和
        sum[0]+=i[0]
        sum[1]+=i[1]
    #求所有聚类中心的平均值得到类中心
    avg=[0,0]
    avg[0]=sum[0]/len(centers)#计算平均值
    avg[1]=sum[1]/len(centers)#计算平均值
    area=3.14*20#设定点的大小
    # 设置图像标题
    print(avg[1])
    plt.title('1特征聚类中心平均值%s，2特征聚类中心平均值%s'%(float('%.3f'%avg[0]),float('%.3f'%avg[1])))
    #画类中心点
    plt.scatter(avg[0],avg[1],s=area,c=2)#画点
    plt.savefig("kmeans_centers.jpg")#保存图片
    plt.show()#显示图片
    return avg

def radiu(avg):
    #画类半径
    maxr1=0
    maxr2=0
    for i in range(len(centers)):
        r=(avg[0]-centers[i][0])#计算每一个聚类中心到平均值聚类中心的距离
        if(maxr1<r):
            maxr1=float('%.2f'%r)#求出距离特征一的聚类中心最远的距离，并保留两位小数
    for i in range(len(centers)):
        r=math.sqrt((avg[1]-centers[i][1])**2)
        if(maxr2<r):
            maxr2=float('%.2f'%r)#求出距离特征二的聚类中心最远的距离，并保留两位小数

    x=[avg[0],maxr1]#坐标集合
    y=[avg[1],maxr2]#坐标集合
    plt.plot(x,x,color="r")#画线
    plt.scatter(x, x)#画点
    plt.savefig("kmeans_radius1.jpg")#保存图片
    plt.show()#显示图片
    plt.plot(y,y,color="b")#画线
    plt.scatter(y, y)#画点
    plt.savefig("kmeans_radius2.jpg")#保存图片
    plt.show()#显示图片


def judge(centers):
    #判断(2,6)是属于哪一类，即计算点(2,6)到所有聚类中心的欧氏距离
    distance={}#使用字典存储距离信息
    for i in range(n):
        dis=math.sqrt((2-centers[i][0])**2+(6-centers[i][1])**2)
        x={i:dis}
        distance.update(x)#更新字典
    #输出按照值排序后的字典对应的键值
    print("点(2,6)属于第%d类"%(sorted(distance.items(), key = lambda kv:(kv[1], kv[0]))[0][0]+1))

if __name__ == '__main__':
    centers=km()#对数据进行kmeans聚类,并可视化散点图，并返回聚类中心
    avg=center(centers)#可视化类中心
    radiu(avg)
    judge(centers)#判断点(2,6)属于哪一类
    #经过分析，我认为，聚为2类比较合适，因为样本中存在几个比较离散的数据，反映在坐标图上分布的比较偏，在聚类数为2的时候，两个簇中的点的
    #数量比较接近，且划分的比较开，而随着聚类数上升，由于偏远点的存在，始终难以促进每个类簇的点数量接近，只有当聚类数达到比较接近样本点数
    #的时候才能将每个类簇分的比较均匀比较开，但是那样的话"聚"的效果则无法显现了