//
// Created by rivatn on 12/10/15.
//

#include "JoinRoomMenu.h"
#ifndef WIN32
# include <unistd.h>
#endif

JoinRoomMenu::JoinRoomMenu(sf::RenderWindow *win)
{
    int i = 0;
    this->nbRooms = 0;
    this->waitRoom = false;
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

    #ifdef WIN32
        Sleep(100000 / 100);
    #else
        usleep(100000);
    #endif
    InfoMenu    *tmp = InfoMenu::getInstance();
    ISocket     *client = InfoMenu::getClient(tmp->getIP(), tmp->getPort(), "TCP");
    Instruction i(Instruction::GETALLROOMNAMES);

    client->attachOnReceive(this->handlerRooms);
    client->writePacket(Packet::pack(i));
    while (this->window->isOpen() && !(InfoMenu::getInstance()->close))
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
            if (this->waitRoom)
            {
                this->transp = 255;
                this->waitingRoom = WaitingRoom::getInstance(this->window, false);
                this->waitingRoom->RenderFrame();
                this->waitRoom = false;
                return;
            }
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
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        this->JoinRoom();
    return 0;
}

void JoinRoomMenu::handlerRooms(ISocket *client)
{
    Packet          *packet;
    Instruction     *instruct;
    JoinRoomMenu    *tmp = JoinRoomMenu::getInstance();

    while ((packet = client->readPacket()) != NULL)
    {
        if (packet->getType() == Packet::Instruct &&
            (instruct = packet->unpack<Instruction>()) != NULL)
        {
            if (instruct->getInstruct() == Instruction::GETALLROOMNAMES)
            {
                for (unsigned int i = 0; i < instruct->getNb(); i++)
                {
                    if ((*instruct)[i] != "")
                        tmp->texts[i]->setString((*instruct)[i]);
                    else
                        tmp->texts[i]->setString("<Room not available>");
                }
            }
            else
                std::cout << "ERROR" << std::endl;
            delete instruct;
        }
        delete packet;
    }
}

void JoinRoomMenu::handlerJoin(ISocket *client)
{
    Packet          *packet;
    Instruction     *instruct;
    JoinRoomMenu    *tmp = JoinRoomMenu::getInstance();

    while ((packet = client->readPacket()) != NULL)
    {
        if (packet->getType() == Packet::Instruct &&
            (instruct = packet->unpack<Instruction>()) != NULL)
        {
            if (instruct->getInstruct() == Instruction::OK)
                tmp->waitRoom = true;
            else
                std::cout << "ERROR" << std::endl;
            delete instruct;
        }
        delete packet;
    }
}

void JoinRoomMenu::JoinRoom()
{
    InfoMenu    *tmp = InfoMenu::getInstance();
    ISocket     *client = InfoMenu::getClient(tmp->getIP(), tmp->getPort(), "TCP");
    Instruction i(static_cast<std::string>(this->texts[this->currentRoom]->getString()), Instruction::JOIN_ROOM);

    client->attachOnReceive(this->handlerJoin);
    client->writePacket(Packet::pack(i));
}
