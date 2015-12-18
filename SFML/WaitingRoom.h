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

    int getKeys();

    static WaitingRoom *getInstance(sf::RenderWindow *, bool);


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
};


#endif //SFML_WAITINGROOM_H
