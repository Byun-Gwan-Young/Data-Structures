#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

int main(void) {
    int arr[N];

    srand((unsigned int)time(NULL));

    /* 배열을 N 이하의 임의의 수로 채우기 */
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % N + 1;  /* 1 ~ N */
    }

    /* 처음부터 끝까지 출력 */
    printf("=== 처음 -> 끝 ===\n");
    for (int i = 0; i < N; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    /* 끝에서 처음까지 출력 */
    printf("\n=== 끝 -> 처음 ===\n");
    for (int i = N - 1; i >= 0; i--) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    /* 총합, 최대값, 최소값 */
    int sum = 0;
    int max = arr[0];
    int min = arr[0];

    for (int i = 0; i < N; i++) {
        sum += arr[i];
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }

    printf("\n=== 통계 ===\n");
    printf("총합  : %d\n", sum);
    printf("최대값: %d\n", max);
    printf("최소값: %d\n", min);

    return 0;
}
