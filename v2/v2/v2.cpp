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
#include <map>
#include <hash_map>
#include <utility>

using namespace std;

const int MAXLINKNUM = 956;
const int MAXREQUESTNUM = 4001;
const int LINENODENUM = 25;
const int ROWNODENUM = 20;
const int NODENUM = 500;
const int FINITY = 65535;
typedef struct
{
	int startNode;//起点
	int endNode;//终点
	int bandWidth;//带宽
	int cost;	//单位成本
	int useBandWidth;//已消耗带宽
}grid;
typedef struct
{
	int vertexNum, edgeNum;//顶点数，边数（连接的边数）
	vector<int*> vexs;//顶点数组
	vector<vector<grid>> matrix;//邻接矩阵
}AdjMatrix;
typedef multimap<int, grid>::iterator iteMultimap;
//存放原始拓扑信息
vector<int> gridTopo[956];
//存放所有业务需求信息
vector<int> request[4001];
//存放结果
vector<vector<int>> result;
//根据网络拓扑图生成multimap
multimap<int, grid> gridMap;
//邻接矩阵顶点
vector<int> vertex;
//邻接矩阵
AdjMatrix graf;



// FUNCTION 声明//

void clearVec();//初始化gridTopo[956]、request[4001]
void readTxt();//读入数据
void getVertex();//存放矩阵顶点
void coutData(vector<vector<int>> &v);//打印二维数组
void getGridMap();//生成网络拓扑multimap
void creatMetrix();//生成邻接矩阵
void getResult();//生成路径
int getTotalCost();//根据路径计算成本
void coutGridMap();//输出gridmap


// FUNCTION定义

//存放矩阵顶点
void getVertex()
{
	int i = 0;
	for (; i < NODENUM; ++i)
		vertex.push_back(i);
}
void clearVec()
{
	for (int i = 0; i<956; i++) gridTopo[i].clear();
	for (int i = 0; i<4001; i++) request[i].clear();
}
void readTxt()
{
	char readLine[1000];
	const char *delim = " ";
	char *p;
	for (int i = 0; i<956; i++)
	{
		cin.getline(readLine, 1000);
		p = strtok(readLine, delim);
		while (p)
		{
			gridTopo[i].push_back(atoi(p));
			p = strtok(NULL, delim);
		}
	}
	for (int i = 0; i<4001; i++)
	{
		cin.getline(readLine, 1000);
		p = strtok(readLine, delim);
		while (p)
		{
			request[i].push_back(atoi(p));
			p = strtok(NULL, delim);
		}
	}
}
//打印二维数组
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
void coutData(vector<int> &v)
{
	if (v.empty())
		cout << "vector is empty!" << endl;
	vector<int>::iterator iter;
	for (iter = v.begin(); iter != v.end(); ++iter)
		cout << *iter << " ";
	cout << endl;
}
//生成网络拓扑multimap
void getGridMap()
{
	int beginNode;
	pair<int, grid> temp;
	for (int i = 1; i < MAXLINKNUM; ++i)
	{
		beginNode = gridTopo[i][0];
		grid gridTemp;
		gridTemp.startNode = beginNode;
		gridTemp.endNode = gridTopo[i][1];
		gridTemp.bandWidth = gridTopo[i][2];
		gridTemp.cost = gridTopo[i][3];
		gridTemp.useBandWidth = 0;
		temp.first = beginNode;
		temp.second = gridTemp;
		gridMap.insert(temp);


		beginNode = gridTopo[i][1];
		gridTemp.startNode = beginNode;
		gridTemp.endNode = gridTopo[i][0];
		temp.first = beginNode;
		temp.second = gridTemp;
		gridMap.insert(temp);
	}
}
//输出gridmap
void coutGridMap()
{
	iteMultimap ite1 = gridMap.begin();
	iteMultimap ite2 = gridMap.end();
	for (; ite1 != ite2; ++ite1)
	{
		cout << ite1->first << " " << ite1->second.endNode << " " << ite1->second.bandWidth
			<< " " << ite1->second.cost << endl;
	}
	cout << endl;
}
//生成邻接矩阵
void creatMetrix()
{//生成邻接矩阵，gridMap网络拓扑图，vertex为顶点数组，LINENODENUM为路口数
	int i, j, k;
	graf.edgeNum = gridMap.size();//边数
	graf.vertexNum = NODENUM;
	pair<iteMultimap, iteMultimap> p;
	//cout << graf.edgeNum << " " << graf.vertexNum << endl;
	for (i = 0; i < graf.vertexNum; i++)
	{
		graf.vexs.push_back(&vertex[i]);
		//        cout << *(graf.vexs.back()) << " ";
	}
	for (i = 0; i < graf.vertexNum; i++)//初始化邻接矩阵
	{
		//cout << "初始化邻接矩阵" << endl;
		vector<grid> temp(graf.vertexNum);
		for (j = 0; j < graf.vertexNum; j++)
		{
			temp[j].cost = FINITY;
			temp[j].useBandWidth = 0;
		}
		graf.matrix.push_back(temp);
	}
	//cout << "邻接矩阵赋值" << endl;
	iteMultimap ite1 = gridMap.begin();
	iteMultimap ite2 = gridMap.end();
	int node1, node2;
	for (; ite1 != ite2; ++ite1)
	{
		node1 = ite1->second.startNode;
		node2 = ite1->second.endNode;
		graf.matrix[node1][node2] = ite1->second;
		//cout << ite1->second.startNode << " " << ite1->second.endNode << " " << node1 << " " << node2 << " "
		//	<< graf.matrix[node1][node2].cost << endl;
	}
}
//void coutAdjMatrix()
//{
//	int i, j;
//	for (i = 0; i < graf.matrix.size(); ++i)
//	{
//		for (j = 0; j < graf.matrix[i].size(); ++j)
//		{
//			cout << graf.matrix[i][j].cost << " ";
//		}
//		cout << endl;
//	}
//	cout << endl;
//}

vector<int> shortPathDijkstra(AdjMatrix &g, int &start, int &end)
{//vertIndex存放路径顶点下标
	//distance存放路径最短长度
	int v, w, k, minValue;
	k = -1;
	vector<int> vertIndex(g.vertexNum, -1);//顶点坐标全部初始化为-1
	vector<int> distance;//路径长度全部初始化为无穷大
	vector<int> final(g.vertexNum, 0);//是最短的记为1，不是最短记为0
	vector<int> pathPlan;

	//cout << " shortPathDijkstra start " << start << " " << end << " " << distance.size();
	//pair<iteMultimap, iteMultimap> p = g.matrix.equal_range(start);
	//while (p.first != p.second)//将于起始点start相连的顶点的长度加入到
	//{
	//	distance[p.first->second.endNode] = (p.first->second.cost);

	//	//cout << distance[p.first->second.endNode] << " ";
	//	++p.first;
	//}
	//cout << " shortPathDijkstra 1 " << distance.size();// [start] << " " << final[start];
	for (v = 0; v < g.vertexNum; v++)
	{
		distance.push_back(g.matrix[start][v].cost);
	}
	distance[start] = 0;
	final[start] = 1;
	//cout << " shortPathDijkstra 2 ";
	for (v = 1; v < g.vertexNum; v++)
	{
		//cout << " shortPathDijkstra 3 " << v << " ";
		minValue = FINITY;
		for (w = 0; w < g.vertexNum; w++)
		{
			if (!final[w] && distance[w] < minValue)
			{
				k = w;
				minValue = distance[w];
			}
		}
		/*if (k == -1)
		return;*/
		final[k] = 1;
		for (w = 0; w < g.vertexNum; w++)
		{
			if (!final[w] && (minValue + g.matrix[k][w].cost) < distance[w])
			{
				distance[w] = minValue + g.matrix[k][w].cost;
				vertIndex[w] = k;
			}
		}
		//for (w = 0; w < g.vertexNum; w++)
		//{
		//	p = g.matrix.equal_range(k);
		//	while (p.first != p.second)
		//	{
		//		if (p.first->second.endNode == w)
		//		{
		//			if (!final[w] && (minValue + p.first->second.cost) < distance[w])
		//			{
		//				distance[w] = minValue + p.first->second.cost;
		//				vertIndex[w] = k;
		//			}
		//			break;
		//		}
		//		//cout << distance[p.first->second.endNode] << " ";
		//		++p.first;
		//	}

		//}
	}
	v = end;
	if (*(g.vexs[v]) != *(g.vexs[start]))
	{
		//            cout << "pathpaln1" << endl;
		k = v;
		if (distance[v] == FINITY)
		{
			pathPlan.push_back(*(g.vexs[start]));
			pathPlan.push_back(*(g.vexs[v]));
			pathPlan.push_back(-1);
			//continue;
		}
		pathPlan.push_back(*(g.vexs[v]));
		while (vertIndex[k] != -1)
		{
			//                cout << "pathpaln2" << endl;
			k = vertIndex[k];
			pathPlan.push_back(*(g.vexs[k]));
		}
		pathPlan.push_back(*(g.vexs[start]));
		reverse(pathPlan.begin(), pathPlan.end());
	}
	//coutData(pathPlan);
	return pathPlan;
}
void coutVector(vector<vector<int> > a)
{
	int lineNum = a.size();
	//    cout << rowNum << " " << lineNum << endl;
	for (int i = 0; i< lineNum; i++)
	{
		int rowNum = a[i].size();
		for (int j = 0; j < rowNum; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
}
//检查带宽是否溢出
bool bandwidthFull(vector<int> &path, int &bandW)
{
	//cout << "bandwidthFull strat" << endl;
	int i, j;
	int pathSize = path.size() - 1;
	pair<iteMultimap, iteMultimap> p;
	grid node;
	bool full = 0;
	int startNode, endNode;
	for (i = 0; i < pathSize; ++i)
	{
		//cout << i << " ";
		startNode = path[i];
		endNode = path[i + 1];
		//node = graf.matrix[startNode][endNode];
		if (graf.matrix[startNode][endNode].useBandWidth + bandW >= 0.8 * graf.matrix[startNode][endNode].bandWidth)
		{
			graf.matrix[startNode][endNode].cost = FINITY;
			full = 1;
		}
		/*while (p.first != p.second)
		{
			cout << i << " ";
			if (p.first->second.endNode == endNode)
			{
				if (p.first->second.useBandWidth + bandW > 0.8 * p.first->second.bandWidth)
				{
					p.first->second.cost = FINITY;
					full = 1;
				}

				break;
			}
		}*/
	}
	return full;
}
//将任务带宽加入useBandWidth中
void addBandwidth(vector<int> &path, int &bandW)
{
	int i, j;
	int pathSize = path.size() - 1;
	//pair<iteMultimap, iteMultimap> p;
	int startNode, endNode;
	for (i = 0; i < pathSize; ++i)
	{
		startNode = path[i];
		endNode = path[i + 1];
		//p = gridMap.equal_range(startNode);
		graf.matrix[startNode][endNode].useBandWidth += bandW;
		/*while (p.first != p.second)
		{
			if (p.first->second.endNode == endNode)
			{
				p.first->second.useBandWidth += bandW;
			}
		}*/
	}
}
//生成路径
void getResult()
{

	int i, j;
	int start, end, bandw;
	int num = 0;
	bool flag = 1;
	vector<int> pathPlan;
	result.push_back({ 0 });//总成本先置为0
	for (i = 1; i < MAXREQUESTNUM; i += 4)
	{
		//cout << i << " ";
		result.push_back(request[i]);
		bandw = request[i][1];
		start = request[i + 1][0];
		num = request[i + 1].size() - 1;
		end = request[i + 1][num];
		//cout << bandw << " " << start << " " << end << " ";
		pathPlan = shortPathDijkstra(graf, start, end);
		while (bandwidthFull(pathPlan, bandw))
		{
			//flag = bandwidthFull(pathPlan, bandw);
			pathPlan.clear();
			pathPlan = shortPathDijkstra(graf, start, end);
		}
		addBandwidth(pathPlan, bandw);
		//cout << " shortPathDijkstra " << endl;
		result.push_back(pathPlan);
		pathPlan.clear();
		//cout << i << " " << endl;
	}
}
//根据路径计算成本
int getTotalCost()
{
	int totalCost = 0;
	pair<iteMultimap, iteMultimap> p;
	int resultSize = result.size();
	int requstBandwidth = 0;
	int singelCost;
	for (int j = 2; j < resultSize; j += 2)
	{
		singelCost = 0;
		requstBandwidth = result[j - 1][1];//请求带宽
		int length = result[j].size() - 1;
		for (int m = 0; m < length; ++m)//匹配路径，计算成本
		{
			int node1 = result[j][m];
			int node2 = result[j][m + 1];
			p = gridMap.equal_range(node1);//从gridMap中匹配相关结点、路径
			while (p.first != p.second)
			{
				if (p.first->second.endNode == node2)
				{
					//cout << node1 << " " << node2 << " " << p.first->second.cost << " ";
					singelCost += (p.first->second.cost);
					break;
				}
				++p.first;
			}
		}
		totalCost += (singelCost*requstBandwidth);
		//cout << singelCost << " " << totalCost << endl;
		//cout << requstBandwidth << endl;
		//cout << singelCost << endl;
	}
	result[0][0] = totalCost;
	return totalCost;

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
void writeToTxt(multimap<int, grid> gridMap, string filePath)
{
	ofstream outf;
	outf.open(filePath);
	if (!outf.is_open())
		cout << "Can't write to this file in the path : " << filePath << endl;
	pair<iteMultimap, iteMultimap> p;
	iteMultimap ite1 = gridMap.begin();
	iteMultimap ite2 = gridMap.end();
	int node;
	for (; ite1 != ite2; ++ite1)
	{
		outf << ite1->first << " " << ite1->second.startNode << " " << ite1->second.endNode << " "
			<< ite1->second.bandWidth << " " << ite1->second.cost << " "
			<< ite1->second.useBandWidth << endl;
	}
	outf.close();
}
int main()
{
	clearVec();
	//1.输入
	readTxt();

	//2.write your code
	getGridMap();
	//coutGridMap();
	//writeToTxt(gridMap, "../gridmap.txt");
	getVertex();
	creatMetrix();
	getResult();
	getTotalCost();
	//vector<int> pathPlan;
	//pathPlan = shortPathDijkstra(graf, 0, 342);
	//coutData(pathPlan);
	//coutAdjMatrix();
	//writeToTxt(result, "../result.txt");
	coutData(result);
	return 0;
}