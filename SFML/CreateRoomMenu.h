//
// Created by rivatn on 12/9/15.
//

#ifndef SFML_CREATEROOMMENU_H
#define SFML_CREATEROOMMENU_H


#include <SFML/Graphics/RenderWindow.hpp>
#include "MainMenu.h"

class MainMenu;

class CreateRoomMenu
{
public:
    CreateRoomMenu(sf::RenderWindow *);
    ~CreateRoomMenu();

    void RenderFrame();
    int getKeys();

    static CreateRoomMenu *getInstance(sf::RenderWindow*);

private:
    sf::RenderWindow    *window;
};


#endif //SFML_CREATEROOMMENU_H
