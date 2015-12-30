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
    if (this->room == NULL) {
        this->room = room;
        room->addUser(this);
    }
    mutex->unlock();
}

bool
User::detachRoom() {

    bool res = false;
    RTypeServer *serv = RTypeServer::getInstance();

    IMutex *mutex = (*MutexVault::getMutexVault())["user" + this->name];
    mutex->lock(true);
    if (this->room != NULL)
    {
        res = true;
        this->room->removeUser(this);
        this->room = NULL;
        serv->getUserSocket(this)->attachOnReceive(RTypeServer::tcpMemberRoom);
    }
    mutex->unlock();
    return (res);
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
