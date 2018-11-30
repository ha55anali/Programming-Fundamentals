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

bool CheckConsistency(int **spine,int FriendNum) {
	for (int row = 0; row < FriendNum; ++row) {
		for (int col = 0; spine[row][col] != -1; ++col) {

			if (spine[row][col] >= FriendNum) {
				return 0;
			}

			if (ArrSearch(spine[spine[row][col]], row) == 0) {
				return 0;
			}
		}
	}
	return 1;
}