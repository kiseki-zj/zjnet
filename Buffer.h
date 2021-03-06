#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <string.h>

const int SIZE = 4096;

class Buffer {
 public:
    Buffer()
    : cur_(data_) {
        bzero();
    }
    void append(const char* buf, size_t len) {
        if (avail() > len) {
            memcpy(cur_, buf, len);
            cur_ += len;
        }
    }

    inline void bzero() { memset(data_, 0, SIZE); }
    inline void reset() { bzero(); cur_ = data_; }
    inline size_t avail() { return end() - cur_; }
    inline const char* end() { return data_ + SIZE; }
    inline const char* data() { return data_; }
    inline size_t len() { return cur_ - data_; }
 private:
    char data_[SIZE];
    char* cur_;

};

#endif