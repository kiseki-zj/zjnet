#include "Logging.h"
#include "AsyncLogging.h"
#include <string.h>
#include <pthread.h>
#include <string>

static pthread_once_t once_control_ = PTHREAD_ONCE_INIT;
static AsyncLogging *AsyncLogger_;

void once_init()
{
    AsyncLogger_ = new AsyncLogging(std::string("test.log"), 1);
    AsyncLogger_->start(); 
}

Logging& Logging::operator<<(const char* msg) {
    this->output(msg, strlen(msg));
    return *this;
}

void Logging::output(const char* msg, size_t len) {
    pthread_once(&once_control_, once_init);
    AsyncLogger_->append(msg, len);
}