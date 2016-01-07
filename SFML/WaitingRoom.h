//
// Created by rivatn on 12/14/15.
//

#ifndef SFML_WAITINGROOM_H
#define SFML_WAITINGROOM_H

#if defined(_WIN32) && !defined(WIN32)
# define _WINSOCKAPI_
# define NOGDI
# include <windows.h>
# define WIN32
#endif

#ifdef WIN32
# include "../Source/System/WinThread.hpp"
#else
# include "../Source/GameEngine/LinuxThread.hpp"
#endif

#include "../Source/GameEngine/OnLevel.h"
#include "../Source/System/window.h"
#include "MainMenu.h"

class WaitingRoom
{
public:
    WaitingRoom(sf::RenderWindow *, bool);
    ~WaitingRoom();

    void RenderFrame();
    void setHost(bool);
    void leave();

    int getKeys();

    static WaitingRoom *getInstance(sf::RenderWindow *win = NULL, bool = false);
    static void handlerLeave(ISocket *);
    static void handlerUsers(ISocket *);
    static void handlerStart(ISocket *);
    static void gameLoop(unsigned int, sf::RenderWindow *);
    static void recvHandler(ISocket *);
    static void gameUpdateHandler(OnLevel &);

private:
    float                       transp;
    bool                        isHost;
    sf::RenderWindow            *window;
    std::vector<sf::Text *>     players;
    sf::Text                    *forHost;
    sf::Texture                 *text;
    sf::Sprite                  *sprite;
    sf::Sprite                  *fondu;
    sf::Clock                   *clock;
    sf::Font                    *font;
    std::vector<sf::Text *>     texts;
    sf::Color                   *yellow;
};


#endif //SFML_WAITINGROOM_H
