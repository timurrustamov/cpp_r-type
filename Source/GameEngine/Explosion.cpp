#include				"GameData.h"
#include				"Explosion.h"

Explosion::Explosion(Explosion::Type type, t2Vector<int> position) : Object(), explosionType(type)
{
	switch (this->explosionType)
	{
	case Explosion::Energy:
		this->animationID = "Explode4";
		this->se.setBuffer(*ResourcesBank::getInstance()->getSoundBuffer("Explosion2"));
		this->size = t2Vector<int>(47, 46);
		this->grid = t2Vector<unsigned int>(4, 2);
		this->impulseFactor = 100;
		this->identifier = GameData::ExplosionStrongLaser;
		break;
	case Explosion::Physic:
		this->animationID = "Explode3";
		this->se.setBuffer(*ResourcesBank::getInstance()->getSoundBuffer("Explosion1"));
		this->size = t2Vector<int>(47, 46);
		this->grid = t2Vector<unsigned int>(4, 2);
		this->impulseFactor = 150;
		this->identifier = GameData::ExplosionStrongPhysic;
		break;
	case Explosion::SmallPhysic:
		this->animationID = "Explode1";
		this->se.setBuffer(*ResourcesBank::getInstance()->getSoundBuffer("Explosion3"));
		this->size = t2Vector<int>(24, 23);
		this->grid = t2Vector<unsigned int>(8, 1);
		this->impulseFactor = 75;
		this->identifier = GameData::ExplosionWeakPhysic;
		break;
	default: // Explosion::SmallEnergy
		this->animationID = "Explode2";
		this->size = t2Vector<int>(24, 23);
		this->grid = t2Vector<unsigned int>(6, 1);
		this->impulseFactor = 50;
		this->identifier = GameData::ExplosionWeakLaser;
		break;
	}

	this->geometry = new Geometry(Rectangle<float>(this->size, position));
	this->geometry->attachToObject(this);
	this->type = Object::Force;
	this->id = Object::getId();
}

void					Explosion::start()
{
	ResourcesBank		*resourceBank = ResourcesBank::getInstance();

	this->entity = new AnimationEntity(this->getId(), 0, this->geometry->getPosition());
	this->timer.addNewEvent("nextStep", 0.1f);
	this->timer.addNewEvent("impulseEnd", 0.15f);

	if (!(this->animation = resourceBank->getAnimation(this->animationID)))
	{
		this->animation = new Animation(this->animationID, this->size, t2Vector<unsigned int>(0, 0), this->grid);
		resourceBank->setAnimation(this->animationID, this->animation);
	}
	this->animation->changeEntity(this->entity);
	if (this->se.getBuffer() != NULL)
		this->se.play();
}

Object					*Explosion::clone(SerializedObject *serializedObject)
{
	Explosion			*newObject = new Explosion(this->explosionType, this->geometry->getPosition());

	newObject->setValues(serializedObject);
	return (newObject);
}

void					Explosion::interact(Object *object)
{
	Geometry *geo1 = this->geometry;
	Geometry *geo2 = object->geometry;

	if (this->timer.eventDone("impulseEnd") || object->getType() == Object::Radiation || object->getType() == Object::Type::Other)
		return;
	geo2->applyImpulse((geo2->getPosition() - geo1->getPosition()).normalize() * static_cast<float>(this->impulseFactor) / 10, 0.1);
}

void					Explosion::lateUpdate()
{
	this->entity->setPosition(this->geometry->getPosition() - this->geometry->getSize() / 2);
	if (this->timer.eventDone("impulseEnd"))
		this->type = Object::Other;
	if (this->timer.eventDone("nextStep"))
	{
		this->entity->setState(this->entity->getState() + 1);
		this->timer.reset("nextStep");
		if (this->entity->getState() > this->grid.getX() * this->grid.getY())
		{
			this->setToDelete();
			this->animation->removeEntity(this->entity->getId());
		}
	}
}