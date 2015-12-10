//
// Created by rivatn on 12/9/15.
//

#include "CreateRoomMenu.h"

CreateRoomMenu::CreateRoomMenu(sf::RenderWindow *win)
{
    this->window = win;

}

CreateRoomMenu::~CreateRoomMenu()
{

}

void CreateRoomMenu::RenderFrame()
{
    while (this->window->isOpen())
    {
        sf::Event  event;
        while (this->window->pollEvent(event))
        {
            if (this->getKeys() == -1)
                return;
            if (event.type == sf::Event::Closed)
                this->window->close();
        }
        this->window->clear();
        this->window->display();
    }
}

CreateRoomMenu *CreateRoomMenu::getInstance(sf::RenderWindow *wind)
{
    static CreateRoomMenu *menu;

    if (menu == NULL)
        menu = new CreateRoomMenu(wind);
    return menu;
}

int CreateRoomMenu::getKeys()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
        return -1;
    return 0;
}
