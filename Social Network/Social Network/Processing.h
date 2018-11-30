#pragma once
#include <iostream>
using namespace std;

bool ArrSearch(int * Arr, int key) {
	for (int c = 0; Arr[c] != -1; ++c) {
		if (Arr[c] == key) {
			return 1;
		}
	}
	return 0;
}

void CopyArr(int ** CopyTo,int ** CopyFrom,int CopyTill){
	for (int c = 0; c < CopyTill; ++c) {
		CopyTo[c] = CopyFrom[c];
	}
}

bool CheckConsistency(int **spine,int FriendNum) {
	for (int row = 0; row < FriendNum; ++row) {
		for (int col = 0; spine[row][col] != -1; ++col) {
			//checks if user exists
			if (spine[row][col] >= FriendNum) {
				return 0;
			}
			//checks if the friendship is mutual
			if (ArrSearch(spine[spine[row][col]], row) == 0) {
				return 0;
			}
		}
	}
	return 1;
}

void AddUser(int ** &Spine, int &FriendNum) {
	//new array with +1 lenght
	int ** NewSpine = new int *[FriendNum + 1];
	CopyArr(NewSpine,Spine,FriendNum);

	//initialize new user
	NewSpine[FriendNum] = new int[1];
	NewSpine[FriendNum][0]= - 1;

	++FriendNum;
	delete[] Spine;
	Spine = NewSpine;
}