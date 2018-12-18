#pragma once

#include "constants.h"
#include "General Functions.h"
#include "Pieces.h"
#include "MovePiece.h"


//return all possible moves of the passed piece
int ** ReturnMovesOfPiece(char Board[][BLenght], char Piece, int Cord[], bool Player, IncludeSpecialArr) {
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
	else if (Piece == 'k' - PlayerModifier) {
		return KingMoves(Board, Cord, Player,PassSpecialArr);
	}
	else {
		return nullptr;
	}
}

//returns KingAttack Array. Array with all the possible attacks of the opponent team
int ** FindCheckedBy(char Board[][BLenght], int Player, IncludeSpecialArr) {

	int ** KingAttack = CreateArrMoves();
	int ** PieceMoves = nullptr;
	int *KingCord = FindKingCord(Board, Player);
	int TempCord[2];
	char Piece;

	for (int row = 0; row < BLenght; ++row) {

		for (int col = 0; col < BLenght; ++col) {

			TempCord[0] = row;
			TempCord[1] = col;
			Piece = Board[row][col];

			PieceMoves= ReturnMovesOfPiece(Board, Piece, TempCord, !Player,PassSpecialArr);

			if (PieceMoves != nullptr) {
				CombineArr(KingAttack, PieceMoves, Piece);

				DeleteMovesArr(PieceMoves);
			}
		}
	}

	delete[] KingCord;

	return KingAttack;
}

bool Check(char Board[][BLenght] ,int Player,IncludeSpecialArr) {

	bool Check;
	int ** KingAttack = FindCheckedBy(Board, Player,PassSpecialArr);

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

bool isCheckRemoved(char Board[][BLenght],int Start[],int End[],int Player,IncludeSpecialArr) {

	//create copies of variables
	char BoardCopy[BLenght][BLenght];
	int EnpassantCopy[2 * BLenght][2];
	bool KingMoveCopy[2];
	bool RookMoveCopy[2][2];

	ArrCopy(Board, BoardCopy);
	CopyEnpassant(EnpassantArr, EnpassantCopy);
	CopyKingMove(KingMove, KingMoveCopy);
	CopyRookMove(RookMove, RookMoveCopy);

	char Piece = Board[Start[0]][Start[1]];

	MovePiece(BoardCopy, Piece, Start, End, Player,EnpassantCopy,KingMoveCopy,RookMoveCopy);

	if (Check(BoardCopy, Player,EnpassantCopy, KingMoveCopy,RookMoveCopy) == 0) {

		ArrCopy(BoardCopy, Board);
		CopyEnpassant(EnpassantCopy, EnpassantArr);
		CopyKingMove(KingMoveCopy, KingMove);
		CopyRookMove(RookMoveCopy, RookMove);

		return 1;
	}

	return 0;
}

