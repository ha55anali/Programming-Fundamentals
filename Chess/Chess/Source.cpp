#include <iostream>
#include <Windows.h>

#include "constants.h"
#include "init Board.h"
#include "Print Board.h"
#include "Pieces.h"
#include "Front End.h"
#include "CheckMate.h"

using namespace std;



int main() {
	char Board[BoardLenght][BoardLenght];

	int EnpassantArr[BoardLenght*2][2];
	for (int c = 0; c < BoardLenght*2-1; ++c) {
		EnpassantArr[c][0] = -1;
		EnpassantArr[c][1] = -1;
	}

	initBoard(Board);

	/*InputCordinate();*/

	int * Start;
	int * End;
	
	bool Mate = 0;
	bool Player = white;

	while (Mate==0) {
		
		PrintBoard(Board);

		if (Check(Board, EnpassantArr, Player) == 1) {

			if (CheckMate(Board, EnpassantArr, Player) == 1) {
				Mate = 1;
				break;
			}

			cout << "Check" << endl;

			cout << "Player " << Player << "'s Turn:\nInput Starting Cord: ";
			Start = InputCordinate();
			cout << "Enter ending cord ";
			End = InputCordinate();

			while (isCheckRemoved(Board, Start, End, EnpassantArr, Player) == 0) {

				cout << "Please remove check";

				cout << "Player " << Player << "'s Turn:\nInput Starting Cord: ";
				Start = InputCordinate();
				cout << "Enter ending cord ";
				End = InputCordinate();
			}
		}
		else {

			cout << "Player " << Player << "'s Turn:\nInput Starting Cord: ";
			Start = InputCordinate();
			cout << "Enter ending cord ";
			End = InputCordinate();

			char Piece = Board[Start[0]][Start[1]];

			while (MovePiece(Board, Piece, Start, End, EnpassantArr, Player) == 0) {
				cout << "Invalid move\n";

				cout << "Player " << Player << "'s Turn:\nInput Starting Cord: ";
				Start = InputCordinate();
				cout << "Enter ending cord ";
				End = InputCordinate();

				char Piece = Board[Start[0]][Start[1]];
			}
		}

		if (Player == white) {
			Player = black;
		}
		else {
			Player = white;
		}

	}

	int dum;
	cin >> dum;

}