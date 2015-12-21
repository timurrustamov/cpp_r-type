//
// Created by rustam_t on 12/14/15.
//

#include "Player.hpp"

Player::Player(t2Vector<int> position, unsigned int playerNo) : Object()
{
    this->geometry = new Geometry(Rectangle<float>(t2Vector<int>(32, 16), position), 150, 5);
    this->geometry->attachToObject(*this);
    this->name = "player";
    this->type = Object::Character;
    this->id = Object::getId();
    this->playerNo = playerNo;
}

Player::Player(int x, int y, unsigned int playerNo)
{
    this->geometry = new Geometry(Rectangle<float>(t2Vector<int>(32, 16), t2Vector<int>(x, y)), 150, 5);
    this->geometry->attachToObject(*this);
    this->name = "player";
    this->type = Object::Character;
    this->id = Object::getId();
    this->playerNo = playerNo;
}

unsigned int
Player::getPlayerNo() const
{
    return (this->playerNo);
}

void
Player::interact(Object *object)
{
    Geometry *geo1 = this->geometry;
    Geometry *geo2 = object->geometry;

    switch (object->getType())
    {
        default :
            geo1->removeImpulse();
            geo2->applyImpulse((geo2->getPosition() - geo1->getPosition()) * 500, 0.1);

            if (geo1->getRect().touchUpper(geo2->getRect()) || geo1->getRect().touchLower(geo2->getRect()))
                geo1->velocity().y() *= -1;
            if (geo1->getRect().touchLeft(geo2->getRect()) || geo1->getRect().touchRight(geo2->getRect()))
                geo1->velocity().x() *= -1;
            geo1->setPosition(geo1->getPreviousPosition(1));
            break;
    }
}
