#pragma once

#include <iostream>

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
	Cord[1] = buff[0] - 'a';
	Cord[0] = 7 - (buff[1] - '1');

	return Cord;
}

