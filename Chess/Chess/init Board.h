#pragma once
#include <iostream>

#include "constants.h"


using namespace std;


void initLastRow(char Board[][BLenght], bool Player) {
	int Temp;
	int row;

	if (Player == white) {
		row = 0;
		Temp = 'A' - 'a';
	}
	else {
		row = 7;
		Temp = 0;
	}

	Board[row][0] = 'r' + Temp;
	Board[row][7] = 'r' + Temp;

	Board[row][1] = 'n' + Temp;
	Board[row][6] = 'n' + Temp;

	Board[row][2] = 'b' + Temp;
	Board[row][5] = 'b' + Temp;

	Board[row][3] = 'q' + Temp;
	Board[row][4] = 'k' + Temp;
}

void initPawnRow(char Board[][BLenght], int Player) {
	int row;
	int Temp;

	if (Player == white) {
		row = 1;
		Temp = 'A' - 'a';
	}
	else {
		row = 6;
		Temp = 0;
	}

	for (int col = 0; col < BLenght; ++col) {
		Board[row][col] = 'p' + Temp;
	}
}

void initEmptySpaces(char Board[][BLenght]) {
	for (int row = 2; row < BLenght - 2; ++row) {
		for (int col = 0; col < BLenght; ++col) {
			Board[row][col] = ' ';
		}
	}
}

void initBoard(char Board[][BLenght]) {
	initLastRow(Board, white);
	initLastRow(Board, black);

	initPawnRow(Board, white);
	initPawnRow(Board, black);

	initEmptySpaces(Board);
}
