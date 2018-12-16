#pragma once
#include <iostream>

#include "constants.h"
#include "General Functions.h"
#include "Piece Movement.h"

using namespace std;

#pragma region rook

/*Takes cord as input
returns an 8x8 int array with all the possible moves for rook*/
int ** RookMoves(char Board[][BoardLenght], int Start[], bool Player) {

	int **Moves = CreateArrMoves();

	VerticalHorizontalMoves(Board, Moves, Start, Player);

	return Moves;
}

//Checks if move is valid for the rook
//returns 1 if valid and moves the rook
//0 if not
bool MoveRook(char Board[][BoardLenght], int Start[], int End[], bool Player) {
	bool valid = 0;

	int ** Moves = RookMoves(Board, Start, Player);

	if (Moves[End[0]][End[1]] == ValidMove || Moves[End[0]][End[1]] == Kill) {
		Board[End[0]][End[1]] = Board[Start[0]][Start[1]];
		Board[Start[0]][Start[1]] = ' ';
		valid = 1;;
	}

	DeleteMovesArr(Moves);

	return valid;
}

#pragma endregion rook

#pragma region Bishop

//returns a 8x8 array with all valid moves for the bishop
int ** BishopMoves(char Board[][BoardLenght], int Start[], bool Player) {

	int **Moves = CreateArrMoves();

	DiagonalMoves(Board, Moves, Start, Player);

	return Moves;
}

//checks if the move is valid
bool MoveBishop(char Board[][BoardLenght], int Start[], int End[], bool Player) {
	bool valid = 0;

	int ** Moves = BishopMoves(Board, Start, Player);

	if (Moves[End[0]][End[1]] == ValidMove || Moves[End[0]][End[1]] == Kill) {
		Board[End[0]][End[1]] = Board[Start[0]][Start[1]];
		Board[Start[0]][Start[1]] = ' ';
		valid = 1;
	}

	DeleteMovesArr(Moves);

	return valid;
}

#pragma endregion Bishop

#pragma region knight

//writes to 8x8 array all the valid moves of the knight
void KnightMoves(char Board[][BoardLenght], int ** Moves, int Start[], int Player) {

	int Temp[2];

	for (int c = -2; c <= 2; c = c + 4) {

		for (int x = -1; x <= 1; x = x + 2) {

			Temp[0] = Start[0] + c;
			Temp[1] = Start[1] + x;

			if (CheckCord(Temp) == 1) {
				PossibleMove(Board, Moves, Temp, Player);
			}

			Temp[0] = Start[0] + x;
			Temp[1] = Start[1] + c;

			if (CheckCord(Temp) == 1) {
				PossibleMove(Board, Moves, Temp, Player);
			}

		}

	}

}

int ** KnightMoves(char Board[][BoardLenght], int Start[], bool Player) {

	int ** Moves = CreateArrMoves();

	KnightMoves(Board, Moves, Start, Player);

	return Moves;
}

bool MoveKnight(char Board[][BoardLenght], int Start[], int End[], bool Player) {
	bool valid = 0;

	int ** Moves = KnightMoves(Board, Start, Player);

	if (Moves[End[0]][End[1]] == ValidMove || Moves[End[0]][End[1]] == Kill) {
		Board[End[0]][End[1]] = Board[Start[0]][Start[1]];
		Board[Start[0]][Start[1]] = ' ';
		valid = 1;
	}

	DeleteMovesArr(Moves);

	return valid;
}

#pragma endregion knight

#pragma region queen

int ** QueenMoves(char Board[][BoardLenght], int Start[], bool Player) {

	int **Moves = CreateArrMoves();

	VerticalHorizontalMoves(Board, Moves, Start, Player);

	DiagonalMoves(Board, Moves, Start, Player);

	return Moves;
}

bool MoveQueen(char Board[][BoardLenght], int Start[], int End[], bool Player) {
	bool valid=0;

	int ** Moves = QueenMoves(Board, Start, Player);

	if (Moves[End[0]][End[1]] == ValidMove || Moves[End[0]][End[1]] == Kill) {
		Board[End[0]][End[1]] = Board[Start[0]][Start[1]];
		Board[Start[0]][Start[1]] = ' ';
		valid = 1;
	}

	DeleteMovesArr(Moves);

	return valid;
}

#pragma endregion queen

#pragma region Pawn

/*Takes cordinate as input
returns 1 if the pawn on the cordinate has moved 2 steps
returns 0 otherwise*/
bool CheckEnpassant(int Cord[], int EnpassantArr[][2]) {

	for (int c = 0; c < BoardLenght * 2 - 1; ++c) {

		if (Cord[0] == EnpassantArr[c][0] && Cord[1] == EnpassantArr[c][1]) {
			return 1;
		}
	}
	return 0;
}

/*Removes the pawn on cordinate from the enpassant array*/
void RemoveEnpassant(int Cord[], int EnpassantArr[][2]) {
	for (int c = 0; c < BoardLenght * 2 - 1; ++c) {
		if (Cord[0] == EnpassantArr[c][0] && Cord[1] == EnpassantArr[c][1]) {
			EnpassantArr[c][0] = -1;
			EnpassantArr[c][1] = -1;
		}
	}
}

/*Takes a pawn cordinate
returns a 8x8 integer array with all the possible pawn moves*/
int ** PawnMoves(char Board[][BoardLenght], int Start[], int EnpassantArr[][2], bool Player) {

	int HomeRow, LastRow, Forward;

	if (Player == black) {
		HomeRow = 1;
		LastRow = BoardLenght - 1;
		Forward = 1;
	}
	else {
		HomeRow = 6;
		LastRow = 0;
		Forward = -1;
	}

	//if pawn is at the end of the row
	if (Start[0] == LastRow)
		return nullptr;

	int ** Moves = CreateArrMoves();
	
	//stores the cordinate to check move
	int Temp[2];

	//check enpassant
	if (Start[0] == HomeRow) {
		Temp[0] = Start[0] + Forward * 2;
		Temp[1] = Start[1];
		if (SquareCheck(Board, Temp, Player) == 0) {
			Moves[Temp[0]][Temp[1]] = Enpassant;
		}
	}

	//check vertical move
	Temp[0] = Start[0] + Forward;
	Temp[1] = Start[1];
	if (SquareCheck(Board, Temp, Player) == 0) {
		Moves[Temp[0]][Temp[1]] = ValidMove;
	}

	//check diagonal kills

	//check to the right
	if (Start[1] < BoardLenght - 2) {
		Temp[0] = Start[0] + Forward;
		Temp[1] = Start[1] + 1;

		if (SquareCheck(Board, Temp, Player) == -1) {
			Moves[Temp[0]][Temp[1]] = Kill;
		}
	}

	//check to the left
	if (Start[1] > 0) {
		Temp[0] = Start[0] + Forward;
		Temp[1] = Start[1] - 1;

		if (SquareCheck(Board, Temp, Player) == -1) {
			Moves[Temp[0]][Temp[1]] = Kill;
		}
	}

	//checks enpassant kills

	//check to the right
	if (Start[1] < BoardLenght - 2) {
		Temp[0] = Start[0];
		Temp[1] = Start[1] + 1;

		if (SquareCheck(Board, Temp, Player) == -1 && CheckEnpassant(Temp, EnpassantArr) == 1) {
			Moves[Temp[0]+Forward][Temp[1]] = EnpassantKill;
		}
	}

	//check to the left
	if (Start[1] > 0) {
		Temp[0] = Start[0];
		Temp[1] = Start[1] - 1;

		if (SquareCheck(Board, Temp, Player) == -1 && CheckEnpassant(Temp, EnpassantArr) == 1) {
			Moves[Temp[0]][Temp[1]] = EnpassantKill;
		}
	}

	return Moves;
}

/*checks if the passed move is valid
returns 1 if it is
returns 0 if not*/
bool MovePawn(char Board[][BoardLenght], int Start[], int End[], int EnpassantArr[][2], bool Player) {
	int ** Moves = PawnMoves(Board, Start, EnpassantArr, Player);

	/*if (Moves == nullptr) {
		PromotePawn(){}
	}*/

	if (Moves[End[0]][End[1]] == ValidMove || Moves[End[0]][End[1]] == Kill) {
		RemoveEnpassant(Start, EnpassantArr);

		Board[End[0]][End[1]] = Board[Start[0]][Start[1]];
		Board[Start[0]][Start[1]] = ' ';
		return 1;
	}

	if (Moves[End[0]][End[1]] == Enpassant) {
		Board[End[0]][End[1]] = Board[Start[0]][Start[1]];
		Board[Start[0]][Start[1]] = ' ';

		int c = 0;
		for (; EnpassantArr[c][0] != -1; ++c);
		EnpassantArr[c][0] = End[0];
		EnpassantArr[c][1] = End[1];

		return 1;
	}

	if (Moves[End[0]][End[1]] == EnpassantKill) {
		int Temp[2] = { Start[0],End[1] };

		RemoveEnpassant(Start, EnpassantArr);
		RemoveEnpassant(Temp, EnpassantArr);

		Board[End[0]][End[1]] = Board[Start[0]][Start[1]];
		Board[Start[0]][Start[1]] = ' ';
		Board[Temp[0]][Temp[1]] = ' ';
		return 1;
	}

	return 0;
}

#pragma endregion Pawn
