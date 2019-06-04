#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

//txt 파일에 저장되어 있는 장소명 / 위도 / 경도로 구성된 각 spot class
vector<string> split(string str, char delimiter);
double getDistance(vector<spotNode> * spots, int idx1, int idx2);

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


double getDistance(vector<spotNode> * spots, int idx1, int idx2) {
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
#pragma once
