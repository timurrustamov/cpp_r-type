#include				"Object.h"

Object::Object(Geometry *_geo, Type _type) : geometry(_geo), type(_type)
{
	this->to_delete = false;
	this->id = getNewId();
	this->entity.setId(this->id);
}

Object::Object(Geometry &_geo, Type _type) : geometry(&_geo), type(_type)
{
	this->to_delete = false;
	this->id = getNewId();
	this->entity.setId(this->id);
}

Object::Object()
{
	to_delete = false;
	this->id = getNewId();
	this->entity.setId(this->id);
}

Object::~Object()
{
	delete this->geometry;
}

unsigned int				Object::getId() const
{
	return (this->id);
}

unsigned int				Object::getIdentifier() const
{
	return (this->identifier);
}

unsigned int
Object::getNewId()
{
	static unsigned int		id = 0;

	return (id++);
}

Object::Type
Object::getType() const
{
	return (this->type);
}

bool Object::mustBeDeleted() const
{
	return (this->to_delete);
}

bool Object::setToDelete()
{
	this->to_delete = true;
	return (true);
}

void Object::setValues(SerializedObject *serializedObject)
{
	this->geometry->setPosition(t2Vector<float>(serializedObject->attr.positionx, serializedObject->attr.positiony));
	this->geometry->setVelocity(t2Vector<float>(serializedObject->attr.velocityx, serializedObject->attr.velocityy));
	this->geometry->setSize(t2Vector<float>(serializedObject->attr.sizex, serializedObject->attr.sizey));
	this->geometry->setInertie(serializedObject->attr.intertia);
	this->geometry->setMaxVelocity(serializedObject->attr.maxVelocity);
}