//
// Created by rustam_t on 12/22/15.
//

#ifndef CPP_R_TYPECPY2_RTYPESERVER_HPP
#define CPP_R_TYPECPY2_RTYPESERVER_HPP

#include <vector>
#include <map>

#if defined(_WIN32) && !defined(WIN32)
# define _WINSOCKAPI_
# define NOGDI
# include <windows.h>
# define WIN32
#endif

#ifdef WIN32
# include "../System/WinSocket.h"
#else
# include "LinuxSocket.h"
#endif

class User;
class GameRoom;

class RTypeServer {

public:
    static RTypeServer *getInstance(int tcpPort = 4242, int udpPort = 4243);
    ~RTypeServer();

    bool createRoom(User *user, const std::string &roomName);
    bool roomNameExists(const std::string &roomName);
    bool joinRoom(User *user, const std::string &roomName);
    bool leaveRoom(User *user);
    bool sendToClient(User *user, Instruction &instruct);
    bool removeRoom(GameRoom *room);

    bool newUser(const std::string &userName, ISocket *client);
    bool removeUser(ISocket *client);
    bool userNameExists(const std::string &username);
    bool startGame(User *user);

    ISocket *getUserSocket(User *user);

    static void tcpGuestWelcomeRoom(ISocket *client);
    static void tcpGuestGoodbyeRoom(ISocket *client);
    static void tcpGuestRoom(ISocket *client);
    static void tcpMemberRoom(ISocket *client);
    static void tcpWaitingRoom(ISocket *client);
    static void tcpHold(ISocket *client);
    static void tcpGamePlay(ISocket *client);

protected:

    RTypeServer(int tcpPort, int udpPort);

    ISocket *tcpServer;
    ISocket *udpServer;

    std::map<ISocket *, User *> userLinks;
    std::vector<GameRoom *> rooms;
};

#include "GameRoom.hpp"
#include "User.hpp"

#endif //CPP_R_TYPECPY2_RTYPESERVER_HPP
