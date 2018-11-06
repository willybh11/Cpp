// MadLibs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;


int main()
{	
	//setup

	string noun1;
	string noun2;
	string adj1;
	string adj2;
	string verb1;
	string verb2;

	cout << "Welcome to Mad Libs." << endl;

	//input section

	cout << "Noun: ";
	getline(cin, noun1);
	cout << "Noun: ";
	getline(cin, noun2);
	cout << "Adjective: ";
	getline(cin, adj1);
	cout << "Adjective: ";
	getline(cin, adj2);
	cout << "Verb (infinitive): ";
	getline(cin, verb1);
	cout << "Verb (past tense): ";
	getline(cin, verb2);

	//output section

	cout << "Although the " << adj1 << " " << noun1 << " was " << verb1 << "," << endl;
	cout << "The "  << adj2 << " " << noun2 << " had already " << verb2 << "." << endl;

    return 0;
}

