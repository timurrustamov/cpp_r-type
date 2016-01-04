//
// Created by rustam_t on 12/22/15.
//

#ifndef CPP_R_TYPECPY2_GAMEROOM_HPP
#define CPP_R_TYPECPY2_GAMEROOM_HPP

#include <algorithm>
#include <string>
#include <vector>
#include "ISocket.h"
#include "User.hpp"
#include "RTypeServer.hpp"

#include					"../System/window.h"
#include					"../GameEngine/OnLevel.h"
#include					"../System/Animation.h"
#include					"../System/ResourcesBank.h"
#include                    "IThread.hpp"
#include					"OnLevel.h"
#ifndef _WIN_32
 # include <unistd.h>
#endif

class User;

class GameRoom {

public:

    enum State
    {
        Waiting,
        Running,
        Error = -1
    };

    GameRoom(const std::string &name, User *);
    ~GameRoom()
    {
        this->setState(GameRoom::Error, this->owner);
		#ifdef _WIN_32
			Sleep(10);
		#else
			usleep(1000); 
		#endif
        this->removeAllUsers();
    };

    void sendToEveryUser(Packet *p);
    static void gameLoop(unsigned int threadId, GameRoom *);
    static void levelUpdate(OnLevel &level);
    const std::string &getName() const;
    bool addUser(User *);
    bool removeUser(User *);
    bool removeAllUsers();
    bool hasUser(User *) const;
    bool startGame(User *);
    unsigned int getUserNo(User *) const;
    const std::vector<User *> &getUsers() const;
    Instruction getUsersInstruction() const;
    bool setState(State state, User *owner);
    State getState() const;

    User *owner;
protected:

    IThread<void, GameRoom *> *th;
    std::string name;
    State state;
    //not own those ptrs
    std::vector<User *> users;
};


#endif //CPP_R_TYPECPY2_GAMEROOM_HPP
