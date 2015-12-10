#include				<iostream>
#include				"Gameplay.h"

Gameplay::Gameplay() : closeGame(false), switchFullScreen(false)
{}

Gameplay::~Gameplay()
{}

void					Gameplay::keyPressed(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Escape:
		this->closeGame = true;
		break;
	case sf::Keyboard::A:
		std::cout << "A has been pressed" << std::endl;
		break;
	case sf::Keyboard::F:
		std::cout << "F has been pressed" << std::endl;
		this->switchFullScreen = true;
		break;
	default:
		break;
	}
}

bool					Gameplay::mustCloseGame() const
{
	return (this->closeGame);
}

bool					Gameplay::mustSwitchFullscreen()
{
	bool				tmp = this->switchFullScreen;

	this->switchFullScreen = false;
	return (tmp);
}