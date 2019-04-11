#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>

#include "coutData.h"
#include "iofile.h"

using namespace std;
 

int main()
{
	string filepath{ "../gridtopoAndRequest.txt" };
	vector<vector<int>> data;
	readFile(filepath, data);
	return 0;
}