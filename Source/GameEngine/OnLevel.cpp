#include				<iostream>
#include				"OnLevel.h"

OnLevel::OnLevel()
{
	this->gameData = GameData::getInstance();
}

OnLevel::~OnLevel()
{}

void					OnLevel::keyPressed(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Escape:
		this->gameData->setMustQuit(true);
		break;
	case sf::Keyboard::A:
		std::cout << "A has been pressed" << std::endl;
		break;
	case sf::Keyboard::F:
		std::cout << "F has been pressed" << std::endl;
		this->gameData->setFullscreen(!this->gameData->getFullscreen());
		break;
	default:
		break;
	}
}