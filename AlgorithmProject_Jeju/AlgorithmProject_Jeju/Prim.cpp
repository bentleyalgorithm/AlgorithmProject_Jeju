#include <iostream>
#include <vector>
#include <string>
#include "init.h"
#include <algorithm>

#define MAX 100000
#define VISITED 10000

using namespace std;

void getPrimMST(vector<spotNode> * spots, vector<vector<double>> * edgeGraph) {

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
			if (edgeGraph->at[lastVisited][i] != MAX && edgeGraph->at[lastVisited][i] != VISITED) {
				//�ڱ� �ڽ� ��尡 �ƴϰ� �湮�ߴ� ��尡 �ƴϸ�
				//Ž���ϸ鼭 ���������� �迭�� �����Ͽ�
				edgesforSort.push_back(pair<double, int>(edgeGraph->at[lastVisited][i], i));
			}
		}

		//�ϼ��� edgesforSort�� �̿��ؼ� �ּҰ��� ��� ���ϱ� 
		sort(edgesforSort.begin(), edgesforSort.end());

		//�����Ŀ� edgesforSort�� ù��° ���� �ι�° int ���� ���� ���
		//�湮�� ��忡 �ش��ϴ� ���� �湮ǥ�� 
		nextNode = edgesforSort.at(0).second;
		edgeGraph->at[lastVisited][nextNode] = VISITED;
		edgeGraph->at[nextNode][lastVisited] = VISITED;

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
		totalWeight += edgeGraph->at[route.at(i)][route.at(i + 1)];
	}
	//������ ��� ���
	cout << spots->at(route.back()).getSpotname() << endl;

}