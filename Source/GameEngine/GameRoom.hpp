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
    ~GameRoom() {};

    const std::string &getName() const;
    bool addUser(User *);
    bool removeUser(User *);
    bool hasUser(User *) const;
    const std::vector<User *> &getUsers() const;
    bool setState(State state, User *owner);
    State getState() const;

protected:

    std::string name;
    State state;
    //not own those ptrs
    User *owner;
    std::vector<User *> users;
};


#endif //CPP_R_TYPECPY2_GAMEROOM_HPP
