//
// Created by rustam_t on 12/15/15.
//

#ifndef CPP_R_TYPECPY2_ROCKET_HPP
#define CPP_R_TYPECPY2_ROCKET_HPP

#include "Object.h"

class Rocket : public Object
{
public:

    Rocket(t2Vector<int> position);
    Rocket(int x, int y);
    virtual ~Rocket() {};

    virtual void interact(Object *);

protected:

    unsigned int collisionNo;
};


#endif //CPP_R_TYPECPY2_ROCKET_HPP
