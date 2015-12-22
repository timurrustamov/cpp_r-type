//
// Created by rustam_t on 12/14/15.
//

#ifndef CPP_R_TYPECPY2_PLAYER_HPP
#define CPP_R_TYPECPY2_PLAYER_HPP

#include "Object.h"
#include "../System/Animation.h"
#include "../System/ResourcesBank.h"

class Player : public Object {

public:

    Player(t2Vector<int> position, unsigned int);
    Player(int x, int y, unsigned int);
    virtual ~Player() {};

    unsigned int getPlayerNo() const;
    virtual void interact(Object *);
	virtual void lateUpdate();
	virtual void start();


protected:
	Animation *animation;
	AnimationEntity *entity;
    unsigned int playerNo;
};


#endif //CPP_R_TYPECPY2_PLAYER_HPP
