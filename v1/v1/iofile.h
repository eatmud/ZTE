
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>

using namespace std;

void readFile(string filePath, vector<vector<int> > &data)
{
	ifstream inf;
	int value;
	vector<int> line;
	inf.open(filePath);
	if (!inf.is_open())
		cout << "Can't open this file in the path : " << filePath << endl;
	while (!inf.eof())
	{
		inf >> value;
		line.push_back(value);
		if (inf.get() == '\n')
		{
			data.push_back(line);
			line.clear();
		}

	}
	//data.erase(data.end() - 1, data.end());
	inf.close();
}


void writeToTxt(vector<vector<int> > &sorce, string filePath)
{
	ofstream outf;
	vector<vector<int>>::iterator lineIter;
	vector<int>::iterator rowIter;
	outf.open(filePath);
	if (!outf.is_open())
		cout << "Can't write to this file in the path : " << filePath << endl;
	for (lineIter = sorce.begin(); lineIter != sorce.end(); ++lineIter)
	{
		for (rowIter = lineIter->begin(); rowIter != lineIter->end(); ++rowIter)
		{
			outf << *rowIter << " ";
		}
		outf << endl;
	}
	outf.close();
}