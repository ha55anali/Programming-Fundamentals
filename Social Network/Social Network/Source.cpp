#include <iostream>

#include "ReadFromFile.h"
#include "Data Manipulation.h"
#include "Data Processing.h"

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

int InputUser(int UserNum) {
	int User;
	cin >> User;
	while (!(User <= 0 && User < UserNum)) {
		cout << "Invalid. Enter Again: ";
		cin >> User;
	}
	return User;
}

int InputUser(int UserNum,int ExcludeUser) {
	int User;
	cin >> User;
	while (!(User <= 0 && User < UserNum && User!=ExcludeUser)) {
		cout << "Invalid. Enter Again: ";
		cin >> User;
	}
	return User;
}

void PrintmainScreen(int UserNum) {
	cout << "Social Network" << endl;
	cout << UserNum << " are present" << endl;
	cout << "Operations Available" << endl << endl;
	cout << "1: Print the Friend Structure" << endl << endl;

	cout << "Data Manipulation:" << endl;
	cout << "2: Add User to the Network " << endl;
	cout << "3: Remove User from the Network " << endl;
	cout << "4: Add a friendship to the Network " << endl;
	cout << "5: Remove a friendship to the Network " << endl;
	cout << "6: Merge Profiles" << endl << endl;

	cout << "Data Analysis: " << endl;
	cout << "7: Find Mutual Friends " << endl;
	cout << "8: Find Friend of Friends" << endl;
	cout << "9: View Friend suggestions" << endl << endl;

	cout << "10: Exit" << endl << endl;

	cout << "Enter your pick: ";
}

void frontEnd(int ** spine, int UserNum) {
	PrintmainScreen(UserNum);
	int choice;
	cin >> choice;

	while (!(choice > 0 && choice < 11)) {
		cout << "invalid options. Enter choice again: ";
		cin >> choice;
	}

	while (choice != 10) {

		while (!(choice > 0 && choice < 11)) {
			cout << "invalid options. Enter choice again: ";
			cin >> choice;
		}

		switch (choice)
		{
		case 1: PrintStruct(spine, UserNum); break;

		case 2: AddUser(spine, UserNum); break;

		case 3:
			int User = InputUser(UserNum);
			RemoveUser(spine, UserNum, User);
			break;

		case 4:
			int UserA = InputUser(UserNum);
			int UserB = InputUser(UserNum, UserA);
			AddFriend(spine, UserNum, UserA, UserB);
			break;

		case 5:
			int UserA = InputUser(UserNum);
			int UserB = InputUser(UserNum, UserA);
			RemoveFriend(spine, UserNum, UserA, UserB);
			break;

		case 6:
			int UserA = InputUser(UserNum);
			int UserB = InputUser(UserNum, UserA);
			MergeProfiles(spine, UserNum, UserA, UserB);
			break;

		default:
			break;
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

	PrintFriendOfFriends(spine, UserNum, 1);

	cout << endl;

	FriendSuggestions(spine, UserNum, 1);


	MergeProfiles(spine, UserNum, 1, 2);

	PrintStruct(spine, UserNum);

	cout << endl << "Check consistancy " << CheckConsistency(spine, UserNum) << endl;

	int dum;
	cin >> dum;
}