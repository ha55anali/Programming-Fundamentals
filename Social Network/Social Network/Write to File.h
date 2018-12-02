#pragma once
#include <iostream>
#include <fstream>
using namespace std;

char * NumToString(int Num) {
	if (Num == 0) {
		char * temp = new char[2];
		temp[0] = '0';
		temp[1] = '\0';
		return temp;
	}

	int DigitCount = 0;
	int n = Num;
	float ten = 10;

	while (n > 0) {
		n = n / 10;
		++DigitCount;
	}

	char *String = new char[DigitCount + 1];

	int c = 0;
	for (int x = DigitCount - 1; c < DigitCount; ++c, --x) {
		String[c] = '0' + (Num / pow(ten, x));
		Num = Num % (int)(pow(ten, x));
	}
	String[c] = '\0';

	return String;
}

void AppendString(char *String, char *Append) {
	int c = strlen(String);

	if (String[0] != '\0') {
		String[c] = ',';
		++c;
	}

	int x = 0;
	for (; Append[x] != '\0'; ++x, ++c) {
		String[c] = Append[x];
	}
	String[c] = '\0';
}

void SaveToFile(int ** spine, int UserNum) {
	ofstream file(FilePath);

	//if file doesnt open
	if (file.fail()) {
		cout << "File cannot be opened";
		return;
	}

	char Lot[FileLineLenght];
	Lot[0] = '\0';
	char temp[FileLineLenght];

	for (int line = 0; line < UserNum; ++line) {
		for (int c = 0; spine[line][c] != -1; ++c) {
			AppendString(Lot, NumToString(spine[line][c]));
		}

		if (line > 0) {
			file << '\n';
		}

		if (Lot[0] == '\0') {
			file << "-1";
		}
		else {
			file << Lot;
		}
		Lot[0] = '\0';
	}

	file.close();
}


