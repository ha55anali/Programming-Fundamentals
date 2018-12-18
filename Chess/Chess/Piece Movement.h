#pragma once

#include "constants.h"
#include "Pieces.h"


//Takes a cordinate and player color as input
//if piece on cordinate is the same color as player, 1 is returned
//if piece is a different color -1 is returned
//if cordinate is empty 0 is returned
int SquareCheck(char Board[][BLenght], int Cord[], bool Player) {
	char Piece = Board[Cord[0]][Cord[1]];

	if (Piece == ' ') {
		return 0;
	}

	if (Piece >= 'a' && Piece <= 'z') {
		if (Player == white) {
			return 1;
		}
		return -1;
	}
	else {
		if (Player == black) {
			return 1;
		}
		return -1;
	}
}

/*Takes a cordinate as input
Writes to an array moves if the move is Valid, kill or not valid
*/
bool PossibleMove(char Board[][BLenght], int ** Moves, int Temp[], int Player) {
	if (SquareCheck(Board, Temp, Player) == 0) {
		Moves[Temp[0]][Temp[1]] = ValidMove;
		return 1;
	}
	if (SquareCheck(Board, Temp, Player) == -1) {
		Moves[Temp[0]][Temp[1]] = Kill;
		return 0;
	}
	if (SquareCheck(Board, Temp, Player) == 1) {
		return 0;
	}
}

/*Takes an 8x8 array and cordinate as input
writes to array all the valid vertical and horizontal moves*/
void VerticalHorizontalMoves(char Board[][BLenght], int ** Moves, int Start[], int Player) {
	int Temp[2];

	//checks moves to the North
	Temp[1] = Start[1];
	for (int Row = Start[0] + 1; Row < BLenght; ++Row) {
		Temp[0] = Row;
		if (PossibleMove(Board, Moves, Temp, Player) == 0) {
			break;
		}
	}

	//checks moves to the South
	for (int Row = Start[0] - 1; Row >= 0; --Row) {
		Temp[0] = Row;
		if (PossibleMove(Board, Moves, Temp, Player) == 0) {
			break;
		}
	}

	//checks moves to the East
	Temp[0] = Start[0];
	for (int Col = Start[1] + 1; Col < BLenght; ++Col) {
		Temp[1] = Col;
		if (PossibleMove(Board, Moves, Temp, Player) == 0) {
			break;
		}
	}

	//checks moves to the West
	for (int Col = Start[1] - 1; Col >= 0; --Col) {
		Temp[1] = Col;
		if (PossibleMove(Board, Moves, Temp, Player) == 0) {
			break;
		}
	}

}

/*writes to array all the possible diagional moves*/
void DiagonalMoves(char Board[][BLenght], int ** Moves, int Start[], int Player) {

	//stores cord to be tested
	int Temp[2];

	//checks South East
	for (int row = Start[0] + 1, col = Start[1] + 1; row < BLenght && col < BLenght; ++row, ++col) {
		Temp[0] = row;
		Temp[1] = col;
		if (PossibleMove(Board, Moves, Temp, Player) == 0) {
			break;
		}
	}

	//checks North East
	for (int row = Start[0] - 1, col = Start[1] + 1; row >= 0 && col < BLenght; --row, ++col) {
		Temp[0] = row;
		Temp[1] = col;
		if (PossibleMove(Board, Moves, Temp, Player) == 0) {
			break;
		}
	}

	//checks North West
	for (int row = Start[0] - 1, col = Start[1] - 1; row >= 0 && col >= 0; --row, --col) {
		Temp[0] = row;
		Temp[1] = col;
		if (PossibleMove(Board, Moves, Temp, Player) == 0) {
			break;
		}
	}

	//checks South West
	for (int row = Start[0] + 1, col = Start[1] - 1; col >= 0 && row < BLenght; --col, ++row) {
		Temp[0] = row;
		Temp[1] = col;
		if (PossibleMove(Board, Moves, Temp, Player) == 0) {
			break;
		}
	}
}

