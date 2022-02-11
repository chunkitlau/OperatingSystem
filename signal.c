#include <stdio.h>
#include <stdlib.h> 
#include <signal.h>
#include<sys/wait.h> 
#include <unistd.h>
#include <sys/types.h>
int wait_flag;
void stop() { 
    printf("\ninterruption\n"); 
} 
int main() {
    int pid1, pid2;
    signal (3, stop);// 或者signal(14, stop);
    while( (pid1 = fork())==-1);
    if(pid1 > 0) {
        while( (pid2 = fork())==-1);
        if(pid2 > 0) {
            wait_flag = 1;
            sleep(5);
            kill(pid1, 16);
            kill(pid2, 17);
            wait(0);
            wait(0);
            printf("\n Parent process is killed! !\n");
            exit(0);
        }
        else {
            wait_flag = 1;
            signal (17, stop);
            printf("\n Child process 2 is killed by parent!!\n");
            exit(0);
        }
    }
    else {
        wait_flag = 1;
        signal (16, stop);
        printf("\n Child process 1 is killed by parent!!\n");
        exit(0);
    }
}