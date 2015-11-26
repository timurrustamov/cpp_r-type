//
// Created by rustam_t on 11/24/15.
//

#include "Geometry.hpp"

Geometry::Geometry(t2Vector<float> position, t2Vector<int> size,
                   float terminalVelocity, float accelerationTime, float inertiaRatio)
{
    this->_position = position;
    this->_size = size;

    this->_terminalVelocity = terminalVelocity;

    this->_accelerationTime = (accelerationTime <= 0 ? 0.00001 : accelerationTime);
    this->_inertiaRatio = inertiaRatio <= 0 ? 0.00001 : inertiaRatio;

    this->_applyed = false;
    this->_currentAccelerationTime = 0;
    this->_velocity.setX(0).setY(0);
    this->_acceleration.setX(0).setY(0);
}

Geometry &
Geometry::tick(float delta_time)
{
    t2Vector<float> acceleration;
    float step;

    if (this->_acceleration != t2Vector<float>(0, 0)) {

        step = (this->_currentAccelerationTime += delta_time) / this->_accelerationTime;
        step = (step > 1) ? 1 : (step);

        acceleration = this->_acceleration * (step * step * (3 - 2 * step));
        this->_velocity += acceleration;
    }
    if (this->_velocity != t2Vector<float>(0, 0)) {

        this->_velocity -= (this->_velocity * this->_inertiaRatio * delta_time);
    }

    if (this->_velocity.length() > this->_terminalVelocity)
        this->_velocity *= this->_terminalVelocity / this->_velocity.length();

    //std::cout << "current velocity " << this->_velocity << std::endl;

    this->_position += this->_velocity * delta_time;
    if (!_applyed) //not a continuous movement
        this->_acceleration.assign(0, 0);

    return (*this);
}

const t2Vector<int>
Geometry::getSize() const
{
    return (this->_size);
}

const t2Vector<float>
Geometry::getPosition() const
{
    return (this->_position);
}

const t2Vector<float>
Geometry::getAcceleration() const
{
    return (this->_acceleration);
}

const t2Vector<float>
Geometry::getVelocity() const
{
    return (this->_velocity);
}

float
Geometry::getClockWiseAngle() const
{
    if (this->_velocity == t2Vector<float>(0, 0))
        return (0);

    t2Vector<float> normal(1, 1);
    float dot = normal.getX() * this->_velocity.getX() + normal.getY() * this->_acceleration.getY();
    float det = normal.getX() * this->_velocity.getY() - normal.getX() * this->_acceleration.getX();
    return (std::atan2(dot, det) * 180 / M_PI);
}