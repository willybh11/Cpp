#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;

class laser {
public:
	laser();
	laser(sf::Vector2f startPos, int angle_raw);

	//variables
	sf::Vector2f pos;
	sf::RectangleShape rect;
	sf::Clock clock;
	int angle;
	int width;
	int length;
	float timer;
	string process;

	//functions
	void Update();
};