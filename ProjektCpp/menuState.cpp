#include "menuState.h"

// Funkcje prywatne
	// wczytanie textur i spritów
void menuState::initSprites()
{
	// ³adowanie textur i ustawianie pozycji
	this->titleTexture.loadFromFile("Textures/title.png");
	this->startTexture.loadFromFile("Textures/start.png");
	this->startHTexture.loadFromFile("Textures/startH.png");
	this->optionTexture.loadFromFile("Textures/option.png");
	this->optionHTexture.loadFromFile("Textures/optionH.png");
	this->infoTexture.loadFromFile("Textures/info.png");

	this->title.setPosition(sf::Vector2f(0.f, 0.f));
	this->title.setTexture(this->titleTexture);

	this->start.setPosition(sf::Vector2f(200.f, 300.f));
	this->start.setTexture(this->startTexture);

	this->startH.setPosition(sf::Vector2f(200.f, 300.f));
	this->startH.setTexture(this->startHTexture);

	this->option.setPosition(sf::Vector2f(200.f, 550.f));
	this->option.setTexture(this->optionTexture);

	this->optionH.setPosition(sf::Vector2f(200.f, 550.f));
	this->optionH.setTexture(this->optionHTexture);

	this->info.setPosition(sf::Vector2f(750.f, 750.f));
	this->info.setTexture(this->infoTexture);
}

	// sprawdz czy mysz znajduje siê na guziku
bool menuState::hoverButton1(sf::Vector2i mousePos)
{
	if (mousePos.x > 200 && mousePos.x < 600)
		if (mousePos.y > 300 && mousePos.y < 500)
			return true;

	return false;
}

bool menuState::hoverButton2(sf::Vector2i mousePos)
{
	if (mousePos.x > 200 && mousePos.x < 600)
		if (mousePos.y > 550 && mousePos.y < 750)
			return true;

	return false;
}

// Konstruktor
menuState::menuState()
{
	this->initSprites();
}

// Funkcje publiczne
	// Sprawdza czy przycisk myszy zosta³ wciœniety na guziku
bool menuState::clickedButton1(sf::Vector2i mousePos)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (this->hoverButton1(mousePos))
			return true;

	return false;
}

bool menuState::clickedButton2(sf::Vector2i mousePos)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (this->hoverButton2(mousePos))
			return true;

	return false;
}

	// funkcja rysuj¹ca
void menuState::render(sf::RenderTarget* window, sf::Vector2i mousePos)
{
	// ustawia szare t³o
	window->clear(sf::Color(50, 50, 50));

	// rysuje tytu³
	window->draw(this->title);

	// rysuje info
	window->draw(this->info);

	// rysuje guziki
	if (this->hoverButton1(mousePos))
		window->draw(this->startH);
	else
		window->draw(this->start);

	if (this->hoverButton2(mousePos))
		window->draw(this->optionH);
	else
		window->draw(this->option);
}
