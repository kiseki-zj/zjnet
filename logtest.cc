#include "AsyncLogging.h"
#include <string.h>
#include <unistd.h>

AsyncLogging logging("test.log", 12, 3);

void printlog(const char* log) {
    while (1) {
        logging.append(log, strlen(log));
        sleep(0.02);
    }
}

int main() {
    logging.start();
    Thread t1(std::bind(printlog, "fuck log 1\n"), "t1");
    Thread t2(std::bind(printlog, "fuck log 2\n"), "t2");
    t1.start();
    t2.start();
    while (1) {
        
    }
       
}