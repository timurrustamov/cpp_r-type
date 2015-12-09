//
// Created by rustam_t on 11/24/15.
//

#include "Geometry.hpp"

Geometry::Geometry(const Rectangle<float> &obj, float terminalVelocity, float accelerationTime, float inertiaRatio)
{
    this->_innerObj = obj;
    this->_node = NULL;

    this->_terminalVelocity = terminalVelocity;

    this->_accelerationTime = (accelerationTime <= 0 ? 0.001 : accelerationTime);
    this->_inertiaRatio = inertiaRatio <= 0 ? 0.001 : inertiaRatio;

    this->_applyed = false;
    this->_currentAccelerationTime = 0;
    this->_velocity.setX(0).setY(0);
    this->_acceleration.setX(0).setY(0);
    int i = -1;
    while (++i < 10)
        this->_previousPosition[i] = obj.getPosition();
}


Geometry &Geometry::operator=(const Geometry &geo) {

    this->_innerObj = geo._innerObj;
    this->_node = geo._node;
    this->_terminalVelocity = geo._terminalVelocity;
    this->_accelerationTime = geo._accelerationTime;
    this->_inertiaRatio = geo._inertiaRatio;
    this->_applyed = geo._applyed;
    this->_velocity = geo._velocity;
    this->_acceleration = geo._acceleration;
    int i = -1;
    while (++i < 10)
        this->_previousPosition[i] = geo._previousPosition[i];
    return (*this);
}

Geometry::Geometry(const Geometry &geo)
{
    this->_innerObj = geo._innerObj;
    this->_node = geo._node;
    this->_terminalVelocity = geo._terminalVelocity;
    this->_accelerationTime = geo._accelerationTime;
    this->_inertiaRatio = geo._inertiaRatio;
    this->_applyed = geo._applyed;
    this->_velocity = geo._velocity;
    this->_acceleration = geo._acceleration;
    int i = -1;
    while (++i < 10)
        this->_previousPosition[i] = geo._previousPosition[i];
}

Geometry::~Geometry()
{
    this->detach();
}

Geometry &
Geometry::tick(float delta_time)
{
    t2Vector<float> acceleration;
    float step;

    this->_previousPosition[this->_currentFrame++ % 10] = this->_innerObj.getPosition();
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

    this->_innerObj.position() += this->_velocity * delta_time;
    if (!_applyed) //not a continuous movement
        this->_acceleration.assign(0, 0);

    return (*this);
}

const Rectangle<float> &
Geometry::getRect() const
{
    return (this->_innerObj);
}

const t2Vector<int>
Geometry::getSize() const
{
    return (this->_innerObj.getSize());
}

const t2Vector<float>
Geometry::getPosition() const
{
    return (this->_innerObj.getPosition());
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

t2Vector<float> &
Geometry::velocity()
{
    return (this->_velocity);
}

float
Geometry::getClockWiseAngle() const
{
    if (this->_velocity == t2Vector<float>(0, 0))
        return (0);

    t2Vector<float> normal(1, 1);
    return (this->_velocity.getAngleTo(normal));
}

Geometry &
Geometry::setRelativeAngle(float angle)
{
    angle = 0.01745329252 * angle;
    float tempx = this->_velocity.getX();

    this->_velocity.x() = this->_velocity.getX() * cosf(angle) - this->_velocity.getY() * sinf(angle);
    this->_velocity.y() = tempx * sinf(angle) + this->_velocity.getY() * cosf(angle);
    return (*this);
}

Geometry &Geometry::setClockWiseAngle(float angle) {

    this->setRelativeAngle(-this->getClockWiseAngle()).setRelativeAngle(angle);
    return (*this);
}

bool
Geometry::isSimulating() const
{
    return (this->_node != NULL);
}

Geometry &
Geometry::attach(QuadTree *quadTree, bool forced)
{
    if (forced)
    {
        this->_node = quadTree;
        return (*this);
    }

    if (this->_node == quadTree)
        return (*this);
    if (this->_node != NULL)
        this->_node->remove(this);
    this->_node = quadTree->insert(this);
    return (*this);
}

Geometry &
Geometry::detach()
{
    if (this->_node != NULL)
        this->_node->remove(this);
    this->_node = NULL;
    return (*this);
}

Geometry &
Geometry::hardDetach()
{
    this->_node = NULL;
    return (*this);
}

QuadTree *
Geometry::getNode() const
{
    return (this->_node);
}

const t2Vector<float> &
Geometry::getPreviousPosition(unsigned int pos) const
{
    if (pos > 10)
        pos = 10;
    return (this->_previousPosition[(this->_currentFrame - 1 + pos) % 10]);
}

t2Vector<float> &
Geometry::position()
{
    return (this->_innerObj.position());
}