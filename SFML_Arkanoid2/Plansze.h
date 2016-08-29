#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Plansze : public sf::Drawable
{
private:
	int zycia;
	int punkty;
	int poziom;
	sf::Font font;
	sf::Text text;
	sf::String napis;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(text);
	}

	int level[20][20];
	int levelKto[20][20];
	int bonusy[20][20];
	int ileBlokow;
	int maxX, maxY;

public:

	Plansze();
	~Plansze();
	void poziom_1();
	void poziom_2();
	void updateDane();
	void addPunkty(int);
	void addZycia(int);
	void addPoziom(int);
	int checkPlansza(int, int);
	int checkKto(int, int);
	int checkBonus(int, int);
	int checkIleBlokow();
	void napisStracilesZycie();
};

