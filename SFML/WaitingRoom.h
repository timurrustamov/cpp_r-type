//
// Created by rivatn on 12/14/15.
//

#ifndef SFML_WAITINGROOM_H
#define SFML_WAITINGROOM_H

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
