#include <SFML/Graphics.hpp>
#include "paddle.h"

Paddle::Paddle(sf::RenderWindow & wnd)
{
	app = &wnd;	
}

void Paddle::move(int direction, sf::Vector2u wndSize)
{	
	if(direction == STOP)
		return;
	if(direction == UP)
	{
		if(int(coords.y - speed) < 0)
			coords.y = 0;
		else 
			coords.y -= speed;
	}
	else if (direction == DOWN)
	{
		if((coords.y + size.y + speed) > wndSize.y)
			coords.y = wndSize.y - size.y;
		else 
			coords.y += speed;
	}	
}
void Paddle::draw()
{
	sf::RectangleShape paddle(size);
	paddle.setPosition(coords.x, coords.y);
	paddle.setFillColor(sf::Color::Red);

	app->draw(paddle);
}

void Paddle::setPos(sf::Vector2u pos)
{
	coords = pos;
}
void Paddle::setSize(sf::Vector2f size)
{
	this->size = size;
}
void Paddle::setSpeed(int speed)
{
	this->speed = speed;
}

int Paddle::getLen()
{
	return size.y;
}
int Paddle::getWidth()
{
	return size.x;
}

sf::Vector2u Paddle::getPos()
{
	return coords;
}
int Paddle::getX()
{
	return coords.x;
}
int Paddle::getY()
{
	return coords.y;
}