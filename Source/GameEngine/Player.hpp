//
// Created by rustam_t on 12/14/15.
//

#ifndef CPP_R_TYPECPY2_PLAYER_HPP
#define CPP_R_TYPECPY2_PLAYER_HPP

#include "Object.h"

class Player : public Object {

public:

    Player(t2Vector<int> position, unsigned int);
    Player(int x, int y, unsigned int);
    virtual ~Player() {};

    unsigned int getPlayerNo() const;
    virtual void interact(Object *);

protected:

    unsigned int playerNo;
};


#endif //CPP_R_TYPECPY2_PLAYER_HPP
