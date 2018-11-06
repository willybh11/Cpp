#include "stdafx.h"
#include <string>
#include <cmath>
#include <iostream>
#include <SFML\Graphics.hpp>
#include "laser.h"
#include "enemy.h"

using namespace std;

#define PI 3.1415926535898

float toDegrees(float radians);
float toRadians(float degrees);
float getAngle(sf::Sprite playerSprite, sf::Vector2f target);
int mapRange(float var, int inp_start, int inp_end, int out_start, int out_end);
float min(float a, float b);
float max(float a, float b);
string toString(int32_t integer);

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Sprites!");

	sf::Texture playerTex;
	playerTex.loadFromFile("Textures/player_ship.png");

	sf::Font font;
	font.loadFromFile("font/Candal.ttf");

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(40);
	text.setFillColor(sf::Color::Blue);
	text.setPosition(1500, 30);
	text.setString("this will be replaced");

	sf::Sprite playerSprite;
	playerSprite.setTexture(playerTex);
	playerSprite.setOrigin(32, 32);
	playerSprite.setScale(1.5, 1.5);
	playerSprite.setPosition(1460, 540);

	sf::Vector2f movement(0, 0);
	sf::Vector2f target;

	sf::RectangleShape rect(sf::Vector2f(1720, 880));
	rect.setPosition(100, 100);
	rect.setOutlineColor(sf::Color::White);
	rect.setFillColor(sf::Color::Black);
	rect.setOutlineThickness(20);

	sf::Vector2u windowSize = window.getSize();
	sf::Texture texture;
	texture.create(windowSize.x, windowSize.y);
	sf::Image screenshot;
	sf::Color pixel = sf::Color::Black;

	laser Lasers[5];

	enemy enemyShip;

	sf::Clock clock1;
	sf::Clock clock2;
	sf::Clock clock3;

	sf::VertexArray arr;

	bool boosting = false;
	bool captured = false;
	bool firstShot = false;
	int laserCount = -1;
	int cooldown;
	int collisions;
	std::vector<int> collisionTimes;
	float timer;
	float gameClock;
	float collisionCooldown;
	float segmentAngle;
	float angle;

	while (window.isOpen())
	{
		if /*timer setup*/ (1)
		{
			timer = clock1.getElapsedTime().asSeconds();
			collisionCooldown = clock2.getElapsedTime().asSeconds();
			gameClock = clock3.getElapsedTime().asSeconds();
		}

		if /*events*/ (1)
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && timer > 1)
				{
					laserCount++;
					clock1.restart();
					cout << "New laser in slot #" << laserCount % 5 << "." << endl;
					captured = false;
					firstShot = true;
					if (boosting)
						Lasers[laserCount % 5] = laser(playerSprite.getPosition(), toDegrees(getAngle(playerSprite, target)) + 90);
					else
						Lasers[laserCount % 5] = laser(playerSprite.getPosition(), toDegrees(getAngle(playerSprite, sf::Vector2f(sf::Mouse::getPosition()))) + 90);
				}

				if (event.type == sf::Event::KeyPressed)
				{
					switch (event.key.code) {
					case sf::Keyboard::Space:
						boosting = true;
						target = sf::Vector2f(sf::Mouse::getPosition());
						break;

					}
				}
			}
		}

		if /*draw cooldown circle*/ (1)
		{
			arr = sf::VertexArray(sf::LinesStrip);
			segmentAngle = toRadians(min(mapRange(timer, 0, 1, 0, 360), 360));
			angle = 0;
			arr.append(playerSprite.getPosition());

			while (angle < segmentAngle)
			{
				sf::Vector2f p
				{
					cos(angle + (0 - segmentAngle / 2)) * 100, //position = cos(angle + lookAngle) * rad
					sin(angle + (0 - segmentAngle / 2)) * 100  //position = sin(angle + lookAngle) * rad        
				};

				p += playerSprite.getPosition();
				arr.append(p);

				angle += segmentAngle / 360;
			}

			arr.append(playerSprite.getPosition());
		}

		if /*update lasers*/ (1)
		{
			for (int i = 0; i < laserCount + 1; i++)
			{
				Lasers[i % 5].Update();
			}
		}

		if /*boundary collision check*/ (1)
		{
			if (playerSprite.getPosition().x > 1820)
				playerSprite.setPosition(1820, playerSprite.getPosition().y);
			else if (playerSprite.getPosition().x < 100)
				playerSprite.setPosition(100, playerSprite.getPosition().y);
			if (playerSprite.getPosition().y < 100)
				playerSprite.setPosition(playerSprite.getPosition().x, 100);
			else if (playerSprite.getPosition().y > 980)
				playerSprite.setPosition(playerSprite.getPosition().x, 980);
		}

		if /*boost check*/ (1)
		{
			//check to stop boosting
			if ((playerSprite.getPosition().x + 5 > target.x
				&&  playerSprite.getPosition().x - 5 < target.x)
				|| (playerSprite.getPosition().y + 5 > target.y
					&&  playerSprite.getPosition().y - 5 < target.y))
			{
				boosting = false;
			}
		}

		if /*boost/friction*/ (1)
		{
			if (boosting)
			{
				movement.x = cos(getAngle(playerSprite, target)) / 1.5;
				movement.y = sin(getAngle(playerSprite, target)) / 1.5;
			}
			else
			{
				movement.x *= 0.997;
				movement.y *= 0.997;
			}
		}

		if /*move/rotate player*/ (1)
		{
			//move and rotate player
			playerSprite.move(movement);
			if (boosting)
				playerSprite.setRotation(toDegrees(getAngle(playerSprite, target)) + 90);
			else
				playerSprite.setRotation(toDegrees(getAngle(playerSprite, sf::Vector2f(sf::Mouse::getPosition()))) + 90);
		}

		if /*move and rotate enemy*/ (1)
		{
			enemyShip.sprite.setRotation(toDegrees(atan2(enemyShip.movement.x, enemyShip.movement.y)) + 90);
			enemyShip.sprite.move(enemyShip.movement);
		}

		if /*initial window setup*/ (1)
		{
			window.clear();
			window.draw(rect);

			for (int i = 0; i < laserCount + 1; i++)
			{
				window.draw(Lasers[i % 5].rect);
			}
		}

		if /*capture check*/ (1)  // capture check
		{
			if (!captured && Lasers[laserCount % 5].length == 999)
			{
				texture.update(window);
				screenshot = texture.copyToImage();
				cout << "Screen captured (half)" << endl;
			}
			if ((!firstShot && !captured)  || (!captured && Lasers[laserCount % 5].length >= 2000))
			{
				texture.update(window);
				screenshot = texture.copyToImage();
				captured = true;	
				cout << "Screen captured." << endl;
			}
		}

		if /*check for enemy collisions*/ (1)
		{
			if (captured && collisionCooldown > 0.2)
			{
				unsigned int x = enemyShip.sprite.getPosition().x;
				unsigned int y = enemyShip.sprite.getPosition().y;
				if (screenshot.getPixel(x, y) == sf::Color::White)
				{
					clock2.restart();
					collisionTimes.push_back(int(gameClock));
					if (screenshot.getPixel(x - 10, y) == sf::Color::Black || screenshot.getPixel(x+10,y) == sf::Color::Black)
						enemyShip.movement.x *= -1;
					if (screenshot.getPixel(x, y - 10) == sf::Color::Black || screenshot.getPixel(x,y+10) == sf::Color::Black)
						enemyShip.movement.y *= -1;
				}
			}
		}

		if /*collisions counter*/ (1)
		{
			collisions = 0;
			for (int i = 0; i < collisionTimes.size(); i++)
			{
				if (collisionTimes[i] > gameClock - 10)
				{
					collisions++;
				}
			}
			string output = "Past 10s: " + toString(collisions);
			text.setString(output);
		}

		if /*post-check window setup*/ (1)
		{
			window.draw(arr);
			window.draw(playerSprite);
			window.draw(enemyShip.sprite);
			window.draw(text);
			window.display();
		}
	}
}

float toDegrees(float radians)
{
	return radians * 180 / PI;
}

float toRadians(float degrees)
{
	return degrees * PI / 180;
}

float getAngle(sf::Sprite playerSprite, sf::Vector2f target)
{
	int X = target.x - playerSprite.getPosition().x;
	int Y = target.y - playerSprite.getPosition().y;

	return atan2((double)Y, (double)X); // in radians
}

int mapRange(float var, int input_start, int input_end, int output_start, int output_end)
{
	int input_range = input_end - input_start;
	int output_range = output_end - output_start;

	int output = (var - input_start)*output_range / input_range + output_start;

	return output;
}

float min(float a, float b)
{
	if (a > b)
		return b;
	else
		return a;
}

float max(float a, float b)
{
	if (a < b)
		return b;
	else
		return a;
}

string toString(int32_t integer)
{
	char numstr[10]; // enough to hold all numbers up to 32-bits
	sprintf_s(numstr, "%i", integer);
	return numstr;
}