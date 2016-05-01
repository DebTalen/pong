#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ball.h"
#include "paddle.h"

Ball::Ball(sf::RenderWindow & wnd)
{
	app = &wnd;

	coords = (sf::Vector2i)wnd.getSize();
	coords.x /= 2;
	coords.y /= 2;
}

bool Ball::intersection(Paddle pad, bool side)
{
	//detecting if ball cross a paddle on the next step
	if(side)
	{//left paddle
		if( ((coords.x - radius) + speed.x) < (pad.getX() /*+ pad.getWidth()*/) &&
			( ((coords.y + speed.y) >= pad.getY()) && ((coords.y + speed.y) <= (pad.getY() + pad.getLen())) ) )
			return true;		
	}
	else
	{//right paddle
		if( ((coords.x + radius) + speed.x) > pad.getX() &&
			( ((coords.y + speed.y) >= pad.getY()) && ((coords.y + speed.y) <= (pad.getY() + pad.getLen())) ) )
			return true;		
	}
	return false;
}

int Ball::updatePos (Paddle pad1, Paddle pad2, sf::Vector2u wndSize)
{
	if((coords.y ) < radius || (coords.y + radius) > wndSize.y)			
		speed.y = -speed.y;	
	else if(coords.x < 0)
		return 1;	
	else if(coords.x > wndSize.x)
		return 2;

	if(intersection(pad1, true))
	{		
		sound.play();
		coords.x -= (coords.x - radius) - (pad1.getX() + pad1.getWidth());
		coords.y += speed.y;

		speed.x = - speed.x;
		speed.x += 1;
	}
	else if(intersection(pad2, false))
	{
		sound.play();
		coords.x += (coords.x + radius) - pad2.getX();
		coords.y += speed.y;

		speed.x = - speed.x;
		speed.x -= 1;
	}
	else 
	{
		coords.x += speed.x;
		coords.y += speed.y;
	}
	return 0;
}

void Ball::draw()
{
	sf::CircleShape shape(radius);
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(coords.x, coords.y);

	app->draw(shape);
}

void Ball::setSound(sf::SoundBuffer  ballSound)
{	
	soundBf = ballSound;
	sound.setBuffer(soundBf);	
}
void Ball::setPos(sf::Vector2u pos)
{
	coords = (sf::Vector2i)pos;
}
void Ball::setSpeed(int speed)
{	
	while(true)
	{
		this->speed.y = (rand()%speed - speed/2);
		this->speed.x = (rand()%speed - speed/2);
		if(this->speed.x != 0 && this->speed.y !=0)
			break;
	}
}
void Ball::setRadius(int radius)
{
	this->radius = radius;
}

int Ball::getX()
{
	return coords.x;
}
int Ball::getY()
{
	return coords.y;
}
int Ball::getSpeed()
{
	return speed.x;
}
int Ball::getRadius()
{
	return radius;
}