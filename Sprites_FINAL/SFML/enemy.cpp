#include "stdafx.h"
#include <iostream>
#include "enemy.h"
#include <SFML\Graphics.hpp>

enemy::enemy()
{
	movement = sf::Vector2f(0.1, -0.2);

	tex.loadFromFile("Textures/enemy_ship.png");

	sprite.setTexture(tex);
	sprite.setPosition(sf::Vector2f(960, 540));
	sprite.setOrigin(30, 30);
}
