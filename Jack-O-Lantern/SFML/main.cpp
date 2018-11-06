#include "stdafx.h"
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(400, 400), "Jack-O-Lantern");

	sf::CircleShape jackOLantern;
	jackOLantern.setRadius(200);
	jackOLantern.setPosition(0, 0);
	jackOLantern.setFillColor(sf::Color(255, 165, 0));	

	sf::CircleShape leftEye;
	leftEye.setPointCount(3);
	leftEye.setRadius(50);
	leftEye.setPosition(50, 75);
	leftEye.setFillColor(sf::Color::Black);

	sf::CircleShape rightEye;
	rightEye.setPointCount(3);
	rightEye.setRadius(50);
	rightEye.setPosition(250, 75);
	rightEye.setFillColor(sf::Color::Black);

	sf::ConvexShape mouth;
	mouth.setFillColor(sf::Color::Black);
	mouth.setPointCount(5);
	mouth.setPoint(0, sf::Vector2f(50, 300));
	mouth.setPoint(1, sf::Vector2f(350, 300));
	mouth.setPoint(2, sf::Vector2f(300, 350));
	mouth.setPoint(3, sf::Vector2f(200, 375));
	mouth.setPoint(4, sf::Vector2f(100, 350));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(jackOLantern);
		window.draw(leftEye);
		window.draw(rightEye);
		window.draw(mouth);
		window.display();
	}
}
