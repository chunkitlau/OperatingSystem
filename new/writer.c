#include<stdlib.h> 
#include<stdio.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/stat.h> 
#include<string.h> 
#include<errno.h> 
#include<fcntl.h> 
#include<unistd.h>
#define PATH "./fifo" 
#define SIZE 128 
int main() { 
    int fd = open(PATH,O_WRONLY); 
    if (fd < 0) { 
        perror("open error"); 
        exit(0); 
    } 
    char Buf[SIZE]; 
    while(1) { 
        printf("please Enter#:");
        fflush(stdout); 
        ssize_t s = read(0,Buf,sizeof(Buf)); 
        if (s<0) { 
            perror("read is failed"); 
            exit(1); 
        } 
        else if(s==0) { 
            printf("read is closed!"); 
            return 1; 
        } 
        else{ 
            Buf[s]= '\0'; 
            write(fd,Buf,strlen(Buf)); 
        } 
    } 
    return 0; 
}