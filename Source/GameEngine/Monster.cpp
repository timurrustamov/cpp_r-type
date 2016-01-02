#include						"Monster.h"

#include "../Monsters/BasicShip.h"
Monster::Monster(std::string _dll, t2Vector<int> _position) : Object(), dll(_dll)
{
	this->type = Object::Ennemy;
	this->id = Object::getId();
	this->geometry = new Geometry(Rectangle<float>(t2Vector<float>(0, 0), _position));
	this->geometry->attachToObject(this);
	this->behaviour = new BasicShip();
	this->start();
}

void							Monster::start()
{
	this->behaviour->start(this);
}

Monster::~Monster()
{
	this->behaviour->onDestroy();
}

Object							*Monster::clone(SerializedObject *serializedObject)
{
	Monster						*newObject = new Monster(this->dll, this->geometry->getPosition());

	newObject->setValues(serializedObject);
	return (newObject);
}

void							Monster::interact(Object *other)
{
	this->behaviour->interact(other);
}

void							Monster::lateUpdate()
{
	this->behaviour->lateUpdate();
}