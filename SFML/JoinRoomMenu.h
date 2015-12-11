//
// Created by rivatn on 12/10/15.
//

#ifndef SFML_JOINROOMMENU_H
#define SFML_JOINROOMMENU_H


#include "MainMenu.h"

class JoinRoomMenu
{
public:
    JoinRoomMenu(sf::RenderWindow*);
    ~JoinRoomMenu();

    static JoinRoomMenu *getInstance(sf::RenderWindow*);

    void RenderFrame();

    int getKeys();

private:
    float               transp;
    sf::RenderWindow    *window;
    sf::Sprite          *sprite;
    sf::Sprite          *fondu;
    sf::Texture         *text;
    sf::Clock           *clock;
};


#endif //SFML_JOINROOMMENU_H
