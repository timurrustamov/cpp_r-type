//
// Created by Zaboon on 12/12/2015.
//

#ifndef CPP_R_TYPE2_TIMER_HPP
#define CPP_R_TYPE2_TIMER_HPP

#include                                                  <iostream>
#include                                                  <string>
#include                                                  <chrono>


class                                                           Timer {
public:
    Timer();
    ~Timer();
    void                                                        start();
    void                                                        stop();
    void                                                        pause();
    void                                                        reset();
    void                                                        refresh();
    void                                                        addTime(int time);
    void                                                        setTimer(int min, int sec, int mil);
private:
    int                                                         _min;
    int                                                         _sec;
    int                                                         _mil;
    bool                                                        _isOn;
    std::chrono::time_point<std::chrono::system_clock>          _time;
};

#endif //CPP_R_TYPE2_TIMER_HPP
