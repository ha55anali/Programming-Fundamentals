#include <iostream>
#include <Windows.h>

#include "constants.h"
#include "init Board.h"
#include "Front End.h"

using namespace std;

int main() {
	char Board[BLenght][BLenght];

	initBoard(Board);

	bool KingMove[2] = { 0,0 };
	//first dimension is player, second is left 0   right 1
	bool RookMove[2][2] = { 0,0 };

	int EnpassantArr[BLenght * 2][2];
	for (int c = 0; c < BLenght * 2 - 1; ++c) {
		EnpassantArr[c][0] = -1;
		EnpassantArr[c][1] = -1;
	}

	MainLoop(Board,EnpassantArr,KingMove, RookMove);

	int dum;
	cin >> dum;

}