//
// Created by rustam_t on 11/24/15.
//

#ifndef CPP_R_TYPE_GEOMETRY_HPP
# define CPP_R_TYPE_GEOMETRY_HPP

#include "t2Vector.hpp"
#include "Rectangle.hpp"
#include "QuadTree.hpp"
#include "Object.h"

class Object;

class QuadTree;

class Geometry {

public:

    Geometry(const Rectangle<float> &obj, float terminalVelocity = 20, float decelerationTime = 0);

    Geometry &operator=(const Geometry &geo);

    Geometry(const Geometry &that);

    ~Geometry();

    Geometry &tick(float delta_time);

    const t2Vector<int> getSize() const;

    bool isSimulating() const;

    Geometry &attach(QuadTree *quadTree, bool forced = false);

    Geometry &attachToObject(Object &obj);

    Object *getObject();

    Geometry &detach();

    Geometry & hardDetach();

    const Rectangle<float> &getRect() const;

    template <typename T>
    Geometry &setSize(t2Vector<T> size)
    {
        this->_innerObj.size() = size;
        return (*this);
    }

    template <typename T>
    Geometry &applyImpulse(t2Vector<T> impulse, float accelerationTime)
    {
        this->_object->timer.addNewEvent("acceleration", accelerationTime);
        this->_acceleration = impulse;
        return (*this);
    }

    template <typename T>
    Geometry addImpulse(t2Vector<T> impulse)
    {
        this->_acceleration.x() += impulse.getX();
        this->_acceleration.y() += impulse.getY();
        this->_object->timer.addNewEvent("acceleration", 0.05);
        return (*this);
    }

    Geometry &removeImpulse()
    {
        this->_object->timer.removeEvent("acceleration");
        return (*this);
    }

    const t2Vector<float> getPosition() const;

    template <typename T>
    Geometry &setPosition(t2Vector<T> position)
    {
        this->_innerObj.position() = position;
        return (*this);
    }

    t2Vector<float> &position();

    const t2Vector<float> getVelocity() const;

    template <typename T>
    Geometry &setVelocity(t2Vector<T> velocity)
    {
        this->_velocity = velocity;
        return (*this);
    }

    t2Vector<float> &velocity();

    const t2Vector<float> getAcceleration() const;

    float getClockWiseAngle() const;

    Geometry & setRelativeAngle(float angle);

    Geometry & setClockWiseAngle(float angle);

    const t2Vector<float> &getPreviousPosition(unsigned int pos) const;

    QuadTree * getNode() const;

private:

    Object *        _object;
    QuadTree *      _node;

    Rectangle<float> _innerObj;
    t2Vector<float> _velocity;
    t2Vector<float> _acceleration;
    t2Vector<float> _previousPosition[10];
    unsigned int _currentFrame;

    float _inertiaRatio;
    float _terminalVelocity;
};


#endif //CPP_R_TYPE_GEOMETRY_HPP
