#include <iostream>
#include <vector>
#include <algorithm>
#include "hamilton.h"
using namespace std;

PathCost ps;

void printAllHamiltonianPaths(Graph const& g, int v, vector<bool> visited, vector<int>& path, int N)
{
	//��� vertices �湮�Ѵٸ�, �ع��� ��� �����Ѵ�.
	// if all the vertices are visited, then
	// Hamiltonian path exists

	if (path.size() == N)
	{
		vector<int> p;
		// print Hamiltonian path
		for (int i : path) {
			//cout << i << " ";
			p.push_back(i);
		}
		ps.push_back(p);
		//cout << endl;

		return;
	}

	//�������� �����ϴ� ��� ������ �ַ������ ����Ǵ� ���� Ȯ���ϱ�
	// Check if every edge starting from vertex v leads
	// to a solution or not
	for (int w : g.adjList[v])
	{
		// process only unvisited vertices as Hamiltonian
		// path visits each vertex exactly once
		// �ع��� ��ΰ� �� ������ ��Ȯ�� �� �� �湮�� �� �湮���� ���� ������ ó��
		if (!visited[w])
		{
			visited[w] = true;
			path.push_back(w);

			//��ο� ���� w�� �߰��ϸ� �ذ�å�� ������ ���θ� �˻��Ѵ�.
			// check if adding vertex w to the path leads
			// to solution or not
			printAllHamiltonianPaths(g, w, visited, path, N);

			// Backtrack
			visited[w] = false;
			path.pop_back();
		}
	}
}

// main function
void hamilton(vector<vector<double>> edgeGraph, int N, vector<string> spotName)
{
	vector<Edge> edges;
	Edge e;
	//edgeGraph�޾ƿͼ� edges�� �ֱ�
	for (int i = 0; i < N; i++) {
		for (int j = i; j < N;j++) {
			if (edgeGraph[i][j] != INT_MAX)
			{
				e.src = i;
				e.dest = j;
				edges.push_back(e);
			}
		}
	}

	// starting node = �׷��� ���鶧 ���� ��带 0���� ��������
	int start = 0;

	// create a graph from edges
	Graph g(edges, N);

	// add starting node to the path
	vector<int> path;
	path.push_back(start);

	// mark start node as visited
	vector<bool> visited(N);
	visited[start] = true;

	printAllHamiltonianPaths(g, start, visited, path, N);

	//��� ��� ���
	//for (int i = 0; i < ps.size(); i++)
	//{
	//	for (int j = 0; j < N; j++)
	//	{
	//		//cout << ps[i][j] << " ";
	//	}
	//	cout << endl;
	//}

	//��� ��ο� ���� cost���
	vector<pair<double,int>> cost;
	for (int i = 0; i < ps.size(); i++) {
		/*vector<double> costNum;
		costNum.push_back(i);*/
		double temp = 0;
		for (int j = 0; j < N-1; j++){
			int k = j + 1;
			int a = ps[i][j];
			int b = ps[i][k];
			temp += edgeGraph[a][b];
		}
		//costNum.push_back(temp);
		cost.push_back(pair<double, int>(temp, i));
	}

	//cost ���
	vector<pair<double, int>>::iterator iter;
	/*for (iter = cost.begin(); iter != cost.end(); iter++)
	{
		cout << iter->first << " " << iter->second << endl;
	}*/

	//cost sort
	sort(cost.begin(), cost.end());
	iter = cost.begin();
	cout <<"��" << ps.size()<<"���� ��� �� mincost of Hamilton Algorithm : "<< iter->first << endl;
	
	int idx = iter->second;
	cout << "path : ";
	for (int  i = 0; i < N-1; i++)
	{
		cout << spotName[ps[idx][i]] << " -> ";
	}
	cout << spotName[ps[idx][N-1]]<< endl;
}