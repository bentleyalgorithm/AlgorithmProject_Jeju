#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

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

class edgeInfo {
public:
	edgeInfo(int r, int c, double value) {
		this->row = r;
		this->col = c;
		this->edgevalue = value;
	}

	int row;
	int col;
	double edgevalue;
};

typedef struct spotInfotxt {
	string spotname;
	double latitude;
	double lontitude;
}spotInfostruct;
//txt ���Ͽ� ����Ǿ� �ִ� ��Ҹ� / ���� / �浵�� ������ �� spot class