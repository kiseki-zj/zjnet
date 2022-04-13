#include "Thread.h"
#include <assert.h>
#include <unistd.h>
Thread::Thread(ThreadFunc func, const std::string& name)
  : func_(std::move(func)),
    name_(name),
    pthreadId_(0),
    started_(false) {
    
}

Thread::~Thread() {
    pthread_detach(pthreadId_);
}

void Thread::start() {
    assert(!started_);
    started_ = true;
    if (pthread_create(&pthreadId_, NULL, startThread, (void*)this)) {
        started_ = false;
        fprintf(stderr, "create thread %s failed\n", getName());
    }
}

void Thread::join() {
    pthread_join(pthreadId_, NULL);
}

void* startThread(void* args) {
    Thread* thisThread = static_cast<Thread*>(args);
    sleep(2);
    fprintf(stderr, "Thread %u:%s start\n", thisThread->getId(), thisThread->getName());
    thisThread->func_();
}