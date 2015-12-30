//
// Created by rivatn on 12/9/15.
//

#ifndef SFML_CREATEROOMMENU_H
#define SFML_CREATEROOMMENU_H


#include <SFML/Graphics/RenderWindow.hpp>
#include "../Source/GameEngine/ISocket.h"
#include "MainMenu.h"
#include "WaitingRoom.h"

class MainMenu;
class WaitingRoom;

class CreateRoomMenu
{
public:
    CreateRoomMenu(sf::RenderWindow *);
    ~CreateRoomMenu();

    void RenderFrame();

    int getKeys(sf::Event *);

    void checkRoom();

    static CreateRoomMenu *getInstance(sf::RenderWindow* win = NULL);
    static void handlerCreate(ISocket *);

private:
    sf::RenderWindow    *window;
    bool                waitRoom;
    bool                joinRoom;
    float               transp;
    sf::Texture         *texture;
    sf::Sprite          *sprite;
    sf::Text            *text;
    sf::Sprite          *fondu;
    sf::Clock           *clock;
    sf::Font            *font;
    std::string         input;
    WaitingRoom         *waitingRoom;
};


#endif //SFML_CREATEROOMMENU_H
