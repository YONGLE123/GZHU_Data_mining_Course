// kmeans.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include<fstream>
#include<sstream> 
#include<string>
#include <iomanip>
#include"kmeans1.h"
using namespace std;

int main()
{
	vector<std::vector<std::vector<double> > >v;
	//使用文件流导入csv文件
	ifstream _csvInput("C:\\Users\\Lenovo\\Desktop\\z-score_Data.csv");
	double** data;
	data= new double*[107];//定义一个数组
	int flag = 0;//标志变量
	for (int i = 0; i < 107; i++)
	{
		data[i] = new double[11];
		string line;//文件中一行的数据
		getline(_csvInput, line);//读取一行数据
		if (flag >0) {
			istringstream Readstr(line);//定义输出控制类对象
			string _partOfstr;//一行中的各个数据
			for (int j = 0; j <= 15; j++)
			{
				getline(Readstr, _partOfstr, ',');
				if (j > 4) {
					data[i-1][j-5] = atof(_partOfstr.c_str());
				}
			}
		}
		flag++;
	}
	ClusterMethod a;
	a.GetClusterd(v, data, 5, 106, 11);//外部接口函数,聚类数4，样本数106，每个样本的特征数11
	//输出
	for (int i = 0; i < v.size(); ++i)
	{
		cout << "第" << i + 1 << "类" << endl;
		for (int j = 0; j < v[i].size(); ++j)
		{
			for (int k = 0; k < v[i][j].size(); ++k)
			{
				cout << v[i][j][k] << " ";
			}
			cout << endl;
		}
	}
}
	



