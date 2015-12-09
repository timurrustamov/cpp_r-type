//
// Created by rustam_t on 12/9/15.
//

#ifndef         CPP_R_TYPE_TIMER_HPP
#define         CPP_R_TYPE_TIMER_HPP

#include            <iostream>
#include            <ctime>

class               Timer
{
public:
    Timer();
    void            start();
    void            stop();
    void            reset();
    bool            isRunning();
    unsigned long   getTime();
    bool            isOver(unsigned long seconds);

private:
    bool            resetted;
    bool            running;
    unsigned long   beg;
    unsigned long   end;
};

#endif          //CPP_R_TYPE_TIMER_HPP
