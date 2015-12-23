//
// Created by rustam_t on 12/15/15.
//

#ifndef CPP_R_TYPECPY2_ROCKET_HPP
#define CPP_R_TYPECPY2_ROCKET_HPP

#include <cstddef>
#include "Object.h"
#include "Explosion.h"
#include "../System/Animation.h"
#include "../System/ResourcesBank.h"

class Rocket : public Object
{
public:

    Rocket(t2Vector<int> position);
    virtual ~Rocket() {};

	virtual Object *clone(SerializedObject *serializedObject);
    virtual void interact(Object *);
	virtual void lateUpdate();
	virtual void start();

protected:
	Animation *animation;
	AnimationEntity *entity;
    unsigned int collisionNo;
};


#endif //CPP_R_TYPECPY2_ROCKET_HPP
