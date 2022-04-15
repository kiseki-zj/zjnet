#include "../Logging.h"
#include <string.h>
#include <unistd.h>

void printlog(const char* log) {
    while (1) {
        //logging.append(log, strlen(log));
        LOG << "log info\n";
        sleep(1);
    }
}

int main() {

    Thread t1(std::bind(printlog, "fuck log 1\n"), "t1");
    Thread t2(std::bind(printlog, "fuck log 2\n"), "t2");
    t1.start();
    t2.start();
    while (1) {
        
    }
       
}