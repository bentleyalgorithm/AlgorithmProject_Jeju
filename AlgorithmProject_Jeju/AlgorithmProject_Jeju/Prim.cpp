#include <iostream>
#include <vector>
#include <string>
#include "init.h"
#include <algorithm>

#define MAX 100000
#define VISITED 10000

using namespace std;

void getPrimMST(vector<spotNode> * spots, vector<vector<double>> * edgeGraph) {

	//spots 들 중에서 사용자가 입력한 시작지점 부터 prim 알고리즘 시작
	//시작 노드 = spots 의 첫번째 요소 

	int visitedCnt = 0, lastVisited = 0;
	int nextNode;
	double totalWeight;

	vector<pair<double, int>> edgesforSort;
	vector<int> route;

	route.push_back(0);

	//모든 지점을 방문할 때 까지 -> route 벡터 완성
	while (visitedCnt < spots->size()){
		for (int i = 0; i < spots->size(); i++) {
			if (edgeGraph->at[lastVisited][i] != MAX && edgeGraph->at[lastVisited][i] != VISITED) {
				//자기 자신 노드가 아니고 방문했던 노드가 아니면
				//탐색하면서 간선값들을 배열에 저장하여
				edgesforSort.push_back(pair<double, int>(edgeGraph->at[lastVisited][i], i));
			}
		}

		//완성된 edgesforSort를 이용해서 최소값인 노드 구하기 
		sort(edgesforSort.begin(), edgesforSort.end());

		//정렬후에 edgesforSort의 첫번째 원소 두번째 int 값이 다음 노드
		//방문할 노드에 해당하는 간선 방문표시 
		nextNode = edgesforSort.at(0).second;
		edgeGraph->at[lastVisited][nextNode] = VISITED;
		edgeGraph->at[nextNode][lastVisited] = VISITED;

		//경로에 노드 추가 
		route.push_back(nextNode);
		visitedCnt++;
		lastVisited = nextNode;

	}

	//완성된 route 벡터로 경로 출력하면서
	cout << "route result : ";
	for (int i = 0; i < route.size()-1; i++) {
		//route 에 저장되어 있는 spot idx 에 해당하는 spots에서 장소명 출력
		cout << spots->at(route.at(i)).getSpotname()<<" -> ";

		//route 에 저장되어 있는 spot idx 다음 spot idx 까지의 edge 값 더하기
		totalWeight += edgeGraph->at[route.at(i)][route.at(i + 1)];
	}
	//마지막 노드 출력
	cout << spots->at(route.back()).getSpotname() << endl;

}