#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <conio.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAX 10000
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define SUBMIT 5

using namespace std;

void init();
void titleDraw();
int menuDraw();
int keyControl();
void gotoxy(int, int);
void init();
void infoDraw();

//txt 파일에 저장되어 있는 장소명 / 위도 / 경도로 구성된 각 spot class
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

	init();
	while (1) {
		titleDraw();
		int menuCode = menuDraw();
		if (menuCode == 0) {
			infoDraw();

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
		else if (menuCode == 1) {
		}
		else if (menuCode == 2) {
			return 0;
		}
		system("cls");
	}

	gotoxy(34, 22);
	menuDraw();
	keyControl();

	cout << "********** HI JEJU-! **********" << endl << endl;
	cout << "Welcome to Jeju Island! Please input places where you want to go without any blank! " << endl;
	cout << "ex>제주유리의성 부지깽이 산고을 자구내포구 소인국테마파크" << endl;

}

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

int menuDraw() {
	int x = 34; //원래 24
	int y = 22; //원래 12
	gotoxy(x + 1, y);
	cout << "경로 추천";

	gotoxy(x + 1, y + 1);
	cout << "이용 방법";
	gotoxy(x - 1, y + 2);
	cout << "-----종료-----";

	while (1) {
		int n = keyControl();
		switch (n) {
		case UP: {
			if (y > 22) {
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, --y);
				cout << ">";
			}
			break;
		}
		case DOWN: {
			if (y < 24) {
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);
				cout << ">";
			}
			break;
		}
		case SUBMIT: {
			return y - 22;
		}
		}
	}
}


void titleDraw() {
	system("color 2f");
	cout << "  ▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩ " << endl;
	cout << "  ▩                                                                            ▩ " << endl;
	cout << "  ▩                                                                            ▩ " << endl;
	cout << "  ▩                                                                            ▩ " << endl;
	cout << "  ▩        ■      ■      ■■■     ■                                       ▩ " << endl;
	cout << "  ▩        ■      ■        ■       ■                                       ▩ " << endl;
	cout << "  ▩        ■      ■        ■       ■                                       ▩ " << endl;
	cout << "  ▩        ■■■■■        ■       ■                                       ▩ " << endl;
	cout << "  ▩        ■      ■        ■       ■                                       ▩ " << endl;
	cout << "  ▩        ■      ■        ■                                                ▩ " << endl;
	cout << "  ▩        ■      ■      ■■■     ■                                       ▩ " << endl;
	cout << "  ▩                                                                            ▩ " << endl;
	cout << "  ▩                                                                            ▩ " << endl;
	cout << "  ▩                  ■■■■■    ■■■■■    ■■■■■   ■      ■       ▩" << endl;
	cout << "  ▩                       ■       ■                ■       ■      ■       ▩          " << endl;
	cout << "  ▩                       ■       ■                ■       ■      ■       ▩ " << endl;
	cout << "  ▩                       ■       ■■■■■        ■       ■      ■       ▩ " << endl;
	cout << "  ▩                       ■       ■                ■       ■      ■       ▩ " << endl;
	cout << "  ▩                       ■       ■                ■       ■      ■       ▩ " << endl;
	cout << "  ▩                 ■■■■       ■■■■■  ■■■■       ■■■■■       ▩ " << endl;
	cout << "  ▩                                                                            ▩ " << endl;
	cout << "  ▩                                                                            ▩ " << endl;
	cout << "  ▩                                                                            ▩ " << endl;
	cout << "  ▩                                                                            ▩ " << endl;
	cout << "  ▩                                                                            ▩ " << endl;
	cout << "  ▩                                                                            ▩ " << endl;
	cout << "  ▩                                                                            ▩ " << endl;
	cout << "  ▩                                                                            ▩ " << endl;
	cout << "  ▩                                                                            ▩ " << endl;
	cout << "  ▩                                                                            ▩ " << endl;
	cout << "  ▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩ " << endl;
}

void infoDraw() {
	system("cls");
	cout << endl;;
	cout << "********** HI JEJU-! **********" << endl << endl;
	cout << "Welcome to Jeju Island! Please input places where you want to go without any blank! " << endl;
	cout << "ex>제주유리의성 부지깽이 산고을 자구내포구 소인국테마파크" << endl;

	/*
	while (1) {
	if (keyControl() == SUBMIT) {
	break;
	}
	}
	*/
}


int keyControl() {
	char temp = _getch();

	if (temp == 72) {
		return UP;
	}
	else if (temp == 75) {
		return LEFT;
	}
	else if (temp == 80) {
		return DOWN;
	}
	else if (temp == 77) {
		return RIGHT;
	}
	else if (temp == ' ') {
		return SUBMIT;
	}

}

void init() {
<<<<<<< HEAD
	system("mode can cols=60 lines=20 | title 占쏙옙 占쏙옙 占쏙옙 占쏙옙");
=======
	system("mode can cols=60 lines=20 | title  Welcome to Jeju!");
>>>>>>> 70ff7cec1b51ebdd2d94eaabe6fd5826da332e2a
}

void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}
