#include "AsyncLogging.h"
#include "LogFile.h"
#include <unistd.h>

AsyncLogging::AsyncLogging(const std::string& basename,
                           off_t rollsize,
                           int flushInterval)
  : running_(false),
    thread_(std::bind(&AsyncLogging::threadFunc, this), "AsyncLogging"),
    flushInterval_(flushInterval),
    currentBuffer_(new Buffer),
    nextBuffer_(new Buffer),
    mutex_(),
    buffers_(), 
    cond_(mutex_),
    basename_(basename) {
    currentBuffer_->bzero();
    nextBuffer_->bzero();
    buffers_.reserve(16);
}

void AsyncLogging::append(const char* logline, int len) {
    MutexLockGuard lock(mutex_);
    if (currentBuffer_->avail() > len) {
        currentBuffer_->append(logline, len);
    } else {
        buffers_.push_back(std::move(currentBuffer_));
        if (nextBuffer_) {
            currentBuffer_ = std::move(nextBuffer_);
        } else {
            currentBuffer_.reset(new Buffer);
        }
        currentBuffer_->append(logline, len);
        cond_.notify();
    }

} 

void AsyncLogging::threadFunc() {
    LogFile output(basename_);
    BufferVec buffersToWrite;
    BufferPtr newBuffer1(new Buffer);
    BufferPtr newBuffer2(new Buffer);
    newBuffer1->bzero();
    newBuffer2->bzero();
    buffersToWrite.reserve(16);
    while (running_) {
        {
            MutexLockGuard lock(mutex_);
            if (buffers_.empty()) {
                cond_.waitforseconds(flushInterval_);
            }   
            buffers_.push_back(std::move(currentBuffer_));
            if (!buffers_.empty()) {
                buffersToWrite.swap(buffers_);
            }
            currentBuffer_ = std::move(newBuffer1);
            if (!nextBuffer_) {
                nextBuffer_ = std::move(newBuffer2);
            }
        }
    
        //output
        int len = 0;
        // for (const auto& buffer : buffersToWrite) {
        //     fprintf(stderr, "%s", buffer->data());
        //     fprintf(stderr, "%d\n", buffer->len());
        //     len += buffer->len();
        // }
        // fprintf(stderr, "Output len = %d", len);
        for (const auto& buffer : buffersToWrite) {
            output.append(buffer->data(), buffer->len());
        }
        output.flush();
        //reset newbuffer
        if (!newBuffer1) {
            newBuffer1 = std::move(buffersToWrite.back());
            buffersToWrite.pop_back();
            newBuffer1->reset();
        }
        if (!newBuffer2) {
            newBuffer2 = std::move(buffersToWrite.back());
            buffersToWrite.pop_back();
            newBuffer2->reset();
        }
        buffersToWrite.clear();
    }
}