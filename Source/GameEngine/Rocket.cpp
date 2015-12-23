//
// Created by rustam_t on 12/15/15.
//

#include "GameData.h"
#include "Rocket.hpp"
#include "Explosion.h"

Rocket::Rocket(t2Vector<int> position) : Object()
{
    this->geometry = new Geometry(Rectangle<float>(t2Vector<int>(10, 10), position), 1000, 2);
    this->geometry->attachToObject(this);
    this->name = "rocket";
    this->type = Object::Projectile;
    this->id = Object::getId();
	this->start();
}

void
Rocket::start()
{
	ResourcesBank		*resourceBank = ResourcesBank::getInstance();

	this->entity = new AnimationEntity(this->getId(), 100, this->geometry->getPosition());
	this->timer.addNewEvent("rotation", 0.2f);
	this->timer.addNewEvent("autoDestruction", 2);
	this->timer.addNewEvent("Destruction", 3);

	if (!resourceBank->getAnimations())
		return;
	if (!(this->animation = resourceBank->getAnimation("Bullets")))
	{
		this->animation = new Animation("Bullets", t2Vector<unsigned int>(12, 12), t2Vector<unsigned int>(0, 0), t2Vector<unsigned int>(25, 9));
		resourceBank->setAnimation("Bullets", this->animation);
	}
	this->animation->changeEntity(this->entity);
}

void
Rocket::interact(Object *object)
{
    Geometry *geo1 = this->geometry;
    Geometry *geo2 = object->geometry;

    switch (object->getType())
    {
	case (Object::Character) :
		return;
	default :
		geo1->removeImpulse();
        geo2->applyImpulse((geo2->getPosition() - geo1->getPosition()) * 100, 0.3);
		if (geo1->getRect().touchUpper(geo2->getRect()) || geo1->getRect().touchLower(geo2->getRect()))
			geo1->velocity().y() *= -1;
		if (geo1->getRect().touchLeft(geo2->getRect()) || geo1->getRect().touchRight(geo2->getRect()))
			geo1->velocity().x() *= -1;
        geo1->setPosition(geo1->getPreviousPosition(0));
		break;
    }
}

void			Rocket::lateUpdate()
{
	GameData	*gameData;
	Explosion	*explosion;

	this->entity->setPosition(this->geometry->getPosition() - this->geometry->getSize() / 2);
	if (this->timer.eventDone("autoDestruction"))
		this->geometry->removeImpulse();
	if (this->timer.eventDone("Destruction"))
	{
		gameData = GameData::getInstance();
		explosion = new Explosion(Explosion::Type::SmallEnergy, true, this->geometry->getPosition());
		gameData->world->createNewObject(explosion);
		this->setToDelete();
		this->animation->removeEntity(this->entity->getId());
	}
	if (this->timer.eventDone("rotation"))
	{
		this->entity->setState((this->entity->getState() + 25) > 152 ? (this->timer.eventDone("autoDestruction") ? 102 : 101) : (this->entity->getState() + 25));
		this->timer.reset("rotation");
	}
}