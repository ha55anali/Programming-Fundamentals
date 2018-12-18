#pragma once

#include "Pieces.h"

bool MovePiece(char Board[][BLenght], char Piece, int Cord[], int EndCord[], bool Player, IncludeSpecialArr) {
	switch (Piece)
	{
	case 'p':return MovePawn(Board, Cord, EndCord, EnpassantArr, Player); break;

	case 'P':return MovePawn(Board, Cord, EndCord, EnpassantArr, Player); break;

	case 'r':return MoveRook(Board, Cord, EndCord, EnpassantArr,RookMove, Player); break;

	case 'R':return MoveRook(Board, Cord, EndCord, EnpassantArr, RookMove, Player); break;

	case 'b':return MoveBishop(Board, Cord, EndCord, EnpassantArr, Player); break;

	case 'B':return MoveBishop(Board, Cord, EndCord, EnpassantArr, Player); break;

	case 'n':return MoveKnight(Board, Cord, EndCord, EnpassantArr, Player); break;

	case 'N':return MoveKnight(Board, Cord, EndCord, EnpassantArr, Player); break;

	case 'q':return MoveQueen(Board, Cord, EndCord, EnpassantArr, Player); break;

	case 'Q':return MoveQueen(Board, Cord, EndCord, EnpassantArr, Player); break;

	case 'k':return MoveKing(Board, Cord, EndCord, PassSpecialArr, Player); break;

	case 'K':return MoveKing(Board, Cord, EndCord, PassSpecialArr, Player); break;

	default:
		return 0;
		break;
	}
}
