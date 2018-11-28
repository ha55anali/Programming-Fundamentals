#include <iostream>
#include <fstream>
using namespace std;

int * CreateFriendArr(char arr[]) {
	int count = 0;
	for (int c = 0; arr[c] != '\0'; ++c) {
		if (arr[c] = ',') {
			++count;
		}
	}
	++count;
	int *temp = new int[count];

	char buffer[10000];
	int buffCount = 0;
	int arrCount = 0;

	for (int c = 0; arr[c] != '\0'; ++c) {
		if (arr[c] = ',') {
			buffCount = 0;
			temp[arrCount] = atoi(buffer);
			++arrCount;
		}
		else {
			buffer[buffCount] = arr[c];
			++buffCount;
		}
	}
	arr[arrCount] = -1;
	return temp;
}

int ** ReadFromFile(int &FriendNum) {
	ifstream file("text.txt");

	int LineCount = 0;
	char buffer[1000];

	while (!file.eof()) {
		file.getline(buffer, 1000);
		++LineCount;
	}
	file.clear();
	file.seekg(0, ios::beg);

	int **spine = new int *[LineCount];

	int count = 0;

	while (!file.eof()) {
		file.getline(buffer, 1000);
		spine[count] = CreateFriendArr(buffer);
	}
	FriendNum = LineCount;
	return spine;
}

int main() {
	int FriendNum = 0;
	int**spine = ReadFromFile(FriendNum);

	for (int c = 0; c < FriendNum; ++c) {
		for (int x = 0; x != -1; ++x) {
			cout << spine[c][x] << " ";
		}
		cout << endl;
	}

	int dum;
	cin >> dum;
}