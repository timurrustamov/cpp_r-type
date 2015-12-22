//
// Created by rivatn on 12/10/15.
//

#include <unistd.h>
#include "JoinRoomMenu.h"

JoinRoomMenu::JoinRoomMenu(sf::RenderWindow *win)
{
    int i = 0;
    this->nbRooms = 0;
    this->currentRoom = 0;
    this->transp = 255;
    this->window = win;
    this->green = new sf::Color(40, 175, 99);
    this->yellow = new sf::Color(255, 254, 0);
    this->font = new sf::Font();
    this->font->loadFromFile("fonts/batmfa__.ttf");
    this->text = new sf::Texture;
    this->clock = new sf::Clock();
    this->text->loadFromFile("images/menu_join_room.png");
    this->sprite = new sf::Sprite(*this->text);
    this->sprite->setPosition(0, 0);
    this->sprite->setScale(0.39, 0.42);
    this->fondu = new sf::Sprite(*this->text);
    this->fondu->setColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(this->transp)));
    this->fondu->setPosition(0, 0);
    this->texts.reserve(4);
    this->texts.resize(4);
    for (std::vector<sf::Text *>::iterator it = this->texts.begin(); it != this->texts.end(); it++)
    {
        *it = new sf::Text("<Room not available>", *this->font, 35);
        (*it)->setScale(0.39, 0.42);
        if (it == this->texts.begin())
            (*it)->setColor(*this->green);
        else
            (*it)->setColor(*this->yellow);
        (*it)->setPosition(150, 100 + i);
        i += 40;
    }
}

JoinRoomMenu::~JoinRoomMenu()
{

}

void JoinRoomMenu::RenderFrame()
{
    float   time = 0;

    usleep(100000);
    while (this->window->isOpen())
    {
        time = this->clock->getElapsedTime().asMilliseconds();
        if (time >= 0.5 && this->transp > 0)
        {
            this->transp -= 4;
            this->fondu->setColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(this->transp)));
            this->clock->restart();
        }
        sf::Event  event;
        while (this->window->pollEvent(event))
        {
            if (this->getKeys() == -1)
            {
                this->transp = 255;
                return;
            }
            if (event.type == sf::Event::Closed)
                this->window->close();
        }
        this->window->clear();
        this->window->draw(*this->sprite);
        if (this->transp > 0)
            this->window->draw(*this->fondu);
        for (std::vector<sf::Text *>::iterator it = this->texts.begin(); it != this->texts.end(); it++)
            this->window->draw(**it);
        this->window->display();
    }
    this->transp = 255;
}



JoinRoomMenu *JoinRoomMenu::getInstance(sf::RenderWindow *window)
{
    static JoinRoomMenu *menu;

    if (menu == NULL)
        menu = new JoinRoomMenu(window);
    return menu;
}

int JoinRoomMenu::getKeys()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        return -1;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && this->currentRoom + 1 < 4)
    {
        this->texts[this->currentRoom]->setColor(*this->yellow);
        this->texts[++this->currentRoom]->setColor(*this->green);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->currentRoom - 1 >= 0)
    {
        this->texts[this->currentRoom]->setColor(*this->yellow);
        this->texts[--this->currentRoom]->setColor(*this->green);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        std::cout << "LOLILOL" << std::endl;
        this->addRoom();
        usleep(120000);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        if (this->texts[this->currentRoom]->getString() != "<Room not available>")
        {
            std::cout << "WAITING ROOM" << std::endl;
            this->waitingRoom = WaitingRoom::getInstance(this->window, false);
            this->waitingRoom->RenderFrame();
        }
    }
    return 0;
}

bool JoinRoomMenu::addRoom()
{
    if (this->nbRooms > 3)
        return false;
    std::string name = "         Room ";
    std::stringstream   ss;
    //ss << ++this->nbRooms;
    name += ss.str();
    if (this->nbRooms - 1 >= 0)
        this->texts[this->nbRooms - 1]->setString(name);
    return true;
}

bool JoinRoomMenu::removeRoom(int i)
{
    this->texts[i]->setString("<Room not available>");
    --this->nbRooms;
    return true ;
}
