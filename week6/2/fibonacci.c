#include <stdio.h>
#include <time.h>

/*
 * 피보나치 수열: F(1)=1, F(2)=1, F(3)=2, ...
 * 큰 N에서도 오버플로를 피하기 위해 unsigned long long 사용
 */

/* 순환(반복)적 방법 - O(N) 시간, O(1) 공간 */
unsigned long long fib_iter(int n)
{
    if (n <= 0) return 0;
    if (n <= 2) return 1;

    unsigned long long prev = 1, curr = 1, next = 0;
    for (int i = 3; i <= n; i++) {
        next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

/* 재귀적 방법 - O(φⁿ) 시간, O(N) 공간 */
unsigned long long fib_rec(int n)
{
    if (n <= 0) return 0;
    if (n <= 2) return 1;
    return fib_rec(n - 1) + fib_rec(n - 2);
}

/*
 * N을 1부터 MAX_N까지 늘려가며 두 방식의 수행 시간을 측정한다.
 * - 순환 방식은 한 번 호출이 너무 빨라서 ITER_REPEAT 번 반복 후 평균을 구한다.
 * - 재귀 방식은 N이 커질수록 급격히 느려지므로 1회만 측정한다.
 */
#define MAX_N        45
#define ITER_REPEAT  1000000

int main(void)
{
    printf("%-4s %-22s %-22s %-22s\n",
           "N", "F(N)", "Iterative(ns)", "Recursive(ns)");
    printf("------------------------------------------------------------------------\n");

    for (int n = 1; n <= MAX_N; n++) {
        struct timespec t1, t2;
        unsigned long long result_i = 0, result_r = 0;

        /* ---- 순환 방법 측정 ---- */
        clock_gettime(CLOCK_MONOTONIC, &t1);
        for (int k = 0; k < ITER_REPEAT; k++) {
            result_i = fib_iter(n);
        }
        clock_gettime(CLOCK_MONOTONIC, &t2);
        double iter_ns =
            ((double)(t2.tv_sec - t1.tv_sec) * 1e9 +
             (double)(t2.tv_nsec - t1.tv_nsec)) / ITER_REPEAT;

        /* ---- 재귀 방법 측정 ---- */
        clock_gettime(CLOCK_MONOTONIC, &t1);
        result_r = fib_rec(n);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        double rec_ns =
            (double)(t2.tv_sec - t1.tv_sec) * 1e9 +
            (double)(t2.tv_nsec - t1.tv_nsec);

        printf("%-4d %-22llu %-22.2f %-22.2f\n",
               n, result_i, iter_ns, rec_ns);
        (void)result_r;
    }
    return 0;
}
