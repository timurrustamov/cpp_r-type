//
// Created by rustam_t on 12/14/15.
//

#include "WallOfPain.hpp"

Wall::Wall(t2Vector<int> size, t2Vector<int> position) {

    this->geometry = new Geometry(Rectangle<float>(size, position), 0, 0);
    this->geometry->attachToObject(this);
    this->name = "invisiblewall";
    this->type = Object::WallOfPain;
    this->id = Object::getId();
}

Wall::Wall(int sizex, int sizey, int x, int y) {

    this->geometry = new Geometry(Rectangle<float>(t2Vector<int>(sizex, sizey), t2Vector<int>(x, y)), 0, 0);
    this->geometry->attachToObject(this);
    this->name = "invisiblewall";
    this->type = Object::WallOfPain;
    this->id = Object::getId();
}

void
Wall::interact(Object *object)
{
    switch (object->getType())
    {
        case (WallOfPain) :
            return;
        default :
            return (object->interact(this));
    }
}

void Wall::lateUpdate() { return; };
void Wall::start() { return; };