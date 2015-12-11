//
// Created by rivatn on 12/7/15.
//

#ifndef SFML_INFOMENU_H
#define SFML_INFOMENU_H

#include <string>
#include <SFML/Graphics.hpp>
#include "Gameplay.h"
#include "MainMenu.h"

class MainMenu;

class InfoMenu
{
public:
    InfoMenu();
    ~InfoMenu();

    void init();
    void showUserForm();
    void showIpForm(char);

    void addLetters(sf::Event*);
    void addNumbers(sf::Event*);

    int cutIP();

    void  getNext();

    std::string getIP() const;
    std::string getUsername() const;
    std::string getPort() const;

private:
    bool                        isDone;
    std::string                 username;
    std::string                 ip;
    std::string                 port;
    std::vector<sf::Texture*>   fileImg;
    std::vector<sf::Sprite*>    sprites;
    std::vector<sf::Text*>      texts;
    sf::RenderWindow            *window;
    sf::Font                    *font;
    MainMenu                    *next;
};


#endif //SFML_INFOMENU_H
