//
// Created by rustam_t on 12/22/15.
//

#include "RTypeServer.hpp"

RTypeServer::RTypeServer(int tcpPort, int udpPort)
{
    this->tcpServer = ISocket::getServer(tcpPort, "TCP");
    this->udpServer = ISocket::getServer(udpPort, "UDP");

    this->tcpServer->attachOnConnect(RTypeServer::tcpGuestWelcomeRoom);
    this->tcpServer->attachOnReceive(RTypeServer::tcpGuestRoom);
    this->tcpServer->attachOnDisconnect(RTypeServer::tcpGuestGoodbyeRoom);
    if (this->tcpServer->start() == -1 || this->udpServer->start() == -1)
        throw BBException("Failed to create server");
}

RTypeServer::~RTypeServer()
{
    this->tcpServer->cancel();
    this->udpServer->cancel();
    sleep(1);
    for (std::map<ISocket *, User *>::iterator it = this->userLinks.begin(); it != this->userLinks.end(); it++)
        delete it->second;
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
    std::vector<User *> users;

    mutex->lock(true);
    std::cout << "Ask for room creation from " << user->getName() << " roomname : " << roomName << std::endl;
    if (!roomName.empty() && !this->roomNameExists(roomName) && this->rooms.size() < 1)
    {
        room = new GameRoom(roomName, user);
        Instruction joined = room->getUsersInstruction();
        users = room->getUsers();
        for (std::vector<User *>::iterator iit = users.begin(); iit != users.end(); iit++)
            RTypeServer::getInstance()->sendToClient(*iit, joined);
        this->rooms.push_back(room);
        res = true;
    }
    mutex->unlock();
    return (res);
}

bool
RTypeServer::joinRoom(User *user, const std::string &roomName) {

    IMutex *mutex = (*MutexVault::getMutexVault())["serverType"];
    std::vector<User *> users;

    bool res = false;
    mutex->lock(true);
    for (std::vector<GameRoom *>::iterator it = this->rooms.begin(); it != this->rooms.end(); it++)
        if ((*it)->getName() == roomName)
        {
            if ((res = (*it)->addUser(user))) {

                Instruction joined = (*it)->getUsersInstruction();
                users = (*it)->getUsers();
                for (std::vector<User *>::iterator iit = users.begin(); iit != users.end(); iit++)
                    RTypeServer::getInstance()->sendToClient(*iit, joined);
            }
            break;
        }
    mutex->unlock();
    return (res);
}

bool
RTypeServer::leaveRoom(User *user) {

    IMutex *mutex = (*MutexVault::getMutexVault())["serverType"];
    GameRoom *room;
    bool mustSend = false;

    bool res = false;
    mutex->lock(true);
    if ((room = user->getRoom()) != NULL) {

        if (room->owner != user)
            mustSend = true;
        user->getRoom()->removeUser(user);
        if (mustSend)
        {
            std::vector<User *> tmp = room->getUsers();
            Instruction i = room->getUsersInstruction();
            for (std::vector<User *>::iterator it = tmp.begin(); it != tmp.end(); it++)
                RTypeServer::getInstance()->getInstance()->sendToClient(*it, i);
        }
        res = true;
    }
    mutex->unlock();
    return (res);
}

bool
RTypeServer::newUser(const std::string &userName, ISocket *client) {

    IMutex *mutex = (*MutexVault::getMutexVault())["serverType"];
    bool res = false;

    mutex->lock(true);
    if (!userName.empty() && !this->userNameExists(userName))
    {
        std::cout << "New user : " << userName << std::endl;
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
        if (it->second != NULL && it->second->getName() == username) {
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
    if (user->getRoom() != NULL)
        res = user->getRoom()->setState(GameRoom::Running, user);
    mutex->unlock();
    return (res);
}

void
RTypeServer::tcpGuestRoom(ISocket *client) {

    Packet *packet;
    Instruction ko(Instruction::KO);
    Instruction *instruct;
    bool success;

    //get packet
    while ((packet = client->readPacket()) != NULL) {

        if (packet->getType() == Packet::Instruct &&
            (instruct = packet->unpack<Instruction>()) != NULL)
        {
            if (instruct->getInstruct() == Instruction::CONNEXION) {

                if ((success = RTypeServer::getInstance()->newUser((*instruct)[0], client))) {
                    client->attachOnReceive(RTypeServer::tcpMemberRoom);
                }
                Instruction i(success ? (Instruction::OK) : (Instruction::KO));
                client->writePacket(Packet::pack(i));
            }
            else
            {
                client->writePacket(Packet::pack(ko));
            }
            delete instruct;
        }
        delete packet;
    }
}

void
RTypeServer::tcpMemberRoom(ISocket *client) {

    RTypeServer *server = RTypeServer::getInstance();
    Packet *packet;
    Instruction *instruct;
    Instruction res(Instruction::KO);
    Instruction ko(Instruction::KO);
    Instruction ok(Instruction::OK);

    if (RTypeServer::getInstance()->userLinks[client] == NULL)
    {
        client->attachOnReceive(RTypeServer::tcpGuestRoom);
        return (RTypeServer::tcpGuestRoom(client));
    }

    while ((packet = client->readPacket()) != NULL) {

        if (packet->getType() == Packet::Instruct &&
            (instruct = packet->unpack<Instruction>()) != NULL)
        {
            if (instruct->getInstruct() == Instruction::DECONNEXION) {
                server->removeUser(client);
                client->writePacket(Packet::pack(ok));
                return;
            }
            else if (instruct->getInstruct() == Instruction::GETALLUSERNAMES)
            {
                res.setInstruct(Instruction::GETALLUSERNAMES);
                IMutex *mutex = (*MutexVault::getMutexVault())["serverType"];
                mutex->lock(true);

                for (std::map<ISocket *, User *>::iterator it = server->userLinks.begin(); it != server->userLinks.end(); it++)
                    res.addName(it->second->getName());
                mutex->unlock();
                client->writePacket(Packet::pack(res));
            }
            else if (instruct->getInstruct() == Instruction::JOIN_ROOM &&
                    server->joinRoom(server->userLinks[client], (*instruct)[0]))
            {
                client->writePacket(Packet::pack(ok));
                client->attachOnReceive(RTypeServer::tcpWaitingRoom);
            }
            else if (instruct->getInstruct() == Instruction::CREATE_ROOM &&
                    server->createRoom(server->userLinks[client], (*instruct)[0]))
            {
                client->writePacket(Packet::pack(ok));
                client->attachOnReceive(RTypeServer::tcpWaitingRoom);
            }
            else if (instruct->getInstruct() == Instruction::GETALLROOMNAMES)
            {
                res.setInstruct(Instruction::GETALLROOMNAMES);

                IMutex *mutex = (*MutexVault::getMutexVault())["serverType"];
                mutex->lock(true);

                for (std::vector<GameRoom *>::iterator it = server->rooms.begin(); it != server->rooms.end(); it++)
                    res.addName((*it)->getName());
                mutex->unlock();
                client->writePacket(Packet::pack(res));
            }
            else
                client->writePacket(Packet::pack(ko));
            delete instruct;
        }
        delete packet;
    }
}

void
RTypeServer::tcpWaitingRoom(ISocket *client) {

    Packet *packet;
    Instruction ko(Instruction::KO);
    Instruction *instruct;
    RTypeServer *server = RTypeServer::getInstance();

    if (server->userLinks[client]->getRoom() == NULL)
    {
        client->attachOnReceive(RTypeServer::tcpMemberRoom);
        return (client->getOnReceive()(client));
    }
    //get packet
    while ((packet = client->readPacket()) != NULL) {

        if (packet->getType() == Packet::Instruct &&
            (instruct = packet->unpack<Instruction>()) != NULL)
        {
            if (instruct->getInstruct() == Instruction::LEAVE_ROOM &&
                    server->leaveRoom(server->userLinks[client]))
            {
                Instruction i(Instruction::OK);
                client->writePacket(Packet::pack(i));
            }
            else if (instruct->getInstruct() == Instruction::GETALLUSERSINROOM)
            {
                Instruction i = server->userLinks[client]->getRoom()->getUsersInstruction();
                client->writePacket(Packet::pack(i));
            }
            else if (instruct->getInstruct() == Instruction::START_GAME)
            {
                if (server->userLinks[client]->getRoom()->startGame(server->userLinks[client]))
                    client->writePacket(Packet::pack(ko));
                else {
                    Instruction i(Instruction::START_GAME);
                    server->userLinks[client]->getRoom()->sendToEveryUser(Packet::pack(i));
                }
            }
            else
                client->writePacket(Packet::pack(ko));

            delete instruct;
        }
        delete packet;
    }
}

void
RTypeServer::tcpGamePlay(ISocket *client) {

    Packet *packet;
    Instruction ko(Instruction::KO);
    unsigned int playerId;
    std::vector<int> *instruct;
    GameRoom *room;

    if ((room = RTypeServer::getInstance()->userLinks[client]->getRoom()) == NULL)
    {
        client->attachOnReceive(RTypeServer::tcpMemberRoom);
        return (client->getOnReceive()(client));
    }
    playerId = room->getUserNo(RTypeServer::getInstance()->userLinks[client]);

    //get packet
    while ((packet = client->readPacket()) != NULL) {

        if (packet->getType() == Packet::IntVector &&
            (instruct = packet->unpack<std::vector<int> >()) != NULL)
        {
            delete instruct;
        }
        delete packet;
    }
}

RTypeServer *RTypeServer::getInstance(int tcpPort, int udpPort) {

    static RTypeServer *instance = NULL;

    if (instance == NULL) {
        try {
            instance = new RTypeServer(tcpPort, udpPort);
        }
        catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return (instance);
}

void RTypeServer::tcpGuestWelcomeRoom(ISocket *client) {

    std::cout << "Client connected " << client->getIp() << std::endl;
}

void RTypeServer::tcpGuestGoodbyeRoom(ISocket *client) {

    RTypeServer::getInstance()->removeUser(client);
    std::cout << "Client disconnected " << client->getIp() << std::endl;
}

bool RTypeServer::removeUser(ISocket *client) {

    std::map<ISocket *, User *>::iterator it;
    IMutex *mutex = (*MutexVault::getMutexVault())["serverType"];
    bool res = false;

    mutex->lock(true);
    if ((it = this->userLinks.find(client)) != this->userLinks.end())
    {
        std::cout << "Removing user : " << this->userLinks[client]->getName() << std::endl;
        RTypeServer::getInstance()->leaveRoom(RTypeServer::getInstance()->userLinks[client]);
        delete it->second;
        client->attachOnReceive(RTypeServer::tcpGuestRoom);
        this->userLinks.erase(it);
        res = true;
    }
    mutex->unlock();
    return (res);
}

bool RTypeServer::removeRoom(GameRoom *room) {

    std::vector<GameRoom *>::iterator it;
    IMutex *mutex = (*MutexVault::getMutexVault())["serverType"];
    bool res = false;

    mutex->lock(true);
    if ((it = std::find(this->rooms.begin(), this->rooms.end(), room)) != this->rooms.end())
    {
        std::cout << "Removing room " << (*it)->getName() << std::endl;
        delete *it;
        this->rooms.erase(it);
        res = true;
    }
    mutex->unlock();
    return (res);
}

bool RTypeServer::sendToClient(User *user, Instruction &instruct) {

    IMutex *mutex = (*MutexVault::getMutexVault())["serverType"];
    mutex->lock(true);
    bool res = false;

    for (std::map<ISocket *, User *>::iterator it = this->userLinks.begin(); it != this->userLinks.end(); it++)
        if (it->second == user)
        {
            it->first->writePacket(Packet::pack(instruct));
            res = true;
            break;
        }
    mutex->unlock();
    return (res);
}

ISocket *RTypeServer::getUserSocket(User *user) {

    ISocket *client = NULL;
    IMutex *mutex = (*MutexVault::getMutexVault())["serverType"];
    mutex->lock(true);

    for (std::map<ISocket *, User *>::iterator it = this->userLinks.begin(); it != this->userLinks.end(); it++)
        if (it->second == user)
        {
            client = it->first;
            break;
        }
    mutex->unlock();
    return (client);
}

void RTypeServer::tcpHold(ISocket *client) {

    IMutex *mutex = (*MutexVault::getMutexVault())["instantiation"];
    mutex->lock(true);
    client->attachOnReceive(RTypeServer::tcpGamePlay);
    mutex->unlock();
}
