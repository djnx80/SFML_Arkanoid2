#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Przedmioty.h"
#include "Plansze.h"

using namespace std;

void odswiezWidok();
void sprawdzKolizjeZPaletka();
void sprawdzKolizjeZBlokami();
bool pobierzoObiekty();
void sprawdzCzyObiektNaDnieEkranu();
void czyCzekaszNaPrzycisk();
void sprawdzKolizjeZBonusami();

int ileMonet = 15;
int ileGwiazdek = 15;
int ktoraMoneta = 0;
bool czekajNaPrzycisk = false;

sf::RenderWindow okno;
sf::Image tlo;
sf::Texture tlotext;
sf::Sprite tlospr;
Przedmioty monety[20];
Przedmioty gwiazdki[20];	// mozna dodac kolejny bonus
Przedmioty pilka;
Przedmioty blok[100];
Przedmioty paletka;
Przedmioty sciana;
Plansze moja_plansza;



bool isCollide(sf::Sprite s1, sf::Sprite s2) {
//	cout << "s1: "<< s1.getGlobalBounds().left << "   "<< s1.getGlobalBounds().top<<endl;
//	cout << "s2: "<< s2.getGlobalBounds().left << "   " << s2.getGlobalBounds().top << endl;
	return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}

int main()
{
	okno.create(sf::VideoMode(800, 600), "Okno");
	okno.setVerticalSyncEnabled(true);	// 60fps
	tlo.loadFromFile("img/background.jpg");
	moja_plansza.poziom_2();
	pobierzoObiekty();
	odswiezWidok();

	while (okno.isOpen())
	{
		sf::Event event;
		while (okno.pollEvent(event)) {
			if (event.type == sf::Event::Closed)	okno.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))	okno.close();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))		paletka.porusz(-8, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	paletka.porusz(8, 0);

		sprawdzKolizjeZBlokami();
		sprawdzKolizjeZPaletka();
		sprawdzKolizjeZBonusami();
		sprawdzCzyObiektNaDnieEkranu();
		czyCzekaszNaPrzycisk();

		moja_plansza.updateDane();
		odswiezWidok();
	}
	return 0;
}

void odswiezWidok() {
	okno.clear();

	for (int i = 0; i < ileMonet; i++) {
		monety[i].updateMe();
	}
	pilka.updateMe();
	paletka.updateMe();

	tlotext.loadFromImage(tlo);
	tlospr.setTexture(tlotext);

	okno.draw(tlospr);
	okno.draw(pilka);
	okno.draw(paletka);
	okno.draw(moja_plansza);

	for (int i = 0; i < ileMonet; i++) {
		okno.draw(monety[i]);
	}
	for (int i = 0; i < moja_plansza.checkIleBlokow(); i++) {
		blok[i].updateMe();
		okno.draw(blok[i]);
	}


	okno.display();
}
void sprawdzCzyObiektNaDnieEkranu() {
	// sprawdz czy przedmioty osiagnely spod ekranu
	if (pilka.getY() > 570) {
		moja_plansza.addZycia(-1);
		pilka.setPozycje(400, 530);
		pilka.setDXY(0, 0);
		paletka.setPozycje(350, 550);
		czekajNaPrzycisk = true;
	}
	for (int i = 0; i < ileMonet; i++) {
		if (monety[i].getY() > 580) {
			monety[i].setDXY(0, 0);
			monety[i].setAktywne(false);
		}
	}
}
void czyCzekaszNaPrzycisk() {
	if (czekajNaPrzycisk == true) {
		bool wcisnales = false;
		moja_plansza.napisStracilesZycie();
		do {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
				wcisnales = true;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				paletka.porusz(-6, 0);
				pilka.porusz(-6, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				paletka.porusz(6, 0);
				pilka.porusz(6, 0);
			}
			odswiezWidok();
		} while (wcisnales == false);
		czekajNaPrzycisk = false;
		pilka.setDXY(5, -8);
	}
}

void sprawdzKolizjeZBonusami() {
	for (int i = 0; i < ileMonet; i++) {
		if (monety[i].czyAktywne() == true) {
			if (isCollide(paletka.getSprite(), monety[i].getSprite())) {
				monety[i].setAktywne(false);
				moja_plansza.addPunkty(2200);
			}
		}
	}

}
void sprawdzKolizjeZBlokami() {
	for (int i = 0; i < moja_plansza.checkIleBlokow(); i++) {
		if (blok[i].czyAktywne() == true) {
			if (isCollide(pilka.getSprite(), blok[i].getSprite())) {
				blok[i].setAktywne(false);
				pilka.setDXY(-100, -100);
				pilka.updateMe();
				moja_plansza.addPunkty(500);

				int tempx = pilka.getX();
				int tempy = pilka.getY();
				int szer = blok[i].getSzerokoscSprita();
				int wys = blok[i].getWysokoscSprita();
				int tx = (tempx / szer);
				int ty = (tempy / wys) - 2;
				cout << "tx:" << tx << "  ty:" << ty << endl;
				//					getchar();
				if (moja_plansza.checkBonus(tx, ty) == 2) {
					monety[ktoraMoneta].setPozycje(tempx, tempy);
					monety[ktoraMoneta].setDXY(0, 3);
					monety[ktoraMoneta].setAktywne(true);
					ktoraMoneta++;
					if (ktoraMoneta > ileMonet - 1)
						ktoraMoneta = 0;
				}

			}
		}
	}
}

bool pobierzoObiekty() {
	for (int i = 0; i < ileMonet; i++) {
		if (monety[i].wczytajTeksture("breakout_sprites.png") == false)	return false;
		monety[i].getSprites(0, 375, 24, 25, 15);
		monety[i].setAktywne(false);
	}

	if (paletka.wczytajTeksture("breakout_sprites.png") == false)	return false;
	paletka.getSprites(0, 240, 120, 30, 1);
	paletka.setPozycje(350, 550);
	if (sciana.wczytajTeksture("breakout_sprites.png") == false)	return false;
	sciana.getSprites(320, 80, 30, 30, 1);
	if (pilka.wczytajTeksture("breakout_sprites.png") == false)	return false;
	pilka.getSprites(160, 200, 17, 17, 1);
	pilka.setPozycje(400, 530);
	pilka.setDXY(5, -8);
	paletka.setPozycje(350, 550);



	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 6; j++) {
			if (moja_plansza.checkPlansza(i, j) == 2) {
				int nr = moja_plansza.checkKto(i, j);
				if (blok[nr].wczytajTeksture("img/brick_blue_small.png") == false)	return -1;
				blok[nr].getSprites(0, 0, 58, 26, 1);
				blok[nr].setPozycje(16 + (i * 59), 35 + (j * 27));
			}
			if (moja_plansza.checkPlansza(i, j) == 3) {
				int nr = moja_plansza.checkKto(i, j);
				if (blok[nr].wczytajTeksture("img/brick_green_small.png") == false)	return -1;
				blok[nr].getSprites(0, 0, 58, 26, 1);
				blok[nr].setPozycje(16 + (i * 59), 35 + (j * 27));
			}
			if (moja_plansza.checkPlansza(i, j) == 4) {
				int nr = moja_plansza.checkKto(i, j);
				if (blok[nr].wczytajTeksture("img/brick_pink_small.png") == false)	return -1;
				blok[nr].getSprites(0, 0, 58, 26, 1);
				blok[nr].setPozycje(16 + (i * 59), 35 + (j * 27));
			}

		}
	}
	return true;
}
void sprawdzKolizjeZPaletka() {
	// aby sprawdzic czy zostaly jakies bloki na plaszny trzeba sprawdzic czy sa jakies aktywne 
	if (isCollide(pilka.getSprite(), paletka.getSprite())) {
		// trzeba sprawdzic w krora czesc paletki uderzyla pilka
		int pilkax = pilka.getX();
		int pilkay = pilka.getY();
		int paletkax = paletka.getX();
		int paletkay = paletka.getY();
		int roznicax = pilkax - paletkax;
		int roznicay = pilkay - paletkay;
		int szerokoscPaletki = paletka.getSzerokoscSprita();
		int kierunekx = pilka.getDX();
		if (kierunekx < 0) {
			kierunekx = -1;
		}
		else
		{
			kierunekx = 1;
		}

		if (roznicax <= 0) {
			cout << " Uderzyles w lewa krawedz" << endl;
			pilka.setDXY(8 * -kierunekx, -100);
		}
		else if (roznicax > 0 && roznicax <= szerokoscPaletki / 4) {
			cout << " Uderzyles w lewa  skrajna cwiartke krawedz" << endl;
			pilka.setDXY(6 * kierunekx, -100);
		}
		else if (roznicax > szerokoscPaletki / 4 && roznicax<szerokoscPaletki / 2) {
			cout << " Uderzyles w lewa  srodkowa cwiartke krawedz" << endl;
			pilka.setDXY(3 * kierunekx, -100);

		}
		else if (roznicax == szerokoscPaletki / 2) {
			cout << " Uderzyles w sam srodek paletki" << endl;
			pilka.setDXY(1 * kierunekx, -100);

		}
		else if (roznicax > szerokoscPaletki / 2 && roznicax <= szerokoscPaletki * 0.75) {
			cout << " Uderzyles w prawa  srodkowa cwiartke krawedz" << endl;
			pilka.setDXY(3 * kierunekx, -100);

		}
		else if (roznicax > szerokoscPaletki * 0.75 && roznicax < szerokoscPaletki) {
			cout << " Uderzyles w prawa  skrajna cwiartke krawedz" << endl;
			pilka.setDXY(6 * kierunekx, -100);

		}
		else if (roznicax >= szerokoscPaletki) {
			cout << " Uderzyles w prawa krawedz" << endl;
			pilka.setDXY(8 * -kierunekx, -100);
		}


		cout << "x:" << pilkax << " y:" << pilkay << "   px:" << paletkax << " py:" << paletkay << "    dx:" << roznicax << " dy:" << roznicay << endl;
		pilka.updateMe();
	}
}

void sortujMonety() {

}