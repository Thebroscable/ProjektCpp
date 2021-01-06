#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>

class Bunny
{
private:
	// Zmienne
	sf::Sprite bunny;
	sf::Vector2f bunnyPos;
	sf::Vector2f bunnyOldPos;
	bool isHidden{ false };
	bool isDead{ false };

	// Funkcje prywatne
	void renderPosition();

public:
	// Konstruktor
	Bunny(sf::Vector2f posXY, sf::Texture* bunnyTx);

	// Funkcje dostêpu
	sf::Vector2f getPos();
	sf::Vector2f getOldPos();
	void setHidden(bool hidden);
	bool getHidden();
	bool getDead();
	void setDead(bool dead);

	// Funkcje publiczne
	void bunnyMove(sf::Vector2f posXY);
	void render(sf::RenderTarget* target);
};