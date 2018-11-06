#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;

class enemy {
public:
	enemy();

	//variables
	sf::Vector2f pos;
	sf::Vector2f movement;
	sf::Texture tex;
	sf::Sprite sprite;
};