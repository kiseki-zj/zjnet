#ifndef _ASYNCLOGGING_H_
#define _ASYNCLOGGING_H_

#include "Thread.h"
#include "Buffer.h"
#include "Mutex.h"
#include "noncopyable.h"
#include <memory>
#include <vector>
#include <string>
class AsyncLogging : noncopyable {
 public:
    AsyncLogging(const std::string& basename,
                 off_t rollsize,
                 int flushInterval = 3);
    ~AsyncLogging() {
        if (running_) {
            stop();
        }
    }

    void append(const char* logline, int len);
    void start() {
        running_ = true;
        thread_.start();
    }
    void stop() {
        running_ = false;
        thread_.join();
    }

 private:
    typedef std::unique_ptr<Buffer> BufferPtr;
    typedef std::vector<BufferPtr> BufferVec;

    void threadFunc();
    bool running_;
    Thread thread_;
    int flushInterval_;
    BufferPtr currentBuffer_, nextBuffer_;
    BufferVec buffers_;
    MutexLock mutex_;
    Condition cond_;
    std::string basename_;

};


#endif