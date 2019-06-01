#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>

#define _CRT_SECURE_NO_WARNINGS
#define MAX 10000

using namespace std;

//txt 파일에 저장되어 있는 장소명 / 위도 / 경도로 구성된 각 sopt class
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
	cout << "ex>제주유리의성 부지깽이 산고을 자구내포구 소인국테마파크" << endl;

	//user가 입력한 string 공백으로 잘라서 spot별로 newSpot 생성해서 spots 벡터에 push
	getline(cin, spotstr);
	vector<string> spotTok = split(spotstr, ' ');

	for (unsigned int i = 0; i < spotTok.size(); i++) {
		newSpot = new spotNode(spotTok.at(i));
		spots.push_back(*newSpot);
	}

	//내장된 제주도 여행지 txt 파일 open 후
	//getline으로 한줄씩 읽어서 장소명 일치하면 위도 경도 저장하기 
	int spotNum = spots.size();

	fin.open("JejuData.txt");
	if (fin.is_open()) {
		for (unsigned int i = 0; i < spotNum; i++) {
			while (getline(fin, linefromtxt)) {
				vector<string> txtTok = split(linefromtxt, ' ');
				
				//사용자가 입력한 장소를 txt 파일에서 찾으면 위도 경도 저장
				if (txtTok.at(0) == spots.at(i).getSpotname()) {
					spots.at(i).setLatitude(atof(txtTok.at(1).c_str()));
					spots.at(i).setLongtitude(atof(txtTok.at(2).c_str()));
					break;
				}
			}
		}
	}

	//간선 그래프 생성
	vector<vector<double>> edgeGraph(spotNum, vector<double>(spotNum, 0));
	for (int i = 0; i < spotNum; i++) {
		for (int j = 0; j < spotNum; j++) {
			//동일 노드 간의 거리는 MAX로 
			if (i == j) edgeGraph[i][j] = MAX;
			else {
				//제곱거리 구하는 함수 getDistance 이용
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

