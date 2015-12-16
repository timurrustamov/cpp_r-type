//
// Created by rivatn on 12/14/15.
//

#include "WaitingRoom.h"

WaitingRoom::WaitingRoom(sf::RenderWindow *win, bool b)
{
    int i = 0;

    this->window = win;
    this->isHost = b;
    this->transp = 255;
    this->text = new sf::Texture();
    this->text->loadFromFile("images/waiting_room.png");
    this->sprite = new sf::Sprite(*this->text);
    this->sprite->setPosition(0, 0);
    this->sprite->setScale(0.39, 0.42);
    this->font = new sf::Font();
    this->font->loadFromFile("fonts/batmfa__.ttf");
    this->players.reserve(4);
    this->players.resize(4);
    for (std::vector<sf::Text *>::iterator it = this->players.begin(); it != this->players.end(); it++)
    {
        *it = new sf::Text("", *this->font, 15);
        (*it)->setPosition(150, 100 + i);
        (*it)->setColor(sf::Color(0, 254, 0));
        i += 40;
    }
    this->clock = new sf::Clock();
    this->fondu = new sf::Sprite(*this->text);
    this->fondu->setColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(this->transp)));
    this->fondu->setPosition(0, 0);
    this->forHost = new sf::Text("I'm the host", *this->font, 20);
    this->forHost->setPosition(150, 140);
}

WaitingRoom::~WaitingRoom()
{

}

void WaitingRoom::RenderFrame()
{
    float   time = 0;

    while (this->window->isOpen())
    {
        time = this->clock->getElapsedTime().asMilliseconds();
        if (time >= 0.5 && this->transp > 0)
        {
            this->transp -= 4;
            this->fondu->setColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(this->transp)));
            this->clock->restart();
        }
        sf::Event  event;
        while (this->window->pollEvent(event))
        {
            if (this->getKeys() == -1)
            {
                this->transp = 255;
                return;
            }
            if (event.type == sf::Event::Closed)
                this->window->close();
        }
        this->window->clear();
        this->window->draw(*this->sprite);
        if (this->transp > 0)
            this->window->draw(*this->fondu);
        if (this->isHost)
            this->window->draw(*this->forHost);
        this->window->display();
    }
    this->transp = 255;
}

void WaitingRoom::setHost(bool b)
{
    this->isHost = b;
}

WaitingRoom *WaitingRoom::getInstance(sf::RenderWindow *win, bool b)
{
    static WaitingRoom  *menu;

    if (menu == NULL)
        menu = new WaitingRoom(win, b);
    else
        menu->setHost(b);
    return menu;
}

int WaitingRoom::getKeys()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        return -1;
    return 0;
}
