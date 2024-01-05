// teststreamfile.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include<iostream>
#include<fstream>
#include<vector>
#include<bitset>
#include<algorithm>
#include<thread>
#include<mutex>
#include<future>
#include<sstream>
#include<malloc.h>
#include<array>
#include"deg.h"


using namespace std;

int findMax(int* arr, int size)
{
	int max = arr[0];

	for (int i = 1; i < size; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}

	return max;
}

int findMinindex(int* arr, int size)
{
	int min = arr[0];
	int minindex = 0;
	for (int i = 1; i < size; i++) {
		if (arr[i] < min) {
			min = arr[i];
			minindex = i;
		}
	}

	return minindex;
}

int main()
{

	vector<int> cubeIndex = { 0, 10, 20, 30, 40, 50, 60, 70, 79, 34};
  

	bitset<80> cube{ 0 };
	for (auto& it : cubeIndex)
		cube[it] = 1;
	int reduceRound = 610;
	cout << cube << endl;
	ifstream file("terms1.txt"); 
	vector<string> elements;
	int lb = 25;
	int ub = 40;
	if (file.is_open()) { 
		string line;

		while (getline(file, line)) { 

			stringstream ss(line);
			std::string token;
			while (getline(ss, token, ',')) {
				elements.push_back(token);
			}
		}
		for (int i = 0; i < elements.size(); i++)
		{
			cout << elements[i] << endl;
		}

		file.close(); 
	}
	cout << "*********************start*********************" << endl;
	cout << "cube：";
	for (int i = 0; i < cube.size(); i++)
	{
		if (cube[i] == 1)
		{
			cout << i << ",";
		}
	}
	cout << endl;
	ofstream out("result.txt");
	while (true)
	{
		int* indexZero = new int[80 - cube.count()];
		int tmpflag = 0;
		for (int i = 0; i < 80; i++)
		{
			if (cube[i] == 0)
			{
				indexZero[tmpflag++] = i;
			}
		}
		int* allDegree = new int[80 - cube.count()];
		int aDindex = 0;
		for (int i = 0; i < 80 - cube.count(); i++)
		{
			cube[indexZero[i]] = 1;
			cout << "当前添加的cube位：" << indexZero[i] << endl;
			cout << "这里当前检索的cube：";
			for (int i = 0; i < cube.size(); i++)
			{
				if (cube[i] == 1)
				{
					cout << i << ",";
				}
			}
			cout << endl;
			int cyclenumber = elements.size() / 3;
			int* midDegree = new int[cyclenumber];
			int mDindex = 0;
			for (int j = 0; j < cyclenumber; j++)
			{
				int num[3];
				int start = j * 3;
				num[0] = stoi(elements[start]);
				num[1] = stoi(elements[start + 1]);
				num[2] = stoi(elements[start + 2]);
			//	num[3] = stoi(elements[start + 3]);
			//	num[4] = stoi(elements[start + 4]);
				bitset<288> finalterm{ 0 };
				finalterm[num[0]] = 1;
				finalterm[num[1]] = 1;
				finalterm[num[2]] = 1;
			//	finalterm[num[3]] = 1;
			//	finalterm[num[4]] = 1;

		
				midDegree[mDindex] = computeDegree(cube, reduceRound, finalterm) - cube.count();


				mDindex++;
			}
			cube[indexZero[i]] = 0;
			allDegree[aDindex] = findMax(midDegree, cyclenumber);
			cout << "当前最大阶数：" << findMax(midDegree, cyclenumber) << endl;
			cout << endl;
			aDindex++;
			delete[] midDegree;
		}
		int newIndex = findMinindex(allDegree, 80 - cube.count());
		cout << "该次检索中阶数最小：" << allDegree[newIndex] << "  当前应该添加的索引：" << indexZero[newIndex] << endl;
		cout << endl;
		cubeIndex.emplace_back(indexZero[newIndex]);
		for (auto& it : cubeIndex)
			cube[it] = 1;

		if (cube.count() >= lb && cube.count() <= ub)
		{

			if (out.is_open())
			{


				out << "*******cube：";
				for (int i = 0; i < cube.size(); i++)
				{
					if (cube[i] == 1)
					{
						out << i << ",";
					}
				}
				out << endl;
			}
			//system("pause");
		}
		delete[] indexZero;
		if (cube.count() >= 50)
		{
			out.close();
			break;
		}
	}

}