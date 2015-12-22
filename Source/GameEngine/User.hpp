//
// Created by rustam_t on 12/22/15.
//

#ifndef CPP_R_TYPECPY2_USER_HPP
#define CPP_R_TYPECPY2_USER_HPP

#include <string>
#include "MutexVault.hpp"
#include "GameRoom.hpp"

class GameRoom;

class User {

public:

    enum State
    {
        Waiting,
        Playing,
        Error = -1
    };

    User(const std::string &name);
    ~User() {};

    const std::string &getName() const;
    void attachRoom(GameRoom *room);
    void detachRoom();
    GameRoom *getRoom() const;
    State getState() const;
    void setState(State state);

protected:

    //not owned
    GameRoom *room;
    std::string name;
    State state;
};


#endif //CPP_R_TYPECPY2_USER_HPP
