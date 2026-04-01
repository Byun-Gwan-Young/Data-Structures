#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>  // Mac 메모리 + CPU 측정
#include <sys/time.h>

// GCD - 유클리드 호제법 (반복)
static long long gcd(long long a, long long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// 피보나치 - 재귀
long long fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(void) {
    printf("%-6s %-20s %-20s %-6s %-15s %-12s %-12s\n",
           "n", "F(n)", "F(n-1)", "GCD", "Time(ms)", "CPU(ms)", "Memory(KB)");
    printf("------------------------------------------------------------------------------------------\n");

    for (int n = 5; n <= 50; n++) {
        // 시작 시점 측정
        clock_t start = clock();
        struct rusage usage_start;
        getrusage(RUSAGE_SELF, &usage_start);

        long long fn   = fibonacci(n);
        long long fn_1 = fibonacci(n - 1);
        long long g    = gcd(fn, fn_1);

        // 종료 시점 측정
        clock_t end = clock();
        struct rusage usage_end;
        getrusage(RUSAGE_SELF, &usage_end);

        // 경과 시간 (ms)
        double elapsed_ms = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;

        // CPU 사용 시간 (user time + system time, ms)
        double cpu_user_ms = (usage_end.ru_utime.tv_sec - usage_start.ru_utime.tv_sec) * 1000.0
                           + (usage_end.ru_utime.tv_usec - usage_start.ru_utime.tv_usec) / 1000.0;
        double cpu_sys_ms  = (usage_end.ru_stime.tv_sec - usage_start.ru_stime.tv_sec) * 1000.0
                           + (usage_end.ru_stime.tv_usec - usage_start.ru_stime.tv_usec) / 1000.0;
        double cpu_total_ms = cpu_user_ms + cpu_sys_ms;

        // 메모리 사용량 (KB) - Mac은 bytes 단위
        long mem_kb = usage_end.ru_maxrss / 1024;

        printf("%-6d %-20lld %-20lld %-6lld %-15.4f %-12.4f %-12ld\n",
               n, fn, fn_1, g, elapsed_ms, cpu_total_ms, mem_kb);

        // 10초 넘으면 종료
        if (elapsed_ms > 10000.0) {
            printf("너무 오래 걸려서 종료합니다.\n");
            break;
        }
    }

    return 0;
}
