// InBetween.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <random>

using namespace std;


int main()
{
	string username;
	fstream f;
	random_device rd;
	int balance;
	int x;
	int y;
	int guess;
	int bet;

	cout << "Enter your username: ";
	getline(cin, username);

	string fileName = username + ".txt";

	f.open(fileName, ios::in);
	f >> balance;

	if (balance < 0) { //i think it ends up being a pointer, which appears to always be -ive
		//create new user
		f.close();
		f.open(fileName, ios::out);
		f << "100";
		cout << "New user created.\n\n";
		f.close();
		f.open(fileName, ios::in);
		f >> balance;
	}

	cout << "In this game, two random numbers are chosen between 1 and 13.\n";
	cout << "The objective is to guess a number between them.\n";
	cout << "You may bet an amount from your balance, but the game is over when you run out.\n\n";

	while (balance != 0) {
		//game loop
		x = rd() % 13 + 1;
		y = rd() % 13 + 1;
		bet = balance + 1;
		guess = 14;
		cout << "Your balance is: $" << balance << endl;

		while (guess > 13 || guess < 1) {				//guess input
			cout << "What is your guess?\t(it must be between 1 and 13)\n>>> ";
			cin >> guess;
		}
		while (bet > balance) {							//bet input
			cout << "What is your bet?\t(it must be smaller than your balance)\n>>> ";
			cin >> bet;
		}
		if (guess >= min(x, y) && guess <= max(x, y)) { //win
			balance += bet;
			cout << "You won! Your guess of " << guess << " was between " << min(x, y) << " & " << max(x, y) << ".\n";
		} else {											//lose
			balance -= bet;
			cout << "You lost. Your guess of "<< guess << " was not between " << min(x,y) << " & " << max(x,y) << ".\n";
		}

	}

	cout << "You're out of cash.\nYour balance will be reset to $100 when you next log in.\n";
	f.open(fileName, ios::out | ios::trunc);
	f << 100;
	f.close();

    return 0;
}


