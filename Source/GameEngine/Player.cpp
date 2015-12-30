//
// Created by rustam_t on 12/14/15.
//

#include				"GameData.h"
#include				"Player.hpp"

Player::Player(t2Vector<int> position, unsigned int playerNo) : Object()
{
    this->geometry = new Geometry(Rectangle<float>(t2Vector<int>(33, 18), position), 320, 5);
    this->geometry->attachToObject(this);
    this->type = Object::Character;
    this->id = Object::getId();
    this->playerNo = playerNo;
	this->start();
}

Player::Player(int x, int y, unsigned int playerNo)
{
    this->geometry = new Geometry(Rectangle<float>(t2Vector<int>(33, 18), t2Vector<int>(x, y)), 320, 5);
    this->geometry->attachToObject(this);
    this->type = Object::Character;
    this->id = Object::getId();
    this->playerNo = playerNo;
	this->start();
}

void					Player::start()
{
	ResourcesBank		*resourceBank = ResourcesBank::getInstance();

	this->entity = new AnimationEntity(this->getId(), 2, this->geometry->getPosition());
	if (!(this->animation = resourceBank->getAnimation("Player")))
	{
		this->animation = new Animation("Player", t2Vector<unsigned int>(33, 18), t2Vector<unsigned int>(101, 0), t2Vector<unsigned int>(10, 1));
		resourceBank->setAnimation("Player", this->animation);
	}
	this->animation->changeEntity(this->entity);
}

Object					*Player::clone(SerializedObject *serializedObject)
{
	Player				*newObject = new Player(this->geometry->getPosition(), serializedObject->attr.playerId);

	newObject->setValues(serializedObject);
	return (newObject);
}

unsigned int			Player::getPlayerNo() const
{
    return (this->playerNo);
}

void					Player::interact(Object *object)
{
    Geometry			*geo1 = this->geometry;
    Geometry			*geo2 = object->geometry;

    switch (object->getType())
    {
	case (Object::Projectile):
		break;
	case (Object::Force):
		break;
	default:
		geo1->removeImpulse();
		geo2->applyImpulse((geo2->getPosition() - geo1->getPosition()) * 500, 0.1);

		if (geo1->getRect().touchUpper(geo2->getRect()) || geo1->getRect().touchLower(geo2->getRect()))
			geo1->velocity().y() *= -1;
		if (geo1->getRect().touchLeft(geo2->getRect()) || geo1->getRect().touchRight(geo2->getRect()))
			geo1->velocity().x() *= -1;
		geo1->setPosition(geo1->getPreviousPosition(0));
		break;
    }
}

void					Player::lateUpdate()
{
	this->entity->setPosition(this->geometry->getPosition() - this->geometry->getSize() / 2);
}

void					Player::launchRocket(Rocket::Type rocketType)
{
	Rocket				*rocket = new Rocket(rocketType, this->geometry->getPosition() + t2Vector<unsigned int>(25, 0));

	rocket->geometry->applyImpulse(t2Vector<float>(30, 0), 0.1f);
	GameData::getInstance()->world->createNewObject(rocket);
}