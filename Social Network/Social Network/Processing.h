#pragma once
#include <iostream>
#include <algorithm>
using namespace std;

bool ArrSearch(int * Arr, int key) {
	for (int c = 0; Arr[c] != -1; ++c) {
		if (Arr[c] == key) {
			return 1;
		}
	}
	return 0;
}

void CopyDoublePointerArr(int ** CopyTo,int ** CopyFrom,int CopyTill){
	for (int c = 0; c < CopyTill; ++c) {
		CopyTo[c] = CopyFrom[c];
	}
}

bool CheckConsistency(int **spine,int UserNum) {
	for (int row = 0; row < UserNum; ++row) {
		for (int col = 0; spine[row][col] != -1; ++col) {
			//checks if user exists
			if (spine[row][col] >= UserNum) {
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

void AddUser(int ** &Spine, int &UserNum) {
	//new array with +1 lenght
	int ** NewSpine = new int *[UserNum + 1];
	CopyDoublePointerArr(NewSpine,Spine,UserNum);

	//initialize new user
	NewSpine[UserNum] = new int[1];
	NewSpine[UserNum][0]= - 1;

	++UserNum;
	delete[] Spine;
	Spine = NewSpine;
}

void CopyArr(int * CopyTo, int * CopyFrom) {
	int c = 0;
	for (; CopyFrom[c] != -1;++c) {
		CopyTo[c] = CopyFrom[c];
	}
	CopyTo[c] = -1;
}

void AddFriendToUser(int **Spine, int UserNum, int User, int UserToFriend) {
	int FriendNum=0;
	//count number of friends of User
	for (int c = 0; Spine[User][c] != -1; ++c) {
		++FriendNum;
	}
	//creates a new array for user
	int * NewUserArr = new int[FriendNum + 2];
	CopyArr(NewUserArr, Spine[User]);

	delete[] Spine[User];
	Spine[User] = NewUserArr;

	Spine[User][FriendNum] = UserToFriend;
	++FriendNum;

	sort(Spine[User], Spine[User] + FriendNum);

	Spine[User][FriendNum] = -1;

}

void AddFriend(int **Spine, int UserNum, int UserA, int UserB) {
	if (ArrSearch(Spine[UserB], UserA) == 1) {
		cout << endl<<"Friendship exists"<<endl;
	}
	else {
		//function increases array size of UserA and stores in it UserB
		AddFriendToUser(Spine, UserNum, UserA, UserB);
		//function increases array size of UserB and stores in it UserA
		AddFriendToUser(Spine, UserNum, UserB, UserA);
	}
}