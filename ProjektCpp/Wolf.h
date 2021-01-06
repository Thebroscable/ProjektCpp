#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>

class Wolf
{
private:
	// Zmienne
	int fat{ 10 };
	bool isMale;
	int tired{ 3 };

	// SFML
	sf::Vector2f wolfPos;
	sf::Vector2f wolfOldPos;
	sf::Sprite wolf;
	sf::Sprite heart[10];
	sf::Sprite stamina[3];

	// Funkcje prywatne
	void renderPosition();
	void updateStats();

public:
	// Konstruktor
	Wolf(sf::Vector2f posXY, bool ismale, sf::Texture* wolfTx, sf::Texture* heartTx, sf::Texture* staminaTx);

	// Funkcje dostêpu
	sf::Vector2f getPos();
	sf::Vector2f getOldPos();
	void updateFat(int number);
	int getFat();
	int getTired();
	void resetTired();
	void downTired();
	bool getGender();

	// Funkcje publiczne
	void setColor();
	void wolfMove(sf::Vector2f posXY);
	void render(sf::RenderTarget* target);
};