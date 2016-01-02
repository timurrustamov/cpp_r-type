//
// Created by rustam_t on 12/14/15.
//

#include "GameData.h"
#include "WallOfPain.hpp"

Wall::Wall(t2Vector<int> size, t2Vector<int> position) {

    this->geometry = new Geometry(Rectangle<float>(size, position), 0, 0);
    this->geometry->attachToObject(this);
    this->type = Object::WallOfPain;
    this->id = Object::getId();
}

Wall::Wall(int sizex, int sizey, int x, int y) {

    this->geometry = new Geometry(Rectangle<float>(t2Vector<int>(sizex, sizey), t2Vector<int>(x, y)), 0, 0);
    this->geometry->attachToObject(this);
    this->type = Object::WallOfPain;
    this->id = Object::getId();
}

Object *
Wall::clone(SerializedObject *serializedObject)
{
	Wall				*newObject = new Wall(this->geometry->getSize(), this->geometry->getPosition());

	newObject->setValues(serializedObject);
	return (newObject);
}

void
Wall::interact(ATTR_UNUSED Object *object)
{
    return;
}

void Wall::lateUpdate() { return; };
void Wall::start() { return; };