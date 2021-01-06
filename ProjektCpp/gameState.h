#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

#include "Bunny.h"
#include "Wolf.h"

class gameState
{
private:
	// Zmianne
	float dt{ 0 };
	const sf::Vector2f bush[49] = {
		sf::Vector2f(288.f, 32.f),
		sf::Vector2f(320.f, 32.f),
		sf::Vector2f(352.f, 32.f),
		sf::Vector2f(384.f, 32.f),
		sf::Vector2f(288.f, 64.f),
		sf::Vector2f(320.f, 64.f),
		sf::Vector2f(576.f, 128.f),
		sf::Vector2f(576.f, 160.f),
		sf::Vector2f(608.f, 128.f),
		sf::Vector2f(608.f, 160.f),
		sf::Vector2f(672.f, 256.f),
		sf::Vector2f(672.f, 288.f),
		sf::Vector2f(640.f, 320.f),
		sf::Vector2f(672.f, 320.f),
		sf::Vector2f(640.f, 352.f),
		sf::Vector2f(672.f, 352.f),
		sf::Vector2f(704.f, 352.f),
		sf::Vector2f(416.f, 288.f),
		sf::Vector2f(416.f, 320.f),
		sf::Vector2f(448.f, 288.f),
		sf::Vector2f(448.f, 320.f),
		sf::Vector2f(192.f, 224.f),
		sf::Vector2f(192.f, 256.f),
		sf::Vector2f(224.f, 224.f),
		sf::Vector2f(224.f, 256.f),
		sf::Vector2f(64.f, 288.f),
		sf::Vector2f(64.f, 320.f),
		sf::Vector2f(64.f, 352.f),
		sf::Vector2f(64.f, 384.f),
		sf::Vector2f(64.f, 416.f),
		sf::Vector2f(96.f, 384.f),
		sf::Vector2f(96.f, 416.f),
		sf::Vector2f(288.f, 480.f),
		sf::Vector2f(320.f, 480.f),
		sf::Vector2f(544.f, 480.f),
		sf::Vector2f(544.f, 512.f),
		sf::Vector2f(576.f, 480.f),
		sf::Vector2f(576.f, 512.f),
		sf::Vector2f(192.f, 608.f),
		sf::Vector2f(192.f, 640.f),
		sf::Vector2f(224.f, 608.f),
		sf::Vector2f(224.f, 640.f),
		sf::Vector2f(256.f, 608.f),
		sf::Vector2f(256.f, 640.f),
		sf::Vector2f(608.f, 704.f),
		sf::Vector2f(640.f, 672.f),
		sf::Vector2f(640.f, 704.f),
		sf::Vector2f(672.f, 672.f),
		sf::Vector2f(672.f, 704.f)
	};

	// Textury
	sf::Texture bunnyTexture;
	sf::Texture wolfTexture;
	sf::Texture mapTexture;
	sf::Texture heartTexture;
	sf::Texture staminaTexture;
	sf::Sprite map;

	// Wektory
	std::vector<Bunny> lotsOfBunny;
	std::vector<Wolf> lotsOfWolfM;
	std::vector<Wolf> lotsOfWolfF;
	std::vector<Bunny> deadBunny;
	std::vector<Wolf> deadWolf;

	// Ustawienia
	unsigned int maxBunny;
	unsigned int numWolfF;
	unsigned int numWolfM;
	unsigned int numBunny;

	// Funkcje inicjalizuj¹ce
	void initMap();
	void initFile(); // czytanie z pliku
	void initOnce(); // ziarno liczb losowych
	void initBunny();
	void initWolf();

	// Funkcje prywatne
	sf::Vector2f shuffleVec(std::vector<sf::Vector2f> numVec); // miesza wektory
	sf::Vector2f SpawnPoint(bool isWolf); // losuje miejsce pojawienia sie na mapie

		// Królik
	void standardMove(Bunny* bunny); // standardowy ruch 
	void bunnyCollision(std::vector<sf::Vector2f>& moveVec); // kolizje krolikow
	void isHidden(Bunny* bunny); // sorawdza czy krolik jest w krzakach
	void bunnyDie(int i); // usuwa krolika
	void newBunny(sf::Vector2f posXY); // tworzy nowego krolika
	void updateBunny(Bunny* bunny); // aktualizuje krolika
	
		// Wilk
	void standardMove(Wolf* wolf); // standardowy ruch
	void wolfCollision(std::vector<sf::Vector2f>& moveVec, bool isMale); // kolizje wilkow
	void wolfEvadeBush(std::vector<sf::Vector2f>& moveVec); // kolizje wilkow/wilczyc z krzakami
	bool followBunny(Wolf* wolf); // podazanie za krolikiem
	bool followWolf(Wolf* wolf); // podazanie za wilczyca
	void eatBunny(Wolf* wolf); // sprawdza czy jest krolik do zjedzenia
	void babyWolf(Wolf* wolf); // sprawdza czy pojawi sie nowy wilk/wilczyca
	bool wolfDie(Wolf* wolf, int i); // sprawdza czy umrze wilk/wilczyca
	void newWolf(sf::Vector2f posXY, int isMale); // tworzy nowego wilka
	void updateWolf(Wolf* wolf, int i); // aktualizuje wilka/wilczyce
	
public:
	// Konstruktor/Destruktor
	gameState();
	~gameState();

	// Funkcje publiczne
	void update(float dt); //aktualizuje wszystko
	void render(sf::RenderTarget* window); // rysuje wszystko
};