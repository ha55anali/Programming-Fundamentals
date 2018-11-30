#pragma once
#include <iostream>
#include <fstream>
using namespace std;

#define FilePath "input.txt"

int * NumBuffToArr(char * LineOfText, int NumCount) {
	int *ArrOfNum = new int[NumCount + 1];
	char NumBuff[10000];
	int NumBuffCount = 0;
	int LotCount = 0;

	for (int c = 0; LineOfText[c] != '\0'; ++c) {
		if (LineOfText[c] == ',') {
			NumBuffCount = 0;
			ArrOfNum[LotCount] = atoi(NumBuff);
			++LotCount;
		}
		else {
			NumBuff[NumBuffCount] = LineOfText[c];
			NumBuff[NumBuffCount + 1] = '\0';
			++NumBuffCount;
		}
	}
	ArrOfNum[LotCount] = atoi(NumBuff);
	++LotCount;
	ArrOfNum[LotCount] = -1;
	return ArrOfNum;
}

int * CreateFriendArr(char LineOfText[]) {
	int NumCount = 0;
	for (int c = 0; LineOfText[c] != '\0'; ++c) {
		if (LineOfText[c] == ',') {
			++NumCount;
		}
	}
	++NumCount;

	return NumBuffToArr(LineOfText, NumCount);
}

int ** ReadFromFile(int &FriendNum) {
	ifstream file(FilePath);

	if (file.fail()) {
		return nullptr;
	}

	int LineCount = 0;
	char LineOfText[1000];

	while (!file.eof()) {
		file.getline(LineOfText, 1000);
		++LineCount;
	}

	file.clear();
	file.seekg(0, ios::beg);

	int **spine = new int *[LineCount];

	int count = 0;

	while (!file.eof()) {
		file.getline(LineOfText, 1000);
		spine[count] = CreateFriendArr(LineOfText);
		++count;
	}

	FriendNum = LineCount;
	return spine;
}