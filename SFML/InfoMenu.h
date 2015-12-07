//
// Created by rivatn on 12/7/15.
//

#ifndef SFML_INFOMENU_H
#define SFML_INFOMENU_H

#include <string>
#include <SFML/Graphics.hpp>

class InfoMenu
{
public:
    InfoMenu();
    ~InfoMenu();

    void init();
    void showUserForm();
    void showIpForm();

    void setIP(const std::string &);
    void setUsername(const std::string &);
    void renderFrame();

    int  getNext();

    std::string getIP() const;
    std::string getUsername() const;
    std::string getPort() const;

private:
    std::string         username;
    std::string         ip;
    std::string         port;
    sf::RenderWindow    *window;
    sf::Texture         *fileImg;
    sf::Sprite          *background;
};


#endif //SFML_INFOMENU_H
