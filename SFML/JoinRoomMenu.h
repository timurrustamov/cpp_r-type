//
// Created by rivatn on 12/10/15.
//

#ifndef SFML_JOINROOMMENU_H
#define SFML_JOINROOMMENU_H

#include <sstream>
#include "MainMenu.h"

class JoinRoomMenu
{
public:
    JoinRoomMenu(sf::RenderWindow*);
    ~JoinRoomMenu();

    static JoinRoomMenu *getInstance(sf::RenderWindow*);

    void RenderFrame();
    bool addRoom();
    bool removeRoom(int);

    int getKeys();

private:
    float                   transp;
    int                     nbRooms;
    int                     currentRoom;
    sf::RenderWindow        *window;
    sf::Sprite              *sprite;
    sf::Sprite              *fondu;
    sf::Texture             *text;
    sf::Clock               *clock;
    sf::Font                *font;
    std::vector<sf::Text *> texts;
    sf::Color               *green;
    sf::Color               *yellow;
};


#endif //SFML_JOINROOMMENU_H
