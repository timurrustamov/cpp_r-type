#include						"../GameEngine/Artifices.h"
#include						"../GameEngine/GameData.h"
#include						"Nautilus.h"

void							Nautilus::start(Object * const that)
{
	ResourcesBank				*resourceBank = ResourcesBank::getInstance();

	this->life = 5;
	this->object = that;
	this->upValve = true;
	this->object->geometry->setMaxVelocity(75);
	this->object->geometry->setSize(t2Vector<unsigned int>(63, 50));
	this->entity = new AnimationEntity(this->object->getId(), 2, this->object->geometry->getPosition());

	if (!(this->animation = resourceBank->getAnimation("Nautilus")) || !(this->animationHit = resourceBank->getAnimation("Nautilus-Hit")))
	{
		this->animation = new Animation("Nautilus", this->object->geometry->getSize(), t2Vector<unsigned int>(0, 0), t2Vector<unsigned int>(5, 1));
		this->animationHit = new Animation("Nautilus-Hit", this->object->geometry->getSize(), t2Vector<unsigned int>(0, 0), t2Vector<unsigned int>(5, 1));
		resourceBank->setAnimation("Nautilus", this->animation);
		resourceBank->setAnimation("Nautilus-Hit", this->animationHit);
	}
	this->animation->changeEntity(this->entity);

	this->object->timer.addNewEvent("rotation", 0.2f);
	this->object->timer.addNewEvent("invincibility", 0.1f);
}

void							Nautilus::lateUpdate()
{
	this->entity->setPosition(this->object->geometry->getPosition() - this->object->geometry->getSize() / 2);
	if (this->object->timer.eventDone("rotation"))
	{
		unsigned int			state = this->entity->getState();

		if (state == 4)
		{
			this->object->geometry->applyImpulse(t2Vector<float>(-5, 10), 0.1f);
			this->upValve = false;
		}
		else if (state == 0)
		{
			this->object->geometry->applyImpulse(t2Vector<float>(-5, -10), 0.1f);
			this->upValve = true;
		}
		else if (state == 2 && rand() % 4 == 0)
		{
			Rocket				*rocket = new Rocket(Rocket::Physic, this->object->geometry->getPosition() - t2Vector<float>(this->object->geometry->getSize().getX(), 0));
			rocket->geometry->applyImpulse(t2Vector<float>(-30, 0), 0.1f);
			GameData::getInstance()->world->createNewObject(rocket);
		}

		this->entity->setState(state + ((this->upValve) ? 1 : -1));
		this->object->timer.reset("rotation");
	}

	if (!this->object->timer.eventDone("invincibility"))
		this->animationHit->changeEntity(this->entity);
	else
		this->animationHit->removeEntity(this->entity->getId());
}

void							Nautilus::interact(Object *other)
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

void        					Nautilus::parseConfig(std::string)
{

}

void        					Nautilus::onDestroy()
{
	Artifices					*artifice = new Artifices(Artifices::Explosion, this->object->geometry->getPosition());
	GameData::getInstance()->world->createNewObject(artifice);

	this->animation->removeEntity(this->entity->getId());
	this->animationHit->removeEntity(this->entity->getId());
}