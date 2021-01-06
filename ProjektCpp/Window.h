#pragma once

#include "gameState.h"
#include "menuState.h"

class Window
{
private:
	// Zmienne
	int states{1};
	sf::Vector2i mousePos;

	sf::RenderWindow *window;
	sf::Event gEvent;

	sf::Clock dtClock;
	float dt;

	gameState* gState;
	menuState* mState;

	// Funkcje inicjalizujace
	void initWindow();

public:
	// Konstruktor / Destruktor
	Window();
	~Window();

	// Funkcje dostepu
	bool windowIsOpen();

	// Funkcje
	void updateSFMLEvent();
	void updateStates();
	void updateDt();
	void update();
	void render();
};