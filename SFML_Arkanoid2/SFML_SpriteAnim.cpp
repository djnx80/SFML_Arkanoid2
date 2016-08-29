#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Przedmioty.h"

using namespace std;

int main()
{
	sf::RenderWindow okno(sf::VideoMode(800, 600), "Okno");
	okno.setVerticalSyncEnabled(true);	// 60fps
	Przedmioty moneta;
	Przedmioty moneta2;

	if (moneta.wczytajTeksture("breakout_sprites.png") == false)	return -1;
	moneta.getSprites(0, 375, 24, 25,16);
	moneta.setPozycje(50, 50);

	if (moneta2.wczytajTeksture("breakout_sprites.png") == false)	return -1;
	moneta2.getSprites(0, 375, 24, 25, 16);
	moneta2.setPozycje(150, 50);

	while (okno.isOpen())
	{
		sf::Event event;
		while (okno.pollEvent(event))	{
			if (event.type == sf::Event::Closed)	okno.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))	okno.close();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))		moneta.porusz(-3,0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	moneta.porusz(3,0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))		moneta.porusz(0, -3);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))		moneta.porusz(0, 3);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))		moneta2.setDXY(1, 1);


		okno.clear();
		okno.draw(moneta);
		okno.draw(moneta2);

		moneta.updateMe();
		moneta2.updateMe();
		okno.display();
	}
	return 0;
}

