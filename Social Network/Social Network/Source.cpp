#include <iostream>

#include "ReadFromFile.h"
#include "Data Manipulation.h"
#include "Data Processing.h"
#include "Front End.h"

using namespace std;

int main() {

	int UserNum = 0;
	int**spine = ReadFromFile(UserNum);

	frontEnd(spine, UserNum);

}