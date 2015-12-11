#include				"Object.h"

Object::Object(Geometry *_geo, std::string const &_name, Type _type) : geometry(_geo), name(_name), type(_type)
{
	this->id = getId();
}

Object::Object(Geometry &_geo, std::string const &_name, Type _type) : geometry(&_geo), name(_name), type(_type)
{
	this->id = getId();
}

Object::~Object()
{
	delete this->geometry;
}

unsigned int				Object::getId()
{
	static unsigned int		id = 0;

	return (id++);
}