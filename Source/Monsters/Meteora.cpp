#include						"../GameEngine/Artifices.h"
#include						"../GameEngine/GameData.h"
#include						"Meteora.h"

void							Meteora::start(Object * const that)
{
	ResourcesBank				*resourceBank = ResourcesBank::getInstance();

	this->life = 20;
	this->object = that;
	this->object->geometry->setSize(t2Vector<unsigned int>(33, 33));
	this->object->geometry->setMaxVelocity(40);
	this->entity = new AnimationEntity(this->object->getId(), 0, this->object->geometry->getPosition());

	if (!(this->animation = resourceBank->getAnimation("Meteora")) || !(this->animationHit = resourceBank->getAnimation("Meteora-Hit")))
	{
		this->animation = new Animation("Meteora", this->object->geometry->getSize(), t2Vector<unsigned int>(0, 0), t2Vector<unsigned int>(4, 2));
		this->animationHit = new Animation("Meteora-Hit", this->object->geometry->getSize(), t2Vector<unsigned int>(0, 0), t2Vector<unsigned int>(4, 2));
		resourceBank->setAnimation("Meteora", this->animation);
		resourceBank->setAnimation("Meteora-Hit", this->animationHit);
	}
	this->animation->changeEntity(this->entity);

	this->object->timer.addNewEvent("rotation", 0.2f);
	this->object->timer.addNewEvent("invincibility", 0.1f);
}

void							Meteora::lateUpdate()
{
	this->entity->setPosition(this->object->geometry->getPosition() - this->object->geometry->getSize() / 2);
	this->object->geometry->addImpulse(t2Vector<float>(-1, 0));
	if (this->object->timer.eventDone("rotation"))
	{
		this->entity->setState((this->entity->getState() + 1) % 4);
		this->object->timer.reset("rotation");
	}

	if (!this->object->timer.eventDone("invincibility"))
		this->animationHit->changeEntity(this->entity);
	else
		this->animationHit->removeEntity(this->entity->getId());
}

void							Meteora::interact(Object *other)
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

void        					Meteora::parseConfig(std::string)
{

}

void        					Meteora::onDestroy()
{
	Artifices					*artifice = new Artifices(Artifices::MeteoraExplosion, this->object->geometry->getPosition());
	GameData::getInstance()->world->createNewObject(artifice);

	this->animation->removeEntity(this->entity->getId());
	this->animationHit->removeEntity(this->entity->getId());
}