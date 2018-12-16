#pragma once

#include "constants.h"
#include "General Functions.h"
#include "Pieces.h"

bool MovePiece(char Board[][BoardLenght], char Piece, int Cord[], int EndCord[], int EnpassantArr[][2], bool Player) {
	switch (Piece)
	{
	case 'p':return MovePawn(Board, Cord, EndCord, EnpassantArr, Player); break;

	case 'P':return MovePawn(Board, Cord, EndCord, EnpassantArr, Player); break;

	case 'r':return MoveRook(Board, Cord, EndCord, Player); break;

	case 'R':return MoveRook(Board, Cord, EndCord, Player); break;

	case 'b':return MoveBishop(Board, Cord, EndCord, Player); break;

	case 'B':return MoveBishop(Board, Cord, EndCord, Player); break;

	case 'n':return MoveKnight(Board, Cord, EndCord, Player); break;

	case 'N':return MoveKnight(Board, Cord, EndCord, Player); break;

	case 'q':return MoveQueen(Board, Cord, EndCord, Player); break;

	case 'Q':return MoveQueen(Board, Cord, EndCord, Player); break;

	default:
		return 0;
		break;
	}
}

//return all possible moves of the passed piece
int ** ReturnMovesOfPiece(char Board[][BoardLenght], char Piece, int Cord[], int EnpassantArr[][2], bool Player) {
	int PlayerModifier = !Player * ('a' - 'A');

	if (Piece == 'p' - PlayerModifier) {
		return PawnMoves(Board, Cord, EnpassantArr, Player);
	}
	else if (Piece == 'r' - PlayerModifier) {
		return RookMoves(Board, Cord, Player);
	}
	else if (Piece == 'n' - PlayerModifier) {
		return KnightMoves(Board, Cord, Player);
	}
	else if (Piece == 'b' - PlayerModifier) {
		return BishopMoves(Board, Cord, Player);
	}
	else if (Piece == 'q' - PlayerModifier) {
		return QueenMoves(Board, Cord, Player);
	}
	else {
		return nullptr;
	}
}

//returns KingAttack Array. Array with all the possible attacks of the opponent team
int ** FindCheckedBy(char Board[][BoardLenght], int EnpassantArr[][2], int Player) {

	int ** KingAttack = CreateArrMoves();
	int ** PieceMoves = nullptr;
	int *KingCord = FindKingCord(Board, Player);
	int TempCord[2];
	char Piece;

	for (int row = 0; row < BoardLenght; ++row) {

		for (int col = 0; col < BoardLenght; ++col) {

			TempCord[0] = row;
			TempCord[1] = col;
			Piece = Board[row][col];

			PieceMoves= ReturnMovesOfPiece(Board, Piece, TempCord, EnpassantArr, !Player);

			if (PieceMoves != nullptr) {
				CombineArr(KingAttack, PieceMoves, Piece);

				DeleteMovesArr(PieceMoves);
			}
		}
	}

	delete[] KingCord;

	return KingAttack;
}

bool Check(char Board[][BoardLenght], int EnpassantArr[][2], int Player) {

	bool Check;
	int ** KingAttack = FindCheckedBy(Board, EnpassantArr, Player);

	int * KingPos = FindKingCord(Board, Player);

	if (KingAttack[KingPos[0]][KingPos[1]] == 1) {
		Check = 1;
	}
	else {
		Check = 0;
	}

	DeleteMovesArr(KingAttack);
	delete[] KingPos;

	return Check;
}

bool isCheckRemoved(char Board[][BoardLenght],int Start[],int End[],int EnpassantArr[][2],int Player) {

	//create copies of variables
	char BoardCopy[BoardLenght][BoardLenght];
	int EnpassantCopy[2 * BoardLenght][2];

	ArrCopy(Board, BoardCopy);
	CopyEnpassant(EnpassantArr, EnpassantCopy);

	char Piece = Board[Start[0]][Start[1]];

	MovePiece(BoardCopy, Piece, Start, End, EnpassantCopy, Player);

	if (Check(BoardCopy, EnpassantCopy, Player) == 0) {

		ArrCopy(BoardCopy, Board);
		CopyEnpassant(EnpassantCopy, EnpassantArr);

		return 1;
	}

	return 0;
}

