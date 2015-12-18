//
// Created by rivatn on 12/8/15.
//

#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow *win)
{
    this->transp = 255;
    this->window = win;
    this->texture.push_back(new sf::Texture());
    this->texture.push_back(new sf::Texture());
    this->texture.push_back(new sf::Texture());
    this->texture[0]->loadFromFile("images/create_room.png");
    this->texture[1]->loadFromFile("images/join_room.png");
    this->texture[2]->loadFromFile("images/exit.png");
    this->sprite.reserve(3);
    this->sprite.resize(3);
    this->sprite[0] = new sf::Sprite(*this->texture[0]);
    this->sprite[1] = new sf::Sprite(*this->texture[1]);
    this->sprite[2] = new sf::Sprite(*this->texture[2]);
    this->sprite[0]->setScale(0.39, 0.42);
    this->sprite[1]->setScale(0.39, 0.42);
    this->sprite[2]->setScale(0.39, 0.42);
    this->fondu = new sf::Sprite(*this->texture[0]);
    this->fondu->setColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(this->transp)));
    this->window->draw(*this->fondu);
    this->song = new sf::Music();
    this->song->openFromFile("musics/tron.ogg");
    this->song->setLoop(true);
    this->song->setVolume(150);
    this->clock = new sf::Clock();
    this->fondu->setPosition(0, 0);
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    sf::Vector2i pos((mode.width / 2) - 640, (mode.height / 2) - 360);
    sf::Vector2u size(1280, 720);
    this->currentImg = 0;
    this->window->setSize(size);
    this->window->setPosition(pos);
}

MainMenu::~MainMenu()
{
    for (std::vector<sf::Texture*>::iterator it = this->texture.begin(); it != this->texture.end(); it++)
        if (*it != NULL)
            delete *it;
    for (std::vector<sf::Sprite*>::iterator it = this->sprite.begin(); it != this->sprite.end(); it++)
        if (*it != NULL)
            delete *it;
}

void MainMenu::RenderFrame()
{
    float   time = 0;

    this->song->play();
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
                return;
            if (event.type == sf::Event::Closed)
                this->window->close();
        }
        this->window->clear();
        this->window->draw(*this->sprite[this->currentImg]);
        if (this->transp > 0)
            this->window->draw(*this->fondu);
        this->window->display();
    }
    this->transp = 255;
}

int MainMenu::getKeys()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            ++this->currentImg;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            --this->currentImg;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        if (this->currentImg == 0)
        {
            this->create_menu = CreateRoomMenu::getInstance(this->window);
            this->create_menu->RenderFrame();
            this->transp = 255;
        }
        else if (this->currentImg == 1)
        {
            this->join_menu = JoinRoomMenu::getInstance(this->window);
            this->join_menu->RenderFrame();
            this->transp = 255;
        }
        else if (this->currentImg == 2)
            return -1;
    }
    if ((this->currentImg = this->currentImg % 3) < 0)
        this->currentImg = 2;
    return 0;
}

MainMenu *MainMenu::getInstance(sf::RenderWindow *wind)
{
    static MainMenu *main;

    if (main == NULL)
        main = new MainMenu(wind);
    return main;
}
