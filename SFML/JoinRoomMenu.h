//
// Created by rivatn on 12/10/15.
//

#ifndef SFML_JOINROOMMENU_H
#define SFML_JOINROOMMENU_H

#include <sstream>
#include "MainMenu.h"
#include "WaitingRoom.h"
#include "../Source/GameEngine/ISocket.h"

class WaitingRoom;

class JoinRoomMenu
{
public:
    JoinRoomMenu(sf::RenderWindow *);
    ~JoinRoomMenu();

    static JoinRoomMenu *getInstance(sf::RenderWindow *win = NULL);
    static void handlerRooms(ISocket *);
    static void handlerJoin(ISocket *);

    void RenderFrame();
    void JoinRoom();

    int getKeys();

private:
    float                   transp;
    bool                    waitRoom;
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
    WaitingRoom             *waitingRoom;
};

#endif //SFML_JOINROOMMENU_H
