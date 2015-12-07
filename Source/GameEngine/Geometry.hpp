//
// Created by rustam_t on 11/24/15.
//

#ifndef CPP_R_TYPE_GEOMETRY_HPP
# define CPP_R_TYPE_GEOMETRY_HPP

# include "t2Vector.hpp"
# ifndef M_PI
#  define M_PI 3.1415926535897932384626433832795
# endif

class Geometry {

public:

    Geometry(t2Vector<float> position, t2Vector<int> size, float terminalVelocity = 20, float accelerationTime = 0, float decelerationTime = 0);

    Geometry &tick(float delta_time);

    const t2Vector<int> getSize() const;

    template <typename T>
    Geometry &setSize(t2Vector<T> size)
    {
        this->_size = size;
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
        this->_position = position;
        return (*this);
    }

    const t2Vector<float> getVelocity() const;

    template <typename T>
    Geometry &setVelocity(t2Vector<T> velocity)
    {
        this->_velocity = velocity;
        return (*this);
    }

    const t2Vector<float> getAcceleration() const;

    float getClockWiseAngle() const;

private:

    unsigned int _objectId;
    t2Vector<int> _size;
    t2Vector<float> _position;
    t2Vector<float> _velocity;
    t2Vector<float> _acceleration;
    bool _applyed;

    float _accelerationTime;
    float _currentAccelerationTime;
    float _inertiaRatio;
    float _terminalVelocity;
};


#endif //CPP_R_TYPE_GEOMETRY_HPP