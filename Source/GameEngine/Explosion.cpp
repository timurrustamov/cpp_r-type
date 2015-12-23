#include				"Explosion.h"

Explosion::Explosion(Explosion::Type type, bool hurting, t2Vector<int> position) : Object()
{
	switch (this->explosionType)
	{
	case Explosion::Type::Energy:
		this->animationID = "Explode4";
		this->size = t2Vector<int>(47, 46);
		this->grid = t2Vector<unsigned int>(4, 2);
		break;
	case Explosion::Type::Physic:
		this->animationID = "Explode3";
		this->size = t2Vector<int>(47, 46);
		this->grid = t2Vector<unsigned int>(4, 2);
		break;
	case Explosion::Type::SmallPhysic:
		this->animationID = "Explode1";
		this->size = t2Vector<int>(24, 23);
		this->grid = t2Vector<unsigned int>(8, 1);
		break;
	case Explosion::Type::SmallEnergy:
		this->animationID = "Explode2";
		this->size = t2Vector<int>(24, 23);
		this->grid = t2Vector<unsigned int>(6, 1);
		break;
	default:
		this->animationID = "Explode2";
		this->size = t2Vector<int>(24, 23);
		this->grid = t2Vector<unsigned int>(6, 1);
		break;
	}

	this->geometry = new Geometry(Rectangle<float>(this->size, position));
	this->geometry->attachToObject(this);
	this->name = "explosion";
	this->type = Object::Force;
	this->explosionType = type;
	this->hurting = hurting;
	this->id = Object::getId();
	this->start();
}

void					Explosion::start()
{
	ResourcesBank		*resourceBank = ResourcesBank::getInstance();

	this->entity = new AnimationEntity(this->getId(), 0, this->geometry->getPosition());
	this->timer.addNewEvent("nextStep", 0.1f);

	if (!(this->animation = resourceBank->getAnimation(this->animationID)))
	{
		this->animation = new Animation(this->animationID, this->size, t2Vector<unsigned int>(0, 0), this->grid);
		resourceBank->setAnimation(this->animationID, this->animation);
	}
	this->animation->changeEntity(this->entity);
}

void					Explosion::interact(Object *object)
{
	return;
}

void					Explosion::lateUpdate()
{
	this->entity->setPosition(this->geometry->getPosition() - this->geometry->getSize() / 2);
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