//
// Created by rustam_t on 12/22/15.
//

#include "RTypeServer.hpp"

RTypeServer::RTypeServer(int tcpPort, int udpPort)
{
    this->tcpServer = ISocket::getServer(tcpPort, "TCP");
    this->udpServer = ISocket::getServer(udpPort, "UDP");

    if (this->tcpServer->start() == -1 || this->udpServer->start() == -1)
        throw BBException("Failed to create server");
}

RTypeServer::~RTypeServer()
{
    this->tcpServer->cancel();
    this->udpServer->cancel();
    sleep(1);
    delete this->tcpServer;
    delete this->udpServer;
}

bool
RTypeServer::roomNameExists(const std::string &roomName) {

    IMutex *mutex = (*MutexVault::getMutexVault())["serverType"];
    bool res = false;
    mutex->lock(true);
    for (std::vector<GameRoom *>::iterator it = this->rooms.begin(); it != this->rooms.end(); it++)
        if ((*it)->getName() == roomName) {
            res = true;
            break;
        }
    mutex->unlock();
    return (res);
}

bool
RTypeServer::createRoom(User *user, const std::string &roomName) {

    IMutex *mutex = (*MutexVault::getMutexVault())["serverType"];
    bool res = false;
    GameRoom *room;

    mutex->lock(true);
    if (!roomName.empty() && !this->roomNameExists(roomName) && this->rooms.size() < 4)
    {
        room = new GameRoom(roomName, user);
        this->rooms.push_back(room);
        res = true;
    }
    mutex->unlock();
    return (res);
}

bool
RTypeServer::joinRoom(User *user, const std::string &roomName) {

    IMutex *mutex = (*MutexVault::getMutexVault())["serverType"];
    GameRoom *room;

    bool res = false;
    mutex->lock(true);
    for (std::vector<GameRoom *>::iterator it = this->rooms.begin(); it != this->rooms.end(); it++)
        if ((*it)->getName() == roomName)
        {
            res = (*it)->addUser(user);
            break;
        }
    mutex->unlock();
    return (res);
}

bool
RTypeServer::leaveRoom(User *user, const std::string &roomName) {

    IMutex *mutex = (*MutexVault::getMutexVault())["serverType"];
    GameRoom *room;

    bool res = false;
    mutex->lock(true);
    if (user->getRoom() != NULL)
        user->getRoom()->removeUser(user);
    mutex->unlock();
}

bool
RTypeServer::newUser(const std::string &userName, ISocket *client) {

    IMutex *mutex = (*MutexVault::getMutexVault())["serverType"];
    bool res = false;

    mutex->lock(true);
    if (this->userLinks.find(client) == this->userLinks.end() && !this->userNameExists(userName))
    {
        this->userLinks[client] = new User(userName);
        res = true;
    }
    mutex->unlock();
    return (res);
}

bool
RTypeServer::userNameExists(const std::string &username) {

    IMutex *mutex = (*MutexVault::getMutexVault())["serverType"];
    bool res = false;

    mutex->lock(true);
    for (std::map<ISocket *, User *>::iterator it = this->userLinks.begin(); it != this->userLinks.end(); it++)
        if (it->second->getName() == username) {
            res = true;
            break;
        }
    mutex->unlock();
    return (res);
}

bool
RTypeServer::startGame(User *user) {

    IMutex *mutex = (*MutexVault::getMutexVault())["serverType"];
    bool res = false;

    mutex->lock(true);
    if (user->getRoom() != NULL) {
        
    }
}

void
RTypeServer::tcpGuestRoom(ISocket *client) {

}

void
RTypeServer::tcpMemberRoom(ISocket *client) {

}

void
RTypeServer::tcpWaitingRoom(ISocket *client) {

}

