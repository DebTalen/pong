#ifndef __BALL__
#define __BALL__

#include "paddle.h"

class Ball 
{
private:
	sf::Vector2i coords;
	sf::Vector2i speed;
	sf::RenderWindow *app;
	sf::SoundBuffer soundBf;
	sf::Sound sound;
	int radius;
	
	bool intersection(Paddle, bool);

public:
	Ball (sf::RenderWindow&);

	int updatePos (Paddle, Paddle, sf::Vector2u);
	void draw();

	void setSound(sf::SoundBuffer);
	void setPos(sf::Vector2u);
	void setSpeed(int);
	void setRadius(int);

	int getX();
	int getY();
	int getSpeed();
	int getRadius();
};

#endif