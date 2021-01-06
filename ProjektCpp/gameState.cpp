#include "gameState.h"

// Funkcje inicjalizuj¹ce
void gameState::initMap()
{
    // inicjalizacja mapy
    this->mapTexture.loadFromFile("Textures/map.png");
    this->map.setTexture(this->mapTexture);
    this->map.setPosition(sf::Vector2f(0.f, 0.f));
}

void gameState::initFile()
{
    // czytanie ustawien z pliku
   std::ifstream fopen("Config/window.ini");
   if (fopen.is_open())
   {
       std::string line;
       while (getline(fopen, line))
       {
           if (line[0] == '#' || line.empty())
               continue;
           line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
           auto delimiterPos = line.find("=");
           int id = std::stoi(line.substr(0, 1));
           unsigned int value = std::stoi(line.substr(delimiterPos + 1));
           switch (id) 
           {
           case 1:
               if (value > 325 || value < 2)
                   this->maxBunny = 325;
               else
                   this->maxBunny = value;
               break;
           case 2:
               if (value > 20 || value < 1)
                   this->numWolfF = 20;
               else
                   this->numWolfF = value;
               break;
           case 3:
               if (value > 20 || value < 1)
                   this->numWolfM = 20;
               else
                   this->numWolfM = value;
               break;
           case 4:
               if (value > 20 || value < 1)
                   this->numBunny = 20;
               else
                   this->numBunny = value;
               break;
           default:
               break;
           }
       }
   }
   else
   {
       // standardowe ustawienie gdy nie ma pliku
       this->maxBunny = 325;
       this->numWolfF = 2;
       this->numWolfM = 2;
       this->numBunny = 10;
   }
   fopen.close();
}

void gameState::initOnce()
{
    // ziarno liczb losowych 
    std::srand((unsigned)std::time(NULL));
}

void gameState::initBunny()
{
    // textury
    this->bunnyTexture.loadFromFile("Textures/bunny.png");
    
    // dodawanie krolikow
    for (unsigned int i = 0; i < this->numBunny; i++)
    {
        this->newBunny(this->SpawnPoint(false));
    }
}

void gameState::initWolf()
{
    // textury
    this->wolfTexture.loadFromFile("Textures/wolf.png");
    this->heartTexture.loadFromFile("Textures/heart.png");
    this->staminaTexture.loadFromFile("Textures/stamina.png");

    // dodawanie wilków i wilczyc
    for (unsigned int i = 0; i < this->numWolfF; i++)
    {
        this->newWolf(this->SpawnPoint(true), 0);
    }
    for (unsigned int i = 0; i < this->numWolfM; i++)
    {
        this->newWolf(this->SpawnPoint(true), 1);
    }
}

// Funkcje prywatne
sf::Vector2f gameState::shuffleVec(std::vector<sf::Vector2f> numVec)
{
    sf::Vector2f temp;
    int randIndex = 0;
    int len = numVec.size();

    // mieszanie wektora
    for (int i = 0; i < len; i++)
    {
        randIndex = std::rand() % len;
        temp = numVec[i];
        numVec[i] = numVec[randIndex];
        numVec[randIndex] = temp;
    }

    return numVec[0];
}

sf::Vector2f gameState::SpawnPoint(bool isWolf)
{
    std::vector<sf::Vector2f> temp;
    
    while (true)
    {
        // losowanie po³o¿enia
        temp.push_back(sf::Vector2f());
        temp[0].x = (float)(((std::rand() % 23) + 1) * 32);
        temp[0].y = (float)(((std::rand() % 23) + 1) * 32);
        
        // wilk nie mo¿e staæ w krzakach
        if (isWolf)
        {
            this->wolfEvadeBush(temp);
        }
        
        // unikanie zajêtych miejsc
        this->bunnyCollision(temp);
        this->wolfCollision(temp, 0);
        this->wolfCollision(temp, 1);
        
        // powtórzenie jeœli wybrane zosta³o z³e miejsce lub koniec
        if (temp.empty())
        {
            continue;
        }
        else
        {
            return temp[0];
        }     
    }
}

    // Królik
void gameState::standardMove(Bunny* bunny)
{
    sf::Vector2f posXY = bunny->getPos();
    sf::Vector2f temp;
    std::vector<sf::Vector2f> moveVec;
    const float arrayP[3] = { -32.f, 32.f, 0.f };

    // tworzy liste rochow
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            temp.x = arrayP[i] + posXY.x;
            temp.y = arrayP[j] + posXY.y;

            if (temp.x > 0.f && temp.y > 0.f && temp.x < 768.f && temp.y < 768.f)
                moveVec.push_back(temp);
        }

    // usuwa ruch 0,0
    moveVec.pop_back();

    // kolizje w krolikami
    this->bunnyCollision(moveVec);

    // jesli nie ma ruchu dodaje stanie miejscu 0,0
    if (moveVec.empty())
        moveVec.push_back(posXY);

    // losowanie ruchu i przemiszczenie
    temp = this->shuffleVec(moveVec);
    bunny->bunnyMove(temp);
}

void gameState::bunnyCollision(std::vector<sf::Vector2f>& moveVec)
{
    for (unsigned int i = 0; i < this->lotsOfBunny.size(); i++)
        for (unsigned int j = 0; j < moveVec.size(); j++)
            if (this->lotsOfBunny[i].getPos() == moveVec[j])
            {
                // usuwa ruchy na krórych znajduje sie krolik
                moveVec.erase(moveVec.begin() + j);
                break;
            }
}

void gameState::isHidden(Bunny* bunny)
{
    bunny->setHidden(false);
    sf::Vector2f posXY = bunny->getPos();

    // sprawdza czy krolik jest w krzakach
    for (int i = 0; i < 49; i++)
        if (this->bush[i] == posXY)
            bunny->setHidden(true);
}

void gameState::bunnyDie(int i)
{
    this->lotsOfBunny[i].setDead(true); // ustawia status na martwego
    this->deadBunny.push_back(this->lotsOfBunny[i]); // dodaje do listy martwych krolikow
    this->lotsOfBunny.erase(this->lotsOfBunny.begin() + i);
}

void gameState::newBunny(sf::Vector2f posXY)
{
    Bunny bunny(posXY, &this->bunnyTexture); // nowy krolik
    this->isHidden(&bunny); // sprawdza czy jest ukryty
    this->lotsOfBunny.push_back(bunny);
}

void gameState::updateBunny(Bunny* bunny)
{
    // zapisuje po³o¿enie królika i status przed ruchem
    sf::Vector2f oldPos = bunny->getPos();

    // wykonuje ruch i sprawdza status
    this->standardMove(bunny);
    this->isHidden(bunny);

    // sprawdza czy mo¿e powstaæ nowy królik i go tworzy 20% szans
    if ((this->lotsOfBunny.size() < maxBunny) && (bunny->getPos() != oldPos))
        if (std::rand() % 5 == 4)
            this->newBunny(oldPos);
}


    // Wilk
void gameState::standardMove(Wolf* wolf)
{
    sf::Vector2f posXY = wolf->getPos();
    sf::Vector2f temp;
    std::vector<sf::Vector2f> moveVec;
    const float arrayP[3] = { -32.f, 32.f, 0.f };

    // przygotowywuje liste rochow
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            temp.x = arrayP[i] + posXY.x;
            temp.y = arrayP[j] + posXY.y;

            if (temp.x > 0.f && temp.y > 0.f && temp.x < 768.f && temp.y < 768.f)
                moveVec.push_back(temp);
        }

    // usuwania (0,0)
    moveVec.pop_back();

    // unikanie wilkow i krzakow
    this->wolfEvadeBush(moveVec);
    this->wolfCollision(moveVec, wolf->getGender());

    // jesli nie ma mozliwego ruchu stoj w miejscu
    if (moveVec.empty())
        moveVec.push_back(posXY);

    // losowanie ruchu
    wolf->wolfMove(this->shuffleVec(moveVec));
}

void gameState::wolfCollision(std::vector<sf::Vector2f>& moveVec, bool isMale)
{   
    // sprawdza kolizje z innymi wilkami/wilczycami
    if (isMale)
    {
        for (unsigned int i = 0; i < this->lotsOfWolfM.size(); i++)
            for (unsigned int j = 0; j < moveVec.size(); j++)
                if (this->lotsOfWolfM[i].getPos() == moveVec[j])
                {
                    // usuwa pozycje na której znajduuje sie wilk
                    moveVec.erase(moveVec.begin() + j);
                    break;
                }
    }
    else 
    {
        for (unsigned int i = 0; i < this->lotsOfWolfF.size(); i++)
            for (unsigned int j = 0; j < moveVec.size(); j++)
                if (this->lotsOfWolfF[i].getPos() == moveVec[j])
                {
                    moveVec.erase(moveVec.begin() + j);
                    break;
                }
    }
}

void gameState::wolfEvadeBush(std::vector<sf::Vector2f>& moveVec)
{
    // porownuje pozycje wilka z krzakiem
    for (unsigned int i = 0; i < moveVec.size(); i++)
        for (int j = 0; j < 49; j++)
        {
            if (moveVec[i] == this->bush[j])
            {
                moveVec.erase(moveVec.begin() + i);
                i--;
                break;
            }
        }
}

bool gameState::followBunny(Wolf* wolf)
{
    sf::Vector2f posXY = wolf->getPos();
    std::vector<sf::Vector2f> moveVec;

    // sprawdza pozycje królików
    int endForLoop = this->lotsOfBunny.size();
    for (int i = 0; i < endForLoop; i++)
    {
        if (!this->lotsOfBunny[i].getHidden()) // 1 ukryty, 0 widzialny
            if (abs(posXY.x - lotsOfBunny[i].getPos().x) == 32)
                if (abs(posXY.y - lotsOfBunny[i].getPos().y) == 32)
                    moveVec.push_back(lotsOfBunny[i].getPos());         
    }

    this->wolfCollision(moveVec, wolf->getGender());

    // jesli nie ma blisko krolika
    if (moveVec.empty())
    {
        // sprawdza staja pozycje krolika
        int endForLoop = this->lotsOfBunny.size();
        for (int i = 0; i < endForLoop; i++)
        {
            if (abs(posXY.x - lotsOfBunny[i].getOldPos().x) == 32)
                if (abs(posXY.y - lotsOfBunny[i].getOldPos().y) == 32)
                    moveVec.push_back(lotsOfBunny[i].getOldPos());
        }

        this->wolfEvadeBush(moveVec);
        this->wolfCollision(moveVec, wolf->getGender());
        if (moveVec.empty())
            return false;
    }

    wolf->wolfMove(this->shuffleVec(moveVec));
    return true;
}

bool gameState::followWolf(Wolf* wolf)
{
    if (wolf->getTired() > 0)
        return false;

    sf::Vector2f posXY = wolf->getPos();
    std::vector<sf::Vector2f> moveVec;

    // sprawdza pozycje wilczyc
    for (unsigned int i = 0; i < this->lotsOfWolfF.size(); i++)
    {
        if (abs(posXY.x - lotsOfWolfF[i].getPos().x) == 32)
            if (abs(posXY.y - lotsOfWolfF[i].getPos().y) == 32)
                    moveVec.push_back(lotsOfWolfF[i].getPos());
    }

    this->wolfCollision(moveVec, wolf->getGender());

    // jesli nie ma blisko wilczycy
    if (moveVec.empty())
    {
        // sprawdza star¹ pozycje wilczyc
        for (unsigned int i = 0; i < this->lotsOfWolfF.size(); i++)
        {
            if (abs(posXY.x - lotsOfWolfF[i].getOldPos().x) == 32)
                if (abs(posXY.y - lotsOfWolfF[i].getOldPos().y) == 32)
                    moveVec.push_back(lotsOfWolfF[i].getOldPos());
        }

        this->wolfCollision(moveVec, wolf->getGender());
        if (moveVec.empty())
            return false;
    }

    wolf->wolfMove(this->shuffleVec(moveVec));
    return true;
}

void gameState::eatBunny(Wolf* wolf)
{
    sf::Vector2f posXY = wolf->getPos();

    // sprawdzanie ka¿dego królika
    for (unsigned int i = 0; i < this->lotsOfBunny.size(); i++)
        if (this->lotsOfBunny[i].getPos() == posXY)
        {
            // usuwa zjedzonego królika i dodaje t³uszcz
            this->bunnyDie(i);
            wolf->updateFat(10); // resetowanie t³uszczu
            return;
        }

    wolf->updateFat(-1); // zmniejsza t³uszcz
    //std::cout << wolf->getFat() << std::endl;
}

void gameState::babyWolf(Wolf* wolf)
{
    int endForLoop = this->lotsOfWolfF.size();
    sf::Vector2f posXY = wolf->getPos();

    // sprawdzemie ka¿dej wilczycy
    for (int i = 0; i < endForLoop; i++)
        if (this->lotsOfWolfF[i].getPos() == posXY && !lotsOfWolfF[i].getTired())
        {
            wolf->resetTired(); // resetowanie zmeczenia na 3
            lotsOfWolfF[i].resetTired(); // resetowanie zmeczenia na 3
            this->newWolf(posXY, std::rand() % 2); // nowy wilk
        }      
}

bool gameState::wolfDie(Wolf* wolf, int i)
{
    if (wolf->getFat() <= 0)
    {
        if (wolf->getGender())
        {
            this->deadWolf.push_back(this->lotsOfWolfM[i]);
            this->lotsOfWolfM.erase(this->lotsOfWolfM.begin() + i);
        }
        else
        {
            this->deadWolf.push_back(this->lotsOfWolfF[i]);
            this->lotsOfWolfF.erase(this->lotsOfWolfF.begin() + i);
        }
        return true;
    }
    return false;
}

void gameState::newWolf(sf::Vector2f posXY, int isMale)
{
    //std::cout << isMale << std::endl;
    Wolf wolf(posXY, isMale, &this->wolfTexture, &this->heartTexture, &this->staminaTexture);
    if (isMale)
        this->lotsOfWolfM.push_back(wolf);
    else
        this->lotsOfWolfF.push_back(wolf);
}

void gameState::updateWolf(Wolf* wolf, int i)
{
    // zmiana koloru
    wolf->setColor();

    // poruszanie sie wilków
    if (wolf->getGender()) // 1 wilk, 0 wilczyca
    {
        if (!this->followWolf(wolf))
            if (!this->followBunny(wolf))
                this->standardMove(wolf);
    }
    else
        if (!this->followBunny(wolf))
            this->standardMove(wolf);

    // sprawdzanie czy wilk zjad³ królika
    this->eatBunny(wolf);

    // zmniejsza zmêczenie
    wolf->downTired();

    // sprawdza czy urodzi siê nowy wilk
    if (wolf->getGender() && !wolf->getTired())
        this->babyWolf(wolf);

    //std::cout << wolf->getPos().x << " " << wolf->getPos().y << "\n";
}

// Konstruktor
gameState::gameState()
{
    this->initOnce();
    this->initFile();
    this->initMap();
    this->initBunny();
    this->initWolf();
}

gameState::~gameState()
{
    this->lotsOfBunny.clear();
    this->lotsOfWolfF.clear();
    this->lotsOfWolfM.clear();
    this->deadBunny.clear();
    this->deadWolf.clear();
}

// Funkcje publiczne
void gameState::update(float dt)
{
    if (this->dt > 1000)
    {
        this->dt = 0;

        this->deadBunny.clear();
        this->deadWolf.clear();

        // królik
        for (unsigned int i = 0; i < this->lotsOfBunny.size(); i++)
            this->updateBunny(&this->lotsOfBunny[i]);

        // wilczyca
        for (int i = 0; i < this->lotsOfWolfF.size(); i++)
            this->updateWolf(&this->lotsOfWolfF[i], i);

        for (unsigned int i = 0; i < this->lotsOfWolfF.size(); i++)
            if (this->wolfDie(&this->lotsOfWolfF[i], i))
                i--;

        // wilk
        for (int i = 0; i < this->lotsOfWolfM.size(); i++)
            this->updateWolf(&this->lotsOfWolfM[i], i);

        for (unsigned int i = 0; i < this->lotsOfWolfM.size(); i++)
            if (this->wolfDie(&this->lotsOfWolfM[i], i))
                i--;
    }
    
    //std::cout << this->dt << std::endl;
    this->dt += dt;
}

void gameState::render(sf::RenderTarget* window)
{
    // Mapa
    window->draw(this->map);

    // martwe króliki
    for (unsigned int i = 0; i < this->deadBunny.size(); i++)
        this->deadBunny[i].render(window);

    // martwe wilki i wilczyce
    for (unsigned int i = 0; i < this->deadWolf.size(); i++)
        this->deadWolf[i].render(window);

    // królik
    for (unsigned int i = 0; i < this->lotsOfBunny.size(); i++)
        this->lotsOfBunny[i].render(window);

    // wilczyca
    for (unsigned int i = 0; i < this->lotsOfWolfF.size(); i++)
        this->lotsOfWolfF[i].render(window);

    // wilk
    for (unsigned int i = 0; i < this->lotsOfWolfM.size(); i++)
        this->lotsOfWolfM[i].render(window);
}