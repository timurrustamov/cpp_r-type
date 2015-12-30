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
        this->removeAllUsers();
    };

    const std::string &getName() const;
    bool addUser(User *);
    bool removeUser(User *);
    bool removeAllUsers();
    bool hasUser(User *) const;
    const std::vector<User *> &getUsers() const;
    Instruction getUsersInstruction() const;
    bool setState(State state, User *owner);
    State getState() const;

    User *owner;
protected:

    std::string name;
    State state;
    //not own those ptrs
    std::vector<User *> users;
};


#endif //CPP_R_TYPECPY2_GAMEROOM_HPP
