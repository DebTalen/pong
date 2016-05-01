#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <sstream>

#include "source/paddle.h"
#include "source/ball.h"
#include "source/menu.h"

#define GAP 20

using namespace sf;

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") 

void begining(RenderWindow & app, Text text, Music & music)
{
	srand(time(NULL));
	Color color(255, 255, 255, 0);

	text.setString("DebTalen Research Facility\n	present:");
	text.setCharacterSize(40);
	text.setPosition(100, 20);

	music.play();
	app.clear(Color::Black);
	app.display();

	for (int i = 0; i < 30; ++i)
		sleep(music.getDuration() / (float)200);
	for (int i = 0; i < 70; ++i)
	{
		color.a++;
		text.setColor(color);
		app.draw(text);
		sleep(music.getDuration() / (float)200);
		app.display();
	}

	text.setString("ENDLESS PAIN PONG v.1.0");
	text.setPosition(250, 300);
	text.setCharacterSize(100);
	text.setStyle(text.Bold);

	color.a = 0;
	for (int i = 0; i < 50; ++i)
	{
		color.a++;
		text.setColor(color);
		app.draw(text);
		sleep(music.getDuration() / (float)200);
		app.display();
	}
	for (int i = 0; i < 40; ++i)
		sleep(music.getDuration() / (float)200);

	music.stop();
}

void menu(RenderWindow & window)
{
	Texture menuTexture1, menuTexture2, menuTexture3;
	menuTexture1.loadFromFile("res/images/menu1.png");
	menuTexture2.loadFromFile("res/images/menu2.png");
	menuTexture3.loadFromFile("res/images/menu3.png");
	Sprite but_newg(menuTexture1), but_set(menuTexture2), but_exit(menuTexture3);

	but_newg.setPosition(800, 30);
	but_set.setPosition(800, 90);
	but_exit.setPosition(800, 150);

	bool isMenu = true;
	int menuNum;

	while (isMenu)
	{
		but_newg.setColor(Color::White);
		but_set.setColor(Color::White);
		but_exit.setColor(Color::White);
		menuNum = 0;
		window.clear(sf::Color::White);

		if (IntRect(800, 30, 900, 50).contains(Mouse::getPosition(window))) { but_newg.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(800, 90, 900, 50).contains(Mouse::getPosition(window))) { but_set.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(800, 150, 900, 50).contains(Mouse::getPosition(window))) { but_exit.setColor(Color::Blue); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;
			//if (menuNum == 2) { window.draw(); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3) { window.close(); isMenu = false; }
		}


		window.draw(but_newg);
		window.draw(but_set);
		window.draw(but_exit);

		window.display();
	}
}

int main()
{
	const int width = 1000;
	const int heigth = 500;
	int score1 = 0, score2 = 0;

	//main window
	RenderWindow wnd(VideoMode(width, heigth), "pong");
	wnd.setVerticalSyncEnabled(true);

	//Sound Effects
	SoundBuffer sBuffer;
	if (!sBuffer.loadFromFile("res/ball1.wav"))
		return -1;

	Music intro, theme;
	if (!intro.openFromFile("res/intro.wav"))
		return -1;
	if (!theme.openFromFile("res/main.wav"))
		return -1;
	theme.setLoop(true);

	//Fonts
	Font scoreFont, mainFont;
	if (!scoreFont.loadFromFile("res/scorefont.ttf"))
		return -1;
	if (!mainFont.loadFromFile("res/mainfont.ttf"))
		return -1;

	//Texts
	Text score, pauseText, introText;
	score.setFont(scoreFont);
	score.setColor(Color::Blue);
	score.setCharacterSize(70);
	score.setPosition(400, 20);

	pauseText.setFont(mainFont);
	pauseText.setColor(Color::Blue);
	pauseText.setCharacterSize(208);
	pauseText.setPosition(190, 80);
	pauseText.setString("pause");

	introText.setFont(mainFont);


	//Paddles
	Paddle plrPaddle(wnd), aiPaddle(wnd);
	plrPaddle.setPos(Vector2u(GAP, heigth / 2));
	plrPaddle.setSize(Vector2f(10, 60));
	plrPaddle.setSpeed(10);

	aiPaddle.setPos(Vector2u(width - GAP, heigth / 2));
	aiPaddle.setSize(Vector2f(10, 60));
	aiPaddle.setSpeed(10);


	//Ball
	Ball ball(wnd);
	ball.setSpeed(8);
	ball.setRadius(10);
	ball.setSound(sBuffer);

	enum directions { UP, DOWN, STOP };
	int check = 0;
	int direction = STOP;

	//intro of the game
	begining(wnd, introText, intro);

	theme.play();
	theme.setVolume(13);

	//game menu
	menu(wnd);

	//main game cycle
	while (wnd.isOpen())
	{
		if (check == 1)
		{
			++score2;
			ball.setPos(Vector2u(width / 2, heigth / 2));
			ball.setSpeed(8);
		}
		else if (check == 2)
		{
			++score1;
			ball.setPos(Vector2u(width / 2, heigth / 2));
			ball.setSpeed(8);
		}

		Event event;
		while (wnd.pollEvent(event))
		{
			if (event.type == Event::Closed)
				wnd.close();

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
			{//refresh
				plrPaddle.setPos(Vector2u(GAP, heigth / 2));
				aiPaddle.setPos(Vector2u(width - GAP, heigth / 2));
				ball.setPos(Vector2u(width / 2, heigth / 2));
				ball.setSpeed(8);
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				menu(wnd);
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up)
				direction = UP;
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down)
				direction = DOWN;
			else if (event.type == Event::KeyReleased)
				direction = STOP;
		}
		wnd.clear(Color::White);

		std::stringstream scr;
		scr << score1 << "\t" << score2;
		score.setString(scr.str());

		//moving ai paddle
		if ((aiPaddle.getY()) > ball.getY())
			aiPaddle.move(UP, wnd.getSize());
		else if ((aiPaddle.getY() + (aiPaddle.getLen() / 3)) < ball.getY())
			aiPaddle.move(DOWN, wnd.getSize());

		//moving player paddle
		plrPaddle.move(direction, wnd.getSize());

		//moving ball
		check = ball.updatePos(plrPaddle, aiPaddle, wnd.getSize());

		//faster music
		//theme.setPitch(0.1 * abs(ball.getSpeed()));

		wnd.draw(score);
		plrPaddle.draw();
		aiPaddle.draw();
		ball.draw();

		wnd.display();
	}

	return EXIT_SUCCESS;
}