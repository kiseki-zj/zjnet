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
        pthread_mutex_lock(&mutex_);
    }
    void unlock() {
        pthread_mutex_unlock(&mutex_);
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