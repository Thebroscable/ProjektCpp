#include "Wolf.h"

// Funkcje prywatne
void Wolf::renderPosition()
{
    // pozycja pojawiania siê na mapie
    if (this->wolf.getPosition().x - this->wolfPos.x > 0)
        wolf.move(sf::Vector2f(-2.f, 0.f));
    else if (this->wolf.getPosition().x - this->wolfPos.x < 0)
        wolf.move(sf::Vector2f(2.f, 0.f));

    if (this->wolf.getPosition().y - this->wolfPos.y > 0)
        wolf.move(sf::Vector2f(0.f, -2.f));
    else if (this->wolf.getPosition().y - this->wolfPos.y < 0)
        wolf.move(sf::Vector2f(0.f, 2.f));
}

void Wolf::updateStats()
{
    // ustawianie po³o¿enia statystyk
    for (int i = 0; i < 10; i++) 
    {
        if (i < 5)
        {
            this->heart[i].setPosition(sf::Vector2f(this->wolf.getPosition().x + 6.f + 4.f * i, this->wolf.getPosition().y + 1));
        }
        else
        {
            this->heart[i].setPosition(sf::Vector2f(this->wolf.getPosition().x + 8.f + 4.f * (i-5), this->wolf.getPosition().y + 4));
        }
    }
    for (int i = 0; i < 3; i++)
    {
        this->stamina[i].setPosition(sf::Vector2f(this->wolf.getPosition().x + 17.f + 3.f * i, this->wolf.getPosition().y + 7));
    }
}

// Konstruktor
Wolf::Wolf(sf::Vector2f posXY, bool ismale, sf::Texture* wolfTx, sf::Texture* heartTx, sf::Texture* staminaTx)
{
    this->isMale = ismale;

    // textury
    this->wolf.setTexture(*wolfTx);
    for (int i = 0; i < 10; i++)
    {
        this->heart[i].setTexture(*heartTx);
    }
    for (int i = 0; i < 3; i++)
    {
        this->stamina[i].setTexture(*staminaTx);
    }
    
    // wybieranie koloru
    this->wolf.setColor(sf::Color::Transparent);

    this->wolf.setPosition(posXY);
    this->wolfPos = posXY;
}

// Funkcje dostêpu
sf::Vector2f Wolf::getPos()
{
    return this->wolfPos;
}

sf::Vector2f Wolf::getOldPos()
{
    return this->wolfOldPos;
}

void Wolf::updateFat(int number)
{
    this->fat += number;
    if (this->fat > 10)
        this->fat = 10;
    else if (this->fat < 0)
        this->fat = 0;
}

int Wolf::getFat()
{
    return this->fat;
}

int Wolf::getTired()
{
    return this->tired;
}

void Wolf::resetTired()
{
    this->tired = 3;
}

void Wolf::downTired()
{
    if (this->tired >= 1)
        this->tired -= 1;
}

bool Wolf::getGender()
{
    return this->isMale;
}

void Wolf::setColor()
{
    if (this->isMale)
        this->wolf.setColor(sf::Color(100, 100, 100));
    else
        this->wolf.setColor(sf::Color(200, 200, 200));
}

// Funkcje publiczne
    // zmiana pozycji wilka
void Wolf::wolfMove(sf::Vector2f posXY)
{
    // zmiana polozenia
    this->wolfOldPos = this->wolfPos;
    this->wolfPos = posXY;
}

    // rysowanie wilka
void Wolf::render(sf::RenderTarget* target)
{
    // ustawianie wilka w ruchu
    this->renderPosition();

    // rysowanie wilka
    target->draw(this->wolf);

    // rysowanie statystyk
    this->updateStats();

    for (int i = 0; i < this->fat; i++)
        target->draw(heart[i]);

    for (int i = 0; i < this->tired; i++)
        target->draw(stamina[i]);
}