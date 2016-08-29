#include "stdafx.h"
#include "Plansze.h"


Plansze::Plansze()	{
	zycia = 5;
	punkty = 0;
	poziom = 1;
	if (!font.loadFromFile("BornAddict.ttf"))
	{
		cout << "Nie udalo sie wczytac czcionki" << endl;
	}


	// wybranie czcionki
	text.setFont(font);
	text.setCharacterSize(24); // w pikselach, nie punktach!
	text.setColor(sf::Color::Blue);

	napis = "";
	text.setString(napis);

}
Plansze::~Plansze()	{	}

void Plansze::updateDane() {
	napis = "    Zycia " + to_string(zycia) + "    Punkty " + to_string(punkty) + "    Poziom " + to_string(poziom);
	text.setString(napis);
	text.setPosition(0, 0);
}

void Plansze::napisStracilesZycie() {
	napis = "Straciles Zycie!";
	text.setString(napis);
	text.setPosition(200, 300);
}

int Plansze::checkPlansza(int x, int y) {
	return level[x][y];
}

int Plansze::checkKto(int x, int y) {
	return levelKto[x][y];
}
int Plansze::checkIleBlokow() { return ileBlokow; }
int Plansze::checkBonus(int x, int y) {
	return bonusy[x][y];
}
void Plansze::poziom_1() {
	ileBlokow = 0;
	maxX = 13;
	maxY = 6;
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 6; j++) {
			level[i][j] = 2;
			levelKto[i][j] = ileBlokow;
			ileBlokow++;
		}
	}
}


void Plansze::poziom_2() {
	ileBlokow = 0;
	maxX = 13;
	maxY = 6;
	int liczba;

	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 6; j++) {
			liczba = (rand() % 3) + 2;
			level[i][j] = liczba;
			levelKto[i][j] = ileBlokow;
			ileBlokow++;
			liczba = (rand() % 3) + 1;
			bonusy[i][j] = liczba;
//			bonusy[i][j] = 2;
		}
	}
}


void Plansze::addPoziom(int ile) { poziom = poziom + ile; }
void Plansze::addZycia(int ile) { zycia = zycia + ile; }
void Plansze::addPunkty(int ile) { punkty = punkty + ile; }
