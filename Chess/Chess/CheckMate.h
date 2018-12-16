#pragma once

#include "constants.h"
#include "Check.h"
//
//void MovePiece(char Board[][BoardLenght],char Piece,int Cord[],int EndCord[],int EnpassantArr[][2],bool Player) {
//	switch (Piece)
//	{
//	case 'p':MovePawn(Board, Cord, EndCord, EnpassantArr, Player); break;
//
//	case 'P':MovePawn(Board, Cord, EndCord, EnpassantArr, Player); break;
//
//	case 'r':MoveRook(Board, Cord, EndCord, Player); break;
//
//	case 'R':MoveRook(Board, Cord, EndCord, Player); break;
//
//	case 'b':MoveBishop(Board, Cord, EndCord, Player); break;
//
//	case 'B':MoveBishop(Board, Cord, EndCord, Player); break;
//
//	case 'n':MoveKnight(Board, Cord, EndCord, Player); break;
//
//	case 'N':MoveKnight(Board, Cord, EndCord, Player); break;
//
//	case 'q':MoveQueen(Board, Cord, EndCord, Player); break;
//
//	case 'Q':MoveQueen(Board, Cord, EndCord, Player); break;
//
//	default:
//		break;
//	}
//}

//Simulates the movement of the passed piece. Returns 1 if check can be removed
bool CheckRemoval(char Board[][BoardLenght], int *Cord, char Piece, int Player, int EnpassantArr[][2]) {
	int EndCord[2];
	int ** PieceMoves = nullptr;

	//create copies of variables
	char BoardCopy[BoardLenght][BoardLenght];
	int EnpassantCopy[2 * BoardLenght][2];

	//Returns all possible moves of the piece
	PieceMoves=ReturnMovesOfPiece(Board, Piece, Cord, EnpassantArr, Player);

	PrintArr(PieceMoves);

	if (PieceMoves == nullptr) {
		return 0;
	}

	//one by one tries all the possible moves of the piece
	for (int row = 0; row < BoardLenght; ++row) {

		for (int col = 0; col < BoardLenght; ++col) {

			if (PieceMoves[row][col] != 0) {

				ArrCopy(Board, BoardCopy);
				CopyEnpassant(EnpassantArr, EnpassantCopy);

				EndCord[0] = row;
				EndCord[1] = col;

				MovePiece(BoardCopy, Piece, Cord, EndCord, EnpassantCopy, Player);

				//if check is removed return 1
				if (Check(BoardCopy, EnpassantCopy, Player) == 0) {
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
bool CheckKingMovement(char Board[][BoardLenght],int * KingPos,int ** KingAttack,int Player) {

	int KingMove[BoardLenght][BoardLenght];
	ArrCopy(KingAttack, KingMove);

	//prevents king from moving to same color pieces
	for (int row = 0; row < BoardLenght; ++row) {

		for (int col = 0; col < BoardLenght; ++col){

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

bool CheckMate(char Board[][BoardLenght], int EnpassantArr[][2], int Player) {
	bool Mate = 1;

	int ** KingAttack = FindCheckedBy(Board, EnpassantArr, Player);
	int *KingPos = FindKingCord(Board, Player);

	//check is the king can move
	Mate = CheckKingMovement(Board, KingPos, KingAttack, Player);

	//if Mate if 0, then checkmate is not possible
	if (Mate == 1) {

		//checks if movement of any other piece can remove check
		int TempCord[2];

		for (int row = 0; row < BoardLenght; ++row) {

			for (int col = 0; col < BoardLenght; ++col) {

				char Piece = Board[row][col];
				TempCord[0] = row;
				TempCord[1] = col;

				//if Piece is of Player, Check its movement
				if (ColorCheck(Piece) == Player) {
					if (CheckRemoval(Board, TempCord, Piece, Player, EnpassantArr) == 1) {
						Mate = 0;
					}
				}

			}
		}
	}

	DeleteMovesArr(KingAttack);
	delete[] KingPos;

	return Mate;
}
