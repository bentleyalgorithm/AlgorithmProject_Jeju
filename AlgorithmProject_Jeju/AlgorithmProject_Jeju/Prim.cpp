#include <iostream>
#include <string>
#include "init.h"
#include <algorithm>

#define MAX 100000
#define VISITED 10000

using namespace std;

/*void getPrimMST(vector<spotNode> * spots, vector<vector<double>> edgeGraph) {

	//spots �� �߿��� ����ڰ� �Է��� �������� ���� prim �˰��� ����
	//���� ��� = spots �� ù��° ��� 

	int visitedCnt = 0, lastVisited = 0;
	int nextNode;
	double totalWeight;

	vector<pair<double, int>> edgesforSort;
	vector<int> route;

	route.push_back(0);

	//��� ������ �湮�� �� ���� -> route ���� �ϼ�
	while (visitedCnt < spots->size()){
		for (int i = 0; i < spots->size(); i++) {
			if (edgeGraph[lastVisited][i] != MAX && edgeGraph[lastVisited][i] != VISITED) {
				//�ڱ� �ڽ� ��尡 �ƴϰ� �湮�ߴ� ��尡 �ƴϸ�
				//Ž���ϸ鼭 ���������� �迭�� �����Ͽ�
				edgesforSort.push_back(pair<double, int>(edgeGraph[lastVisited][i], i));
			}
		}

		//�ϼ��� edgesforSort�� �̿��ؼ� �ּҰ��� ��� ���ϱ� 
		sort(edgesforSort.begin(), edgesforSort.end());

		//�����Ŀ� edgesforSort�� ù��° ���� �ι�° int ���� ���� ���
		//�湮�� ��忡 �ش��ϴ� ���� �湮ǥ�� 
		nextNode = edgesforSort.at(0).second;
		edgeGraph[lastVisited][nextNode] = VISITED;
		edgeGraph[nextNode][lastVisited] = VISITED;

		//��ο� ��� �߰� 
		route.push_back(nextNode);
		visitedCnt++;
		lastVisited = nextNode;

	}

	//�ϼ��� route ���ͷ� ��� ����ϸ鼭
	cout << "route result : ";
	for (int i = 0; i < route.size()-1; i++) {
		//route �� ����Ǿ� �ִ� spot idx �� �ش��ϴ� spots���� ��Ҹ� ���
		cout << spots->at(route.at(i)).getSpotname()<<" -> ";

		//route �� ����Ǿ� �ִ� spot idx ���� spot idx ������ edge �� ���ϱ�
		totalWeight += edgeGraph[route.at(i)][route.at(i + 1)];
	}
	//������ ��� ���
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

	//���� �� ���� �ʿ��� edge��
	vector<vector<double>> edgeForweight(totalnodeNum, vector<double>(totalnodeNum, 0));
	for (int i = 0; i < totalnodeNum; i++) {
		for (int j = 0; j < totalnodeNum; j++) {
			edgeForweight[i][j] = edgeGraph[i][j];
		}
	}

	vector<edgeInfo> edgesforSort;
	edgeInfo * cadiEdge;
	vector<int> route;

	//spots�� 0��° ���ҿ� ���� ��带 ������ ����
	route.push_back(0);

	//�� �湮 ��� ���� ����ڰ� �Է��� ���̶� ������ ������ 
	while (visiteInreal < totalnodeNum){

		//�湮�� ��� ���鿡 ����� �������� ��� ���
		for (int i = 0; i<route.size(); i++) {
			for (int j = 0; j < totalnodeNum; j++) {
				if (edgeGraph[i][j] != MAX && edgeGraph[i][j] != VISITED) {
					//�������� ������ vector�� �־�α�
					cadiEdge = new edgeInfo(i, j, edgeGraph[i][j]);
					edgesforSort.push_back(*cadiEdge);
				}
			}
		}

		//�������� �� �����鿡�� �ּҰ� ã�Ƴ���
		int minrow, mincol;  //mincol�� ���� ã�ư� ���ο� ��� idx �� in spots����
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

		//���� �湮�� ��尡 ��¥ ���� �湮�� ����� ��
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

	cout << "�� �̵��Ÿ� = " << totalWeight << endl << endl;
	
}