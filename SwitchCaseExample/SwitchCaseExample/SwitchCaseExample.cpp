// SwitchCaseExample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;


int main() {
	int n;
	cout << "Enter a number: ";
	cin >> n;

	switch (n) {
		case 1:  cout << "You chose 1." << endl; break;
		case 2:  cout << "You chose 2." << endl; break;
		case 3:  cout << "You chose 3." << endl; break;
		case 4:  cout << "You chose 4." << endl; break;
		case 5:  cout << "You chose 5." << endl; break;
		default: cout << "Nice try."    << endl; break;
	}

    return 0;
}
