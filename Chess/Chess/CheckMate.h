#pragma once

#include "constants.h"
#include "Check.h"
#include "Piece Movement.h"


//Simulates the movement of the passed piece. Returns 1 if check can be removed
bool CheckRemoval(char Board[][BLenght], int *Cord, char Piece, int Player,IncludeSpecialArr) {
	int EndCord[2];
	int ** PieceMoves = nullptr;

	//create copies of variables
	char BoardCopy[BLenght][BLenght];
	int EnpassantCopy[2 * BLenght][2];
	bool KingMoveCopy[2];
	bool RookMoveCopy[2][2];

	//Returns all possible moves of the piece
	PieceMoves=ReturnMovesOfPiece(Board, Piece, Cord, Player, PassSpecialArr);

	PrintArr(PieceMoves);

	if (PieceMoves == nullptr) {
		return 0;
	}

	//one by one tries all the possible moves of the piece
	for (int row = 0; row < BLenght; ++row) {

		for (int col = 0; col < BLenght; ++col) {

			if (PieceMoves[row][col] != 0) {

				ArrCopy(Board, BoardCopy);
				CopyEnpassant(EnpassantArr, EnpassantCopy);
				CopyKingMove(KingMove, KingMoveCopy);
				CopyRookMove(RookMove, RookMoveCopy);

				EndCord[0] = row;
				EndCord[1] = col;

				MovePiece(BoardCopy, Piece, Cord, EndCord, Player, EnpassantCopy,KingMoveCopy,RookMoveCopy);

				//if check is removed return 1
				if (Check(BoardCopy, Player, EnpassantCopy, KingMoveCopy, RookMoveCopy) == 0) {
					DeleteMovesArr(PieceMoves);
					return 1;
				}
			}

		}
	}
	DeleteMovesArr(PieceMoves);
	return 0;
}

//Checks if check can be removed by moving king
//checks all the moves of king
bool CheckKingMovement(char Board[][BLenght],int * KingPos,int ** KingAttack,int Player) {

	int KingMove[BLenght][BLenght];
	ArrCopy(KingAttack, KingMove);

	//prevents king from moving to same color pieces
	for (int row = 0; row < BLenght; ++row) {

		for (int col = 0; col < BLenght; ++col){

			if (ColorCheck(Board[row][col]) == Player) {
				KingMove[row][col] = 1;
			}
		}
	}
	cout << endl << "King move" << endl;
	PrintArr(KingMove);

	int TempCord[2];
	for (int c = -1; c <= 1; c = c + 2) {
		for (int x = -1; x <= 1; x = x + 2) {
			TempCord[0] = c + KingPos[0];
			TempCord[1] = x + KingPos[1];
			if (CheckCord(TempCord) == 1) {
				if (KingMove[TempCord[0]][TempCord[1]] == 0) {
					return 0;
				}
			}
		}
	}

	return 1;
}

bool CheckMate(char Board[][BLenght], int Player,IncludeSpecialArr) {
	bool Mate = 1;

	int ** KingAttack = FindCheckedBy(Board, Player,PassSpecialArr);
	int *KingPos = FindKingCord(Board, Player);

	//checks if movement of any other piece can remove check
	int TempCord[2];

	for (int row = 0; row < BLenght; ++row) {

		for (int col = 0; col < BLenght; ++col) {

			char Piece = Board[row][col];
			TempCord[0] = row;
			TempCord[1] = col;

			//if Piece is of Player, Check its movement
			if (ColorCheck(Piece) == Player) {
				if (CheckRemoval(Board, TempCord, Piece, Player,PassSpecialArr) == 1) {
					Mate = 0;
				}
			}

		}
	}

	DeleteMovesArr(KingAttack);
	delete[] KingPos;

	return Mate;
}
