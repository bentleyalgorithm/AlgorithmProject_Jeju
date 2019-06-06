#include <iostream>
#include <climits>
#include <vector>
#include <stdio.h>
#include "main.cpp"

//using namespace std;
//int N = spotNum;	//spot number
//int E;	//edge number
//void routeCom(int a, int b, double cost);
//
//
//typedef struct point {
//	double x, y;
//	char c;
//};
//
//typedef struct edge {
//	int v1, v2;
//};
//
//
//
//
//typedef vector<vector<double>> graph;	//각 노드 간의 간선들의 무게를 저장한 graph
//vector<edge> adj_edge;			//노드를 연결한 간선들의 집합
//
//vector<vector<int>> path;	//경로 출력을 위한 이차원 벡터
//
//int* parent = new int[N];
//double** route = new double* [N];
//
//
////kruska algorithm
//void kruskal(graph g, int N) {
//
//	for (int i = 0; i < N; i++)
//	{
//		route[i] = new double[N];
//		memset(route[i], 0, sizeof(double) * N);
//	}
//
//	double mincost = 0;	//최종 경로의 비용
//
//	for (int i = 0; i < N; i++) {
//		parent[i] = i;
//	}
//
//	int edge_count = 0;
//	while (edge_count < N - 1)
//	{
//		int min = INT_MAX, a = -1, b = -1;
//		for (int i = 0; i < N; i++) {
//			for (int j = i; j < N; j++) {
//				if (find(i) != find(j) && g[i][j] < min) {
//					min = g[i][j];
//					a = i;
//					b = j;
//				}
//			}
//		}
//		union1(a, b);
//		routeCom(a, b, min);
//		printf("Edge %d:(%d, %d) cost:%d \n",
//			edge_count++, a, b, min);
//		mincost += min;
//	}
//	cout << "\nMinimum cost = " << mincost << endl;
//
//	cout << endl;
//
//	//선택된 간선들의 cost + path 초기화
//	for (int i = 0; i < N; i++) {
//		vector<int> vertex;
//		for (int j = 0; j < N; j++) {
//			cout << route[i][j] << "\t";
//			//값이 있는 경우만 2차원 벡터에 넣어줌
//			if (route[i][j] != 0) {
//				vertex.push_back(j);
//			}
//		}
//		path.push_back(vertex);
//		cout << endl;
//	}
//
//	for (int i = 0; i < path.size(); i++)
//	{
//		cout << i << " - ";
//		for (int j = 0; j < path[i].size(); j++)
//		{
//			cout << path[i][j] << "\t";
//		}
//		cout << endl;
//	}
//}
//
//int find(int i)
//{
//	while (parent[i] != i)
//		i = parent[i];
//	return i;
//}
//
//void union1(int i, int j)
//{
//	int a = find(i);
//	int b = find(j);
//	parent[a] = b;
//}
//
////선택된 노드들 table 값 넣기
//void routeCom(int a, int b, double cost) {
//	route[a][b] = cost;
//	route[b][a] = cost;
//}
//

