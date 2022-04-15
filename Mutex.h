#ifndef _MUTEX_H_
#define _MUTEX_H_

#include <pthread.h>
#include "noncopyable.h"

class MutexLock : noncopyable {
 public:
    MutexLock()
    : holder_(0) {
        pthread_mutex_init(&pmutex_, NULL);
    }   
    void lock() {
        pthread_mutex_lock(&pmutex_);
    }
    void unlock() {
        pthread_mutex_unlock(&pmutex_);
    }

 private:
    friend class Condition;
    pthread_mutex_t pmutex_;
    pid_t holder_;

};

class MutexLockGuard : noncopyable {
 public:
    explicit MutexLockGuard(MutexLock& mutex)
    : mutex_(mutex) {
        mutex_.lock();
    }
    ~MutexLockGuard() {
        mutex_.unlock();
    }

 private:
    MutexLock& mutex_;
};

class Condition : noncopyable {
 public:
    explicit Condition(MutexLock& mutex) 
    : mutex_(mutex) {
        pthread_cond_init(&pcond_, NULL);
    }
    ~Condition() {
        pthread_cond_destroy(&pcond_);
    }
    void wait() {
        pthread_cond_wait(&pcond_, &mutex_.pmutex_);
    }
    void notify() {
        pthread_cond_signal(&pcond_);
    }
    void waitforseconds(double seconds);

 private:
    MutexLock& mutex_;
    pthread_cond_t pcond_;
};

#endif