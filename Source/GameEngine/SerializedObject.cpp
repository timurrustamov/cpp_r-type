//
// Created by rustam_t on 12/16/15.
//

#include "SerializedObject.hpp"

SerializedObject::SerializedObject(Object &obj)
{
    this->attr.id = obj.getId();
    this->attr.name = obj.getName();
    if ((this->attr.type = obj.getType()) == Object::Character)
        this->attr.playerId = (dynamic_cast<Player &>(obj)).getPlayerNo();
    else
        this->attr.playerId = BAD_ID;
    this->attr.sizex = obj.geometry->getSize().getX();
    this->attr.sizey = obj.geometry->getSize().getY();
    this->attr.positionx = obj.geometry->getPosition().getX();
    this->attr.positiony = obj.geometry->getPosition().getY();
    this->attr.intertia = obj.geometry->getInertia();
    this->attr.maxVelocity = obj.geometry->getMaxVelocity();
    this->attr.velocityx = obj.geometry->getVelocity().getX();
    this->attr.velocityy = obj.geometry->getVelocity().getY();
    this->inited = true;
}

SerializedObject::SerializedObject(std::vector<unsigned char> &binaryString)
{
    if (binaryString.size() >= sizeof(ObjectAttributes)) {
        std::memcpy(&(this->attr), &binaryString[0], sizeof(ObjectAttributes));
        this->inited = true;
    }
}

std::vector<unsigned char> &
SerializedObject::toBinaryString() {

    this->binaryString.resize(sizeof(ObjectAttributes));
    std::memcpy(&this->binaryString[0], &this->attr, sizeof(ObjectAttributes));
    return (this->binaryString);
}

bool SerializedObject::isInited() const {

    return (this->inited);
}

SerializedObject::SerializedObject(unsigned char *tmp, unsigned long int length) {

    if (length < sizeof(ObjectAttributes))
        return;
    std::memcpy(&this->attr, tmp, sizeof(ObjectAttributes));
    this->inited = true;
}
