#pragma once
#include <iostream>
#include "Write to File.h"
using namespace std;

void PrintStruct(int ** spine, int UserNum) {
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

#define InputLenght 1000
int InputNumber() {
	bool number=1 ;

	char buff[InputLenght];
	cin >> buff;

	for (int c = 0; buff[c] != '\0'; ++c) {
		if (!(buff[c] >= '0'&& buff[c] <= '9')) number = 0;
	}

	while (number == 0) {
		number = 1;
		cout << "Enter a number: ";
		cin >> buff;

		for (int c = 0; buff[c] != '\0'; ++c) {
			if (!(buff[c] >= '0'&& buff[c] <= '9')) number = 0;
		}
	}

	return atoi(buff);
}
#undef InputLenght

int InputUser(int UserNum) {
	cout << "Enter user: ";
	int User;
	User= InputNumber();
	while (!(User >= 0 && User < UserNum)) {
		cout << "Invalid. Enter Again: ";
		User = InputNumber();
	}
	return User;
}

int InputUser(int UserNum, int ExcludeUser) {
	cout << "Enter Second User: ";
	int User;
	User = InputNumber();
	while (!(User >= 0 && User < UserNum && User != ExcludeUser)) {
		cout << "Invalid. Enter Again: ";
		User = InputNumber();
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
	cout << "9: View Friend suggestions" << endl;
	cout << "10: Check Consistency " << endl << endl;

	cout << "11: Save to File" << endl;
	cout << "12: Exit" << endl << endl;

	cout << "Enter your pick: ";
}

void frontEnd(int ** &spine, int UserNum) {
	const int OptionCount = 12;
	int dummy;

	PrintmainScreen(UserNum);
	int choice;
	choice = InputNumber();

	while (!(choice > 0 && choice < OptionCount + 1)) {
		cout << "invalid options. Enter choice again: ";
		choice = InputNumber();
	}

	while (choice != OptionCount) {

		int UserA;
		int UserB;
		int User;

		switch (choice)
		{
		case 1: PrintStruct(spine, UserNum); break;

		case 2: AddUser(spine, UserNum);
			cout << "Friend is added" << endl;
			break;

		case 3:
			User = InputUser(UserNum);
			RemoveUser(spine, UserNum, User);
			break;

		case 4:
			cout << "Enter two users: " << endl;
			UserA = InputUser(UserNum);
			UserB = InputUser(UserNum, UserA);
			AddFriend(spine, UserNum, UserA, UserB);
			break;

		case 5:
			cout << "Enter two users: " << endl;
			UserA = InputUser(UserNum);
			UserB = InputUser(UserNum, UserA);
			RemoveFriend(spine, UserNum, UserA, UserB);
			break;

		case 6:
			cout << "Enter two users: " << endl;
			UserA = InputUser(UserNum);
			UserB = InputUser(UserNum, UserA);
			MergeProfiles(spine, UserNum, UserA, UserB);
			break;

		case 7:
			cout << "Enter two users: " << endl;
			UserA = InputUser(UserNum);
			UserB = InputUser(UserNum, UserA);
			PrintMutualFriends(spine, UserNum, UserA, UserB);
			break;

		case 8:
			cout << "Enter two users: " << endl;
			User = InputUser(UserNum);
			PrintFriendsOfFriends(spine, UserNum, User);
			break;

		case 9:
			User = InputUser(UserNum);
			FriendSuggestions(spine, UserNum, User);
			break;

		case 10:
			if (CheckConsistency(spine, UserNum) == 1) {
				cout << "Strcuture is consistent" << endl;
			}
			else {
				cout << "Structure is not consistent" << endl;
			}
			break;

		case 11:
			SaveToFile(spine, UserNum);
			break;

		case 12:
			deleteStruct(spine, UserNum);
			break;
		}

		cout << "Press any key to continue ";
		cin.get();
		cin.ignore();
		system("CLS");


		PrintmainScreen(UserNum);
		cin >> choice;

		while (!(choice > 0 && choice < OptionCount + 1)) {
			cout << "invalid options. Enter choice again: ";
			choice = InputNumber();
		}

	}
}