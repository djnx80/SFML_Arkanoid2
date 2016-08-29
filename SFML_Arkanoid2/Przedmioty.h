#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Przedmioty : public sf::Drawable
{

private:
	sf::Texture textura;
	sf::Sprite klatkaAnim[16];
	int ileKlatekAnim;
	int aktualnaKlatkaAnim;
	int szerokoscSprite;
	int wysokoscSprite;
	int minX, maxX;
	int minY, maxY;		// min i maxymalne wartosci na ktore moze sie przemieszczac sprajt
	int x, y;
	int dx, dy;
	bool aktywne;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (aktywne == true)
			target.draw(klatkaAnim[aktualnaKlatkaAnim]);
	}

public:
	Przedmioty();
	~Przedmioty();
	
	void pokazDane();
	void setPozycje(int, int);
	bool wczytajTeksture(sf::String);
	sf::Texture getTeksture();
	void setTeksture(sf::Texture);
	sf::Sprite getSprite();
	void getSprites(int, int, int, int, int);
	void updateMe();
	void setAktywne(bool);
	bool czyAktywne();
	void porusz(int, int);
	void setDXY(int, int);
	int getX();
	int getY();
	int getDX();
	int getDY();

	int getSzerokoscSprita();
	int getWysokoscSprita();
};

