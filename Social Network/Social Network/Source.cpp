#include <iostream>
#include "ReadFromFile.h"
using namespace std;

void PrintStruct(int ** spine,int FriendNum) {
	if (spine == nullptr) {
		cout << "Error in opening file";
	}
	else {
		for (int c = 0; c < FriendNum; ++c) {
			for (int x = 0; spine[c][x] != -1; ++x) {
				cout << spine[c][x] << " ";
			}
			cout << endl;
		}
	}
}

int main() {

	int FriendNum = 0;
	int**spine = ReadFromFile(FriendNum);

	PrintStruct(spine, FriendNum);

	int dum;
	cin >> dum;
}