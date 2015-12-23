//
// Created by rustam_t on 12/16/15.
//

#ifndef CPP_R_TYPECPY2_SERIALIZEDOBJECT_HPP
#define CPP_R_TYPECPY2_SERIALIZEDOBJECT_HPP

#include <cstddef>
#include <cstring>
#include "Object.h"
#include "Player.hpp"

struct ObjectAttributes
{
    unsigned int    id;
    unsigned int    playerId;
    Object::Type    type;
    std::string     name;
    int             sizex;
    int             sizey;
    float           positionx;
    float           positiony;
    float           maxVelocity;
    float           intertia;
    float           velocityx;
    float           velocityy;
};

class SerializedObject {

public:

    SerializedObject(Object &obj);
    SerializedObject(std::vector<unsigned char> &binaryString);
    SerializedObject(unsigned char *tmp, unsigned long int length);
    ~SerializedObject() {};

    bool                        isInited() const;
    std::vector<unsigned char>  &toBinaryString();
    ObjectAttributes attr;

private:
    bool                       inited;
    std::vector<unsigned char> binaryString;
};


#endif //CPP_R_TYPECPY2_SERIALIZEDOBJECT_HPP