#include "Bunny.h"

void Bunny::renderPosition()
{
    // ustawianie pozycji rysowania krolika
    if (this->bunny.getPosition().x - this->bunnyPos.x > 0)
        bunny.move(sf::Vector2f(-2.f, 0.f));
    else if (this->bunny.getPosition().x - this->bunnyPos.x < 0)
        bunny.move(sf::Vector2f(2.f, 0.f));

    if (this->bunny.getPosition().y - this->bunnyPos.y > 0)
        bunny.move(sf::Vector2f(0.f, -2.f));
    else if (this->bunny.getPosition().y - this->bunnyPos.y < 0)
        bunny.move(sf::Vector2f(0.f, 2.f));
}

// Konstruktor
Bunny::Bunny(sf::Vector2f posXY, sf::Texture* bunnyTx)
{
    // ustawianie pozycji i textur krolika
    this->bunny.setTexture(*bunnyTx);
    this->bunny.setPosition(posXY);
    this->bunnyPos = posXY;
}

// Funkcje dostêpu
sf::Vector2f Bunny::getPos()
{
    return this->bunnyPos;
}

sf::Vector2f Bunny::getOldPos()
{
    return this->bunnyOldPos;
}

void Bunny::setHidden(bool hidden)
{
    // ustawianie koloru
    this->isHidden = hidden;
    if (hidden)
        bunny.setColor(sf::Color(255, 255, 255, 128));
    else
        bunny.setColor(sf::Color::White);
}

bool Bunny::getHidden()
{
    return this->isHidden;
}

void Bunny::setDead(bool dead)
{
    this->isDead = dead;
}

bool Bunny::getDead()
{
    return this->isDead;
}

// Funkcje publiczne
    // Zmiana pozycji królika
void Bunny::bunnyMove(sf::Vector2f posXY)
{
    // zmiana pozycji
    this->bunnyOldPos = this->bunnyPos;
    this->bunnyPos = posXY;
}

    // Rysowanie królika
void Bunny::render(sf::RenderTarget* target)
{
    // jeœli martwy to znika
    if (this->isDead && (this->bunny.getPosition() == this->bunnyPos))
        this->bunny.setColor(sf::Color::Transparent);

    // rysowanie
    this->renderPosition();
    target->draw(this->bunny);
}