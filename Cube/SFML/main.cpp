#include "stdafx.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(300, 300), "Window Title");

	sf::Vector2f point1 = sf::Vector2f(100, 100); //   1  ---  2
	sf::Vector2f point2 = sf::Vector2f(200, 100); //   |       |
	sf::Vector2f point3 = sf::Vector2f(100, 200); //   |       |
	sf::Vector2f point4 = sf::Vector2f(200, 200); //   3  ---  4

	sf::Vector2f curPos = sf::Vector2f(150, 150);
	sf::Vector2f lastPos;

	bool flipped = false;

	void moveX(float diff, sf::Vector2f &point1, sf::Vector2f &point2, sf::Vector2f &point3, sf::Vector2f &point4);


	while (window.isOpen())
	{
		lastPos = curPos;
		curPos = sf::Vector2f(sf::Mouse::getPosition());

		if (point1.x > 150 && !flipped)
		{
			flipped = true;
			cout << "2: " << point2.x << "," << point2.y << endl;
			cout << "4: " << point4.x << "," << point4.y << endl;
			sf::Vector2f temp = point2;
			point2 = point4;
			point4 = temp;
			cout << "Flipped!" << endl;
			cout << "2: " << point2.x << "," << point2.y << endl;
			cout << "4: " << point4.x << "," << point4.y << endl;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
		{
			float diff = (curPos.x - lastPos.x) / 20;
			moveX(diff, point1, point2, point3, point4);
		}

	
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(); 
		// lines go counter-clockwise
		sf::Vertex line1[] = { point1,point2 };
		sf::Vertex line2[] = { point2,point4 };
		sf::Vertex line3[] = { point4,point3 };
		sf::Vertex line4[] = { point3,point1 };
		window.draw(line1, 2, sf::Lines);
		window.draw(line2, 2, sf::Lines);
		window.draw(line3, 2, sf::Lines);
		window.draw(line4, 2, sf::Lines);

		window.display();
	}

}

void moveX(float diff, sf::Vector2f &point1, sf::Vector2f &point2, sf::Vector2f &point3, sf::Vector2f &point4)
{
	point1.y -= diff / 3;
	point1.x += diff / 2;

	point2.y += diff / 3;
	point2.x -= diff / 2;

	point3.y += diff / 3;
	point3.x += diff / 2;

	point4.y -= diff / 3;
	point4.x -= diff / 2;
}

/*void xMinus(float diff, sf::Vector2f &point1, sf::Vector2f &point2, sf::Vector2f &point3, sf::Vector2f &point4)
{
	point1.y += diff;
	point1.x -= diff;

	point2.y -= diff;
	point2.x += diff;

	point3.y -= diff;
	point3.x -= diff;
	
	point4.y += diff;
	point4.x += diff;

}*/