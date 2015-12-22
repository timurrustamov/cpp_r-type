#include				<iostream>
#include				"../System/RTypeException.h"
#include				"../System/Animation.h"
#include				"OnLevel.h"

OnLevel::OnLevel() : level(static_cast<Level *>(0)), backgroundEntity(0, 0, t2Vector<int>(0, 0))
{
	this->gameData = GameData::getInstance();
	this->gameData->resourceBank->setAnimations(&this->animations);
}

OnLevel::~OnLevel()
{}

#include "Rocket.hpp"

void					OnLevel::loadLevel(Level *newLevel)
{
	this->level = newLevel;
	this->level->load();
	if (!this->level->isLoaded())
		throw RTypeException("Could not load level" + this->level->getTitle());

	this->level->playMusic();
	this->gameData->resourceBank->setTexture("Player", "../Assets/Graphics/Sprites/r-typesheet1.png");
	this->gameData->resourceBank->setTexture("Bullets", "../Assets/Graphics/Sprites/Bullets.png");
	this->animations["Background"] = new Animation("Background", this->level->getTexture(), t2Vector<unsigned int>(this->level->getSize(), this->gameData->getHeight()));
	this->animations["Background"]->changeEntity(&this->backgroundEntity);
	this->timer.addNewEvent("scrolling", static_cast<float>(this->level->getScrollSpeed()) / 100);
	this->timer.addNewEvent("shoot", 0.2f);
	this->world = new World(t2Vector<int>(this->gameData->getWidth(), this->gameData->getHeight()), true, true);
	this->gameData->world = this->world;
	this->world->createNewPlayer(t2Vector<unsigned int>(this->gameData->getWidth() / 10, this->gameData->getHeight() / 2), 0);
	this->player = dynamic_cast<Player *>(this->world->getPlayerObject(0));
}

void					OnLevel::keyPressed(sf::Keyboard::Key key)
{
	unsigned int		id;

	switch (key)
	{
	case sf::Keyboard::Escape:
		this->gameData->setMustQuit(true);
		break;
	case sf::Keyboard::F:
		this->gameData->setFullscreen(!this->gameData->getFullscreen());
		break;
	case sf::Keyboard::Space:
		if (!this->timer.eventDone("shoot")) break;
		id = this->world->createNewObject<Rocket>(this->player->geometry->getPosition() + t2Vector<unsigned int>(25, 0));
		this->world->getObject(id)->geometry->applyImpulse(t2Vector<float>(30, 0), 0.1f);
		this->timer.reset("shoot");
		break;
	default:
		break;
	}
}

void					OnLevel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (std::map<std::string, Animation *>::const_iterator animation = this->animations.begin(); animation != this->animations.end(); ++animation)
		animation->second->draw(target, states);
}

void					OnLevel::updateLogic(sf::Time *time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		this->player->geometry->addImpulse(t2Vector<float>(-1, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->player->geometry->addImpulse(t2Vector<float>(1, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		this->player->geometry->addImpulse(t2Vector<float>(0, -1));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		this->player->geometry->addImpulse(t2Vector<float>(0, 1));
	this->world->tick(time->asSeconds());
}

void					OnLevel::updateGraphics()
{
	if (this->timer.eventDone("scrolling"))
	{
		this->backgroundEntity.setPosition(this->backgroundEntity.getPosition() + t2Vector<int>(-1, 0));
		this->animations["Background"]->changeEntity(&this->backgroundEntity);
		this->timer.addNewEvent("scolling", static_cast<float>(this->level->getScrollSpeed()) / 100);
		this->timer.reset("scrolling");
	}

	for (std::map<std::string, Animation *>::const_iterator animation = this->animations.begin(); animation != this->animations.end(); ++animation)
		animation->second->prepareVertices();
}