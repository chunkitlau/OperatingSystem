
#include<stdio.h>
#include<sys/time.h>
#include<unistd.h>
#include<stdlib.h>
#define K 10
#define EPS 0.02
#define M 200
#define INF 1000000000
int main(int argc, char* argv[]) {
    struct timeval tv_begin,tv_end;
    int ktest[K];
    for (int k = 0; k < K; ++k) ktest[k] = INF;
    for (int round = 0; round < M; ++round) {
        gettimeofday(&tv_begin,NULL);
        //system("./demo1");
        system(argv[1]);
        gettimeofday(&tv_end,NULL);
        int delta = tv_end.tv_sec * 1e6 + tv_end.tv_usec - (tv_begin.tv_sec * 1e6 + tv_begin.tv_usec);
        printf("In %d delta %d usec\n", round, delta);
        for (int k = 0; k < K; ++k)
            if (delta < ktest[k]) {
                for (int p = K - 1; p > k; --p)
                    ktest[p] = ktest[p - 1];
                ktest[k] = delta;
                break;
            }
        int isFinish = 1;
        for (int k = 1; k < K; ++k)
            if (ktest[k - 1] * (1 + EPS) < ktest[k]) {
                isFinish = 0;
                break;
            }
        if (isFinish) {
            int sum = 0;
            for (int k = 0; k < K; ++k)
                sum += ktest[k];
            printf("K-Best: %lf usec\n", 1.0 * sum / K);
            exit(0);
        }
    }
    printf("Can't find K-Best\n");
    //printf(“tv_begin: %d sec %d usec\n”,tv_begin.tv_sec,tv_begin.tv_usec);
    //printf(“tv_end: %d sec %d usec\n”,tv_end.tv_sec,tv_end.tv_usec);
}