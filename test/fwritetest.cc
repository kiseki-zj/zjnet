#include <stdio.h>
#include <unistd.h>
char buf[500000]{'a'};
int main() {
    
    // FILE* fp = fopen("./tt", "w");
    // while (1) {
    //     int nwrite = fwrite_unlocked(buf, 1, sizeof buf, fp);
    //     printf("%d\n", nwrite);
    //     sleep(2);
    // }
    
    //FILE* fp = fopen(STDIN_FILENO, "r");
    while (1) {
        int nread = fread/*_unlocked*/(buf, 1, 20, stdin);
        fprintf(stderr, "%d\n", nread);
        sleep(2);
    }

}