#pragma once
#include <iostream>
using namespace std;

void PrintMutualFriends(int ** Spine, int UserNum, int UserA, int UserB) {
	int *MutualFriends = new int[UserNum];

	//Finds Mutual Friends
	int MutualFriendCount = 0;
	for (int c = 0; Spine[UserA][c] != -1; ++c) {
		for (int x = 0; Spine[UserB][x] != -1; ++x) { //bin search?
			if (Spine[UserA][c] == Spine[UserB][x]) {
				MutualFriends[MutualFriendCount] = Spine[UserA][c];
				++MutualFriendCount;
				break;
			}
		}
	}

	//Prints Mutual Friends
	for (int c = 0; c < MutualFriendCount; ++c) {
		cout << MutualFriends[c]<<" ";
	}
}

bool CheckFriend(int *FriendList, int UserChecked) {
	for (int c = 0; FriendList[c] != -1; ++c) {
		if (FriendList[c] == UserChecked) {
			return 1;
		}
	}
	return 0;
}

void PrintFriendOfFriends(int ** Spine, int UserNum, int User) {
	int *FriendList = new int[UserNum];
	int UserFriendCount = 0;
	
	//Put friends of user into the array
	for (int c=0; Spine[User][c] != -1; ++c) {
		FriendList[c] = Spine[User][c];
		++UserFriendCount;
	}
	FriendList[UserFriendCount] = -1;

	//puts friends of friends of user into the array
	for (int c = 0; Spine[User][c] != -1; ++c) {
		int Friend = Spine[User][c];
		for (int x = 0; Spine[Friend][x] != -1; ++x) {
			if (CheckFriend(FriendList, Spine[Friend][x]) == 0) { //checks if friend is already added
				FriendList[UserFriendCount] = Spine[Friend][x];
				++UserFriendCount;
				FriendList[UserFriendCount] = -1;
			}
		}
	}

	sort(FriendList, FriendList + UserFriendCount);

	//outputs array
	for (int c = 0; c < UserFriendCount; ++c) {
		cout << FriendList[c] << " ";
	}
}

