#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>

#define _CRT_SECURE_NO_WARNINGS
#define MAX 10000

using namespace std;

//txt ���Ͽ� ����Ǿ� �ִ� ��Ҹ� / ���� / �浵�� ������ �� sopt class
class spotNode {
private:
	string spotname;
	double latitude;
	double longtitude;
public:
	spotNode(string spotstr) {
		this->spotname = spotstr;
		this->latitude = this->longtitude = NULL;
	}
	void setLatitude(double lat) { this->latitude = lat; }
	void setLongtitude(double lon) { this->longtitude = lon; }
	string getSpotname() { return this->spotname; }
	double getLatitude() { return this->latitude; }
	double getLongtitude() { return this->longtitude; }
};

vector<string> split(string str, char delimiter);
double getDistance(vector<spotNode> * spots, int idx1, int idx2);

//-----------------main program-------------------
int main() {

	string spotstr;
	string linefromtxt;

	ifstream fin;

	vector<spotNode> spots;
	spotNode * newSpot;

	cout << "********** HI JEJU-! **********" << endl << endl;
	cout << "Welcome to Jeju Island! Please input places where you want to go without any blank! " << endl;
	cout << "ex>���������Ǽ� �������� ����� �ڱ������� ���α��׸���ũ" << endl;

	//user�� �Է��� string �������� �߶� spot���� newSpot �����ؼ� spots ���Ϳ� push
	getline(cin, spotstr);
	vector<string> spotTok = split(spotstr, ' ');

	for (unsigned int i = 0; i < spotTok.size(); i++) {
		newSpot = new spotNode(spotTok.at(i));
		spots.push_back(*newSpot);
	}

	//����� ���ֵ� ������ txt ���� open ��
	//getline���� ���پ� �о ��Ҹ� ��ġ�ϸ� ���� �浵 �����ϱ� 
	int spotNum = spots.size();

	fin.open("JejuData.txt");
	if (fin.is_open()) {
		for (unsigned int i = 0; i < spotNum; i++) {
			while (getline(fin, linefromtxt)) {
				vector<string> txtTok = split(linefromtxt, ' ');
				
				//����ڰ� �Է��� ��Ҹ� txt ���Ͽ��� ã���� ���� �浵 ����
				if (txtTok.at(0) == spots.at(i).getSpotname()) {
					spots.at(i).setLatitude(atof(txtTok.at(1).c_str()));
					spots.at(i).setLongtitude(atof(txtTok.at(2).c_str()));
					break;
				}
			}
		}
	}

	//���� �׷��� ����
	vector<vector<double>> edgeGraph(spotNum, vector<double>(spotNum, 0));
	for (int i = 0; i < spotNum; i++) {
		for (int j = 0; j < spotNum; j++) {
			//���� ��� ���� �Ÿ��� MAX�� 
			if (i == j) edgeGraph[i][j] = MAX;
			else {
				//�����Ÿ� ���ϴ� �Լ� getDistance �̿�
				edgeGraph[i][j] = getDistance(&spots, i, j);
			}
		}
	}

	return 0;
}

double getDistance(vector<spotNode> * spots ,int idx1, int idx2) {
	double distance = 0;
	distance += pow((spots->at(idx1).getLatitude()) - (spots->at(idx2).getLatitude()), 2);
	distance += pow((spots->at(idx1).getLongtitude()) - (spots->at(idx2).getLongtitude()), 2);
	
	return distance;
}
vector<string> split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str);
	string temp;

	while (getline(ss, temp, delimiter)) {
		internal.push_back(temp);
	}
	return internal;
}

