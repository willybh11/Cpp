// WorkingWithFiles.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;


int main()
{
	fstream file;
	string firstWord;
	string firstLine;
	file.open("test.txt");

	if (file.is_open()) {
		cout << "File opened successfully."  << endl;
	}
	else {
		cout << "Something is wrong here..." << endl;
	}

	file >> firstWord;
	getline(file, firstLine);

	cout << "First Word: " << firstWord << endl;
	cout << "First Line: " << firstLine << endl;

	file.close();
    return 0;
}

