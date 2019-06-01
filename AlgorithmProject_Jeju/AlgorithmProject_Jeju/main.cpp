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

//txt ���Ͽ� ����Ǿ� �ִ� ��Ҹ� / ���� / �浵�� ������ �� spot class
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
	cout << "ex>���������Ǽ� �������� ����� �ڱ������� ���α��׸���ũ" << endl;

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
	int x = 34; //���� 24
	int y = 22; //���� 12
	gotoxy(x + 1, y);
	cout << "��� ��õ";

	gotoxy(x + 1, y + 1);
	cout << "�̿� ���";
	gotoxy(x - 1, y + 2);
	cout << "-----����-----";

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
	cout << "  �̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢� " << endl;
	cout << "  ��                                                                            �� " << endl;
	cout << "  ��                                                                            �� " << endl;
	cout << "  ��                                                                            �� " << endl;
	cout << "  ��        ��      ��      ����     ��                                       �� " << endl;
	cout << "  ��        ��      ��        ��       ��                                       �� " << endl;
	cout << "  ��        ��      ��        ��       ��                                       �� " << endl;
	cout << "  ��        ������        ��       ��                                       �� " << endl;
	cout << "  ��        ��      ��        ��       ��                                       �� " << endl;
	cout << "  ��        ��      ��        ��                                                �� " << endl;
	cout << "  ��        ��      ��      ����     ��                                       �� " << endl;
	cout << "  ��                                                                            �� " << endl;
	cout << "  ��                                                                            �� " << endl;
	cout << "  ��                  ������    ������    ������   ��      ��       ��" << endl;
	cout << "  ��                       ��       ��                ��       ��      ��       ��          " << endl;
	cout << "  ��                       ��       ��                ��       ��      ��       �� " << endl;
	cout << "  ��                       ��       ������        ��       ��      ��       �� " << endl;
	cout << "  ��                       ��       ��                ��       ��      ��       �� " << endl;
	cout << "  ��                       ��       ��                ��       ��      ��       �� " << endl;
	cout << "  ��                 �����       ������  �����       ������       �� " << endl;
	cout << "  ��                                                                            �� " << endl;
	cout << "  ��                                                                            �� " << endl;
	cout << "  ��                                                                            �� " << endl;
	cout << "  ��                                                                            �� " << endl;
	cout << "  ��                                                                            �� " << endl;
	cout << "  ��                                                                            �� " << endl;
	cout << "  ��                                                                            �� " << endl;
	cout << "  ��                                                                            �� " << endl;
	cout << "  ��                                                                            �� " << endl;
	cout << "  ��                                                                            �� " << endl;
	cout << "  �̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢� " << endl;
}

void infoDraw() {
	system("cls");
	cout << endl;;
	cout << "********** HI JEJU-! **********" << endl << endl;
	cout << "Welcome to Jeju Island! Please input places where you want to go without any blank! " << endl;
	cout << "ex>���������Ǽ� �������� ����� �ڱ������� ���α��׸���ũ" << endl;

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
	system("mode can cols=60 lines=20 | title �� �� �� ��");
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
