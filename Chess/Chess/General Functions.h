#pragma once

#include "constants.h"


//copies char array of 8x8
void ArrCopy(char CopyFrom[][BoardLenght], char  CopyTo[][BoardLenght]) {
	for (int row = 0; row < BoardLenght; ++row) {

		for (int col = 0; col < BoardLenght; ++col) {

			CopyTo[row][col] = CopyFrom[row][col];
		}
	}
}

//copies int array of 8x8
void ArrCopy(int ** CopyFrom, int CopyTo[][BoardLenght]) {
	for (int row = 0; row < BoardLenght; ++row) {

		for (int col = 0; col < BoardLenght; ++col) {

			CopyTo[row][col] = CopyFrom[row][col];
		}
	}
}

void PrintArr(int ** Arr) {

	if (Arr == nullptr) {
		cout << "Empty" << endl;
		return;
	}
	for (int row = 0; row < BoardLenght; ++row) {

		for (int col = 0; col < BoardLenght; ++col) {

			cout << Arr[row][col] << " ";
		}
		cout << endl;
	}
}

void PrintArr(int Arr[][BoardLenght]) {

	if (Arr == nullptr) {
		cout << "Empty" << endl;
		return;
	}
	for (int row = 0; row < BoardLenght; ++row) {

		for (int col = 0; col < BoardLenght; ++col) {

			cout << Arr[row][col] << " ";
		}
		cout << endl;
	}
}

//returns color of character passed
int ColorCheck(char Piece) {
	if (Piece >= 'A' && Piece <= 'Z') {
		return black;
	}
	else if(Piece >= 'a' && Piece <= 'z') {
		return white;
	}
	return -1;
}

//checks if cordinate is out of board
bool CheckCord(int cord[]) {
	if (cord[0] < 0) return 0;

	if (cord[1] < 0) return 0;

	if (cord[0] >= BoardLenght) return 0;

	if (cord[1] >= BoardLenght) return 0;

	return 1;
}


/*Creates and initializes integer 8x8 array*/
int ** CreateArrMoves() {

	//allocation
	int ** Moves = new int*[BoardLenght];
	for (int c = 0; c < BoardLenght; ++c) {
		Moves[c] = new int[BoardLenght];
	}

	//initialization
	for (int c = 0; c < BoardLenght; ++c) {
		for (int x = 0; x < BoardLenght; ++x) {
			Moves[c][x] = NotValid;
		}
	}

	return Moves;
}

//deleted passed array
void DeleteMovesArr(int ** Moves) {

	for (int c = 0; c < BoardLenght; ++c) {
		delete[] Moves[c];
	}

	delete[] Moves;

}

//combines two dynamically allocated arrays
void CombineArr(int ** CopyTo, int ** CopyFrom, char Piece) {
	if (Piece == 'p' || Piece == 'P') {
		for (int row = 0; row < BoardLenght; ++row) {
			for (int col = 0; col < BoardLenght; ++col) {

				if (CopyFrom[row][col] == 2) {

					CopyTo[row][col] = 1;
				}
			}
		}
	}
	else {
		for (int row = 0; row < BoardLenght; ++row) {
			for (int col = 0; col < BoardLenght; ++col) {
				if (CopyFrom[row][col] != 0) {

					CopyTo[row][col] = 1;
				}
			}
		}
	}
}


void CopyEnpassant(int CopyFrom[][2], int CopyTo[][2]) {
	for (int c = 0; c < BoardLenght * 2 - 1; ++c) {
		CopyTo[c][0] = CopyFrom[c][0];
		CopyTo[c][1] = CopyFrom[c][1];
	}
}

//returns cordinate of the king
int * FindKingCord(char Board[][BoardLenght], int Player) {
	int * Cord = new int[2];

	for (int row = 0; row < BoardLenght; ++row) {

		for (int col = 0; col < BoardLenght; ++col) {

			if (Board[row][col] == 'k' && Player == white) {
				Cord[0] = row;
				Cord[1] = col;
				return Cord;
			}

			if (Board[row][col] == 'K' && Player == black) {
				Cord[0] = row;
				Cord[1] = col;
				return Cord;
			}
		}
	}
}
