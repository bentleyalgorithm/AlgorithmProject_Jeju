#include <iostream>
#include <string>
#include "init.h"
#include <algorithm>

#define MAX 100000
#define VISITED 10000

using namespace std;

/*void getPrimMST(vector<spotNode> * spots, vector<vector<double>> edgeGraph) {

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
			if (edgeGraph[lastVisited][i] != MAX && edgeGraph[lastVisited][i] != VISITED) {
				//자기 자신 노드가 아니고 방문했던 노드가 아니면
				//탐색하면서 간선값들을 배열에 저장하여
				edgesforSort.push_back(pair<double, int>(edgeGraph[lastVisited][i], i));
			}
		}

		//완성된 edgesforSort를 이용해서 최소값인 노드 구하기 
		sort(edgesforSort.begin(), edgesforSort.end());

		//정렬후에 edgesforSort의 첫번째 원소 두번째 int 값이 다음 노드
		//방문할 노드에 해당하는 간선 방문표시 
		nextNode = edgesforSort.at(0).second;
		edgeGraph[lastVisited][nextNode] = VISITED;
		edgeGraph[nextNode][lastVisited] = VISITED;

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
		totalWeight += edgeGraph[route.at(i)][route.at(i + 1)];
	}
	//마지막 노드 출력
	cout << spots->at(route.back()).getSpotname() << endl;

}*/

void getPrimMST(vector<spotNode> * spots, vector<vector<double>> edgeGraph) {

	int visiteInreal = 0;
	double totalWeight = 0;
	int totalnodeNum = spots->size();
	int * visitedCheck = new int[totalnodeNum];
	for (int i = 0; i < totalnodeNum; i++) {
		visitedCheck[i] = 0;
	}

	//간선 값 계산시 필요한 edge값
	vector<vector<double>> edgeForweight(totalnodeNum, vector<double>(totalnodeNum, 0));
	for (int i = 0; i < totalnodeNum; i++) {
		for (int j = 0; j < totalnodeNum; j++) {
			edgeForweight[i][j] = edgeGraph[i][j];
		}
	}

	vector<edgeInfo> edgesforSort;
	edgeInfo * cadiEdge;
	vector<int> route;

	//spots의 0번째 원소에 시작 노드를 설정된 상태
	route.push_back(0);

	//실 방문 노드 수가 사용자가 입력한 곳이랑 동일할 때까지 
	while (visiteInreal < totalnodeNum){

		//방문한 모든 노드들에 연결된 간선들을 모두 고려
		for (int i = 0; i<route.size(); i++) {
			for (int j = 0; j < totalnodeNum; j++) {
				if (edgeGraph[i][j] != MAX && edgeGraph[i][j] != VISITED) {
					//고려대상인 간선들 vector에 넣어두기
					cadiEdge = new edgeInfo(i, j, edgeGraph[i][j]);
					edgesforSort.push_back(*cadiEdge);
				}
			}
		}

		//고려대상이 된 간선들에서 최소값 찾아내기
		int minrow, mincol;  //mincol이 새로 찾아갈 새로운 노드 idx 값 in spots에서
		double minedge;

		for (int i = 1;i<edgesforSort.size();i++){
			if (edgesforSort.at(i).edgevalue < edgesforSort.at(i - 1).edgevalue) {
				minrow = edgesforSort.at(i).row;
				mincol = edgesforSort.at(i).col;
				minedge = edgesforSort.at(i).edgevalue;
			}
		}

		edgeGraph[minrow][mincol] = VISITED;
		edgeGraph[mincol][minrow] = VISITED;

		bool reallynew = true;

		//새로 방문한 노드가 진짜 새로 방문한 노드일 때
		for (int i = 0; i < route.size(); i++) {
			if (route.at(i) == mincol) {
				reallynew = false;
			}
		}
		route.push_back(mincol);

		if (reallynew) visiteInreal++;
	}

	for (int i = 0; i < route.size(); i++) {
		totalWeight += edgeForweight[route.at(i)][route.at(i + 1)];

		if (!visitedCheck[route.at(i)]) {
			cout << spots->at(route.at(i)).getSpotname();
			if (i < route.size()) cout << " -> ";
		}
	}

	cout << "총 이동거리 = " << totalWeight << endl << endl;
	
}