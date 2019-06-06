#pragma once
#include <iostream>
#include <vector>
using namespace std;

// data structure to store graph edges
// �׷����� ���� �����ϱ� ���� �ڷᱸ��
struct Edge {
	int src, dest;
};

typedef vector<vector<int>> PathCost;

// class to represent a graph object
class Graph
{
public:
	// An array of vectors to represent adjacency list
	// ������ ����Ʈ�� ��Ÿ���� ���� ���� �迭
	vector<vector<int>> adjList;

	// Constructor
	Graph(vector<Edge> const& edges, int N)
	{
		// resize the vector to N elements of type vector<int>
		adjList.resize(N);

		// add edges to the undirected graph
		for (unsigned i = 0; i < edges.size(); i++)
		{
			int src = edges[i].src;
			int dest = edges[i].dest;

			adjList[src].push_back(dest);
			adjList[dest].push_back(src);
		}
	}
};
void printAllHamiltonianPaths(Graph const& g, int v, vector<bool> visited, vector<int>& path, int N);
void hamilton(vector<vector<double>> edgeGraph, int N, vector<string> spotName);
