//
// Created by rustam_t on 12/22/15.
//

#include "User.hpp"

User::User(const std::string &name) : name(name), state(User::Waiting), room(NULL)
{
}

const std::string &
User::getName() const
{
    return (this->name);
}

User::State
User::getState() const
{
    State state;

    IMutex *mutex = (*MutexVault::getMutexVault())["user" + this->name];
    mutex->lock(true);
    state = this->state;
    mutex->unlock();
    return (state);
}

void
User::setState(State state)
{
    IMutex *mutex = (*MutexVault::getMutexVault())["user" + this->name];
    mutex->lock(true);
    this->state = state;
    mutex->unlock();
}

void
User::attachRoom(GameRoom *room) {

    IMutex *mutex = (*MutexVault::getMutexVault())["user" + this->name];
    mutex->lock(true);
    if (this->room == NULL)
        this->room = room;
    mutex->unlock();
}

void
User::detachRoom() {

    GameRoom *tmp;

    IMutex *mutex = (*MutexVault::getMutexVault())["user" + this->name];
    mutex->lock(true);
    if ((tmp = this->room) != NULL)
    {
        this->room = NULL;
        tmp->removeUser(this);
    }
    mutex->unlock();
}

GameRoom *
User::getRoom() const {

    GameRoom *room;

    IMutex *mutex = (*MutexVault::getMutexVault())["user" + this->name];
    mutex->lock(true);
    room = this->room;
    mutex->unlock();
    return (room);
}
