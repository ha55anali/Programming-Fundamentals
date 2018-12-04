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

bool PawnMove(char Board[][BoardLenght], int Start[], int End[]) {
	bool CheckMove[BoardLenght][BoardLenght];

	if (Board[Start[0] + 1][Start[1]] == ' ') {
		CheckMove[Start[0] + 1][Start[1]] == 1;
	}

	if (Start[1]==)
}

int main() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	char Board[BoardLenght][BoardLenght];

	initBoard(Board);

	PrintBoard(Board);

	InputCordinate();

	int dum;
	cin >> dum;

}