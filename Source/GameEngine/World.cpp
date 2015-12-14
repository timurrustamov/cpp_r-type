//
// Created by rustam_t on 12/8/15.
//

#include "World.hpp"

World::World(t2Vector<int> size, bool verticalWalls, bool horizontalWalls) : _qt(Rectangle<int>(size, size / 2))
{
    std::cout << _qt.countSubTotal() << std::endl;
    if (verticalWalls)
    {
        this->newGeometry(Rectangle<float>(size.getX() - 2, 1, size.getX() / 2, 1), 0, 0, 0);
        this->newGeometry(Rectangle<float>(size.getX() - 2, 1, size.getX() / 2, size.getY() - 1), 0, 0, 0);
    }
    if (horizontalWalls)
    {
        this->newGeometry(Rectangle<float>(1, size.getY() - 2, 1, size.getY() / 2), 0, 0, 0);
        this->newGeometry(Rectangle<float>(1, size.getY() - 2, size.getX() - 1, size.getY() / 2), 0, 0, 0);
    }
}

World::~World()
{
    //this->_qt.clear();
    for (std::vector<Geometry *>::iterator it = this->_objects.begin(); it != this->_objects.end(); it++)
        delete (*it);
    for (std::vector<Geometry *>::iterator it = this->_players.begin(); it != this->_players.end(); it++)
        delete (*it);
}

World &
World::newGeometry(Geometry *geo)
{
    this->_objects.push_back(geo);
    this->_qt.insert(geo);
    return (*this);
}

Geometry *
World::newGeometry(const Rectangle<float> &obj, float terminalVelocity, float accelerationTime, float inertiaRatio)
{
    Geometry *geo = new Geometry(obj, terminalVelocity, accelerationTime, inertiaRatio);
    this->_objects.push_back(geo);
    this->_qt.insert(geo);
    return (geo);
}

World &
World::bindPlayerObject(Geometry *geo)
{
    if (this->_players.size() < MAX_PLAYERS) {
        this->_players.push_back(geo);
        this->_qt.insert(geo);
    }
    return (*this);
}

Geometry *
World::bindPlayerObject(const Rectangle<float> &obj, float terminalVelocity, float accelerationTime, float inertiaRatio)
{
    Geometry *pl = new Geometry(obj, terminalVelocity, accelerationTime, inertiaRatio);
    if (this->_players.size() < MAX_PLAYERS) {
        this->_players.push_back(pl);
        this->_qt.insert(pl);
        return (pl);
    }
    return (NULL);
}

World &
World::removePlayerObject(Geometry *geo)
{
    unsigned int i = 0;
    while (i < MAX_PLAYERS && i < this->_players.size())
    {
        if (geo == this->_players[i])
        {
            this->_qt.remove(geo);
            this->_players.erase(this->_players.begin() + i);
            return (*this);
        }
        i++;
    }
    return (*this);
}

World &
World::tick(float seconds)
{
    std::map<Geometry *, std::vector<Geometry *> > interactionmap;

    for (std::vector<Geometry *>::iterator it = this->_objects.begin(); it != this->_objects.end(); it++) {
        QuadTree::testCollision(*it, interactionmap);
        (*it)->attach(&(this->_qt)).tick(seconds);
    }
    for (std::vector<Geometry *>::iterator it = this->_players.begin(); it != this->_players.end(); it++) {
        QuadTree::testCollision(*it, interactionmap);
        (*it)->attach(&(this->_qt)).tick(seconds);
    }
    return (*this);
}