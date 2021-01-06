#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>

class menuState
{
private:
	// Zmienne
	sf::Texture titleTexture;
	sf::Texture startTexture;
	sf::Texture startHTexture;
	sf::Texture optionTexture;
	sf::Texture optionHTexture;
	sf::Texture infoTexture;
	sf::Sprite title;
	sf::Sprite start;
	sf::Sprite startH;
	sf::Sprite option;
	sf::Sprite optionH;
	sf::Sprite info;

	// Funkcje prywatne
	void initSprites();
	bool hoverButton1(sf::Vector2i mousePos);
	bool hoverButton2(sf::Vector2i mousePos);

public:
	// Konstruktor
	menuState();

	// Funkcje publiczne
	bool clickedButton1(sf::Vector2i mousePos);
	bool clickedButton2(sf::Vector2i mousePos);
	void render(sf::RenderTarget* window, sf::Vector2i mousePos);
};

