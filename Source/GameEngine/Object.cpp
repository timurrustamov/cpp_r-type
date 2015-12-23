#include				"Object.h"

Object::Object(Geometry *_geo, std::string const &_name, Type _type) : geometry(_geo), name(_name), type(_type)
{
	this->to_delete = false;
	this->id = getNewId();
	this->entity.setId(this->id);
}

Object::Object(Geometry &_geo, std::string const &_name, Type _type) : geometry(&_geo), name(_name), type(_type)
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

const std::string &
Object::getName() const {

	return (this->name);
}
