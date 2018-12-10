#pragma once
#include <iostream>
using namespace std;

bool CheckFriend(int *FriendList, int UserChecked) {
	for (int c = 0; FriendList[c] != -1; ++c) {
		if (FriendList[c] == UserChecked) {
			return 1;
		}
	}
	return 0;
}

int * FindMutualFriends(int ** Spine, int UserNum, int UserA, int UserB) {
	int *MutualFriends = new int[UserNum];

	//Finds Mutual Friends
	int MutualFriendCount = 0;
	for (int c = 0; Spine[UserA][c] != -1; ++c) { //traverses friends of UserA

		//linear search to locate Spine[UserA][c] in friends of UserB
		for (int x = 0; Spine[UserB][x] != -1; ++x) { //traverses friends of UserB

			if (Spine[UserA][c] == Spine[UserB][x]) {

				MutualFriends[MutualFriendCount] = Spine[UserA][c];
				++MutualFriendCount;
				break;
			}
		}
	}
	MutualFriends[MutualFriendCount] = -1;

	return MutualFriends;
}

void PrintMutualFriends(int ** Spine, int UserNum, int UserA, int UserB) {
	
	int * MutualFriends = FindMutualFriends(Spine, UserNum, UserA, UserB);

	//Prints Mutual Friends
	cout << "Mutual Friends are:" << endl;

	if (MutualFriends[0] == -1) {
		cout << "Please add more friends";
	}
	for (int c = 0; MutualFriends[c]!=-1; ++c) {

		cout << MutualFriends[c]<<" ";
	}
	cout << endl;
}

int * FindFriendsOfFriends(int ** Spine, int UserNum, int User) {
	int *FriendList = new int[UserNum];
	int UserFriendCount = 0;

	//Put friends of user into the array
	for (int c = 0; Spine[User][c] != -1; ++c) {
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
				FriendList[UserFriendCount] = -1; //make sure CheckFriend function works
			}
		}
	}

	FriendList[UserFriendCount] = -1;

	sort(FriendList, FriendList + UserFriendCount);

	return FriendList;
}

void PrintFriendsOfFriends(int ** Spine, int UserNum, int User) {
	
	int * FriendList=FindFriendsOfFriends(Spine, UserNum, User);

	//outputs array
	cout << "Friend of Friends are" << endl;
	if (FriendList[0] == -1) {
		cout << "Please add more friends";
	}

	for (int c = 0; FriendList[c]!=-1; ++c) {
		cout << FriendList[c] << " ";
	}
	cout<<endl;
}

int FindNumOfMutualFriends(int ** Spine, int UserNum, int UserA, int UserB) {
	int * MutualFriends=FindMutualFriends(Spine, UserNum, UserA, UserB);
	int MutualFriendCount = 0;

	for (int c = 0; MutualFriends[c] != -1; ++c) {
		++MutualFriendCount;
	}

	return MutualFriendCount;
}


#define NumFriendSuggestions 3
void FriendSuggestions(int ** Spine,int UserNum, int User) {
	int *NumOfMutualFriends=new int[UserNum];

	//fills array with number of mutual friends for each user
	for (int c = 0; c < UserNum; ++c) {
		NumOfMutualFriends[c] = FindNumOfMutualFriends(Spine, UserNum, User, c);
	}

	//outer loop counts the friend suggestions and stores in FriendSuggests
	int FriendSuggests[NumFriendSuggestions][2];
	for (int x = 0, LowerLimit = 0; x < NumFriendSuggestions; ++x, ++LowerLimit) {
		int MaxIndex = LowerLimit;

		//find the friend with greatest number of mutual friends
		for (int c = LowerLimit + 1; c < UserNum; ++c) {
			if (NumOfMutualFriends[c] > NumOfMutualFriends[MaxIndex]) {
				MaxIndex = c;
			}
		}

		//stores the info in a separate array
		FriendSuggests[x][0] = MaxIndex;
		FriendSuggests[x][1] = NumOfMutualFriends[MaxIndex];

		//moves the friend checked to the beginning so wont be checked again
		swap(NumOfMutualFriends[LowerLimit], NumOfMutualFriends[MaxIndex]);
	}
	
	//print the information
	cout << endl << "Suggested friends are for user " << User << " are: \n";
	
	for (int c = 0; c < NumFriendSuggestions; ++c) {
		cout << FriendSuggests[c][0] << " with " << FriendSuggests[c][1] << " friends common"<<endl;
	}

}
#undef NumFriendSuggestions

void MergeProfiles(int ** Spine, int &UserNum, int UserA, int UserB) {
	//keeps user A and deleted user B

	//checks if both Users have no friends
	if (!(Spine[UserA][0] == -1 && Spine[UserB][0] == -1)) {

		int *CombinedFriends = new int[UserNum];
		CombinedFriends[0] = -1;

		//stores friends of A in CombinedFriends
		int Count = 0;
		for (; Spine[UserA][Count] != -1; ++Count) {
			CombinedFriends[Count] = Spine[UserA][Count];
		}

		//stores friends of B in Combines Friends
		for (int x = 0; Spine[UserB][x] != -1; ++x) {
			if (CheckFriend(CombinedFriends, Spine[UserB][x]) == 0) { //eliminates duplicates
				CombinedFriends[Count] = Spine[UserB][x];
				++Count;
				CombinedFriends[Count] = -1; //ensure checkFriends work
			}
		}

		if (Count != 0) {
			sort(CombinedFriends, CombinedFriends + Count - 1);
		}

		CombinedFriends[Count] = -1; //-1 is written again if UserB has some orignal friends
		++Count;

		int * NewUserArr = new int[Count];
		CopyArr(NewUserArr, CombinedFriends);

		delete[] Spine[UserA];
		Spine[UserA] = NewUserArr;

		//Mutual Friends will have both A and B in their lists
		int * MutualFriends = FindMutualFriends(Spine, UserNum, UserA, UserB);

		//removes B from Mutual Friends
		for (int c = 0; MutualFriends[c] != -1; ++c) {
			RemoveFriendFromUser(Spine, UserNum, MutualFriends[c], UserB);
		}

		//replaces B in the structure with A
		for (int c = 0; c < UserNum; ++c) {
			for (int x = 0; Spine[c][x] != -1; ++x) {
				if (Spine[c][x] == UserB) {
					Spine[c][x] = UserA;
				}
			}
		}
	}
	RemoveUser(Spine, UserNum, UserB);
}

