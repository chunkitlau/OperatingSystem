#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ORANGE_MAX_VALUE 1000000
#define APPLE_MAX_VALUE  100000000
#define MSECOND          1000000
#define NUM_THREADS 1
struct apple{
    unsigned long long a;
    unsigned long long b;
};
struct orange{
    int a[ORANGE_MAX_VALUE];
    int b[ORANGE_MAX_VALUE];
};
cpu_set_t mask;
void* p_apple(void *test) {
    CPU_ZERO(&mask);
    CPU_SET(1,&mask);
    int sum;
    for(sum = 0; sum < APPLE_MAX_VALUE; sum++){
        ((struct apple *)test)->a += sum;
        ((struct apple *)test)->b += sum;
    }
}
void p_orange(void *test1) {
    int sum = 0;
    for(int index = 0; index < ORANGE_MAX_VALUE; index++){
        sum += ((struct orange *)test1)->a[index] + ((struct orange *)test1)->b[index];
    }
}
int main(int argc, const char* argv[]) {
    struct apple test;
    struct orange test1;
	CPU_ZERO(&mask);
    CPU_SET(0,&mask);
    // 定义线程的 id 变量，多个变量使用数组
    pthread_t tids[NUM_THREADS];
    //参数依次是：创建的线程id，线程参数，调用的函数，传入的函数参数
    int ret0 = pthread_create(&tids[0], NULL, p_apple, &test);
    if (ret0 != 0){
        printf("pthread_create error: error_code=%d\n", ret0);
    }
    p_orange(&test1);
    pthread_join(tids[0],NULL);
    return 0;
}