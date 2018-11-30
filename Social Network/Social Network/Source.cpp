#include <iostream>

#include "ReadFromFile.h"
#include "Processing.h"

using namespace std;

void PrintStruct(int ** spine,int UserNum) {
	if (spine == nullptr) {
		cout << "Error in opening file";
	}
	else {
		for (int c = 0; c < UserNum; ++c) {
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

	int UserNum = 0;
	int**spine = ReadFromFile(UserNum);

	PrintStruct(spine, UserNum);

	cout << endl << "Check consistancy " << CheckConsistency(spine, UserNum) << endl;

	AddUser(spine, UserNum);

	AddFriend(spine, UserNum, 3,5);

	PrintStruct(spine, UserNum);

	RemoveFriend(spine, UserNum, 3, 8);

	PrintStruct(spine, UserNum);

	cout << endl << "Check consistancy " << CheckConsistency(spine, UserNum) << endl;

	RemoveUser(spine, UserNum, 5);

	PrintStruct(spine, UserNum);

	cout << endl << "Check consistancy " << CheckConsistency(spine, UserNum) << endl;

	int dum;
	cin >> dum;
}