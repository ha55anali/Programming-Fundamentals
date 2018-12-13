#include <iostream>
#include <Windows.h>

#include "constants.h"
#include "init Board.h"
#include "Print Board.h"
#include "Pieces.h"

using namespace std;

bool CheckFormat(char arr[]) {
	//lenght check
	if (strlen(arr) != 2)
		return 0;

	//checks column
	if (!(arr[0] >= 'a' && arr[0] <= 'h'))
		return 0;

	//checks row
	if (!(arr[1] >= '1' && arr[1] <= '8'))
		return 0;

	return 1;
}

int * InputCordinate() {
	char buff[100];
	cin >> buff;

	while (CheckFormat(buff) == 0) {
		cout << "Invalid Enter Again: ";
		cin >> buff;
	}

	int *Cord = new int[2];
	Cord[1] = buff[0]-'a';
	Cord[0] = buff[1] - '1';

	return Cord;
}



int main() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	char Board[BoardLenght][BoardLenght];

	int EnpassantArr[BoardLenght*2][2];
	for (int c = 0; c < BoardLenght*2-1; ++c) {
		EnpassantArr[c][0] = -1;
		EnpassantArr[c][1] = -1;
	}

	initBoard(Board);

	PrintBoard(Board);

	/*InputCordinate();*/

	int start[2] = { 1,1 };
	int end[2] = { 3,1 };
	
	bool Player = white;
	while (true) {
		cout << "\n Plyaer" << Player << endl;
		int*test = InputCordinate();
		cout << endl << test[0] << " " << test[1];

		int*test2 = InputCordinate();
		cout << endl << test2[0] << " " << test2[1];

		switch (Board[test[0]][test[1]])
		{
		case 'p':MovePawn(Board, test, test2, EnpassantArr, Player); break;

		case 'P':MovePawn(Board, test, test2, EnpassantArr, Player); break;

		case 'r':MoveRook(Board, test, test2, Player); break;

		case 'R':MoveRook(Board, test, test2, Player); break;

		case 'b':MoveBishop(Board, test, test2, Player); break;

		case 'n':MoveKnight(Board, test, test2, Player); break;

		case 'N':MoveKnight(Board, test, test2, Player); break;

		case 'q':MoveQueen(Board, test, test2, Player); break;

		default:
			break;
		}

		PrintBoard(Board);

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