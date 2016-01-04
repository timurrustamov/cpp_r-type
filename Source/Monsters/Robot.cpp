#include						"../GameEngine/Artifices.h"
#include						"../GameEngine/GameData.h"
#include						"Robot.h"

void							Robot::start(Object * const that)
{
	ResourcesBank				*resourceBank = ResourcesBank::getInstance();

	this->life = 500;
	this->object = that;
	this->freeFall = true;
	this->object->geometry->setMaxVelocity(200);
	this->object->geometry->setSize(t2Vector<unsigned int>(60, 47));
	this->entity = new AnimationEntity(this->object->getId(), 7, this->object->geometry->getPosition());

	if (!(this->animation = resourceBank->getAnimation("Robot")) || !(this->animationHit = resourceBank->getAnimation("Robot-Hit")))
	{
		this->animation = new Animation("Robot", this->object->geometry->getSize(), t2Vector<unsigned int>(0, 0), t2Vector<unsigned int>(5, 2));
		this->animationHit = new Animation("Robot-Hit", this->object->geometry->getSize(), t2Vector<unsigned int>(0, 0), t2Vector<unsigned int>(5, 2));
		resourceBank->setAnimation("Robot", this->animation);
		resourceBank->setAnimation("Robot-Hit", this->animationHit);
	}
	this->animation->changeEntity(this->entity);

	this->object->timer.addNewEvent("rotation", 0.1f);
	this->object->timer.addNewEvent("fly", 0.5f + static_cast<float>((rand() % 100)) / 100);
	this->object->timer.addNewEvent("invincibility", 0.1f);
}

void							Robot::lateUpdate()
{
	this->entity->setPosition(this->object->geometry->getPosition() - this->object->geometry->getSize() / 2);
	if (this->freeFall)
	{
		this->object->geometry->addImpulse(t2Vector<float>(0, 0.05f));
		this->entity->setState(7);
	}
	else
	{
		this->object->geometry->addImpulse(t2Vector<float>(-10, 0));
		if (this->object->timer.eventDone("rotation"))
		{
			this->entity->setState((this->entity->getState() + 1) % 5);
			this->object->timer.reset("rotation");
		}
	}

	if (this->object->timer.eventExists("landing"))
	{
		this->object->geometry->setVelocity(t2Vector<float>(0, 0));
		this->object->geometry->applyImpulse(t2Vector<float>(0, 0), 0.1f);
		if (this->object->timer.eventDone("landing"))
			this->object->timer.removeEvent("landing");
		else
			this->entity->setState(8);
	}
	else if (this->object->timer.eventDone("fly") && this->freeFall == false)
	{
		this->object->geometry->applyImpulse(t2Vector<float>(-100, -1000), 1);
		this->object->geometry->setPosition(this->object->geometry->getPosition() + t2Vector<float>(0, -10));
		this->freeFall = true;
		this->object->timer.reset("fly");
		this->entity->setState(5);
	}

	if (!this->object->timer.eventDone("invincibility"))
		this->animationHit->changeEntity(this->entity);
	else
		this->animationHit->removeEntity(this->entity->getId());
}

void							Robot::interact(Object *other)
{
	/*
	if (other->getType() == Object::WallOfPain)
		this->object->setToDelete();
	*/
	// for testing purpose:
	if (other->getType() == Object::WallOfPain && this->freeFall)
	{
		this->freeFall = false;
		this->object->timer.reset("fly");
		this->object->timer.addNewEvent("landing", 0.5f);
		this->object->geometry->setVelocity(t2Vector<float>(0, 0));
		this->object->geometry->applyImpulse(t2Vector<float>(0, 0), 0.1f);
	}
	else if (this->object->timer.eventDone("invincibility") && other->getType() != Object::WallOfPain) // change here too
	{
		if (--this->life <= 0)
			this->object->setToDelete();
		if (other->getType() == Object::Radiation || other->getType() == Object::Projectile)
			this->object->timer.reset("invincibility");
	}
}

void        					Robot::parseConfig(std::string)
{

}

void        					Robot::onDestroy()
{
	Artifices					*artifice = new Artifices(Artifices::Explosion, this->object->geometry->getPosition());
	
	if (GameData::getInstance()->world != NULL)
		GameData::getInstance()->world->createNewObject(artifice);
	this->animation->removeEntity(this->entity->getId());
	this->animationHit->removeEntity(this->entity->getId());
}

Animation						*Robot::getAnimationSheet() const
{
	return (this->animation);
}