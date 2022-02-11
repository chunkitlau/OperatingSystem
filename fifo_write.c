#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#define PATH "./fifo"
int main()
{
    // 打开FIFO命名管道
    int fd = open(PATH, O_WRONLY);
    if (fd < 0)
    {
        perror("open error");
        exit(0);
    }
    char Buf[BUFSIZ];
    while (1)
    {
        // 从标准输入读取数据并缓存到Buf中
        printf("please Enter #: ");
        fflush(stdout);
        ssize_t s = read(0, Buf, sizeof(Buf));
        if (s < 0)
        {
            perror("read is failed");
            exit(1);
        }
        else if (s == 0)
        {
            printf("read is closed!");
            return 1;
        }
        else
        {
            Buf[s] = '\0';
            // 将数据写入FIFO管道
            write(fd, Buf, strlen(Buf));
        }
        // sleep(1);
    }
    return 0;
}