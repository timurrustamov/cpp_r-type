//
// Created by rivatn on 12/14/15.
//

#include "WaitingRoom.h"

WaitingRoom::WaitingRoom(sf::RenderWindow *win, bool b)
{
    int i = 0;

    this->window = win;
    this->isHost = b;
    this->transp = 255;
    this->yellow = new sf::Color(255, 254, 0);
    this->text = new sf::Texture();
    this->text->loadFromFile("images/waiting_room.png");
    this->sprite = new sf::Sprite(*this->text);
    this->sprite->setPosition(0, 0);
    this->sprite->setScale(0.39, 0.42);
    this->font = new sf::Font();
    this->font->loadFromFile("fonts/batmfa__.ttf");
    this->players.reserve(4);
    this->players.resize(4);
    for (std::vector<sf::Text *>::iterator it = this->players.begin(); it != this->players.end(); it++)
    {
        *it = new sf::Text("", *this->font, 35);
        (*it)->setScale(0.39, 0.42);
        (*it)->setPosition(35, 100 + i);
        (*it)->setColor(sf::Color(255, 254, 0));
        i += 40;
    }
    this->clock = new sf::Clock();
    this->fondu = new sf::Sprite(*this->text);
    this->fondu->setColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(this->transp)));
    this->fondu->setPosition(0, 0);
    this->texts.reserve(4);
    this->texts.resize(4);
}

WaitingRoom::~WaitingRoom()
{

}

void WaitingRoom::RenderFrame()
{
    float   time = 0;
    InfoMenu    *tmp = InfoMenu::getInstance();
    ISocket     *client = InfoMenu::getClient(tmp->getIP(), tmp->getPort(), "TCP");
    Instruction i(Instruction::GETALLUSERSINROOM);

    client->attachOnReceive(this->handlerUsers);
    client->writePacket(Packet::pack(i));
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
                for (std::vector<sf::Text *>::iterator it = this->players.begin(); it != this->players.end(); it++)
                    (*it)->setString("");
                return;
            }
            if (event.type == sf::Event::Closed)
                this->window->close();
        }
        this->window->clear();
        this->window->draw(*this->sprite);
        if (this->transp > 0)
            this->window->draw(*this->fondu);
        for (std::vector<sf::Text *>::iterator it = this->players.begin(); it != this->players.end(); it++)
            this->window->draw(**it);
        this->window->display();
    }
    this->transp = 255;
}

void WaitingRoom::setHost(bool b)
{
    this->isHost = b;
}

WaitingRoom *WaitingRoom::getInstance(sf::RenderWindow *win, bool b)
{
    static WaitingRoom  *menu;

    if (menu == NULL)
        menu = new WaitingRoom(win, b);
    else
        menu->setHost(b);
    return menu;
}

int WaitingRoom::getKeys()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        this->leave();
        return -1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && this->isHost)
    {
        InfoMenu    *tmp = InfoMenu::getInstance();
        ISocket     *client = InfoMenu::getClient(tmp->getIP(), tmp->getPort(), "TCP");
        Instruction i(Instruction::START_GAME);

        client->attachOnReceive(this->handlerStart);
        client->writePacket(Packet::pack(i));
    }
    return 0;
}

void WaitingRoom::handlerLeave(ISocket *client)
{
    Packet          *packet;
    Instruction     *instruct;
    WaitingRoom     *tmp = WaitingRoom::getInstance();

    while ((packet = client->readPacket()) != NULL)
    {
        if (packet->getType() == Packet::Instruct &&
            (instruct = packet->unpack<Instruction>()) != NULL)
        {
            if (instruct->getInstruct() == Instruction::OK)
                std::cout << "I'm leaving bitch !" << std::endl;
            else
                std::cout << "ERROR" << std::endl;
            delete instruct;
        }
        delete packet;
    }
    client->attachOnReceive(tmp->handlerUsers);
}

void WaitingRoom::handlerUsers(ISocket *client)
{
    Packet          *packet;
    Instruction     *instruct;
    WaitingRoom     *tmp = WaitingRoom::getInstance();

    while ((packet = client->readPacket()) != NULL)
    {
        if (packet->getType() == Packet::Instruct &&
            (instruct = packet->unpack<Instruction>()) != NULL)
        {
            if (instruct->getInstruct() == Instruction::GETALLUSERSINROOM)
            {
                std::cout << "GETTTT USERSSSSS" << std::endl;
                for (unsigned int i = 0; i < instruct->getNb(); i++)
                    tmp->players[i]->setString((*instruct)[i]);
            }
            else
                std::cout << "ERROR" << std::endl;
            delete instruct;
        }
        delete packet;
    }
}

void WaitingRoom::handlerStart(ISocket *client)
{
    Packet          *packet;
    Instruction     *instruct;
    WaitingRoom     *tmp = WaitingRoom::getInstance();

    while ((packet = client->readPacket()) != NULL)
    {
        if (packet->getType() == Packet::Instruct &&
            (instruct = packet->unpack<Instruction>()) != NULL)
        {
            if (instruct->getInstruct() == Instruction::OK)
                std::cout << "GAME START" << std::endl;
            else
                std::cout << "ERROR" << std::endl;
            delete instruct;
        }
        delete packet;
    }
}

void WaitingRoom::leave()
{
    InfoMenu    *tmp = InfoMenu::getInstance();
    ISocket     *client = InfoMenu::getClient(tmp->getIP(), tmp->getPort(), "TCP");
    Instruction i(Instruction::LEAVE_ROOM);

    client->attachOnReceive(this->handlerLeave);
    client->writePacket(Packet::pack(i));
}