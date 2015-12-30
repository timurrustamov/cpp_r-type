//
// Created by rustam_t on 12/22/15.
//

#include "GameRoom.hpp"

GameRoom::GameRoom(const std::string &name, User *owner) : name(name), state(Waiting), owner(owner)
{
    std::cout << "New Room : " << name << "; Creator : " << owner->getName() << std::endl;
    this->users.push_back(owner);
    owner->attachRoom(this);
}

const std::string &
GameRoom::getName() const
{
    return (this->name);
}

bool
GameRoom::addUser(User *user)
{
    IMutex *mutex = (*MutexVault::getMutexVault())["room" + this->name];
    bool res = false;

    mutex->lock(true);
    if (!this->hasUser(user) && this->users.size() < 4 && !this->hasUser(user)) {
        this->users.push_back(user);
        user->attachRoom(this);
        res = true;
    }
    mutex->unlock();
    return (res);
}

bool GameRoom::removeUser(User *user) {

    IMutex *mutex = (*MutexVault::getMutexVault())["room" + this->name];
    bool res = false;

    mutex->lock(true);
    if (this->hasUser(user)) {

        std::cout << "Removing user " << user->getName() << " from room " << this->name << std::endl;
        this->users.erase(std::find(this->users.begin(), this->users.end(), user));
        if (user->getRoom() != NULL)
            user->detachRoom();
        if (this->owner == user) {

            this->removeAllUsers();
            RTypeServer::getInstance()->removeRoom(this);
        }
        res = true;
    }
    mutex->unlock();
    return (res);
}

bool
GameRoom::hasUser(User *user) const
{
    IMutex *mutex = (*MutexVault::getMutexVault())["room" + this->name];
    bool res = false;

    mutex->lock(true);
    if (std::find(this->users.begin(), this->users.end(), user) != this->users.end())
        res = true;
    mutex->unlock();
    return (res);
}

bool
GameRoom::setState(State state, User *user)
{
    if (this->owner != user)
        return (false);

    IMutex *mutex = (*MutexVault::getMutexVault())["room" + this->name];

    mutex->lock(true);
    if ((this->state = state) == Running)
        for (std::vector<User *>::iterator it = this->users.begin(); it != this->users.end(); it++)
            (*it)->setState(User::Playing);
    mutex->unlock();
    return (true);
}

GameRoom::State
GameRoom::getState() const
{
    IMutex *mutex = (*MutexVault::getMutexVault())["room" + this->name];
    State state;

    mutex->lock(true);
    state = this->state;
    mutex->unlock();
    return (state);
}

const std::vector<User *> &
GameRoom::getUsers() const {

    return (this->users);
}

bool
GameRoom::removeAllUsers() {

    RTypeServer *server = RTypeServer::getInstance();
    IMutex *mutex = (*MutexVault::getMutexVault())["room" + this->name];
    Instruction instruct(Instruction::LEAVE_ROOM);

    mutex->lock(true);
    while (this->users.size() > 0) {
        server->sendToClient(this->users[0], instruct);
        this->users[0]->detachRoom();
    }
    mutex->unlock();
    return (true);
}

Instruction
GameRoom::getUsersInstruction() const {

    Instruction instruct(Instruction::GETALLUSERSINROOM);
    IMutex *mutex = (*MutexVault::getMutexVault())["room" + this->name];

    mutex->lock(true);
    for (std::vector<User *>::const_iterator it = this->users.begin(); it != this->users.end(); it++)
        instruct.addName((*it)->getName());
    mutex->unlock();
    return (instruct);
}
