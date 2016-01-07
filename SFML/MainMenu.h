//
// Created by rivatn on 12/8/15.
//

#ifndef SFML_MAINMENU_H
#define SFML_MAINMENU_H

#if defined(_WIN32) && !defined(WIN32)
# define _WINSOCKAPI_
# define NOGDI
# include <windows.h>
# define WIN32
#endif

#include <iostream>
#include <SFML/Audio.hpp>
#include "InfoMenu.h"
#include "CreateRoomMenu.h"
#include "JoinRoomMenu.h"

class CreateRoomMenu;
class JoinRoomMenu;

class MainMenu
{
public:
    MainMenu(sf::RenderWindow *);
    ~MainMenu();

    void RenderFrame();

    int getKeys();

    static MainMenu *getInstance(sf::RenderWindow *wind = NULL);
    sf::Music                       *song;
    bool exit() const;

private:
    int                             currentImg;
    float                           transp;
    bool                            exit1;
    sf::RenderWindow                *window;
    std::vector<sf::Texture *>      texture;
    std::vector<sf::Sprite *>       sprite;
    CreateRoomMenu                  *create_menu;
    JoinRoomMenu                    *join_menu;
    sf::Clock                       *clock;
    sf::Sprite                      *fondu;
};


#endif //SFML_MAINMENU_H
