#pragma once
#include <iostream>
#include <Windows.h>

#include "constants.h"

using namespace std;

void PrintRow(char Board[][BoardLenght], int RowNum, int cellheight, int cellwidth) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	bool Flag; //checks whether the row has white first or black cell first
	if (RowNum % 2 == 0)
		Flag = 0; //black first
	else
		Flag = 1; //white first

	for (int x = 0; x < cellheight; ++x) {

		for (int col = 0; col < BoardLenght; ++col) {

			//set color of the cell
			if (col % 2 == Flag) {
				SetConsoleTextAttribute(hConsole, 240);
			}
			else {
				SetConsoleTextAttribute(hConsole, 15);
			}

			//first the cell
			for (int c = 0; c < cellwidth; ++c) {
				//checks if the peice has to be printed
				if (x + 1 == cellheight / 2 && c + 1 == cellwidth / 2) {
					cout << Board[RowNum][col];
				}
				else {
					cout << " ";
				}
			}
		}

		//outputs labels
		SetConsoleTextAttribute(hConsole, 15);
		if (x + 1 == cellheight / 2) {
			cout << "  " << RowNum;
		}

		cout << endl;
	}
}

void PrintBoard(char Board[][BoardLenght]) {

	int cellwidth = 8;
	int cellheight = cellwidth / 2;

	//prints alphabetical labels
	for (int x = 0; x < BoardLenght; ++x) {
		for (int c = 0; c + 1 < cellwidth / 2; ++c) {
			cout << " ";
		}
		cout << (char)('A' + x);
		for (int c = 0; c < cellwidth / 2; ++c) {
			cout << " ";
		}
	}
	cout << endl << endl;


	for (int row = 0; row < BoardLenght; ++row) {
		PrintRow(Board, row, cellheight, cellwidth);
	}
}