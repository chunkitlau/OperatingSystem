#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sched.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<time.h>
#include<algorithm>
/*
int main(){
    srand(time(0));
    int pid_fork_1, pid_fork_2, pid_fork_3, status;
    if((pid_fork_1 = fork()) == 0){ // fork 系统调用 （1）
        // 子进程处理过程1：通过exec调入自身执行代码 
        printf("Child process 1!\n");
        int pid_get = getpid(); // getpid 系统调用
        printf("P1: pid_fork_1=%d pid_get=%d\n", pid_fork_1, pid_get);
        // 增加数十到数百毫秒的延迟，保证进程执行时间不少于3个时间片 (5)
        sleep(std::max(rand() % 1000, 10) / 1000.0);
        // 父进程创建子进程后，子进程通过exec()调入自身执行代码 （2）
        if(execl("/bin/echo", "echo", "P1: executed by execl", NULL) < 0) {
            // 异常处理
            printf("P1: Error on execl\n"); // exec 系统调用
            exit(0); // exit 系统调用
        }
    }
    else if (pid_fork_1 < 0){
        // 异常处理
        printf("P1: fork error\n");
        exit(0);
    }

    if((pid_fork_2 = fork()) == 0){ // fork 系统调用 （1）
        // 子进程处理过程2：通过exit主动结束 
        printf("Child process 2!\n");
        int pid_get = getpid(); // getpid 系统调用
        printf("P2: pid_fork_2=%d pid_get=%d\n", pid_fork_2, pid_get);
        // 增加数十到数百毫秒的延迟，保证进程执行时间不少于3个时间片 (5)
        sleep(std::max(rand() % 1000, 10) / 1000.0);
        // 进程可以自己通过exit()主动结束 （3）
        printf("P2: Child process 2 exit(0)!\n");
        exit(0); // exit 系统调用
    }
    else if (pid_fork_2 < 0){
        printf("P2: fork error\n");
        exit(0);
    }

    if((pid_fork_3 = fork()) == 0){ // fork 系统调用 （1）
        // 子进程处理过程3：通过父进程kill结束 
        printf("Child process 3!\n");
        int pid_get = getpid(); // getpid 系统调用
        printf("P3: pid_fork_3=%d pid_get=%d\n", pid_fork_3, pid_get);
        // 睡眠10秒
        sleep(10);
        printf("P3: Child process 3 exit(0)!\n");
        exit(0); // exit 系统调用
    }
    else if (pid_fork_3 < 0){
        printf("P3: fork error\n");
        exit(0);
    }

    // 父进程处理过程 
    printf("Parent process!\n");
    int child_pid = wait(&status); // wait 系统调用
    printf("P: wait process %d with status %d\n", child_pid, status);
    // 也可以被父进程执行kill()命令来结束
    kill(pid_fork_3,SIGABRT); // kill 系统调用
    printf("P: kill process %d\n", pid_fork_3);
    sleep(3);
    printf("Parent process return!\n");
    return 0;
    
    //int r2 = clone(fn, child_stack, flags, arg); // clone 系统调用
    //signal(sig, func); // signal 系统调用
}
*/
int value = 0;
int child_progress(void *arg){
    while(value < 10) {
        printf("child_progress 2,value = %d\n",value);
        value++;
        sleep(std::max(rand() % 1000, 10) / 1000.0);
    }
    return 0;
}
int main(){
    srand(time(0));
    int pid_fork_1, pid_fork_2, pid_fork_3, status;
    if((pid_fork_1 = fork()) == 0){ // fork 系统调用 （1）
        /*子进程处理过程1：通过exec调入自身执行代码 */
        printf("Child process 1!\n");
        int pid_get = getpid(); // getpid 系统调用
        printf("P1: pid_fork_1=%d pid_get=%d\n", pid_fork_1, pid_get);
        // 增加数十到数百毫秒的延迟，保证进程执行时间不少于3个时间片 (5)
        sleep(std::max(rand() % 1000, 10) / 1000.0);
        // 进程可以自己通过exit()主动结束 （3）
        printf("P1: Child process 1 exit(0)!\n");
        exit(0); // exit 系统调用
    }
    else if (pid_fork_1 < 0){
        // 异常处理
        printf("P1: fork error\n");
        exit(0);
    }

    char *stack = (char*)malloc(4096);
    if (stack == NULL) {
        printf("malloc fail\n");
    }
    //子进程继承父进程的数据空间/在子进程结束后运行/将子进程的id存储到tid变量中
    int tid = 0, mask = CLONE_VM|CLONE_VFORK|CLONE_CHILD_SETTID;
    if((pid_fork_2 = clone(child_progress, stack + 4096, mask, NULL, NULL, NULL, &tid)) >= 0){ // clone 系统调用 （1）
        /*子进程处理过程2：通过exit主动结束 */
        printf("clone child process 2 pid %d, tid %d!\n", pid_fork_2, tid);
    }
    else if (pid_fork_2 < 0){
        printf("P2: clone error\n");
        exit(0);
    }

    /*父进程处理过程 */
    printf("Parent process!\n");
    while(value < 20){
        printf("father, value = %d\r\n",value);
        value ++;
        sleep(std::max(rand() % 1000, 10) / 1000.0);
    }
    printf("Parent process return!\n");
    return 0;
    
    //signal(sig, func); // signal 系统调用
}