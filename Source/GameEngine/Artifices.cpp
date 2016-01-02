#include				"GameData.h"
#include				"Artifices.h"

Artifices::Artifices(Artifices::Type type, t2Vector<int> position) : Object(), artificeType(type)
{
	switch (this->artificeType)
	{
	default: // Artifices::Explosion:
		this->animationID = "ExplosionArtifice";
		this->textureName = "Player";
		this->size = t2Vector<int>(34, 30);
		this->gridPosition = t2Vector<unsigned int>(61, 342);
		this->grid = t2Vector<unsigned int>(6, 1);
		this->minState = 0;
		this->maxState = 5;
		this->identifier = GameData::ArtificeExplosion;
		
		this->timer.addNewEvent("nextStep", 0.05f);
		this->timer.addNewEvent("destruction", 0.3f);
		break;
	}

	this->geometry = new Geometry(Rectangle<float>(this->size, position));
	this->geometry->attachToObject(this);
	this->type = Object::Other;
	this->id = Object::getId();
}

void					Artifices::start()
{
	ResourcesBank		*resourceBank = ResourcesBank::getInstance();

	this->entity = new AnimationEntity(this->getId(), this->minState, this->geometry->getPosition());
	if (!(this->animation = resourceBank->getAnimation(this->animationID)))
	{
		this->animation = new Animation(this->animationID, resourceBank->getTexture(this->textureName), this->size, this->gridPosition, this->grid);
		resourceBank->setAnimation(this->animationID, this->animation);
	}
	this->animation->changeEntity(this->entity);
}

Object					*Artifices::clone(SerializedObject *serializedObject)
{
	Artifices			*newObject = new Artifices(this->artificeType, this->geometry->getPosition());

	newObject->setValues(serializedObject);
	return (newObject);
}

void					Artifices::interact(Object *object)
{
	return;
}

void					Artifices::lateUpdate()
{
	this->entity->setPosition(this->geometry->getPosition() - this->geometry->getSize() / 2);
	if (this->timer.eventDone("nextStep"))
	{
		unsigned int	tmp = (this->entity->getState() + 1) % (this->maxState + 1);
		this->entity->setState((tmp < this->minState) ? this->minState : tmp);
		this->timer.reset("nextStep");
	}
	if (this->timer.eventDone("destruction"))
	{
		this->setToDelete();
		this->animation->removeEntity(this->entity->getId());
	}
}