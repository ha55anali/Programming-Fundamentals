#include <iostream>
#include <Windows.h>

#include "constants.h"
#include "init Board.h"
#include "Print Board.h"

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

void InputCordinate() {
	char buff[100];

	cin >> buff;

	while (CheckFormat(buff) == 0) {
		cout << "Invalid Enter Again: ";
		cin >> buff;
	}
}

int SquareCheck(char Board[][BoardLenght], int Point[], bool Player) {
	char Piece = Board[Point[0]][Point[1]];

	if (Piece == ' '){
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

bool PawnMove(char Board[][BoardLenght], int Start[], int End[],bool Player) {
	bool CheckMove[BoardLenght][BoardLenght];

	int Temp[2];

	if (Start[1] == 1) {
		Temp[0] =Start[0]+2;
		Temp[1] = Start[1];
		if (SquareCheck(Board, Temp, Player) ==0 ) {
			CheckMove[Temp[0]][Temp[1]]==1;
		}
	}

	Temp[0] = Start[0]+1;
	Temp[1] = Start[1];
	if (SquareCheck(Board, Temp, Player) == 0) {
		CheckMove[Temp[0]][Temp[1]] == 1;
	}

	return 0;
}

int main() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	char Board[BoardLenght][BoardLenght];

	initBoard(Board);

	PrintBoard(Board);

	/*InputCordinate();*/

	int start[2] = { 1,1 };
	int end[2] = { 3,1 };
	
	PawnMove(Board, start, end, black);

	int dum;
	cin >> dum;

}