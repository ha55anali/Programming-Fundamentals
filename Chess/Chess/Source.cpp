#include <iostream>
#include <Windows.h>

#include "init Board.h"
#include "Print Board.h"

using namespace std;




int main() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	char Board[BoardLenght][BoardLenght];

	initBoard(Board);

	PrintBoard(Board);

	int dum;
	cin >> dum;

}