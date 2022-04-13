#include "Thread.h"
#include <functional>
#include <unistd.h>
void func1() {
    fprintf(stderr, "fuck 1\n");
}

void func2(int k) {
    fprintf(stderr, "fuck 2 %d\n", k);
}

int main() {
    Thread t1(std::bind(func1), "t1");
    Thread t2(std::bind(func2, 10), "t2");
    if (1) {
        int a = 5;

    }
    fprintf(stdout, "%d", a);
    t2.start();
    sleep(2);
    t1.start();
    sleep(2);
}