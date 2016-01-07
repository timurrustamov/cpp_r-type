//
// Created by rivatn on 12/7/15.
//

#ifndef SFML_INFOMENU_H
#define SFML_INFOMENU_H

#if defined(_WIN32) && !defined(WIN32)
# define _WINSOCKAPI_
# define NOGDI
# include <windows.h>
# define WIN32
#endif

#include <string>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Gameplay.h"
#include "MainMenu.h"
#include "../Source/GameEngine/ISocket.h"

class MainMenu;

class InfoMenu
{
public:
    InfoMenu();
    ~InfoMenu();

    void init();
    void showUserForm();
    void showIpForm();

    void addLetters(sf::Event*);
    void addNumbers(sf::Event*);

    int cutIP();

    void  getNext();
    void  checkUsername();

    static ISocket *getClient(const std::string&, int, const std::string&);
    static void recieveHandler(ISocket*);

    const std::string &getIP() const;
    const std::string &getUsername() const;
    int getPort() const;

    static InfoMenu *getInstance();

    bool checkIp();
    bool                        close;

private:
    bool                        isDone;
    bool                        _error;
    std::string                 username;
    std::string                 ip;
    std::string                 port;
    int                         _port;
    std::vector<sf::Texture*>   fileImg;
    std::vector<sf::Sprite*>    sprites;
    std::vector<sf::Text*>      texts;
    sf::RenderWindow            *window;
    sf::Font                    *font;
    MainMenu                    *next;
};


#endif //SFML_INFOMENU_H
