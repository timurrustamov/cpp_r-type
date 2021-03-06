//
// Created by rustam_t on 12/8/15.
//

#include <SFML/Window/Keyboard.hpp>
#include "GameData.h"
#include "World.hpp"
#include "IMutex.hpp"
#include "MutexVault.hpp"

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

    for (unsigned int i = 0; i < MAX_PLAYERS; i++)
        this->_playersId.push_back(BAD_ID);
}

World::~World()
{
    for (std::map<unsigned int, Object *>::iterator it = this->_objects.begin(); it != this->_objects.end(); it++)
        delete (it->second);
    for (std::map<unsigned int, Object *>::iterator it = this->_samples.begin(); it != this->_samples.end(); it++)
        delete (it->second);
}

unsigned int						World::createNewObject(Object *newobj) {
    Player *playerptr = dynamic_cast<Player *>(newobj);

    IMutex *mutex = (*MutexVault::getMutexVault())["gameobjects"];

    mutex->lock(true);
    if (playerptr != NULL) {

        mutex->unlock();
        return (BAD_ID);
    }
    this->_objects[newobj->getId()] = newobj;
    this->_qt.insert(newobj->geometry);
	newobj->start();
    mutex->unlock();
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

    IMutex *mutex = (*MutexVault::getMutexVault())["gameobjects"];

    mutex->lock(true);
    for (std::map<unsigned int, Object *>::iterator it = this->_objects.begin(); it != this->_objects.end(); it++) {
        if (it->second != NULL)
        {
            this->_qt.testCollision(it->second->geometry, interactionmap)->attach(&(this->_qt)).tick(seconds);
            it->second->lateUpdate();
        }
    }
    mutex->unlock();

    //check players first
    mutex->lock(true);
    for (unsigned int i = 0; i < MAX_PLAYERS; i++)
        if (this->_playersId[i] != BAD_ID && this->_objects[this->_playersId[i]]->mustBeDeleted())
        {
            this->timer.addNewEvent(
                    "player" + MutexVault::toString(i), 3);
            std::cout << "player" + MutexVault::toString(i) << std::endl;
            this->_objects[this->_playersId[i]]->geometry->detach();
            delete this->_objects[this->_playersId[i]];
            this->_objects.erase(this->_playersId[i]);
            this->_playersId[i] = BAD_ID;
        }
    mutex->unlock();
    mutex->lock(true);
    for (std::map<unsigned int, Object *>::iterator it = this->_objects.begin(); it != this->_objects.end(); it++)
        if (it->second != NULL && it->second->mustBeDeleted())
        {
            it->second->geometry->detach();
            delete (it->second);
            this->_objects.erase(it);
        }
    mutex->unlock();
    return (*this);
}

Snapshot *
World::getSnapshot() {

    std::vector<SerializedObject *> objects;

    IMutex *mutex = (*MutexVault::getMutexVault())["gameobjects"];

    mutex->lock(true);
    for (std::map<unsigned int, Object *>::iterator it = this->_objects.begin(); it != this->_objects.end(); it++) {

        if (it->second != NULL && !it->second->mustBeDeleted() && it->second->getType() != Object::Other)
            objects.push_back(new SerializedObject(*it->second));
    }
    mutex->unlock();
    return (new Snapshot(this->_qt.getSize(), objects));
}

World &
World::loadSnapshot(Snapshot *snap)
{
    IMutex *mutex = (*MutexVault::getMutexVault())["gameobjects"];

    mutex->lock(true);
    //look for integrity of objects
    for (std::map<unsigned int, Object *>::iterator it = this->_objects.begin(); it != this->_objects.end(); it++) {
        if (it->second != NULL && !it->second->mustBeDeleted() &&
            snap->objects.find(it->second->getId()) == snap->objects.end() && it->second->getType() != Object::Other) {
            it->second->setToDelete();
        }
    }
    //replace and load new objects
    for (std::map<unsigned int, SerializedObject *>::iterator it = snap->objects.begin(); it != snap->objects.end(); it++) {
        if (it->second->attr.playerId != BAD_ID && this->getPlayerObject(it->second->attr.playerId) != NULL)
            this->getPlayerObject(it->second->attr.playerId)->geometry->setPosition(t2Vector<float>(it->second->attr.positionx, it->second->attr.positiony));
        else if (this->_objects.find(it->second->attr.id) != this->_objects.end()) {
            this->_objects[it->second->attr.id]->setValues(it->second);
        }
		else if (this->_samples[it->second->attr.identifier] != NULL && this->_samples[it->second->attr.identifier]->getType() != Object::Other) {
            if (this->_samples[it->second->attr.identifier]->getType() == Object::Character) {
                unsigned int plId = this->createNewPlayer(static_cast<int>(it->second->attr.positionx),
                                      static_cast<int>(it->second->attr.positiony), it->second->attr.playerId);
                if (plId != BAD_ID)
                    this->_objects[plId]->setValues(it->second);
            }
            else
                this->createNewObject(it->second->attr.identifier, it->second);
        }
    }
    mutex->unlock();
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

    IMutex *mutex = (*MutexVault::getMutexVault())["gameobjects"];

    mutex->lock(true);
	if (this->_samples.find(identifier) != this->_samples.end())
	{
		id = this->createNewObject(this->_samples[identifier]->clone(serializedObject));
		if (this->_samples[identifier]->getType() == Object::Character)
			this->_playersId[this->_samples[identifier]->getIdentifier()] = id;
	}
    mutex->unlock();
	return (id);
}

World &World::loadPlayerActions(unsigned int playerNo, std::vector<int> *actions) {

    IMutex *mutex = (*MutexVault::getMutexVault())["gameobjects"];
    std::vector<sf::Keyboard::Key> keys;

    mutex->lock(true);
    Object *player;
    Player *truePlayer;
    if ((player = this->getPlayerObject(playerNo)) != NULL && (truePlayer = dynamic_cast<Player *>(player)) != NULL)
    {
        for (std::vector<int>::iterator it = actions->begin(); it != actions->end(); it++)
            keys.push_back(static_cast<sf::Keyboard::Key>(*it));
        truePlayer->move(keys);
    }
    mutex->unlock();
    return (*this);
}
