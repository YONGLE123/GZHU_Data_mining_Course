#pragma once
#include<iostream>
#include<vector>
using namespace std;

class ClusterMethod {
public:
	int mSampleNum;//������
	int mClusterNum;//������
	int mFeatureNum;//ÿ��������������
	double** mpsample;//�洢��������
	double** mpCenters;//�洢��������
	double** pDistances;//�������
	int* ClusterResult;//������
	int MaxIterationTimes;//����������

public:
	void GetClusterd(vector<std::vector<std::vector<double> > >& v, double** feateres, 
		int ClusterNum, int SampleNum, int FeatureNum);//�ⲿ�ӿ�
	void Initialize(double** features, int ClusterNum, int SampleNum, int FeatureNum);//���ʼ��
	void k_means(vector < vector<vector<double> > >&v);//�㷨���
	void k_means_Initialize();//�������ĳ�ʼ��
	void k_means_Calculate(vector<vector<vector<double> > >& v);//�������
};
//�ຯ����ʵ��
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
//��ʼ������ʵ��
void ClusterMethod::Initialize(double** features, int ClusterNum, int SampleNum, int FeatureNum)
{
	mpsample = features;
	mClusterNum = ClusterNum;//������
	mSampleNum = SampleNum;//������
	mFeatureNum = FeatureNum;//������
	MaxIterationTimes = 10;//����������Ϊ10

	mpCenters = new double* [mClusterNum];//�������ľ���
	for (int i = 0; i < mClusterNum; i++) {
		mpCenters[i] = new double[mFeatureNum];//ÿһ���������ľ����Ԫ�ض�Ӧ��������Ŀ��Ԫ��
	}
	pDistances = new double* [mSampleNum];//�������
	for (int i = 0; i < mSampleNum; i++) {
		mpCenters[i] = new double[mClusterNum];//ÿһ���������ľ����Ԫ�ض�Ӧ��������Ŀ��Ԫ��
	}
	ClusterResult = new int[mSampleNum];
}
//�㷨���
void ClusterMethod::k_means(vector<vector<vector<double> > >& v)
{
	k_means_Initialize();
	k_means_Calculate(v);
}
//��ʼ����������
void ClusterMethod::k_means_Initialize()
{
	for (int i = 0; i < mClusterNum; ++i)
	{
		for (int k = 0; k < mFeatureNum; ++k)
		{
			mpCenters[i][k] = mpsample[i][k];//��ʼ�ľ������ľ�������������ֵ
		}
	}
}
//�������
void ClusterMethod::k_means_Calculate(vector<vector<vector<double> > >& v)
{
	double J = DBL_MAX;//Ŀ�꺯��
	int time = MaxIterationTimes;//����������
	pDistances = new double* [mSampleNum];
	while (time)
	{
		double now_J = 0;//�ϴθ��¾������ĺ��Ŀ�꺯��
		--time;//��������������
		//�����ʼ��
		for (int i = 0; i < mSampleNum; ++i)
		{
			pDistances[i] = new double[mClusterNum];
			for (int j = 0; j < mClusterNum; ++j)
			{
				pDistances[i][j] = 0;//��ʼ���������ÿһ��Ԫ��ֵΪ0
			}
		}
		//����ŷʽ����
		for (int i = 0; i < mSampleNum; ++i)
		{
			for (int j = 0; j < mClusterNum; ++j)
			{
				for (int k = 0; k < mFeatureNum; ++k)
				{
					pDistances[i][j] += abs(pow(mpsample[i][k], 2) - pow(mpCenters[j][k], 2));//����ŷ�Ͼ���
				}
				now_J += pDistances[i][j];
			}
		}
		if (J - now_J < 0.01)//Ŀ�꺯�����ٱ仯����ѭ��
		{
			break;
		}
		J = now_J;

		//a�����ʱ������
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
			//	v[ClusterResult[i]].push_back(vec);���ﲻ��������v�������ݣ���Ϊvû�г�ʼ����С
		}
		v = a;

		//�����µľ�������
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
	p.open("C:\\Users\\Lenovo\\Desktop\\output.csv", ios::out | ios::trunc);//���ļ�·��
	//�����������
	cout << "�������ģ�" << endl;
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

