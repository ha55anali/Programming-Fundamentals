#pragma once

#include <fstream>

#include "constants.h"

using namespace std;

void StringCopy(char * CopyTo, char * CopyFrom) {

	for (int c = 0; c < BLenght; ++c) {
		CopyTo[c] = CopyFrom[c];
	}

	CopyTo[BLenght] = '\0';
}

void SaveGame(char Board[][BLenght],bool Player,IncludeSpecialArr) {
	char Buff[100];
	
	ofstream file;
	file.open("save.txt");

	//saves board
	for (int row = 0; row < BLenght; ++row) {

		StringCopy(Buff, Board[row]);

		file << Buff;
	}

	//saves player turn
	file << "\n" << Player;

	//saves EnpassantArr
	int x = 0;
	for (int c = 0; c < 2 * BLenght - 1; ++c) {
		if (EnpassantArr[c][0] == -1) {
			Buff[x] = '9';
		}
		else {
			Buff[x] = EnpassantArr[c][0] + '0';
		}
		++x;
		if (EnpassantArr[c][1] == -1) {
			Buff[x] = '9';
		}
		else {
			Buff[x] = EnpassantArr[c][1] + '0';
		}
		++x;
	}
	Buff[x] = '\0';
	file << '\n' << Buff;

	//saves KingMove
	for (int c = 0; c < 2; ++c) {
		Buff[c]=KingMove[c]+ '0';
		Buff[c+1] = '\0';
	}
	file << '\n' << Buff;

	//saves RookMove
	for (int c = 0, x = 0; c < 2; ++c) {
		for (int y = 0; y < 2; ++y) {
			Buff[x]=RookMove[c][y]+ '0';
			++x;
			Buff[x] = '\0';
		}
	}
	file << '\n' << Buff;

	file.close();
}

void LoadGame(char Board[][BLenght],bool &Player, IncludeSpecialArr) {
	char Buff[100];

	ifstream file;
	file.open("save.txt");

	//read the board
	file.getline(Buff, 100);
	for (int row = 0, buffCount=0; row < BLenght; ++row) {

		for (int col = 0; col < BLenght; ++col) {

			Board[row][col] = Buff[buffCount];
			++buffCount;

		}
	}

	//load Player
	file.getline(Buff, 100);
	Player = Buff[0]-'0';

	//read EnpassantArr
	file.getline(Buff, 100);
	for (int c = 0, x = 0; c < 2 * BLenght - 1; ++c) {
		if (Buff[x] == '9') {
			EnpassantArr[c][0] = -1;
		}
		else {
			EnpassantArr[c][0] = Buff[x] - '0';
		}
		++x;
		if (Buff[x] == '9') {
			EnpassantArr[c][0] = -1;
		}
		else {
			EnpassantArr[c][1] = Buff[x] - '0';
		}
		++x;
	}

	//read KingMove
	file.getline(Buff, 100);
	for (int c = 0; c < 2; ++c) {
		KingMove[c] = Buff[c]- '0';
	}

	//read RookMove
	file.getline(Buff, 100);
	for (int c = 0,x=0; c < 2; ++c) {
		for (int y = 0; y < 2; ++y) {
			RookMove[c][y] = Buff[x]- '0';
			++x;
		}
	}
}