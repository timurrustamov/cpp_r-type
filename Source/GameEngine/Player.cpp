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
	this->chargeShotEntity = new AnimationEntity(this->getId(), 0, this->geometry->getPosition());

	this->timer.addNewEvent("loadingChargeShot", 0.07f);
	this->timer.addNewEvent("laser", 0.1f);
	this->timer.addNewEvent("rocket", 0.5f);

	this->chargeShot1.setBuffer(*ResourcesBank::getInstance()->getSoundBuffer("ChargeShot"));
	this->chargeShot2.setBuffer(*ResourcesBank::getInstance()->getSoundBuffer("ChargeShot2"));
	this->chargeShot1.setVolume(66.6);
	this->chargeShot2.setVolume(66.6);

	if (!(this->animation = resourceBank->getAnimation("Player")))
	{
		this->animation = new Animation("Player", t2Vector<unsigned int>(33, 18), t2Vector<unsigned int>(101, 0), t2Vector<unsigned int>(10, 1));
		this->chargeShotLoading = new Animation("LoadingChargeShot", ResourcesBank::getInstance()->getTexture("Player"), t2Vector<unsigned int>(31, 32), t2Vector<unsigned int>(2, 51), t2Vector<unsigned int>(8, 1));

		resourceBank->setAnimation("Player", this->animation);
		resourceBank->setAnimation("LoadingChargeShot", this->chargeShotLoading);
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
	case (Object::Radiation):
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
	this->chargeShotEntity->setPosition(this->geometry->getPosition() - this->geometry->getSize() / 2 + t2Vector<int>(20, 0));
	if (this->timer.eventDone("loadingChargeShot"))
	{
		this->chargeShotEntity->setState((this->chargeShotEntity->getState() + 1) % 7);
		this->timer.reset("loadingChargeShot");
	}
}

#include				"Monster.h"

void					Player::launchRocket(Rocket::Type rocketType)
{
	Rocket				*rocket;
	Monster				*monster;
	
	if (!this->timer.eventDone("rocket")) return;
	monster = new Monster("cool", this->geometry->getPosition() + t2Vector<unsigned int>(500, 0));
	GameData::getInstance()->world->createNewObject(monster);

	/*
	rocket = new Rocket(rocketType, this->geometry->getPosition() + t2Vector<unsigned int>(25, 0));
	rocket->geometry->applyImpulse(t2Vector<float>(30, 0), 0.1f);
	GameData::getInstance()->world->createNewObject(rocket);
	*/
	this->timer.reset("rocket");
}

void					Player::laser(Laser::Type laserType)
{
	Laser				*laser;

	if (!this->timer.eventDone("laser")) return;
	laser = new Laser(laserType, this->geometry->getPosition() + t2Vector<unsigned int>(25, 0));
	laser->geometry->applyImpulse(t2Vector<float>(30, 0), 0.1f);
	GameData::getInstance()->world->createNewObject(laser);
	this->timer.reset("laser");
}

void					Player::chargeShot()
{
	if (this->timer.eventExists("chargeShot1"))
	{
		this->chargeShotLoading->changeEntity(this->chargeShotEntity);
		if (this->timer.eventDone("chargeShot1") && !this->timer.eventExists("chargeShot2"))
		{
			this->timer.addNewEvent("chargeShot2", 2);
			this->chargeShot2.play();
		}
	}
	else
	{
		this->timer.addNewEvent("chargeShot1", 2);
		this->chargeShot1.play();
	}
}

void					Player::unleashShot()
{
	Laser				*laser = NULL;
	Rocket				*rocket = NULL;

	this->chargeShotLoading->removeEntity(this->chargeShotEntity->getId());
	if (this->timer.eventDone("chargeShot2"))
	{
		laser = new Laser(Laser::ChargeShot, this->geometry->getPosition() + t2Vector<unsigned int>(30, 0));
		rocket = new Rocket(Rocket::Energy, this->geometry->getPosition() + t2Vector<int>(60, 30));
		rocket->geometry->applyImpulse(t2Vector<float>(30, 15), 0.2f);
		GameData::getInstance()->world->createNewObject(rocket);
		rocket = new Rocket(Rocket::Energy, this->geometry->getPosition() + t2Vector<int>(60, -30));
		rocket->geometry->applyImpulse(t2Vector<float>(30, -15), 0.2f);
		GameData::getInstance()->world->createNewObject(rocket);
		rocket = new Rocket(Rocket::Energy, this->geometry->getPosition() + t2Vector<int>(60, 14));
		rocket->geometry->applyImpulse(t2Vector<float>(30, 7.5f), 0.2f);
		GameData::getInstance()->world->createNewObject(rocket);
		rocket = new Rocket(Rocket::Energy, this->geometry->getPosition() + t2Vector<int>(60, -14));
		rocket->geometry->applyImpulse(t2Vector<float>(30, -7.5f), 0.2f);
		GameData::getInstance()->world->createNewObject(rocket);
	}
	else if (this->timer.eventDone("chargeShot1"))
	{
		laser = new Laser(Laser::MiddleChargeShot, this->geometry->getPosition() + t2Vector<unsigned int>(27, 0));
		rocket = new Rocket(Rocket::LowEnergy, this->geometry->getPosition() + t2Vector<int>(60, 14));
		rocket->geometry->applyImpulse(t2Vector<float>(30, 7.5f), 0.2f);
		GameData::getInstance()->world->createNewObject(rocket);
		rocket = new Rocket(Rocket::LowEnergy, this->geometry->getPosition() + t2Vector<int>(60, -14));
		rocket->geometry->applyImpulse(t2Vector<float>(30, -7.5f), 0.2f);
		GameData::getInstance()->world->createNewObject(rocket);
	}
	
	this->chargeShot1.stop();
	this->chargeShot2.stop();
	this->timer.removeEvent("chargeShot1").removeEvent("chargeShot2");
	
	if (laser != NULL)
	{
		laser->geometry->applyImpulse(t2Vector<float>(30, 0), 0.1f);
		GameData::getInstance()->world->createNewObject(laser);
	}
}