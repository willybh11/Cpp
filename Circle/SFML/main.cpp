#include "stdafx.h"
#include <SFML/Graphics.hpp>
int main()
{
	sf::RenderWindow window(sf::VideoMode(400, 200), "SFML Works!");

	sf::CircleShape circle;
	circle.setRadius(50);
	circle.setPosition(200, 100);
	circle.setFillColor(sf::Color::Cyan);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(circle);
		window.display();
	}
}