
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {

	vector<string> list;

	list.push_back("Hey look, a string!");
	list.push_back("Oh no, a string!");
	list.push_back("Wow! a string!");

	cout << "The list: " << endl;

	for (string element : list) { cout << element << endl; }

	cout << "The second element of the list:" << endl;
	cout << list[1] << endl;

}