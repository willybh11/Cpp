#pragma once
#include <string>
#include <iostream>

using namespace std;

class player {
public:
	player();
	player(string inputName);

	string name;

	void Greet();
};