#pragma once
#include <iostream>
#include <fstream>
using namespace std;

#define FilePath "input.txt"
#define FileLineLenght 1000

//converts forwarded string to int array
int * NumBuffToArr(char * LineOfText, int NumCount) {

	int *ArrOfNum = new int[NumCount + 1]; //array to store numbers
	char NumBuff[FileLineLenght]; //char array to store each number before conversion to int
	int NumBuffCount = 0;
	int ArrOfNumCount = 0;

	for (int c = 0; LineOfText[c] != '\0'; ++c) {
		if (LineOfText[c] == ',') {
			//previous number has ended
			NumBuffCount = 0;
			ArrOfNum[ArrOfNumCount] = atoi(NumBuff);
			++ArrOfNumCount;
		}
		else {
			//append to previous number
			NumBuff[NumBuffCount] = LineOfText[c];
			NumBuff[NumBuffCount + 1] = '\0';
			++NumBuffCount;
		}
	}
	//store the number in NumBuff to ArrOfNum
	ArrOfNum[ArrOfNumCount] = atoi(NumBuff);
	++ArrOfNumCount;
	//add sentinal
	ArrOfNum[ArrOfNumCount] = -1;

	return ArrOfNum;
}

//returns an int Array made from a string
int * CreateNumArr(char LineOfText[]) {
	//counts amount of integers in LineOfText
	int NumCount = 0;
	for (int c = 0; LineOfText[c] != '\0'; ++c) {
		if (LineOfText[c] == ',') {
			++NumCount;
		}
	}
	++NumCount;

	//function returns int pointer array with numbers
	return NumBuffToArr(LineOfText, NumCount);
}

int ** ReadFromFile(int &UserNum) {
	ifstream file(FilePath);

	//if file doesnt open
	if (file.fail()) {
		return nullptr;
	}

	int LineCount = 0;
	char LineOfText[FileLineLenght];

	//read to end of file to count number of lines
	while (!file.eof()) {
		file.getline(LineOfText, FileLineLenght);
		++LineCount;
	}
	
	//returns file pointer to start
	file.clear();
	file.seekg(0, ios::beg);

	int **spine = new int *[LineCount];
	int count = 0;

	while (!file.eof()) {
		file.getline(LineOfText, FileLineLenght);
		//function returns int array pointer with the numbers 
		spine[count] = CreateNumArr(LineOfText);
		++count;
	}

	UserNum = LineCount;
	return spine;
}