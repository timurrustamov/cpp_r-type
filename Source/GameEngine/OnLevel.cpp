#include				<iostream>
#include				"../System/RTypeException.h"
#include				"../System/Animation.h"
#include				"OnLevel.h"

OnLevel::OnLevel()
{
	this->gameData = GameData::getInstance();

	try
	{
		this->gameData->resourceBank->setTexture("Ship", "../Assets/Graphics/Sprites/r-typesheet32.png");
		this->gameData->resourceBank->setTexture("Background", "../Assets/Graphics/Backgrounds/background_1.png");
		this->test = new Animation("Ship", t2Vector<unsigned int>(260, 143), t2Vector<unsigned int>(0, 0), t2Vector<unsigned int>(2, 4));
		this->background = new Animation("Background", t2Vector<unsigned int>(this->gameData->getWidth(), this->gameData->getHeight()), t2Vector<unsigned int>(0, 0), t2Vector<unsigned int>(1, 1));

		this->test->changeEntity(0, 0, t2Vector<int>(40, 40));
		this->test->changeEntity(1, 0, t2Vector<int>(250, 40));
		this->test->changeEntity(2, 0, t2Vector<int>(500, 40));
		this->test->changeEntity(3, 0, t2Vector<int>(200, 300));
		this->test->changeEntity(4, 0, t2Vector<int>(450, 300));
		this->background->changeEntity(0, 0, t2Vector<int>(0, 0));
	}
	catch (const RTypeException &exception)
	{
		std::cerr << exception.what() << std::endl;
		system("pause");
	}
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
	case sf::Keyboard::Space:
		this->test->changeEntity(1, 4, t2Vector<int>(250, 40));
		break;
	case sf::Keyboard::F:
		std::cout << "F has been pressed" << std::endl;
		this->gameData->setFullscreen(!this->gameData->getFullscreen());
		break;
	default:
		break;
	}
}

void					OnLevel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	this->background->draw(target, states);
	this->test->draw(target, states);
}

void					OnLevel::updateGraphics()
{
	this->test->prepareVertices();
	this->background->prepareVertices();
}