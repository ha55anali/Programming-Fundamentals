#pragma once
#include <iostream>
#include <algorithm>
using namespace std;

#pragma region "Misc Functions"

//checks if value is found in int array
bool ArrSearch(int * Arr, int key) {
	for (int c = 0; Arr[c] != -1; ++c) {
		if (Arr[c] == key) {
			return 1;
		}
	}
	return 0;
}

//Copies values of one pointer array to another
void CopyDoublePointerArr(int ** CopyTo,int ** CopyFrom,int CopyTill){
	for (int c = 0; c < CopyTill; ++c) {
		CopyTo[c] = CopyFrom[c];
	}
}

//copies one array to another
void CopyArr(int * CopyTo, int * CopyFrom) {
	int c = 0;
	for (; CopyFrom[c] != -1; ++c) {
		CopyTo[c] = CopyFrom[c];
	}
	CopyTo[c] = -1;
}

#pragma endregion "Misc Functions"

//checks if structure is consistent
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

#pragma region "Add Friend"

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
			cout << endl << "Friendship exists" << endl;
		}
		else {
			//function increases array size of UserA and stores in it UserB
			AddFriendToUser(Spine, UserNum, UserA, UserB);
			//function increases array size of UserB and stores in it UserA
			AddFriendToUser(Spine, UserNum, UserB, UserA);
		}
}

#pragma endregion "Add Friend"

#pragma region "Remove Friend"

//locates where in the array a friend is stored
int LocateUser(int * FriendList, int Friend) {
	for (int c = 0; FriendList[c] != -1; ++c) {
		if (FriendList[c] == Friend) {
			return c;
		}
	}
}

void RemoveFriendFromUser(int **Spine, int UserNum, int User, int Friend) {
	int FriendNum = 0;
	for (int c = 0; Spine[User][c] != -1; ++c) {
		++FriendNum;
	}

	int FriendLocation = LocateUser(Spine[User], Friend);

	//overwrite the user to be deleted and shift back the friends
	int c = FriendLocation + 1;
	for (; Spine[User][c] != -1; ++c) {
		Spine[User][c - 1] = Spine[User][c];
	}
	Spine[User][c - 1] = -1;

	//create a new array and copy over the information from the old one
	int * NewUserArr = new int[FriendNum];
	--FriendNum;
	CopyArr(NewUserArr, Spine[User]);

	delete[] Spine[User];
	Spine[User] = NewUserArr;
}

void RemoveFriend(int **Spine, int UserNum, int UserA, int UserB) {
		if (ArrSearch(Spine[UserB], UserA) == 1) {
			RemoveFriendFromUser(Spine, UserNum, UserA, UserB);
			RemoveFriendFromUser(Spine, UserNum, UserB, UserA);
		}
		else {
			cout << "Users are already not friends";
		}
}

#pragma endregion "Remove Friend"

void RemoveUser(int **Spine,int &UserNum,int User) {
	//remove user from Friends
	for (int c = 0; c < UserNum; ++c) {
		for (int x = 0; Spine[c][x] != -1; ++x) {
			if (Spine[c][x] == User) {
				RemoveFriend(Spine, UserNum, User, c);
			}
		}
	}

	//deletes user Array
	delete[] Spine[User];

	//shifts users backwards and overwrites user
	for (int c = User + 1; c < UserNum; ++c) {
		Spine[c - 1] = Spine[c];
	}
	--UserNum;

	//Decrement Friendlists of moved user
	for (int c = 0; c < UserNum; ++c) {
		for (int x = 0; Spine[c][x] != -1; ++x) {
			if (Spine[c][x] > User) {
				--Spine[c][x];
			}
		}
	}
}

void deleteStruct(int ** &Spine,int UserNum) {
	//deallocates all pointers in the pointer array
	for (int c = 0; c < UserNum; ++c) {
		delete[] Spine[c];
	}

	//deallocates the pointer array
	delete[] Spine;
	Spine = nullptr;
}
