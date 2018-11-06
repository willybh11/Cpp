#include "stdafx.h"
#include <SFML/Graphics.hpp>

enum GameState {
	MENU,
	GAMEPLAY
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	// start on the menu.
	GameState currentState = MENU;



	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space) {
					if (currentState == MENU) {
						currentState = GAMEPLAY;
					}
					else {
						currentState = MENU;
					}
				}

			}
		}

		window.clear();

		if (currentState = GAMEPLAY) {
			window.draw(shape);
		}

		window.display();
	}

	return 0;
}