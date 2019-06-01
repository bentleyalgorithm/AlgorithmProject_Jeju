#include <iostream>
#include <vector>
using namespace std;

int main() {
	vector<int> test;
	for (int i = 0; i < 10; i++)
	{
		test.push_back(i);
		cout << test[i] << endl;
	}

	return 0;
}