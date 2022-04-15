#include "Mutex.h"
#include <sys/time.h>
#include <errno.h>
#include <sys/types.h>
void Condition::waitforseconds(double seconds) {
    struct timeval now;
    const int64_t nanopersecond = 1e9;
    timespec end;
    int64_t nanoseconds = static_cast<int64_t>(seconds * nanopersecond);
    gettimeofday(&now, NULL);
    end.tv_sec = now.tv_sec + (now.tv_usec*1000 + nanoseconds) / nanopersecond;
    end.tv_nsec = (now.tv_usec*1000 + nanoseconds) % nanopersecond;
    pthread_cond_timedwait(&pcond_, &mutex_.pmutex_, &end);
}