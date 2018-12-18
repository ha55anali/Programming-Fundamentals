#pragma once

#include <iostream>

#include "constants.h"
#include "Print Board.h"
#include "Pieces.h"
#include "CheckMate.h"
#include "Draw.h"
#include "Save Load.h"

using namespace std;

//checks format of passed string
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

//returns an array of cordinate after taking input
int * InputCordinate(char Board[][BLenght],bool Player, IncludeSpecialArr) {
	char buff[100];
	cin >> buff;

	if (strlen(buff) == 1 && (buff[0] == 'z' || buff[0] == 'Z')) {
		SaveGame(Board,Player,PassSpecialArr);
		cout << "Game saved\nEnter move: ";
		cin >> buff;
	}

	while (CheckFormat(buff) == 0) {
		cout << "Invalid Enter Again: ";
		cin >> buff;
	}


	int *Cord = new int[2];
	Cord[1] = buff[0] - 'a';
	Cord[0] = 7 - (buff[1] - '1');

	return Cord;
}

//writes start and end corindate to passed arrays
void InputStartEndCord(char Board[][BLenght],int * &Start, int * &End, bool Player, IncludeSpecialArr) {
	cout << "Player " << Player << "'s Turn:\nInput Starting Cord(press z to save): ";
	Start = InputCordinate(Board,Player, PassSpecialArr);
	cout << "Enter ending cord(press z to save): ";
	End = InputCordinate(Board, Player, PassSpecialArr);
}

//switches player turns
void SwitchTurn(bool &Player) {
	if (Player == white) {
		Player = black;
	}
	else {
		Player = white;
	}
}

//if check is detected, ensures that check is removed
//returns 1 if checkmate
bool HandleCheck(char Board[][BLenght], int * &Start, int * &End,bool Player, IncludeSpecialArr) {
	//if check mate end game
	if (CheckMate(Board, Player,PassSpecialArr) == 1) {
		return 1;
	}

	cout << "Check" << endl;
	InputStartEndCord(Board, Start, End, Player,PassSpecialArr);

	//makes sure that check is removed
	while (isCheckRemoved(Board, Start, End, Player,PassSpecialArr) == 0) {

		cout << "Please remove check";

		InputStartEndCord(Board, Start, End, Player, PassSpecialArr);
	}

	return 0;
}

void LoadGameFrontEnd(char Board[][BLenght], bool &Player, IncludeSpecialArr) {
	cout << "Do you want to load game? 1 for yes, 0 for no: ";

	char buff[100];
	cin >> buff;

	while (!(strlen(buff) == 1 && (buff[0] == '1' || buff[0] == '0'))) {
		cout << "please enter 0 or 1";
		cin >> buff;
	}

	if (buff[0] == '1') {
		LoadGame(Board,Player, PassSpecialArr);
	}
}

//main loop
//prints interface. takes input and moves pieces
void MainLoop(char Board[][BLenght],IncludeSpecialArr) {
	int * Start = nullptr;
	int * End = nullptr;

	bool Mate = 0;
	bool Stale = 0;
	bool Player = white;

	LoadGameFrontEnd(Board,Player, PassSpecialArr);

	//runs until checkmate or stalemate
	while (Mate == 0 && Stale==0) {

		PrintBoard(Board);

		//if checked
		if (Check(Board, Player, PassSpecialArr) == 1) {

			if (HandleCheck(Board, Start, End, Player, PassSpecialArr) == 1) {
				Mate = 1;
				break;
			}
		}
		//no check, procede as normal
		else {
			if (Stalemate(Board, Player, PassSpecialArr) == 1) {
				Stale = 1;
				break;
			}

			InputStartEndCord(Board,Start, End, Player,PassSpecialArr);

			char Piece = Board[Start[0]][Start[1]];

			//makes sure move input is valid
			while (MovePiece(Board, Piece, Start, End,Player, PassSpecialArr) == 0) {
				cout << "Invalid move\n";

				InputStartEndCord(Board, Start, End, Player, PassSpecialArr);
				char Piece = Board[Start[0]][Start[1]];
			}
		}

		//check if pawn is to be promoted
		if (Board[End[0]][End[1]]=='p' || Board[End[0]][End[1]] == 'P') {
			int LastRow;
			if (Player == black) {
				LastRow = BLenght - 1;
			}
			else {
				LastRow = 0;
			}

			if (End[0] == LastRow) {
				PromotePawn(Board, End,Player);
			}
		}
		
		//switch turn
		SwitchTurn(Player);

	}

	if (Mate == 1) {
		cout << endl << "Check mate";
	}
	if (Stale == 1) {
		cout << endl << "Stalemate";
	}


}

