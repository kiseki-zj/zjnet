#ifndef _THREAD_H_
#define _THREAD_H_


#include "Mutex.h"
#include "noncopyable.h"
#include <functional>
#include <pthread.h>
#include <string>

class Thread : noncopyable {
 public:
    typedef std::function<void()> ThreadFunc;
    explicit Thread(ThreadFunc, const std::string& name = std::string());
    ~Thread();
    void start();
    void join();
    pthread_t getId() { return pthreadId_; }
    char* getName() { return (char*)name_.c_str(); }

    ThreadFunc func_;
 private:    
    std::string name_;
    pthread_t pthreadId_;
    bool started_;

};
void* startThread(void*);

#endif