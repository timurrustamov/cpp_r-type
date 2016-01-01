#include					"GameData.h"
#include					"Laser.h"

Laser::Laser(Laser::Type _type, t2Vector<int> _position) : Object(), laserType(_type)
{
	switch (this->laserType)
	{
	case Laser::MiddleChargeShot:
		this->geometry = new Geometry(Rectangle<float>(t2Vector<int>(48, 14), _position), 700);
		this->se.setBuffer(*ResourcesBank::getInstance()->getSoundBuffer("Shoot2"));
		this->gridPosition = t2Vector<unsigned int>(166, 136);
		this->animationID = "MiddleChargeShot";
		break;
	case Laser::ChargeShot:
		this->geometry = new Geometry(Rectangle<float>(t2Vector<int>(80, 16), _position), 1400);
		this->se.setBuffer(*ResourcesBank::getInstance()->getSoundBuffer("Explosion2"));
		this->gridPosition = t2Vector<unsigned int>(103, 170);
		this->animationID = "ChargeShot";
		break;
	default: // shot
		this->geometry = new Geometry(Rectangle<float>(t2Vector<int>(15, 4), _position), 350);
		this->se.setBuffer(*ResourcesBank::getInstance()->getSoundBuffer("Shoot1"));
		this->gridPosition = t2Vector<unsigned int>(234, 107);
		this->animationID = "Shot";
		break;
	}

	this->timer.addNewEvent("Destruction", 10);
	this->timer.addNewEvent("rotation", 0.2f);
	this->geometry->attachToObject(this);
	this->type = Object::Radiation;
	this->id = Object::getId();
	this->start();
}

void						Laser::start()
{
	ResourcesBank			*resourceBank = ResourcesBank::getInstance();

	this->entity = new AnimationEntity(this->getId(), 0, this->geometry->getPosition());

	if (!(this->animation = resourceBank->getAnimation(this->animationID)))
	{
		this->animation = new Animation(this->animationID, ResourcesBank::getInstance()->getTexture("Player"), this->geometry->getSize(), this->gridPosition, t2Vector<unsigned int>(2, 1));
		resourceBank->setAnimation(this->animationID, this->animation);
	}
	this->animation->changeEntity(this->entity);
	this->se.setVolume(66.6);
	this->se.play();
}

Object						*Laser::clone(SerializedObject *serializedObject)
{
	Laser					*newObject = new Laser(this->laserType, this->geometry->getPosition());

	newObject->setValues(serializedObject);
	return (newObject);
}

void						Laser::interact(Object *object)
{
	if (this->type == Laser::ChargeShot) return;
	switch (object->getType())
	{
	case (Object::Character):
		return;
	case (Object::Radiation):
		return;
	default:
		this->timer.addNewEvent("Destruction", 0);
		break;
	}
}

void						Laser::lateUpdate()
{
	if (this->mustBeDeleted())
		this->animation->removeEntity(this->entity->getId());
	this->entity->setPosition(this->geometry->getPosition() - this->geometry->getSize() / 2);
	if (this->timer.eventDone("Destruction"))
	{
		this->setToDelete();
		this->animation->removeEntity(this->entity->getId());
	}
	else if (this->timer.eventDone("rotation"))
	{
		this->entity->setState(this->entity->getState() ^ 1);
		this->timer.reset("rotation");
	}
}