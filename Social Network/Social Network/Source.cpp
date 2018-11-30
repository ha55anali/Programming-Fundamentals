#include <iostream>

#include "ReadFromFile.h"
#include "Processing.h"

using namespace std;

void PrintStruct(int ** spine,int FriendNum) {
	if (spine == nullptr) {
		cout << "Error in opening file";
	}
	else {
		for (int c = 0; c < FriendNum; ++c) {
			cout << c << ":  ";
			if (spine[c][0] == -1) cout << -1;
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

	cout << endl <<"Check consistancy "<< CheckConsistency(spine, FriendNum)<<endl;

	AddUser(spine, FriendNum);

	PrintStruct(spine, FriendNum);
	cout << 1;

	int dum;
	cin >> dum;
}