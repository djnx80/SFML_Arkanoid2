#include "stdafx.h"
#include "Przedmioty.h"


Przedmioty::Przedmioty()	{
	x = 100;
	y = 100;
	aktywne = false;
	dx = 0;
	dy = 0;
	minX = 0;
	minY = 0;
	maxX = 800;
	maxY = 700;
	ileKlatekAnim = 1;
	aktualnaKlatkaAnim = 0;
	szerokoscSprite = 10;
	wysokoscSprite = 10;
}
Przedmioty::~Przedmioty()	{}

void Przedmioty::pokazDane() {
	cout << "x:" << x << " y:" << y<<"  aktywne:"<<aktywne << endl;
}

void Przedmioty::setAktywne(bool czyAktywne) {
	aktywne = czyAktywne;
}
void Przedmioty::updateMe() {
	if (ileKlatekAnim > 1) {
		aktualnaKlatkaAnim++;
		if (aktualnaKlatkaAnim >= ileKlatekAnim)	aktualnaKlatkaAnim = 0;
	}

	x = x + dx;
	y = y + dy;
	if (x < minX) {
		x = minX;
		dx = -dx;
	}
	if (x > maxX - szerokoscSprite) {
		x = maxX - szerokoscSprite;
		dx = -dx;
	}
	if (y < minY) {
		y = minY;
		dy = -dy;
	}
	if (y > maxY - wysokoscSprite) {
		y = maxY - wysokoscSprite;
		dy = -dy;
	}

	for (int i = 0; i<ileKlatekAnim; i++)
		klatkaAnim[i].setPosition(x, y);
}

void Przedmioty::setPozycje(int nx, int ny) {
	x = nx;
	y = ny;
}
void Przedmioty::getSprites(int startx, int starty, int szer, int wys, int ile) {
	ileKlatekAnim = ile;
	aktualnaKlatkaAnim = 0;
	for (int i = 0; i < ile; i++) {
		klatkaAnim[i].setTextureRect(sf::IntRect(startx+(i * szer), starty, szer, wys));
		klatkaAnim[i].setTexture(textura);
	}

	szerokoscSprite = szer;
	wysokoscSprite = wys;
	aktywne = true;
}

sf::Texture Przedmioty::getTeksture() {
	return textura;
}

void Przedmioty::setTeksture(sf::Texture tekstur) {
	sf::Image tempimg;
	tempimg = tekstur.copyToImage();
	textura.loadFromImage(tempimg);
}
sf::Sprite Przedmioty::getSprite() {
	return klatkaAnim[aktualnaKlatkaAnim];
}

bool Przedmioty::wczytajTeksture(sf::String filename) {

	sf::Image img;
	if (!img.loadFromFile(filename))
	{
		cout << "Nie wczytalem tekstury z " << endl;
		getchar();
		return false;
	}

	img.createMaskFromColor(sf::Color::White);

	textura.loadFromImage(img);
	textura.setSmooth(true);
	return true;
}

void Przedmioty::porusz(int tx, int ty) {
	x = x + tx;
	y = y + ty;
}

bool Przedmioty::czyAktywne() {
	return aktywne;
}
void Przedmioty::setDXY(int tx, int ty) {
	if (tx == -100) {
		dx = -dx;
	} else if (tx == 100)	{
		dx = dx;
	}	else {
		dx = tx;
	}

	if (ty == -100) {
		dy = -dy;
	}
	else if (ty == 100) {
		dy = dy;
	}	else {
		dy = ty;
	}
}

int Przedmioty::getX() { return x; }
int Przedmioty::getY() { return y; }
int Przedmioty::getDX() { return dx; }
int Przedmioty::getDY() { return dy; }
int Przedmioty::getSzerokoscSprita() { return szerokoscSprite; }
int Przedmioty::getWysokoscSprita() { return wysokoscSprite; }