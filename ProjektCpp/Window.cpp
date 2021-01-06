#include "Window.h"

// Funkcje inicjalizujace
void Window::initWindow()
{
    sf::VideoMode window_bounds(800, 800);
    unsigned framerate_limit = 60;
    bool vertical_sync_enabled = false;

    // tworzenie okna
    this->window = new sf::RenderWindow(window_bounds, "Wyspa Wilkow",
        sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

// Konstruktor / Destruktor
Window::Window() 
{
    this->initWindow();

    // tworzy menu
    this->mState = new menuState;
}

Window::~Window()
{
    delete this->window;
    delete this->gState;
    delete this->mState;
}

// Funkcje dostepu
bool Window::windowIsOpen()
{
    return this->window->isOpen();
}

// Funkcje
void Window::updateSFMLEvent()
{
    // pobieranie eventów
    while (this->window->pollEvent(this->gEvent))
    {
        // zamykanie okna
        if (this->gEvent.type == sf::Event::Closed)
            this->window->close();
    }
}

void Window::updateStates()
{
    // sprawdza czy wciœniety jest esc
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && this->states == 0)
    {
        this->states = 1;
        delete this->gState;
    }  
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        this->states = 1;  

    // sprawdza wciœniêcie guzików z menu
    if (this->states == 1)
    {
        if (this->mState->clickedButton1(this->mousePos))
        {
            this->gState = new gameState;
            this->states = 0;
        }
        if (this->mState->clickedButton2(this->mousePos))
            system("notepad.exe Config/window.ini");
    }
}

void Window::updateDt()
{
    // zegar
    this->dt = this->dtClock.restart().asMilliseconds();  

    //system("cls");
    //std::cout << this->dt << "\n";
}

void Window::update()
{
    // aktualizuje
    this->updateSFMLEvent();
    this->updateStates();
    this->updateDt();

    // pozycja myszki
    this->mousePos = sf::Mouse::getPosition(*this->window);

    // wysy³a czas
    if (this->states == 0)
        this->gState->update(this->dt);
}

void Window::render()
{
    // czyszczenie
    this->window->clear();

    if (this->states == 0)
        this->gState->render(this->window);
    else if (this->states == 1)
        this->mState->render(this->window, this->mousePos);

    // wyœwietlanie
    this->window->display();
}