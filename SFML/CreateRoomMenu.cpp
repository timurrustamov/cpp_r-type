//
// Created by rivatn on 12/9/15.
//

#include <unistd.h>
#include "CreateRoomMenu.h"

CreateRoomMenu::CreateRoomMenu(sf::RenderWindow *win)
{
    this->window = win;
    this->window = win;
    this->input = "";
    this->transp = 255;
    this->texture = new sf::Texture();
    this->texture->loadFromFile("images/menu_create_room.png");
    this->sprite = new sf::Sprite(*this->texture);
    this->sprite->setPosition(0, 0);
    this->sprite->setScale(0.39, 0.42);
    this->font = new sf::Font();
    this->font->loadFromFile("fonts/batmfa__.ttf");
    this->text = new sf::Text(this->input, *this->font, 30);
    this->text->setScale(0.39, 0.42);
    this->text->setColor(sf::Color(0, 0, 0));
    this->text->setPosition(230, 149);
    this->clock = new sf::Clock();
    this->fondu = new sf::Sprite(*this->texture);
    this->fondu->setColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(this->transp)));
    this->fondu->setPosition(0, 0);
    this->waitRoom = false;
    this->joinRoom = false;
}

CreateRoomMenu::~CreateRoomMenu()
{
    delete this->texture;
    delete this->sprite;
    delete this->font;
    delete this->clock;
    delete this->fondu;
}

void CreateRoomMenu::RenderFrame()
{
    float   time = 0;

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
            if (this->getKeys(&event) == -1)
            {
                this->input = "";
                this->transp = 255;
                return;
            }
            if (this->waitRoom)
            {
                this->waitingRoom = WaitingRoom::getInstance(this->window, true);
                this->input = "";
                this->transp = 255;
                this->waitingRoom->RenderFrame();
                this->waitRoom = false;
                return;
            }
            else if (this->joinRoom)
            {
                JoinRoomMenu *join = JoinRoomMenu::getInstance(this->window);
                this->input = "";
                this->transp = 255;
                join->RenderFrame();
                this->joinRoom = false;
                return;
            }
            if (event.type == sf::Event::Closed)
                this->window->close();
        }
        this->text->setString(this->input);
        this->window->clear();
        this->window->draw(*this->sprite);
        if (this->transp > 0)
            this->window->draw(*this->fondu);
        this->window->draw(*this->text);
        this->window->display();
    }
    this->transp = 255;
}

CreateRoomMenu *CreateRoomMenu::getInstance(sf::RenderWindow *wind)
{
    static CreateRoomMenu *menu;

    if (menu == NULL)
        menu = new CreateRoomMenu(wind);
    return menu;
}

int CreateRoomMenu::getKeys(sf::Event *event)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        return -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !this->input.empty())
    {
        this->checkRoom();
        usleep(120000);
    }
    if (event->type == sf::Event::TextEntered && this->input.size() < 9)
    {
        if (((event->text.unicode >= 65 && event->text.unicode <= 90) ||
             (event->text.unicode >= 97 && event->text.unicode <= 122)) && this->input.size() + 1 < 9)
            this->input += static_cast<char>(event->text.unicode);
        else if (event->text.unicode == 8) if (this->input.length() != 0)
            this->input.erase(this->input.begin() + this->input.length() - 1);
    }
    return 0;
}

void    CreateRoomMenu::handlerCreate(ISocket *client)
{
    Packet          *packet;
    Instruction     *instruct;
    CreateRoomMenu  *tmp = CreateRoomMenu::getInstance();

    while ((packet = client->readPacket()) != NULL)
    {
        if (packet->getType() == Packet::Instruct &&
            (instruct = packet->unpack<Instruction>()) != NULL)
        {
            if (instruct->getInstruct() == Instruction::OK)
                tmp->waitRoom = true;
            else if (instruct->getInstruct() == Instruction::KO)
                tmp->joinRoom = true;
            else
                std::cout << "ERROR" << std::endl;
            delete instruct;
        }
        delete packet;
    }
}

void    CreateRoomMenu::checkRoom()
{
    InfoMenu    *tmp = InfoMenu::getInstance();
    ISocket     *client = InfoMenu::getClient(tmp->getIP(), tmp->getPort(), "TCP");
    Instruction i(this->input, Instruction::CREATE_ROOM);

    client->attachOnReceive(this->handlerCreate);
    client->writePacket(Packet::pack(i));
}