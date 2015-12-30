//
// Created by rivatn on 12/7/15.
//

#include "InfoMenu.h"
#include <iostream>
#include <unistd.h>

InfoMenu::InfoMenu()
{
    this->fileImg.push_back(new sf::Texture());
    this->fileImg.push_back(new sf::Texture());
    this->sprites.reserve(2);
    this->sprites.resize(2);
    this->texts.reserve(3);
    this->texts.resize(3);
    this->isDone = false;
    this->_error = false;
}

InfoMenu::~InfoMenu()
{
    for (std::vector<sf::Texture*>::iterator it = this->fileImg.begin(); it != this->fileImg.end(); it++)
        if (*it != NULL)
            delete *it;
    for (std::vector<sf::Sprite*>::iterator it = this->sprites.begin(); it != this->sprites.end(); it++)
        if (*it != NULL)
            delete *it;
    for (std::vector<sf::Text*>::iterator it = this->texts.begin(); it != this->texts.end(); it++)
        if (*it != NULL)
            delete *it;
    delete this->font;
    delete this->window;
}

void InfoMenu::init()
{
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    sf::Vector2i size((mode.width / 2) - 250, (mode.height / 2) - 150);
    this->window = new sf::RenderWindow(sf::VideoMode(500, 300), "R-TYPE");
    this->window->setPosition(size);
    this->fileImg[0]->loadFromFile("images/background.png");
    this->fileImg[1]->loadFromFile("images/rectangle.png");
    this->sprites[0] = new sf::Sprite(*this->fileImg[0]);
    this->sprites[1] = new sf::Sprite(*this->fileImg[1]);
    this->font = new sf::Font();
    this->font->loadFromFile("fonts/batmfa__.ttf");
}

void InfoMenu::showUserForm()
{
    sf::Color   color(0, 0, 0);

    this->isDone = false;
    this->username = "";
    this->texts[1] = new sf::Text("(max 8 characters)", *this->font, 10);
    this->texts[2] = new sf::Text(this->username, *this->font, 30);
    this->texts[0] = new sf::Text("Enter your username:", *this->font, 20);
    this->texts[0]->setPosition(10, 90);
    this->texts[1]->setPosition(10, 120);
    this->texts[2]->setPosition(20, 143);
    this->sprites[1]->setPosition(8, 140);
    this->sprites[1]->setScale(1.5, 0.5);
    this->texts[2]->setColor(color);
    while (this->window->isOpen())
    {
        sf::Event  event;
        while (this->window->pollEvent(event))
        {
            this->addLetters(&event);
            if (event.type == sf::Event::Closed)
                this->window->close();
        }
        if (this->isDone)
        {
            std::cout << "GO" << std::endl;
            return;
        }
        if (!this->_error)
            this->texts[0]->setString("Enter your username:");
        else
            this->texts[0]->setString("Username is already used:");
        this->texts[2]->setString(this->username);
        this->window->clear();
        this->window->draw(*this->sprites[0]);
        this->window->draw(*this->sprites[1]);
        this->window->draw(*this->texts[0]);
        this->window->draw(*this->texts[1]);
        this->window->draw(*this->texts[2]);
        this->window->display();
    }
}

void InfoMenu::showIpForm()
{
    sf::Color   color(0, 0, 0);
    this->isDone = false;
    this->texts[1] = new sf::Text("(Ex: 192.168.10.20:4242)", *this->font, 10);
    this->texts[2] = new sf::Text(this->ip, *this->font, 30);
    this->texts[0] = new sf::Text("Enter the ip address and port:", *this->font, 20);
    this->texts[0]->setPosition(10, 90);
    this->texts[1]->setPosition(10, 120);
    this->texts[2]->setPosition(20, 143);
    this->sprites[1]->setPosition(8, 140);
    this->sprites[1]->setScale(1.5, 0.5);
    this->texts[2]->setColor(color);
    while (this->window->isOpen())
    {
        if (this->isDone)
        {
            this->_error = false;
            this->showUserForm();
            return;
        }
        sf::Event  event;
        while (this->window->pollEvent(event))
        {
            this->addNumbers(&event);
            if (event.type == sf::Event::Closed)
                this->window->close();
        }
        if (!this->_error)
            this->texts[0]->setString("Enter the ip address and port:");
        else
        {
            this->ip = "";
            this->texts[0]->setString("Wrong ip address, try again:");
        }
        this->texts[2]->setString(this->ip);
        this->window->draw(*this->sprites[0]);
        this->window->draw(*this->sprites[1]);
        this->window->draw(*this->texts[0]);
        this->window->draw(*this->texts[1]);
        this->window->draw(*this->texts[2]);
        this->window->display();
    }
}

const std::string &InfoMenu::getIP() const
{
    return this->ip;
}

const std::string &InfoMenu::getUsername() const
{
    return this->username;
}

int InfoMenu::getPort() const
{
    return this->_port;
}

void InfoMenu::getNext()
{
    this->next = MainMenu::getInstance(this->window);
    this->next->RenderFrame();
}

void InfoMenu::addLetters(sf::Event *event)
{
    if (event->type == sf::Event::TextEntered && this->username.size() < 9)
    {
        if (((event->text.unicode >= 65 && event->text.unicode <= 90) ||
                (event->text.unicode >= 97 && event->text.unicode <= 122)) && this->username.size() + 1 < 9)
            this->username += static_cast<char>(event->text.unicode);
        else if (event->text.unicode == 8)
            if (this->username.length() != 0)
                this->username.erase(this->username.begin() + this->username.length() - 1);
        if (event->text.unicode == 13)
            this->checkUsername();
    }
}

void InfoMenu::addNumbers(sf::Event *event)
{
    if (event->type == sf::Event::TextEntered && this->ip.size() < 21)
    {
        if (((event->text.unicode >= '0' && event->text.unicode <= '9') ||
             event->text.unicode == ':' || event->text.unicode == '.') && this->ip.size() + 1 < 21)
            this->ip += static_cast<char>(event->text.unicode);
        else if (event->text.unicode == 8)
            if (this->ip.length() != 0)
                this->ip.erase(this->ip.begin() + this->ip.length() - 1);
        if (event->text.unicode == 13)
        {
            if (!this->checkIp())
                this->_error = true;
            else
                this->isDone = true;
        }
    }
}

int InfoMenu::cutIP()
{
    size_t  found;
    size_t  size;

    size = this->ip.size();
    if (((found = this->ip.find(":")) != std::string::npos) && !this->ip.empty())
    {
        this->port = this->ip.substr(found + 1, this->ip.size());
        this->ip = this->ip.substr(0, found);
    }
    if (found == std::string::npos)
    {
        this->ip = "";
        this->port = "";
        return -1;
    }
    else
        return 0;
}

ISocket *InfoMenu::getClient(const std::string& ip, int port, const std::string& proto)
{
    static std::map<std::string, ISocket *> clients;

    if (clients[proto] == NULL)
        clients[proto] = ISocket::getClient(ip, port, proto);
    return clients[proto];
}

bool InfoMenu::checkIp()
{
    this->cutIP();
    std::cout << "IP : " << this->ip << std::endl;
    std::istringstream   buff(this->port);
    buff >> this->_port;
    std::cout << "PORT : " << this->_port << std::endl;
    ISocket *client = InfoMenu::getClient(this->ip, this->_port, "TCP");
    client->attachOnReceive(this->recieveHandler);
    return (client->start() != -1);
}

void InfoMenu::recieveHandler(ISocket *client)
{
    Packet      *packet;
    Instruction *instruct;
    InfoMenu    *tmp = InfoMenu::getInstance();

    while ((packet = client->readPacket()) != NULL)
    {
        if (packet->getType() == Packet::Instruct &&
            (instruct = packet->unpack<Instruction>()) != NULL)
        {
            if (instruct->getInstruct() == Instruction::OK)
                tmp->isDone = true;
            else if (instruct->getInstruct() == Instruction::KO)
                tmp->_error = true;
            else
                std::cout << "ERROR" << std::endl;
            delete instruct;
        }
        delete packet;
    }
}

void InfoMenu::checkUsername()
{
    ISocket     *client = InfoMenu::getClient(this->ip, this->_port, "TCP");
    Instruction i(this->username, Instruction::CONNEXION);

    client->writePacket(Packet::pack(i));
}

InfoMenu *InfoMenu::getInstance()
{
    static InfoMenu *menu;

    if (menu == NULL)
        menu = new InfoMenu();
    return menu;
}
