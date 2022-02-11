#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#define PATH "./fifo"

int main()
{
    // 创建FIFO命名管道
    if (mkfifo(PATH, 0777) == -1)
    {
        perror("mkefifo error");
        exit(0);
    }
    // 打开FIFO命名管道
    int fd = open(PATH, O_RDONLY);
    if (fd < 0)
    {
        printf("open fd is error\n");
        return 0;
    }
    char Buf[BUFSIZ];
    while (1)
    {
        ssize_t s = read(fd, Buf, sizeof(Buf));
        if (s < 0)
        {
            perror("read error");
            exit(1);
        }
        else if (s == 0)
        {
            printf("Client quit! I should quit!\n");
            break;
        }
        else
        {
            Buf[s] = '\0';
            // 输出数据
            printf("client #: %s", Buf);
            fflush(stdout);
        }
    }
    // 关闭管道
    close(fd);
    return 0;
}