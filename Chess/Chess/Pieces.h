#pragma once
#include <iostream>

#include "constants.h"

using namespace std;

int SquareCheck(char Board[][BoardLenght], int Point[], bool Player) {
	char Piece = Board[Point[0]][Point[1]];

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

#pragma region Pawn

bool CheckEnpassant(int Cord[], int EnpassantArr[][2]) {
	for (int c = 0; c < BoardLenght * 2 - 1; ++c) {
		if (Cord[0] == EnpassantArr[c][0] && Cord[1] == EnpassantArr[c][1]) {
			return 1;
		}
	}
}

void RemoveEnpassant(int Cord[], int EnpassantArr[][2]) {
	for (int c = 0; c < BoardLenght * 2 - 1; ++c) {
		if (Cord[0] == EnpassantArr[c][0] && Cord[1] == EnpassantArr[c][1]) {
			EnpassantArr[c][0] = -1;
			EnpassantArr[c][1] = -1;
		}
	}
}

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


	if (Start[0] == LastRow)
		return nullptr;

#pragma region "Declare array"
	int ** Moves = new int*[BoardLenght];
	for (int c = 0; c < BoardLenght; ++c) {
		Moves[c] = new int[BoardLenght];
	}

	for (int c = 0; c < BoardLenght; ++c) {
		for (int x = 0; x < BoardLenght; ++x) {
			Moves[c][x] = NotValid;
		}
	}
#pragma endregion "Declare array"

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

bool MovePawn(char Board[][BoardLenght], int Start[], int End[], int EnpassantArr[][2], bool Player) {
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

bool RookPossibleMove(char Board[][BoardLenght],int ** Moves,int Temp[],int Player) {
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

void VerticalHorizontalMoves(char Board[][BoardLenght],int ** Moves,int Start[], int Player) {
	int Temp[2];

	Temp[1] = Start[1];
	for (int c = Start[0] + 1; c < BoardLenght; ++c) {
		Temp[0] = c;
		if (RookPossibleMove(Board, Moves, Temp, Player) == 0) {
			break;
		}
	}

	for (int c = Start[0] - 1; c >= 0; --c) {
		Temp[0] = c;
		if (RookPossibleMove(Board, Moves, Temp, Player) == 0) {
			break;
		}
	}

	Temp[0] = Start[0];
	for (int c = Start[0] + 1; c < BoardLenght; ++c) {
		Temp[1] = c;
		if (RookPossibleMove(Board, Moves, Temp, Player) == 0) {
			break;
		}
	}

	for (int c = Start[1] - 1; c >= 0; --c) {
		Temp[1] = c;
		if (RookPossibleMove(Board, Moves, Temp, Player) == 0) {
			break;
		}
	}

	for (int c = 0; c < BoardLenght; ++c) {
		for (int x = 0; x < BoardLenght; ++x) {
			cout << Moves[c][x] << " ";
		}
		cout << endl;
	}
}

int ** RookMoves(char Board[][BoardLenght], int Start[], bool Player) {
#pragma region "Declare array"
	int ** Moves = new int*[BoardLenght];
	for (int c = 0; c < BoardLenght; ++c) {
		Moves[c] = new int[BoardLenght];
	}

	for (int c = 0; c < BoardLenght; ++c) {
		for (int x = 0; x < BoardLenght; ++x) {
			Moves[c][x] = NotValid;
		}
	}
#pragma endregion "Declare array"

	VerticalHorizontalMoves(Board, Moves, Start, Player);

	return Moves;
}

bool MoveRook(char Board[][BoardLenght], int Start[], int End[], bool Player) {
	int ** Moves = RookMoves(Board, Start, Player);

	if (Moves[End[0]][End[1]] == ValidMove || Moves[End[0]][End[1]] == Kill) {
		Board[End[0]][End[1]] = Board[Start[0]][Start[1]];
		Board[Start[0]][Start[1]] = ' ';
		return 1;
	}

	return 0;
}

#pragma endregion rook

#pragma region Bishop

bool BishopPossibleMoves(char Board[][BoardLenght], int ** Moves, int Temp[], int Player) {

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

void DiagonalMoves(char Board[][BoardLenght], int ** Moves, int Start[], int Player) {

	int Temp[2];

	for (int row = Start[0] +1, col = Start[1]+1; row < BoardLenght && col < BoardLenght; ++row, ++col) {
		Temp[0] = row;
		Temp[1] = col;
		if (RookPossibleMove(Board, Moves, Temp, Player) == 0) {
			break;
		}
	}

	for (int row = Start[0]-1, col = Start[1]+1; row >= 0 && col < BoardLenght; --row, ++col) {
		Temp[0] = row;
		Temp[1] = col;
		if (RookPossibleMove(Board, Moves, Temp, Player) == 0) {
			break;
		}
	}

	for (int row = Start[0]-1, col = Start[1]-1; row >= 0 && col >= 0; --row, --col) {
		Temp[0] = row;
		Temp[1] = col;
		if (RookPossibleMove(Board, Moves, Temp, Player) == 0) {
			break;
		}
	}

	for (int row = Start[0]+1, col = Start[1]-1; col >= 0 && row < BoardLenght; --col, ++row) {
		Temp[0] = row;
		Temp[1] = col;
		if (RookPossibleMove(Board, Moves, Temp, Player) == 0) {
			break;
		}
	}

}

int ** BishopMoves(char Board[][BoardLenght], int Start[], bool Player) {

#pragma region "Declare array"
	int ** Moves = new int*[BoardLenght];
	for (int c = 0; c < BoardLenght; ++c) {
		Moves[c] = new int[BoardLenght];
	}

	for (int c = 0; c < BoardLenght; ++c) {
		for (int x = 0; x < BoardLenght; ++x) {
			Moves[c][x] = NotValid;
		}
	}
#pragma endregion "Declare array"

	DiagonalMoves(Board, Moves, Start, Player);

	for (int c = 0; c < BoardLenght; ++c) {
		for (int x= 0; x< BoardLenght; ++x){
			cout<<Moves[c][x]<<" ";
		}
			cout<<endl;
	}

	return Moves;
}

bool MoveBishop(char Board[][BoardLenght], int Start[], int End[], bool Player) {
	int ** Moves = BishopMoves(Board, Start, Player);

	if (Moves[End[0]][End[1]] == ValidMove || Moves[End[0]][End[1]] == Kill) {
		Board[End[0]][End[1]] = Board[Start[0]][Start[1]];
		Board[Start[0]][Start[1]] = ' ';
		return 1;
	}

	return 0;
}

#pragma endregion Bishop

//#pragma region rook
//
//bool RookPossibleMove(char Board[][BoardLenght], int ** Moves, int Temp[], int Player) {
//	if (SquareCheck(Board, Temp, Player) == 0) {
//		Moves[Temp[0]][Temp[1]] = ValidMove;
//		return 1;
//	}
//	if (SquareCheck(Board, Temp, Player) == -1) {
//		Moves[Temp[0]][Temp[1]] = Kill;
//		return 0;
//	}
//	if (SquareCheck(Board, Temp, Player) == 1) {
//		return 0;
//	}
//}
//
//void VerticalHorizontalMoves(char Board[][BoardLenght], int ** Moves, int Start[], int Player) {
//	int Temp[2];
//
//	Temp[1] = Start[1];
//	for (int c = Start[0] + 1; c < BoardLenght; ++c) {
//		Temp[0] = c;
//		if (RookPossibleMove(Board, Moves, Temp, Player) == 0) {
//			break;
//		}
//	}
//
//	for (int c = Start[0] - 1; c >= 0; --c) {
//		Temp[0] = c;
//		if (RookPossibleMove(Board, Moves, Temp, Player) == 0) {
//			break;
//		}
//	}
//
//	Temp[0] = Start[0];
//	for (int c = Start[0] + 1; c < BoardLenght; ++c) {
//		Temp[1] = c;
//		if (RookPossibleMove(Board, Moves, Temp, Player) == 0) {
//			break;
//		}
//	}
//
//	for (int c = Start[1] - 1; c >= 0; --c) {
//		Temp[1] = c;
//		if (RookPossibleMove(Board, Moves, Temp, Player) == 0) {
//			break;
//		}
//	}
//
//	for (int c = 0; c < BoardLenght; ++c) {
//		for (int x = 0; x < BoardLenght; ++x) {
//			cout << Moves[c][x] << " ";
//		}
//		cout << endl;
//	}
//}
//
//int ** RookMoves(char Board[][BoardLenght], int Start[], bool Player) {
//#pragma region "Declare array"
//	int ** Moves = new int*[BoardLenght];
//	for (int c = 0; c < BoardLenght; ++c) {
//		Moves[c] = new int[BoardLenght];
//	}
//
//	for (int c = 0; c < BoardLenght; ++c) {
//		for (int x = 0; x < BoardLenght; ++x) {
//			Moves[c][x] = NotValid;
//		}
//	}
//#pragma endregion "Declare array"
//
//	VerticalHorizontalMoves(Board, Moves, Start, Player);
//
//	return Moves;
//}
//
//bool MoveRook(char Board[][BoardLenght], int Start[], int End[], bool Player) {
//	int ** Moves = RookMoves(Board, Start, Player);
//
//	if (Moves[End[0]][End[1]] == ValidMove || Moves[End[0]][End[1]] == Kill) {
//		Board[End[0]][End[1]] = Board[Start[0]][Start[1]];
//		Board[Start[0]][Start[1]] = ' ';
//		return 1;
//	}
//
//	return 0;
//}
//
//#pragma endregion rook

#pragma region knight

bool KnightPossibleMoves(char Board[][BoardLenght], int ** Moves, int Temp[], int Player) {

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

bool CheckCord(int cord[]) {
	if (cord[0] < 0) return 0;

	if (cord[1] < 0) return 0;

	if (cord[0] >=BoardLenght) return 0;

	if (cord[1] >= BoardLenght) return 0;

	return 1;
}

void KnightMoves(char Board[][BoardLenght], int ** Moves, int Start[], int Player) {

	int Temp[2];

	for (int c = -2; c <= 2; c = c + 4) {

		for (int x = -1; x <= 1; x = x + 2) {

			Temp[0] = Start[0] + c;
			Temp[1] = Start[1] + x;

			if (CheckCord(Temp) == 1) {
				RookPossibleMove(Board, Moves, Temp, Player);
			}

			Temp[0] = Start[0] + x;
			Temp[1] = Start[1] + c;

			if (CheckCord(Temp) == 1) {
				RookPossibleMove(Board, Moves, Temp, Player);
			}

		}

	}

}

int ** KnightMoves(char Board[][BoardLenght], int Start[], bool Player) {

#pragma region "Declare array"
	int ** Moves = new int*[BoardLenght];
	for (int c = 0; c < BoardLenght; ++c) {
		Moves[c] = new int[BoardLenght];
	}

	for (int c = 0; c < BoardLenght; ++c) {
		for (int x = 0; x < BoardLenght; ++x) {
			Moves[c][x] = NotValid;
		}
	}
#pragma endregion "Declare array"

	KnightMoves(Board, Moves, Start, Player);

	for (int c = 0; c < BoardLenght; ++c) {
		for (int x = 0; x < BoardLenght; ++x) {
			cout << Moves[c][x] << " ";
		}
		cout << endl;
	}

	return Moves;
}

bool MoveKnight(char Board[][BoardLenght], int Start[], int End[], bool Player) {
	int ** Moves = KnightMoves(Board, Start, Player);

	if (Moves[End[0]][End[1]] == ValidMove || Moves[End[0]][End[1]] == Kill) {
		Board[End[0]][End[1]] = Board[Start[0]][Start[1]];
		Board[Start[0]][Start[1]] = ' ';
		return 1;
	}

	return 0;
}

#pragma endregion knight

#pragma region queen

bool QueenPossibleMove(char Board[][BoardLenght], int ** Moves, int Temp[], int Player) {
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

int ** QueenMoves(char Board[][BoardLenght], int Start[], bool Player) {
#pragma region "Declare array"
	int ** Moves = new int*[BoardLenght];
	for (int c = 0; c < BoardLenght; ++c) {
		Moves[c] = new int[BoardLenght];
	}

	for (int c = 0; c < BoardLenght; ++c) {
		for (int x = 0; x < BoardLenght; ++x) {
			Moves[c][x] = NotValid;
		}
	}
#pragma endregion "Declare array"

	VerticalHorizontalMoves(Board, Moves, Start, Player);

	DiagonalMoves(Board, Moves, Start, Player);

	return Moves;
}

bool MoveQueen(char Board[][BoardLenght], int Start[], int End[], bool Player) {
	int ** Moves = QueenMoves(Board, Start, Player);

	if (Moves[End[0]][End[1]] == ValidMove || Moves[End[0]][End[1]] == Kill) {
		Board[End[0]][End[1]] = Board[Start[0]][Start[1]];
		Board[Start[0]][Start[1]] = ' ';
		return 1;
	}

	return 0;
}

#pragma endregion queen
