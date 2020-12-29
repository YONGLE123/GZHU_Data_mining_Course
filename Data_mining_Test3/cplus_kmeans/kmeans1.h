#pragma once
#include<iostream>
#include<vector>
using namespace std;

class ClusterMethod {
public:
	int mSampleNum;//样本数
	int mClusterNum;//聚类数
	int mFeatureNum;//每个样本的特征数
	double** mpsample;//存储输入样本
	double** mpCenters;//存储聚类中心
	double** pDistances;//距离矩阵
	int* ClusterResult;//聚类结果
	int MaxIterationTimes;//最大迭代次数

public:
	void GetClusterd(vector<std::vector<std::vector<double> > >& v, double** feateres, 
		int ClusterNum, int SampleNum, int FeatureNum);//外部接口
	void Initialize(double** features, int ClusterNum, int SampleNum, int FeatureNum);//类初始化
	void k_means(vector < vector<vector<double> > >&v);//算法入口
	void k_means_Initialize();//聚类中心初始化
	void k_means_Calculate(vector<vector<vector<double> > >& v);//聚类计算
};
//类函数的实现
void ClusterMethod::GetClusterd(vector<std::vector<std::vector<double> > >& v, double** feateres, int ClusterNum, int SampleNum, int FeatureNum)
{
	Initialize(feateres, ClusterNum, SampleNum, FeatureNum);
	k_means(v);
	/*for (int i = 0; i < mClusterNum; i++) {
		delete[]mpCenters[i];
	}
	for (int i = 0; i < mSampleNum; i++) {
		delete[]pDistances[i];
	}*/
}
//初始化函数实现
void ClusterMethod::Initialize(double** features, int ClusterNum, int SampleNum, int FeatureNum)
{
	mpsample = features;
	mClusterNum = ClusterNum;//聚类数
	mSampleNum = SampleNum;//样本数
	mFeatureNum = FeatureNum;//特征数
	MaxIterationTimes = 10;//最大迭代次数为10

	mpCenters = new double* [mClusterNum];//聚类中心矩阵
	for (int i = 0; i < mClusterNum; i++) {
		mpCenters[i] = new double[mFeatureNum];//每一个聚类中心矩阵的元素对应有特征数目的元素
	}
	pDistances = new double* [mSampleNum];//距离矩阵
	for (int i = 0; i < mSampleNum; i++) {
		mpCenters[i] = new double[mClusterNum];//每一个聚类中心矩阵的元素对应有特征数目的元素
	}
	ClusterResult = new int[mSampleNum];
}
//算法入口
void ClusterMethod::k_means(vector<vector<vector<double> > >& v)
{
	k_means_Initialize();
	k_means_Calculate(v);
}
//初始化聚类中心
void ClusterMethod::k_means_Initialize()
{
	for (int i = 0; i < mClusterNum; ++i)
	{
		for (int k = 0; k < mFeatureNum; ++k)
		{
			mpCenters[i][k] = mpsample[i][k];//初始的聚类中心矩阵用样本矩阵赋值
		}
	}
}
//聚类过程
void ClusterMethod::k_means_Calculate(vector<vector<vector<double> > >& v)
{
	double J = DBL_MAX;//目标函数
	int time = MaxIterationTimes;//最大迭代次数
	pDistances = new double* [mSampleNum];
	while (time)
	{
		double now_J = 0;//上次更新距离中心后的目标函数
		--time;//最大迭代次数减少
		//距离初始化
		for (int i = 0; i < mSampleNum; ++i)
		{
			pDistances[i] = new double[mClusterNum];
			for (int j = 0; j < mClusterNum; ++j)
			{
				pDistances[i][j] = 0;//初始化距离矩阵每一个元素值为0
			}
		}
		//计算欧式距离
		for (int i = 0; i < mSampleNum; ++i)
		{
			for (int j = 0; j < mClusterNum; ++j)
			{
				for (int k = 0; k < mFeatureNum; ++k)
				{
					pDistances[i][j] += abs(pow(mpsample[i][k], 2) - pow(mpCenters[j][k], 2));//计算欧氏距离
				}
				now_J += pDistances[i][j];
			}
		}
		if (J - now_J < 0.01)//目标函数不再变化结束循环
		{
			break;
		}
		J = now_J;

		//a存放临时分类结果
		vector<vector<vector<double> > > a(mClusterNum);
		for (int i = 0; i < mSampleNum; ++i)
		{

			double min = DBL_MAX;
			for (int j = 0; j < mClusterNum; ++j)
			{
				if (pDistances[i][j] < min)
				{
					min = pDistances[i][j];
					ClusterResult[i] = j;
				}
			}

			vector<double> vec(mFeatureNum);
			for (int k = 0; k < mFeatureNum; ++k)
			{
				vec[k] = mpsample[i][k];
			}
			a[ClusterResult[i]].push_back(vec);
			//	v[ClusterResult[i]].push_back(vec);这里不能这样给v输入数据，因为v没有初始化大小
		}
		v = a;

		//计算新的聚类中心
		for (int j = 0; j < mClusterNum; ++j)
		{
			for (int k = 0; k < mFeatureNum; ++k)
			{
				mpCenters[j][k] = 0;
			}
		}
		for (int j = 0; j < mClusterNum; ++j)
		{
			for (int k = 0; k < mFeatureNum; ++k)
			{
				for (int s = 0; s < v[j].size(); ++s)
				{
					mpCenters[j][k] += v[j][s][k];
				}
				if (v[j].size() != 0)
				{
					mpCenters[j][k] /= v[j].size();
				}
			}
		}
	}
	ofstream p;
	p.open("C:\\Users\\Lenovo\\Desktop\\output.csv", ios::out | ios::trunc);//打开文件路径
	//输出聚类中心
	cout << "聚类中心：" << endl;
	for (int j = 0; j < mClusterNum; ++j)
	{
		for (int k = 0; k < mFeatureNum; ++k)
		{
			cout << mpCenters[j][k] << " ";
			p << mpCenters[j][k] << ",";
		}
		cout << endl;
		p << endl;
	}
	p.close();
}

