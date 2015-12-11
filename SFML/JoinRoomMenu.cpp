//
// Created by rivatn on 12/10/15.
//

#include "JoinRoomMenu.h"

JoinRoomMenu::JoinRoomMenu(sf::RenderWindow *win)
{
    this->transp = 255;
    this->window = win;
    this->text = new sf::Texture;
    this->clock = new sf::Clock();
    this->text->loadFromFile("images/menu_join_room.png");
    this->sprite = new sf::Sprite(*this->text);
    this->sprite->setPosition(0, 0);
    this->sprite->setScale(0.39, 0.42);
    this->fondu = new sf::Sprite(*this->text);
    this->fondu->setColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(this->transp)));
    this->fondu->setPosition(0, 0);
}

JoinRoomMenu::~JoinRoomMenu()
{

}

void JoinRoomMenu::RenderFrame()
{
    float   time = 0;

    while (this->window->isOpen())
    {
        time = this->clock->getElapsedTime().asMilliseconds();
        if (time >= 1 && this->transp > 0)
        {
            this->transp -= 2;
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
        this->window->display();
    }
    this->transp = 255;
}



JoinRoomMenu *JoinRoomMenu::getInstance(sf::RenderWindow *window)
{
    static JoinRoomMenu *menu;

    if (menu == NULL)
        menu = new JoinRoomMenu(window);
    return menu;
}

int JoinRoomMenu::getKeys()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
        return -1;
    return 0;
}
