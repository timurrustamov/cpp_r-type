#include			"window.h"

Window::Window(const char *_title, unsigned int _width, unsigned int _height, bool _fullscreen) : title(_title), fullscreen(_fullscreen), width(_width), height(_height)
{}
Window::~Window() {}

void				Window::launchWindow()
{
	try
	{
		this->window.create(sf::VideoMode(this->width, this->height), this->title, (this->fullscreen) ? sf::Style::Fullscreen : sf::Style::Close);
		this->window.setView(view = sf::View(sf::FloatRect(0.f, 0.f, this->width, this->height)));
	}
	catch (const std::exception &err)
	{
		throw RTypeException("Cannot load level: " + std::string(err.what()));;
	}
}

void				Window::switchFullscreen()
{
	this->fullscreen = !this->fullscreen;
	this->window.create(sf::VideoMode(this->width, this->height), this->title, (this->fullscreen) ? sf::Style::Fullscreen : sf::Style::Close);
	this->window.setView(view = sf::View(sf::FloatRect(0.f, 0.f, this->width, this->height)));
}

bool				Window::isOpen() const
{
	return (this->window.isOpen());
}

void				Window::attachGameplay(IGameplay *gameplay)
{
	this->gameplay = gameplay;
}

void				Window::callGameplay()
{
	GameData		*gameData = GameData::getInstance();
	sf::Event		event;

	while (this->isOpen() && this->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed || gameData->getMustQuit())
			this->window.close();
		if (gameData->getFullscreen() != this->fullscreen)
			this->switchFullscreen();
		if (event.type == sf::Event::KeyPressed)
		{
			this->gameplay->keyPressed(event.key.code);
		}
	}
}