//
// Created by rustam_t on 12/8/15.
//

#include "World.hpp"

World::World(t2Vector<int> size, bool verticalWalls, bool horizontalWalls) : _qt(Rectangle<int>(size, size / 2))
{
    if (verticalWalls)
    {
        Object *verticallWall = new Wall(size.getX() - 2, 300, size.getX() / 2, -150);
        verticallWall->geometry->attach(&this->_qt);
        this->_objects[verticallWall->getId()] = verticallWall;
        verticallWall = new Wall(size.getX() - 2, 300, size.getX() / 2, size.getY() + 150);
        verticallWall->geometry->attach(&this->_qt);
        this->_objects[verticallWall->getId()] = verticallWall;
    }
    if (horizontalWalls)
    {
        Object *horizontalWall = new Wall(300, size.getY() - 2, -150, size.getY() / 2);
        horizontalWall->geometry->attach(&this->_qt);
        this->_objects[horizontalWall->getId()] = horizontalWall;
        horizontalWall = new Wall(300, size.getY() - 2, size.getX() + 150, size.getY() / 2);
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

unsigned int						World::createNewObject(Object *newobj)
{
    Player							*playerptr = dynamic_cast<Player *>(newobj);

    if (playerptr != NULL)
        return (BAD_ID);
    this->_objects[newobj->getId()] = newobj;
    this->_qt.insert(newobj->geometry);
    return (newobj->getId());
}


unsigned int
World::createNewObject(Object::Type type) {

    return (0);
}

World &
World::tick(float seconds)
{
    std::map<Geometry *, std::vector<Geometry *> > interactionmap;

    for (std::map<unsigned int, Object *>::iterator it = this->_objects.begin(); it != this->_objects.end(); it++) {
        if (it->second != NULL)
        {
            this->_qt.testCollision(it->second->geometry, interactionmap)->attach(&(this->_qt)).tick(seconds);
            it->second->lateUpdate();
        }
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

Snapshot *
World::getSnapshot() {

    std::vector<SerializedObject *> objects;

    for (std::map<unsigned int, Object *>::iterator it = this->_objects.begin(); it != this->_objects.end(); it++)
        if (it->second != NULL && !it->second->mustBeDeleted())
            objects.push_back(new SerializedObject(*it->second));

    return (new Snapshot(this->_qt.getSize(), objects));
}

World &
World::loadSnapshot(Snapshot *snap)
{
    //look for integrity of objects
    for (std::map<unsigned int, Object *>::iterator it = this->_objects.begin(); it != this->_objects.end(); it++)
        if (it->second != NULL && !it->second->mustBeDeleted() && snap->objects.find(it->second->getId()) == snap->objects.end())
            it->second->setToDelete();

    //replace and load new objects
    for (std::map<unsigned int, SerializedObject *>::iterator it = snap->objects.begin(); it != snap->objects.end(); it++) {
        if (this->_objects.find(it->second->attr.id) != this->_objects.end()) {
            this->_objects[it->second->attr.id]->geometry->setVelocity(t2Vector<float>(it->second->attr.velocityx, it->second->attr.velocityy));
            this->_objects[it->second->attr.id]->geometry->setPosition(t2Vector<float>(it->second->attr.positionx, it->second->attr.positiony));
        }
        else if (this->_samples[it->second->attr.identifier] != NULL)
            this->createNewObject(it->second->attr.identifier, it->second);
    }
    return (*this);
}

World &
World::addSample(Object *object) {

    this->_samples[object->getIdentifier()] = object;
    return (*this);
}

unsigned int
World::createNewObject(unsigned int identifier, SerializedObject *serializedObject) {

    unsigned int id = BAD_ID;

    if (this->_samples.find(identifier) != this->_samples.end())
        this->createNewObject(this->_samples[identifier]->clone(serializedObject));
    return (id);
}
