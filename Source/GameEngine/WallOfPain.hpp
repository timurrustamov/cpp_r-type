//
// Created by rustam_t on 12/14/15.
//

#ifndef CPP_R_TYPECPY2_WALLOFPAIN_HPP
#define CPP_R_TYPECPY2_WALLOFPAIN_HPP

#include <cstddef>
#include "Object.h"

class Wall : public Object {

public:

    Wall(t2Vector<int> size, t2Vector<int> position);
    Wall(int sizex, int sizey, int x, int y);
    virtual ~Wall() {};

	virtual Object *clone(SerializedObject *serializedObject);
    virtual void interact(Object *);
	virtual void lateUpdate();
	virtual void start();
};

#endif //CPP_R_TYPECPY2_WALLOFPAIN_HPP
