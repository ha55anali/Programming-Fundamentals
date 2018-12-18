#pragma once
#include <iostream>

#include "constants.h"
#include "General Functions.h"
#include "Piece Movement.h"

using namespace std;


#pragma region Pawn

/*Takes cordinate as input
returns 1 if the pawn on the cordinate has moved 2 steps
returns 0 otherwise*/
bool CheckEnpassant(int Cord[], int EnpassantArr[][2]) {

	for (int c = 0; c < BLenght * 2 - 1; ++c) {

		if (Cord[0] == EnpassantArr[c][0] && Cord[1] == EnpassantArr[c][1]) {
			return 1;
		}
	}
	return 0;
}

/*Removes the pawn on cordinate from the enpassant array*/
void PromotePawn(char Board[][BLenght], int * Cord, bool Player) {
	cout << endl << "Promote Pawn" << endl;
	cout << "Press 1 for queen\nPress 2 for rook\nPress 3 for bishop\nPress 4 for knight" << endl;

	char Buff[1000];
	cin >> Buff;

	while (strlen(Buff) != 1 && !(Buff[0] > '0' && Buff[0] < '5')) {
		cout << "Wrong entry";
		cin >> Buff;
	}

	int PlayerModifier = !Player * ('a' - 'A');

	switch (Buff[0])
	{
	case '1':Board[Cord[0]][Cord[1]] = 'q' - PlayerModifier; break;

	case '2':Board[Cord[0]][Cord[1]] = 'r' - PlayerModifier; break;

	case '3':Board[Cord[0]][Cord[1]] = 'b' - PlayerModifier; break;

	case '4':Board[Cord[0]][Cord[1]] = 'n' - PlayerModifier; break;
	default:
		break;
	}
}

void RemoveEnpassant(int Cord[], int EnpassantArr[][2]) {
	for (int c = 0; c < BLenght * 2 - 1; ++c) {
		if (Cord[0] == EnpassantArr[c][0] && Cord[1] == EnpassantArr[c][1]) {
			EnpassantArr[c][0] = -1;
			EnpassantArr[c][1] = -1;
		}
	}
}

/*Takes a pawn cordinate
returns a 8x8 integer array with all the possible pawn moves*/
int ** PawnMoves(char Board[][BLenght], int Start[], int EnpassantArr[][2], bool Player) {

	int HomeRow, LastRow, Forward;

	if (Player == black) {
		HomeRow = 1;
		LastRow = BLenght - 1;
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

	//check vertical move
	Temp[0] = Start[0] + Forward;
	Temp[1] = Start[1];
	if (SquareCheck(Board, Temp, Player) == 0) {

		Moves[Temp[0]][Temp[1]] = ValidMove;

		//check enpassant
		if (Start[0] == HomeRow) {
			Temp[0] = Start[0] + Forward * 2;
			Temp[1] = Start[1];
			if (SquareCheck(Board, Temp, Player) == 0) {
				Moves[Temp[0]][Temp[1]] = Enpassant;
			}
		}
	}

	//check diagonal kills

	//check to the right
	if (Start[1] < BLenght - 2) {
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
	if (Start[1] < BLenght - 2) {
		Temp[0] = Start[0];
		Temp[1] = Start[1] + 1;

		if (SquareCheck(Board, Temp, Player) == -1 && CheckEnpassant(Temp, EnpassantArr) == 1) {
			Moves[Temp[0] + Forward][Temp[1]] = EnpassantKill;
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
bool MovePawn(char Board[][BLenght], int Start[], int End[], int EnpassantArr[][2], bool Player) {
	int ** Moves = PawnMoves(Board, Start, EnpassantArr, Player);

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


#pragma region rook

/*Takes cord as input
returns an 8x8 int array with all the possible moves for rook*/
int ** RookMoves(char Board[][BLenght], int Start[], bool Player) {

	int **Moves = CreateArrMoves();

	VerticalHorizontalMoves(Board, Moves, Start, Player);

	return Moves;
}

//Checks if move is valid for the rook
//returns 1 if valid and moves the rook
//0 if not
bool MoveRook(char Board[][BLenght], int Start[], int End[],int EnpassantArr[][2],bool RookMove[][2], bool Player) {
	bool valid = 0;

	int ** Moves = RookMoves(Board, Start, Player);

	if (Moves[End[0]][End[1]] == ValidMove || Moves[End[0]][End[1]] == Kill) {
		Board[End[0]][End[1]] = Board[Start[0]][Start[1]];
		Board[Start[0]][Start[1]] = ' ';
		valid = 1;

		if (CheckEnpassant(End, EnpassantArr) == 1) {
			RemoveEnpassant(End,EnpassantArr);
		}
	}

	if (Start[1] == 0) {
		RookMove[Player][0] = 1;
	}
	if (Start[1] == 7) {
		RookMove[Player][0] = 1;
	}

	DeleteMovesArr(Moves);

	return valid;
}

#pragma endregion rook

#pragma region Bishop

//returns a 8x8 array with all valid moves for the bishop
int ** BishopMoves(char Board[][BLenght], int Start[], bool Player) {

	int **Moves = CreateArrMoves();

	DiagonalMoves(Board, Moves, Start, Player);

	return Moves;
}

//checks if the move is valid
bool MoveBishop(char Board[][BLenght], int Start[], int End[], int EnpassantArr[][2], bool Player) {
	bool valid = 0;

	int ** Moves = BishopMoves(Board, Start, Player);

	if (Moves[End[0]][End[1]] == ValidMove) {
		Board[End[0]][End[1]] = Board[Start[0]][Start[1]];
		Board[Start[0]][Start[1]] = ' ';
		valid = 1;
	}

	if (Moves[End[0]][End[1]] == Kill) {
		Board[End[0]][End[1]] = Board[Start[0]][Start[1]];
		Board[Start[0]][Start[1]] = ' ';
		valid = 1;

		if (CheckEnpassant(End, EnpassantArr) == 1) {
			RemoveEnpassant(End,EnpassantArr);
		}
	}
	

	DeleteMovesArr(Moves);

	return valid;
}

#pragma endregion Bishop

#pragma region knight

//writes to 8x8 array all the valid moves of the knight
void KnightMoves(char Board[][BLenght], int ** Moves, int Start[], int Player) {

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

int ** KnightMoves(char Board[][BLenght], int Start[], bool Player) {

	int ** Moves = CreateArrMoves();

	KnightMoves(Board, Moves, Start, Player);

	return Moves;
}

bool MoveKnight(char Board[][BLenght], int Start[], int End[],int EnpassantArr[][2], bool Player) {
	bool valid = 0;

	int ** Moves = KnightMoves(Board, Start, Player);

	if (Moves[End[0]][End[1]] == ValidMove || Moves[End[0]][End[1]] == Kill) {
		Board[End[0]][End[1]] = Board[Start[0]][Start[1]];
		Board[Start[0]][Start[1]] = ' ';
		valid = 1;

		if (CheckEnpassant(End, EnpassantArr) == 1) {
			RemoveEnpassant(End,EnpassantArr);
		}
	}

	DeleteMovesArr(Moves);

	return valid;
}

#pragma endregion knight

#pragma region queen

int ** QueenMoves(char Board[][BLenght], int Start[], bool Player) {

	int **Moves = CreateArrMoves();

	VerticalHorizontalMoves(Board, Moves, Start, Player);

	DiagonalMoves(Board, Moves, Start, Player);

	return Moves;
}

bool MoveQueen(char Board[][BLenght], int Start[], int End[],int EnpassantArr[][2], bool Player) {
	bool valid=0;

	int ** Moves = QueenMoves(Board, Start, Player);

	if (Moves[End[0]][End[1]] == ValidMove || Moves[End[0]][End[1]] == Kill) {
		Board[End[0]][End[1]] = Board[Start[0]][Start[1]];
		Board[Start[0]][Start[1]] = ' ';
		valid = 1;

		if (CheckEnpassant(End, EnpassantArr) == 1) {
			RemoveEnpassant(End, EnpassantArr);
		}
	}

	DeleteMovesArr(Moves);

	return valid;
}

#pragma endregion queen

#pragma region King

int ** KingMoves(char Board[][BLenght], int Start[], bool Player,IncludeSpecialArr) {
	int ** Moves = CreateArrMoves();

	int TempCord[2];

	for (int c = -1; c <= 1; ++c) {

		for (int x = -1; x <= 1; ++x) {

			TempCord[0] = Start[0] + c;
			TempCord[1] = Start[1] + x;

			//ensures cord is in board
			if (CheckCord(TempCord) == 1) {

				if (SquareCheck(Board, TempCord, Player) == 0) {
					Moves[TempCord[0]][TempCord[1]] = ValidMove;
				}
				else if (SquareCheck(Board, TempCord, Player) == -1) {
					Moves[TempCord[0]][TempCord[1]] = Kill;
				}
			}

		}
	}

	//checks for castleing
	if (KingMove[Player] == 0) {

		int HomeRow;
		if (Player == white) {
			HomeRow = 7;
		}
		else HomeRow = 0;

		//checks left side
		if (RookMove[Player][0] == 0) {
			bool empty = 1;

			//check if path is empty
			for (int col = 2; col <= 3; ++col) {
				if (Board[HomeRow][col] != ' ') {
					empty = 0;
				}
			}

			if (empty == 1) {
				Moves[HomeRow][2] = Castle;
			}
		}

		//checks right side
		if (RookMove[Player][1] == 0) {
			bool empty = 1;

			//check if path is empty
			for (int col = 5; col <= 6; ++col) {
				if (Board[HomeRow][col] != ' ') {
					empty = 0;
				}
			}

			if (empty == 1) {
				Moves[HomeRow][6] = Castle;
			}
		}
	}

	return Moves;
}

bool MoveKing(char Board[][BLenght], int Start[], int End[],IncludeSpecialArr, bool Player) {
	bool valid = 0;

	int ** Moves = KingMoves(Board, Start, Player,PassSpecialArr);

	if (Moves[End[0]][End[1]] == ValidMove || Moves[End[0]][End[1]] == Kill) {
		Board[End[0]][End[1]] = Board[Start[0]][Start[1]];
		Board[Start[0]][Start[1]] = ' ';
		valid = 1;

		if (CheckEnpassant(End, EnpassantArr) == 1) {
			RemoveEnpassant(End, EnpassantArr);
		}
	}

	if (Moves[End[0]][End[1]] == Castle) {

		//move king
		Board[End[0]][End[1]] = Board[Start[0]][Start[1]];
		Board[Start[0]][Start[1]] = ' ';

		//move rook

		//check right side
		if (End[1] == 6) {
			Board[Start[0]][5] = Board[Start[0]][7];
			Board[Start[0]][7] = ' ';
		}

		//check left side
		if (End[1] == 2) {
			Board[Start[0]][3] = Board[Start[0]][0];
			Board[Start[0]][0] = ' ';
		}

		valid = 1;
	}

	KingMove[Player] = 1;

	DeleteMovesArr(Moves);

	return valid;
}
#pragma endregion King
