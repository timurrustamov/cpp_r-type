//
// Created by rustam_t on 11/24/15.
//

#ifndef CPP_R_TYPE_GEOMETRY_HPP
#define CPP_R_TYPE_GEOMETRY_HPP

#include "t2Vector.hpp"
#include "Rectangle.hpp"
#include "QuadTree.hpp"

class QuadTree;

class Geometry {

public:

    Geometry(const Rectangle<float> &obj, float terminalVelocity = 20, float accelerationTime = 0, float decelerationTime = 0);

    Geometry &operator=(const Geometry &geo);

    Geometry(const Geometry &that);

    ~Geometry();

    Geometry &tick(float delta_time);

    const t2Vector<int> getSize() const;

    bool isSimulating() const;

    Geometry &attach(QuadTree *quadTree, bool forced = false);

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
    Geometry &applyImpulse(t2Vector<T> impulse)
    {
        this->_applyed = true;
        this->_currentAccelerationTime = 0;
        this->_acceleration = impulse;
        return (*this);
    }

    template <typename T>
    Geometry addImpulse(t2Vector<T> impulse)
    {
        this->_acceleration += impulse;
        return (*this);
    }

    Geometry &removeImpulse()
    {
        this->_currentAccelerationTime = 0;
        this->_acceleration.assign(0, 0);
        this->_applyed = false;
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

    unsigned int _objectId;
    QuadTree *      _node;

    Rectangle<float> _innerObj;
    t2Vector<float> _velocity;
    t2Vector<float> _acceleration;
    t2Vector<float> _previousPosition[10];
    unsigned int _currentFrame;
    bool _applyed;

    float _accelerationTime;
    float _currentAccelerationTime;
    float _inertiaRatio;
    float _terminalVelocity;
};


#endif //CPP_R_TYPE_GEOMETRY_HPP
