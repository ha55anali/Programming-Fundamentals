#include <iostream>



using namespace std;

#define BoardLenght 8
#define white 0
#define black 1

void initLastRow(char Board[][BoardLenght], bool Player) {
	int Temp;
	int row;

	if (Player == white) {
		row = 0;
		Temp = 'A' - 'a';
	}
	else {
		row = 7;
		Temp = 0;
	}

	Board[row][0] = 'r' + Temp;
	Board[row][7] = 'r' + Temp;

	Board[row][1] = 'n' + Temp;
	Board[row][6] = 'n' + Temp;

	Board[row][2] = 'b' + Temp;
	Board[row][5] = 'b' + Temp;

	Board[row][3] = 'q' + Temp;
	Board[row][4] = 'k' + Temp;
}

void initPawnRow(char Board[][BoardLenght],int Player) {
	int row;
	int Temp;

	if (Player == white) {
		row = 1;
		Temp = 'A' - 'a';
	}
	else {
		row = 6;
		Temp = 0;
	}

	for (int col = 0; col < BoardLenght; ++col) {
		Board[row][col]= 'p' + Temp;
	}
}

void initEmptySpaces(char Board[][BoardLenght]) {
	for (int row = 2; row < BoardLenght-2; ++row) {
		for (int col = 0; col < BoardLenght; ++col) {
			Board[row][col] = ' ';
		}
	}
}

void initBoard(char Board[][BoardLenght]) {
	initLastRow(Board, white);
	initLastRow(Board, black);

	initPawnRow(Board, white);
	initPawnRow(Board, black);

	initEmptySpaces(Board);
}

void PrintBoard(char Board[][BoardLenght]) {
	for (int c = 0; c < BoardLenght; ++c) {
		for (int x = 0; x < BoardLenght; ++x) {
			cout << Board[c][x] << " ";
		}
		cout << endl;
	}
}

int main() {

	char Board[BoardLenght][BoardLenght];

	initBoard(Board);

	PrintBoard(Board);

	int dum;
	cin >> dum;

}