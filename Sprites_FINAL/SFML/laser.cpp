#include "stdafx.h"
#include <iostream>
#include "laser.h"
#include <SFML\Graphics.hpp>

laser::laser()
{
	//do nothing, it will be reinstantiated eventually
}

laser::laser(sf::Vector2f startPos, int angle_raw)
{
	angle = angle_raw;
	pos = startPos;
	length = 0;
	width = 30;
	timer = 0;
	process = "rising";
	timer = clock.getElapsedTime().asSeconds();
	rect = sf::RectangleShape(pos);

}

void laser::Update()
{
	timer = clock.getElapsedTime().asSeconds();
	rect.setPosition(pos);
	rect.setRotation(angle - 90);

	if (length < 2000)
	{
		length += 3;
	}
	
	rect.setSize(sf::Vector2f(length, width));
}
