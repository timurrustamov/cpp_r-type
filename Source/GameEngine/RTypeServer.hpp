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
    static RTypeServer *getInstance(int tcpPort = 4242, int udpPort = 4243);
    ~RTypeServer();

    bool createRoom(User *user, const std::string &roomName);
    bool roomNameExists(const std::string &roomName);
    bool joinRoom(User *user, const std::string &roomName);
    bool leaveRoom(User *user, const std::string &roomName);

    bool newUser(const std::string &userName, ISocket *client);
    bool userNameExists(const std::string &username);
    bool startGame(User *user);

    static void tcpGuestWelcomeRoom(ISocket *client);
    static void tcpGuestGoodbyeRoom(ISocket *client);
    static void tcpGuestRoom(ISocket *client);
    static void tcpMemberRoom(ISocket *client);
    static void tcpWaitingRoom(ISocket *client);

protected:

    RTypeServer(int tcpPort, int udpPort);

    ISocket *tcpServer;
    ISocket *udpServer;

    std::map<ISocket *, User *> userLinks;
    std::vector<GameRoom *> rooms;
};


#endif //CPP_R_TYPECPY2_RTYPESERVER_HPP
