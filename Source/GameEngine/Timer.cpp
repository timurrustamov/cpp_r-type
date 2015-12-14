//
// Created by Zaboon on 12/12/2015.
//

#include                                                  "Timer.hpp"

Timer::Timer() {
    this->_time = std::chrono::system_clock::now();
    this->_isOn = false;
    this->setTimer(0, 0, 0);
}

Timer::~Timer() {

}

void                                                            Timer::start() {
    this->_isOn = true;
}

void                                                            Timer::stop() {
    this->pause();
    this->reset();
}

void                                                            Timer::pause() {
    this->_isOn = false;
}

void                                                            Timer::refresh() {
    int                                                         timeLeft = this->_isOn ?
                                                                         std::chrono::duration_cast<std::chrono::milliseconds>(this->_isOn - this->_time).count()
                                                                                     : 0;
    std::chrono::time_point<std::chrono::system_clock>           _now = std::chrono::system_clock::now();

    this->_time = _now;
    this->addTime(timeLeft);
}

void                                                            Timer::addTime(int time) {
    //TODO Add time to the timer.
}

void                                                            Timer::setTimer(int min, int sec, int mil) {
    this->_min = min;
    this->_sec = sec;
    this->mil = mil;
}
