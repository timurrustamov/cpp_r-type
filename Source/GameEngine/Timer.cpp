//
// Created by rustam_t on 12/15/15.
//

#include "Timer.hpp"

Timer::Timer() {

}

Timer &
Timer::addNewEvent(const std::string &name, float seconds) {

    if (this->eventExists(name))
        this->_events[name].first = seconds;
    else
        this->_events[name] = std::make_pair(seconds, sf::Clock());
    return (*this);
}

Timer &
Timer::removeEvent(const std::string &name)
{
    std::map<std::string, std::pair<float, sf::Clock> >::iterator it;

    if ((it = this->_events.find(name)) != this->_events.end())
        this->_events.erase(it);
    return (*this);
}

bool
Timer::eventExists(const std::string &name)
{
    return (this->_events.find(name) != this->_events.end());
}

bool
Timer::eventDone(const std::string &name) {

    if (this->_events.find(name) != this->_events.end())
    {
        if (this->_events[name].first <= this->_events[name].second.getElapsedTime().asSeconds())
            return (true);
    }
    return (false);
}

bool
Timer::operator[](const std::string &name) {

    return (this->eventDone(name));
}

Timer &
Timer::reset(const std::string &name) {

    if (this->eventExists(name))
        this->_events[name].second.restart();
    return (*this);
}

float
Timer::elapsedTime(const std::string &name) {

    if (this->eventExists(name))
        return (this->_events[name].second.getElapsedTime().asSeconds());
    return (0.0);
}

float
Timer::advancement(const std::string &name) {

    if (this->eventExists(name) && this->_events[name].first > 0.0000001) {
        return (this->_events[name].second.getElapsedTime().asSeconds() >= this->_events[name].first ?
                (1) : this->_events[name].second.getElapsedTime().asSeconds() / this->_events[name].first);
    }
    return (0);
}

float
Timer::leftTime(const std::string &name) {

    if (this->eventExists(name) && this->_events[name].first > 0.0000001)
        return (this->_events[name].first - this->elapsedTime(name));
    return (0);
}

std::pair<std::string, float>
Timer::operator[](unsigned int pos) {

    if (pos < this->size())
    {
        std::map<std::string, std::pair<float, sf::Clock> >::iterator it = this->_events.begin();
        for (unsigned int i = 0; i < pos; i++)
            it++;
        return (std::make_pair(it->first, this->leftTime(it->first)));
    }
    return (std::make_pair("", 0));
}

unsigned int Timer::size() const {

    return (static_cast<unsigned int>(this->_events.size()));
}
