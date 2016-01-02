//
// Created by rustam_t on 12/15/15.
//

#include					"GameData.h"
#include					"Rocket.hpp"
#include					"Explosion.h"

Rocket::Rocket(Rocket::Type _type, t2Vector<int> _position) : Object(), rocketType(_type)
{
	switch (this->rocketType)
	{
	case Rocket::Energy:
		this->explosionEnum = static_cast<unsigned char >(Explosion::Energy);
		this->se.setBuffer(*ResourcesBank::getInstance()->getSoundBuffer("BombEnergy"));
		this->initialState = 147;
		this->identifier = GameData::RocketStrongLaser;
		break;
	case Rocket::LowPhysic:
		this->explosionEnum = static_cast<unsigned char >(Explosion::SmallPhysic);
		this->se.setBuffer(*ResourcesBank::getInstance()->getSoundBuffer("Bomb"));
		this->timer.addNewEvent("rotation", 0.2f);
		this->initialState = 104;
		this->identifier = GameData::RocketWeakPhysic;
		break;
	case Rocket::Physic:
		this->explosionEnum = static_cast<unsigned char >(Explosion::Physic);
		this->se.setBuffer(*ResourcesBank::getInstance()->getSoundBuffer("BombPhysic"));
		this->initialState = 139;
		this->identifier = GameData::RocketStrongPhysic;
		break;
	default: // Rocket::LowEnergy
		this->explosionEnum = static_cast<unsigned char >(Explosion::SmallEnergy);
		this->se.setBuffer(*ResourcesBank::getInstance()->getSoundBuffer("BombLaser"));
		this->timer.addNewEvent("rotation", 0.2f);
		this->initialState = 100;
		this->identifier = GameData::RocketWeakLaser;
		break;
	}

	this->geometry = new Geometry(Rectangle<float>(t2Vector<int>(12, 12), _position), 1000, 1);
	this->geometry->attachToObject(this);
    this->type = Object::Projectile;
    this->id = Object::getId();
}

void						Rocket::start()
{
	ResourcesBank			*resourceBank = ResourcesBank::getInstance();

	this->entity = new AnimationEntity(this->getId(), this->initialState, this->geometry->getPosition());
	this->timer.addNewEvent("autoDestruction", 2);
	this->timer.addNewEvent("Destruction", 3);

	if (!(this->animation = resourceBank->getAnimation("Bullets")))
	{
		this->animation = new Animation("Bullets", t2Vector<unsigned int>(12, 12), t2Vector<unsigned int>(0, 0), t2Vector<unsigned int>(25, 9));
		resourceBank->setAnimation("Bullets", this->animation);
	}
	this->animation->changeEntity(this->entity);
	this->se.play();
}

Object						*Rocket::clone(SerializedObject *serializedObject)
{
	Rocket					*newObject = new Rocket(this->rocketType, this->geometry->getPosition());

	newObject->setValues(serializedObject);
	return (newObject);
}

void						Rocket::interact(Object *object)
{
	switch (object->getType())
	{
	case (Object::Character):
		return;
	default:
		this->timer.addNewEvent("Destruction", 0);
		break;
    }
}

void						Rocket::lateUpdate()
{
	Explosion				*explosion;

	if (this->mustBeDeleted())
		this->animation->removeEntity(this->entity->getId());
	this->entity->setPosition(this->geometry->getPosition() - this->geometry->getSize() / 2);
	if (this->timer.eventDone("autoDestruction"))
		this->geometry->removeImpulse();
	if (this->timer.eventDone("Destruction"))
	{
		explosion = new Explosion(static_cast<Explosion::Type>(this->explosionEnum), this->geometry->getPosition());
		GameData::getInstance()->world->createNewObject(explosion);
		this->setToDelete();
		this->animation->removeEntity(this->entity->getId());
	}
	if (this->timer.eventDone("rotation"))
	{
		this->entity->setState((this->entity->getState() + 25) > this->initialState + 52 ? (this->timer.eventDone("autoDestruction") ? this->initialState + 2 : this->initialState + 1) : (this->entity->getState() + 25));
		this->timer.reset("rotation");
	}
}