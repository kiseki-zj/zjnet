#ifndef _LOGGING_H_
#define _LOGGING_H_

#include "AsyncLogging.h"
#include <string>

#define LOG Logging(__FILE__, __LINE__)

class Logging {
 public:
    explicit Logging(const char* file, int line)
    : file_(file),
      line_(line) {
        //formattime();
    }
    ~Logging() {

    }
    void output(const char*, size_t);
    //void formattime();

    Logging& operator<<(const char*);

 private:
    const char* file_;
    int line_;

};



#endif