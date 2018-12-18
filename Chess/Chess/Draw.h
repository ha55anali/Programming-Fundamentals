#pragma once

#include "Check.h"

//Simulates the movement of the passed piece. Returns 1 a move is possible
bool CheckPossibleMoves(char Board[][BLenght], int *Cord, char Piece, int Player, IncludeSpecialArr) {
	int EndCord[2];
	int ** PieceMoves = nullptr;

	bool MovePossible=0;

	//Returns all possible moves of the piece
	PieceMoves = ReturnMovesOfPiece(Board, Piece, Cord, Player, PassSpecialArr);

	if (PieceMoves == nullptr) {
		return 0;
	}

	//one by one tries all the possible moves of the piece
	for (int row = 0; row < BLenght; ++row) {

		for (int col = 0; col < BLenght; ++col) {

			if (PieceMoves[row][col] != 0) {

				//create copies of variables
				char BoardCopy[BLenght][BLenght];
				int EnpassantCopy[2 * BLenght][2];
				bool KingMoveCopy[2];
				bool RookMoveCopy[2][2];

				ArrCopy(Board, BoardCopy);
				CopyEnpassant(EnpassantArr, EnpassantCopy);
				CopyKingMove(KingMove, KingMoveCopy);
				CopyRookMove(RookMove, RookMoveCopy);

				EndCord[0] = row;
				EndCord[1] = col;

				MovePiece(BoardCopy, Piece, Cord, EndCord, Player, EnpassantCopy,KingMoveCopy,RookMoveCopy);

				if (Check(BoardCopy, Player, EnpassantCopy, KingMoveCopy, RookMoveCopy) != 1) {

					MovePossible = 1;
					break;

				}
			}

		}
	}
	DeleteMovesArr(PieceMoves);
	return MovePossible;
}


//assumes no check
bool Stalemate(char Board[][BLenght], bool Player, IncludeSpecialArr) {
	bool Stale = 1;

	//checks if movement of any other piece can remove check
	int TempCord[2];

	for (int row = 0; row < BLenght; ++row) {

		for (int col = 0; col < BLenght; ++col) {

			char Piece = Board[row][col];
			TempCord[0] = row;
			TempCord[1] = col;

			//if Piece is of Player, Check its movement
			if (ColorCheck(Piece) == Player) {
				if (CheckPossibleMoves(Board, TempCord, Piece, Player,PassSpecialArr) == 1) {
					Stale = 0;
				}
			}

		}
	}

	return Stale;
}