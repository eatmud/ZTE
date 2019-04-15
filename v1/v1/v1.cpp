#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stdlib.h>

#include "coutData.h"
#include "iofile.h"

using namespace std;
 
//存放原始拓扑信息
vector<int> gridTopo[956];
//存放所有业务需求信息
vector<int> request[4001];

vector<vector<int>> data;

void clearVec()
{
	for (int i = 0; i<956; i++) gridTopo[i].clear();
	for (int i = 0; i<4001; i++) request[i].clear();
}
//void readTxt()
//{
//	char readLine[1000];
//	const char *delim = " ";
//	char *p;
//	for (int i = 0; i<956; i++)
//	{
//		cin.getline(readLine, 1000);
//		p = strtok(readLine, delim);
//		while (p)
//		{
//			gridTopo[i].push_back(atoi(p));
//			p = strtok(NULL, delim);
//		}
//	}
//	for (int i = 0; i<4001; i++)
//	{
//		cin.getline(readLine, 1000);
//		p = strtok(readLine, delim);
//		while (p)
//		{
//			request[i].push_back(atoi(p));
//			p = strtok(NULL, delim);
//		}
//	}
//}

void getdata()
{
	int i = 0;
	vector<vector<int>>::iterator lineIter;
	vector<int>::iterator rowIter;
	for (lineIter = data.begin(); lineIter != data.end() && i < 956; ++lineIter,++i)
	{
		for (rowIter = lineIter->begin(); rowIter != lineIter->end(); ++rowIter)
		{
			gridTopo[i].push_back(*rowIter);
		}		
	}
	for (i = 0; lineIter != data.end() && i < 4001; ++lineIter, ++i)
	{
		for (rowIter = lineIter->begin(); rowIter != lineIter->end(); ++rowIter)
		{
			request[i].push_back(*rowIter);
		}
	}
}
void coutgridTopo()
{
	if (gridTopo->empty())
	{
		cout << "gridTopo is empty" << endl;
		return;
	}
	int lineNum = 956;
	int rowNum = 0;
	int i, j;
	for (i = 0; i < lineNum; ++i)
	{
		rowNum = gridTopo[i].size();
		for (j = 0; j < rowNum;++j)
			cout << gridTopo[i][j] << " ";
		cout << endl;
	}
}
void coutrequest()
{
	if (request->empty())
	{
		cout << "request is empty" << endl;
		return;
	}
	int lineNum = 4001;
	int rowNum = 0;
	int i, j;
	for (i = 0; i < lineNum; ++i)
	{
		rowNum = request[i].size();
		for (j = 0; j < rowNum; ++j)
			cout << request[i][j] << " ";
		cout << endl;
	}
}
int main()
{
	//readTxt();
	string filepath{ "../gridtopoAndRequest.txt" };
	readFile(filepath, data);
	//coutData(data);
	getdata();
	coutgridTopo();
	coutrequest();

	return 0;
}