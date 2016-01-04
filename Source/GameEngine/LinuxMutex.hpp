//
// Created by rustam_t on 10/6/15.
//

#ifndef PROJECT2_LINUXMUTEX_HPP
#define PROJECT2_LINUXMUTEX_HPP

#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>

class LinuxMutex : public IMutex
{
public:

    LinuxMutex()
    {
        locknb = 0;
        _tid = -1;
        pthread_mutex_init(&this->_mutex, NULL);
    }

    virtual bool lock(bool wait = true)
    {
        bool thisth = static_cast<bool>(pthread_equal(static_cast<pid_t>(syscall(SYS_gettid)), this->_tid));
        if (this->_tid == -1 || !(thisth))
        {
            pthread_mutex_lock(&this->_mutex);
            this->_status = IMutex::Locked;
            this->_tid = static_cast<pid_t>(syscall(SYS_gettid));
            locknb++;
            return (true);
        }
        if (thisth)
            locknb++;
        return (false);
    };

    virtual bool unlock()
    {
        bool thisth = static_cast<bool>(pthread_equal(static_cast<pid_t>(syscall(SYS_gettid)), this->_tid));
        if (this->_tid == -1)
            return false;
        if (thisth && --this->locknb > 0)
            return false;
        this->_status = IMutex::Unlocked;
        this->_tid = -1;
        pthread_mutex_unlock(&this->_mutex);
        return (true);
    }

    ~LinuxMutex()
    {
        pthread_mutex_destroy(&this->_mutex);
    };

protected:

    pthread_mutex_t _mutex;
    pid_t           _tid;
    unsigned int    locknb;
};

#endif //PROJECT2_LINUXMUTEX_HPP
