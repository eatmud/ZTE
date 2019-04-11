#ifndef _COUTDATA_H_
#define _COUTDATA_H_

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <iterator>
#include <algorithm>

using namespace std;

void coutData(vector<vector<int>> &v)
{
	if (v.empty())
		cout << "vector is empty!" << endl;
	vector<vector<int>>::iterator lineIter;
	vector<int>::iterator rowIter;
	vector<int> temp;
	for (lineIter = v.begin(); lineIter != v.end(); ++lineIter)
	{
		temp = *lineIter;
		for (rowIter = temp.begin(); rowIter != temp.end(); ++rowIter)
			cout << *rowIter << " ";
		cout << endl;
	}
}
void coutData(list<list<int>> &v)
{
	if (v.empty())
		cout << "vector is empty!" << endl;
	list<list<int>>::iterator lineIter;
	list<int>::iterator rowIter;
	list<int> temp;
	for (lineIter = v.begin(); lineIter != v.end(); ++lineIter)
	{
		temp = *lineIter;
		for (rowIter = temp.begin(); rowIter != temp.end(); ++rowIter)
			cout << *rowIter << " ";
		cout << endl;
	}
}
void coutData(vector<int> &v)
{
	if (v.empty())
		cout << "vector is empty!" << endl;
	vector<int>::iterator iter;
	for (iter = v.begin(); iter != v.end(); ++iter)
		cout << *iter << " ";
	cout << endl;
}
void coutData(list<int> &v)
{
	if (v.empty())
		cout << "vector is empty!" << endl;
	list<int>::iterator iter;
	for (iter = v.begin(); iter != v.end(); ++iter)
		cout << *iter << ",";
	cout << endl;
}

#endif