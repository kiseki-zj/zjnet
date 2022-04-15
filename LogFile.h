#ifndef _LOGFILE_H_
#define _LOGFILE_H_

#include <stdio.h>
#include <string>
#include <assert.h>
#include "noncopyable.h"
class LogFile : noncopyable{
 public:
    explicit LogFile(std::string& pathname) 
    : fp_(fopen(pathname.c_str(), "a")) {
        assert(fp_);
        //::setbuffer(fp_, buffer_, sizeof buffer_);
        //自定义缓冲区和大小，我觉得没必要
    }
    ~LogFile() {
        fclose(fp_);
    }
    void append(const char* logline, size_t len) {
        int nwrite = 0;
        int remain = len;
        while (nwrite != len) {
            int n = write(logline, remain);
            nwrite += n;
            remain -= n;
            if (remain) {
                logline += n;
                fprintf(stderr, "LogFile append failed\n");
            }
        }
    }
    void flush() {
        // 对于写流，fflush用于把标准库实现的用户态缓冲中的内容全部复制到内核缓冲区
        // 对于读流，fflush把用户缓冲删除
        ::fflush(fp_);
    }
 private:
    size_t write(const char* ptr, size_t size) {
        // 1.fwrite_unlocked是线程不安全的，但是只有log线程这一个线程会写
        // 2.有无unlocked区别在于性能，unlocked内部不会加锁
        // 3.有无unlocked都是阻塞IO，见fwritetest.cc
        // 4.流IO是标准库函数，缓冲在用户态
        return ::fwrite_unlocked(ptr, 1, size, fp_);
    }
    FILE* fp_;

};

#endif