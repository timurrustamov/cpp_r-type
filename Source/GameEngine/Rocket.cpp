//
// Created by rustam_t on 12/15/15.
//

#include "Rocket.hpp"

Rocket::Rocket(t2Vector<int> position) : Object()
{
    this->geometry = new Geometry(Rectangle<float>(t2Vector<int>(10, 10), position), 350, 0.1);
    this->geometry->attachToObject(*this);
    this->name = "rocket";
    this->type = Object::Projectile;
    this->id = Object::getId();
}

Rocket::Rocket(int x, int y)
{
    this->geometry = new Geometry(Rectangle<float>(t2Vector<int>(10, 10), t2Vector<int>(x, y)), 350, 0.1);
    this->geometry->attachToObject(*this);
    this->name = "rocket";
    this->type = Object::Projectile;
    this->id = Object::getId();
}

void
Rocket::interact(Object *object)
{
    Geometry *geo1 = this->geometry;
    Geometry *geo2 = object->geometry;

    switch (object->getType())
    {
        default :
            geo1->removeImpulse();
            geo2->applyImpulse((geo2->getPosition() - geo1->getPosition()) * 100, 0.3);

            if (geo1->getRect().touchUpper(geo2->getRect()) || geo1->getRect().touchLower(geo2->getRect()))
                geo1->velocity().y() *= -1;
            if (geo1->getRect().touchLeft(geo2->getRect()) || geo1->getRect().touchRight(geo2->getRect()))
                geo1->velocity().x() *= -1;
            geo1->setPosition(geo1->getPreviousPosition(1));
            break;
    }
}