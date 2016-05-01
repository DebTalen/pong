#ifndef __PLAYER_PADDLE__
#define __PLAYER_PADDLE__

class Paddle
{
private:
	sf::Vector2u coords;
	sf::Vector2f size;
	sf::RenderWindow *app;
	enum directions {UP, DOWN, STOP};
	int speed;

public:
	Paddle(sf::RenderWindow&);
	
	void move(int, sf::Vector2u);
	void draw();

	void setPos(sf::Vector2u);
	void setSize(sf::Vector2f);
	void setSpeed(int);
	
	sf::Vector2u getPos();
	int getLen();
	int getWidth();
	int getX();
	int getY();
};

#endif