//
// Created by rustam_t on 12/22/15.
//

#ifndef CPP_R_TYPECPY2_RTYPESERVER_HPP
#define CPP_R_TYPECPY2_RTYPESERVER_HPP

#include <vector>
#include <map>

#include "LinuxSocket.h"
#include "GameRoom.hpp"

class RTypeServer {

public:
    RTypeServer(int tcpPort, int udpPort);
    ~RTypeServer();

    bool createRoom(User *user, const std::string &roomName);
    bool roomNameExists(const std::string &roomName);
    bool joinRoom(User *user, const std::string &roomName);
    bool leaveRoom(User *user, const std::string &roomName);

    bool newUser(const std::string &userName, ISocket *client);
    bool userNameExists(const std::string &username);
    bool startGame(User *user);

    static void tcpGuestRoom(ISocket *client);
    static void tcpMemberRoom(ISocket *client);
    static void tcpWaitingRoom(ISocket *client);

protected:

    ISocket *tcpServer;
    ISocket *udpServer;

    std::map<ISocket *, User *> userLinks;
    std::vector<GameRoom *> rooms;
};


#endif //CPP_R_TYPECPY2_RTYPESERVER_HPP
