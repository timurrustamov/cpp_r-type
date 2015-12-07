//
// Created by rivatn on 12/7/15.
//

#include "InfoMenu.h"
#include <iostream>

InfoMenu::InfoMenu()
{

}

InfoMenu::~InfoMenu()
{

}

void InfoMenu::init()
{
    this->window = new sf::RenderWindow(sf::VideoMode(600, 400), "R-TYPE");
    this->fileImg = new sf::Texture();
    this->fileImg->loadFromFile("/home/rivatn/Projects/cpp/cpp_r-type/SFML/images/background.png");
    this->background = new sf::Sprite(*this->fileImg);
}

void InfoMenu::showUserForm()
{
    while (this->window->isOpen())
    {
        sf::Event  event;
        while (this->window->pollEvent(event))
            if (event.type == sf::Event::Closed)
                this->window->close();
        this->window->clear();
        this->window->draw(*this->background);
        this->window->display();
    }
}

void InfoMenu::showIpForm()
{

}

void InfoMenu::renderFrame()
{

}

void InfoMenu::setIP(const std::string &string)
{

}

void InfoMenu::setUsername(const std::string &string)
{

}

std::string InfoMenu::getIP() const
{
    return this->ip;
}

std::string InfoMenu::getUsername() const
{
    return this->username;
}

std::string InfoMenu::getPort() const
{
    return this->port;
}

int InfoMenu::getNext()
{
    return 0;
}

