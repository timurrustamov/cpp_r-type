//
// Created by rustam_t on 12/8/15.
//

#include "World.hpp"

World::World(t2Vector<int> size, bool verticalWalls, bool horizontalWalls) : _qt(Rectangle<int>(size, size / 2))
{
    if (verticalWalls)
    {
        Object *verticallWall = new Wall(size.getX() - 2, 1, size.getX() / 2, 1);
        verticallWall->geometry->attach(&this->_qt);
        this->_objects[verticallWall->getId()] = verticallWall;
        verticallWall = new Wall(size.getX() - 2, 1, size.getX() / 2, size.getY() - 1);
        verticallWall->geometry->attach(&this->_qt);
        this->_objects[verticallWall->getId()] = verticallWall;
    }
    if (horizontalWalls)
    {
        Object *horizontalWall = new Wall(1, size.getY() - 2, 1, size.getY() / 2);
        horizontalWall->geometry->attach(&this->_qt);
        this->_objects[horizontalWall->getId()] = horizontalWall;
        horizontalWall = new Wall(1, size.getY() - 2, size.getX() - 1, size.getY() / 2);
        horizontalWall->geometry->attach(&this->_qt);
        this->_objects[horizontalWall->getId()] = horizontalWall;
    }

    this->_playersId.resize(MAX_PLAYERS);
    for (unsigned int i = 0; i < MAX_PLAYERS; i++)
        this->_playersId[i] = BAD_ID;
}

World::~World()
{
    for (std::map<unsigned int, Object *>::iterator it = this->_objects.begin(); it != this->_objects.end(); it++)
        delete (it->second);
}

World &
World::tick(float seconds)
{
    std::map<Geometry *, std::vector<Geometry *> > interactionmap;

    for (std::map<unsigned int, Object *>::iterator it = this->_objects.begin(); it != this->_objects.end(); it++) {
        if (it->second != NULL)
            this->_qt.testCollision(it->second->geometry, interactionmap)->attach(&(this->_qt)).tick(seconds);
    }

    //check players first
    for (unsigned int i = 0; i < MAX_PLAYERS; i++)
        if (this->_playersId[i] != BAD_ID && this->_objects[this->_playersId[i]]->mustBeDeleted())
        {
            delete this->_objects[this->_playersId[i]];
            this->_objects.erase(this->_playersId[i]);
            this->_playersId[i] = BAD_ID;
        }

    for (std::map<unsigned int, Object *>::iterator it = this->_objects.begin(); it != this->_objects.end(); it++)
        if (it->second != NULL && it->second->mustBeDeleted())
        {
            delete (it->second);
            this->_objects.erase(it);
        }
    return (*this);
}