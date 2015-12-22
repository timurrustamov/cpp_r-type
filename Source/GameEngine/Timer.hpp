//
// Created by rustam_t on 12/15/15.
//

#ifndef CPP_R_TYPECPY2_TIMER_HPP
#define CPP_R_TYPECPY2_TIMER_HPP

#include <cstddef>
#include <string>
#include <utility>
#include <map>
#include <algorithm>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

class Timer {

public:

    Timer();
    ~Timer() {};
    Timer &addNewEvent(const std::string &name, float seconds);
    Timer &removeEvent(const std::string &name);
    Timer &reset(const std::string &name);

    bool eventExists(const std::string &name);
    float elapsedTime(const std::string &name);
    float advancement(const std::string &name);
    bool eventDone(const std::string &name);
    bool operator[](const std::string &name);

protected:

    std::map<std::string, std::pair<float, sf::Clock> > _events;
};


#endif //CPP_R_TYPECPY2_TIMER_HPP
