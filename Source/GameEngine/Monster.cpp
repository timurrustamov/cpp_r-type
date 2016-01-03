#include						"Monster.h"

#include						"../Monsters/BasicShip.h"
#include						"../Monsters/Meteora.h"
#include						"../Monsters/Nautilus.h"
#include						"../Monsters/Robot.h"

Monster::Monster(std::string _dll, t2Vector<int> _position) : Object(), dll(_dll)
{
	this->type = Object::Ennemy;
	this->id = Object::getId();
	this->geometry = new Geometry(Rectangle<float>(t2Vector<float>(0, 0), _position));
	this->geometry->attachToObject(this);

	// nul à changer =>
	if (this->dll == "Meteora")
	{
		this->setIdentifier(66); // NUL A CHIER A CHANGER
		this->behaviour = new Meteora();
	}
	else if (this->dll == "Nautilus")
	{
		this->setIdentifier(67); // NUL A CHIER A CHANGER
		this->behaviour = new Nautilus();
	}
	else if (this->dll == "Robot")
	{
		this->setIdentifier(68); // NUL A CHIER A CHANGER
		this->behaviour = new Robot();
	}
	else
	{
		this->setIdentifier(69); // NUL A CHIER A CHANGER
		this->behaviour = new BasicShip();
	}
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