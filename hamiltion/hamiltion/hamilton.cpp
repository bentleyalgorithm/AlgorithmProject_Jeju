#include <iostream>
#include <vector>
#include <algorithm>
#include "hamilton.h"
using namespace std;

PathCost ps;

void printAllHamiltonianPaths(Graph const& g, int v, vector<bool> visited, vector<int>& path, int N)
{
	//모든 vertices 방문한다면, 해밀턴 경로 존재한다.
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

	//정점에서 시작하는 모든 에지가 솔루션으로 연결되는 여부 확인하기
	// Check if every edge starting from vertex v leads
	// to a solution or not
	for (int w : g.adjList[v])
	{
		// process only unvisited vertices as Hamiltonian
		// path visits each vertex exactly once
		// 해밀턴 경로가 각 정점을 정확히 한 번 방문할 때 방문되지 않은 정점만 처리
		if (!visited[w])
		{
			visited[w] = true;
			path.push_back(w);

			//경로에 정점 w를 추가하면 해결책이 나올지 여부를 검사한다.
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
	//edgeGraph받아와서 edges에 넣기
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

	// starting node = 그래프 만들때 시작 노드를 0으로 보내버림
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

	//모든 경로 출력
	//for (int i = 0; i < ps.size(); i++)
	//{
	//	for (int j = 0; j < N; j++)
	//	{
	//		//cout << ps[i][j] << " ";
	//	}
	//	cout << endl;
	//}

	//모든 경로에 대한 cost계산
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

	//cost 출력
	vector<pair<double, int>>::iterator iter;
	/*for (iter = cost.begin(); iter != cost.end(); iter++)
	{
		cout << iter->first << " " << iter->second << endl;
	}*/

	//cost sort
	sort(cost.begin(), cost.end());
	iter = cost.begin();
	cout <<"총" << ps.size()<<"개의 경로 중 mincost of Hamilton Algorithm : "<< iter->first << endl;
	
	int idx = iter->second;
	cout << "path : ";
	for (int  i = 0; i < N-1; i++)
	{
		cout << spotName[ps[idx][i]] << " -> ";
	}
	cout << spotName[ps[idx][N-1]]<< endl;
}