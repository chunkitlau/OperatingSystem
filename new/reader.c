#include<stdlib.h> 
#include<stdio.h> 
#include<sys/types.h> 
#include<sys/stat.h> 
#include<fcntl.h> 
#include<errno.h> 
#include<unistd.h>
#define PATH "./fifo" 
#define SIZE 128 
int main() { 
    // umask(0); 
    // unlink(PATH);
    if (mkfifo(PATH,0777) == -1) { 
        perror("mkefifo error"); 
        exit(0); 
    } 
    int fd = open(PATH,O_RDONLY); 
    if (fd<0) { 
        printf("open fd is error\n"); 
        return 0; 
    } 
    char Buf[SIZE]; 
    while(1){ 
        ssize_t s = read(fd,Buf,sizeof(Buf)); 
        if (s<0) { 
            perror("read error");
            exit(1); 
        } 
        else if (s == 0) { 
            printf("client quit! i shoud quit!\n"); 
            break; 
        } else { 
            Buf[s] = '\0'; 
            printf("client# %s ",Buf); 
            fflush(stdout); 
        } 
    } 
    close(fd); 
    return 3; 
}