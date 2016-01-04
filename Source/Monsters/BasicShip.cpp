#include						"../GameEngine/Artifices.h"
#include						"../GameEngine/GameData.h"
#include						"BasicShip.h"

void							BasicShip::start(Object * const that)
{
	ResourcesBank				*resourceBank = ResourcesBank::getInstance();

	this->life = 3;
	this->object = that;
	this->object->geometry->setSize(t2Vector<unsigned int>(21, 24));
	this->object->geometry->setMaxVelocity(100);
	this->entity = new AnimationEntity(this->object->getId(), 0, this->object->geometry->getPosition());

	if (!(this->animation = resourceBank->getAnimation("BasicShip")) || !(this->animationHit = resourceBank->getAnimation("BasicShip-Hit")))
	{
		this->animation = new Animation("BasicShip", this->object->geometry->getSize(), t2Vector<unsigned int>(0, 0), t2Vector<unsigned int>(8, 1));
		this->animationHit = new Animation("BasicShip-Hit", this->object->geometry->getSize(), t2Vector<unsigned int>(0, 0), t2Vector<unsigned int>(8, 1));
		resourceBank->setAnimation("BasicShip", this->animation);
		resourceBank->setAnimation("BasicShip-Hit", this->animationHit);
	}
	this->animation->changeEntity(this->entity);

	this->object->timer.addNewEvent("rotation", 0.2f);
	this->object->timer.addNewEvent("invincibility", 0.1f);
}

void							BasicShip::lateUpdate()
{
	this->entity->setPosition(this->object->geometry->getPosition() - this->object->geometry->getSize() / 2);
	this->object->geometry->addImpulse(t2Vector<float>(-1, 0));
	if (this->object->timer.eventDone("rotation"))
	{
		this->entity->setState((this->entity->getState() + 1) % 8);
		this->object->timer.reset("rotation");
	}

	if (!this->object->timer.eventDone("invincibility"))
		this->animationHit->changeEntity(this->entity);
	else
		this->animationHit->removeEntity(this->entity->getId());
}

void							BasicShip::interact(Object *other)
{
	if (other->getType() == Object::WallOfPain)
		this->object->setToDelete();
	else if (this->object->timer.eventDone("invincibility"))
	{
		if (--this->life <= 0)
			this->object->setToDelete();
		if (other->getType() == Object::Radiation || other->getType() == Object::Projectile)
			this->object->timer.reset("invincibility");
	}
}

void        					BasicShip::parseConfig(std::string)
{

}

void        					BasicShip::onDestroy()
{
	Artifices					*artifice = new Artifices(Artifices::Explosion, this->object->geometry->getPosition());

	if (GameData::getInstance()->world != NULL)
		GameData::getInstance()->world->createNewObject(artifice);
	this->animation->removeEntity(this->entity->getId());
	this->animationHit->removeEntity(this->entity->getId());
}

Animation						*BasicShip::getAnimationSheet() const
{
	return (this->animation);
}