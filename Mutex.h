#ifndef _MUTEX_H_
#define _MUTEX_H_

#include <pthread.h>

class MutexLock {
 public:
    MutexLock()
    : holder_(0) {
        pthread_mutex_init(&mutex_, NULL);
    }
    
    void lock() {

    }

    void unlock() {

    }


 private:
    pthread_mutex_t mutex_;
    pid_t holder_;

};

class MutexLockGuard {
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

#endif