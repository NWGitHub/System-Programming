// getallprimeThread_improved.c
// Build:   gcc -O3 -pthread -o primes getallprimeThread_improved.c
// Run:     ./primes           //  5  ()
//          ./primes -t1       //  ()

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>

#define NTHREAD 5
#define NMAX    500000
#define CHUNK   (NMAX / NTHREAD) // 10000

typedef struct {
    int start, end;
    int *buf;
    size_t count, cap;
} Range;

static inline bool is_prime(int n){
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;
    for (int i = 5; (int64_t)i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0) return false;
    return true;
}

static void vec_init(Range *r){
    r->cap = 1024; r->count = 0;
    r->buf = (int*)malloc(r->cap * sizeof(int));
    if (!r->buf){ perror("malloc"); exit(1); }
}
static void vec_push(Range *r, int v){
    if (r->count == r->cap){
        r->cap *= 2;
        int *nb = (int*)realloc(r->buf, r->cap * sizeof(int));
        if (!nb){ perror("realloc"); exit(1); }
        r->buf = nb;
    }
    r->buf[r->count++] = v;
}

static void* worker(void *arg){
    Range *r = (Range*)arg;
    vec_init(r);
    for (int n = r->start; n <= r->end; ++n)
        if (is_prime(n)) vec_push(r, n);
    return NULL;
}

static double now_ms(void){
    struct timespec ts; clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec * 1000.0 + (double)ts.tv_nsec / 1e6;
}

int main(int argc, char **argv){
    int threads = NTHREAD;
    if (argc >= 2 && (argv[1][0]=='-' && (argv[1][1]=='t'||argv[1][1]=='T'))){
        int t = atoi(argv[1]+2); if (t == 1) threads = 1;
    }

    Range ranges[NTHREAD]; pthread_t th[NTHREAD];
    for (int i = 0; i < NTHREAD; ++i){
        ranges[i].start = i * CHUNK + 1;
        ranges[i].end   = (i + 1) * CHUNK;
        ranges[i].buf = NULL; ranges[i].count = ranges[i].cap = 0;
    }

    double t0 = now_ms();

    if (threads == 1){
        for (int i = 0; i < NTHREAD; ++i) worker(&ranges[i]);
    }else{
        for (int i = 0; i < NTHREAD; ++i)
            if (pthread_create(&th[i], NULL, worker, &ranges[i]) != 0){ perror("pthread_create"); return 1; }
        for (int i = 0; i < NTHREAD; ++i) pthread_join(th[i], NULL);
    }

    double t1 = now_ms();

    //  
    for (int i = 0; i < NTHREAD; ++i){
        for (size_t j = 0; j < ranges[i].count; ++j)
            printf("%d ", ranges[i].buf[j]);
        free(ranges[i].buf);
    }

    double t2 = now_ms();
    fprintf(stderr, "\nCompute time: %.3f ms  |  Total (compute + print): %.3f ms\n",
            t1 - t0, t2 - t0);
    fprintf(stderr, "Mode: %s\n", threads==1 ? "single-thread" : "5-thread");
    return 0;
}
