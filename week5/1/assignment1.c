#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int N;
    printf("배열 크기 N을 입력하세요: ");
    scanf("%d", &N);

    // 동적 할당
    int *arr = (int *)malloc(sizeof(int) * N);
    if (arr == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        return 1;
    }

    // 0~N 사이의 임의의 수로 배열 채우기 (포인터 기법 사용)
    srand((unsigned int)time(NULL));
    for (int i = 0; i < N; i++) {
        *(arr + i) = rand() % (N + 1);  // 0 이상 N 이하
    }

    // 처음부터 끝까지 출력
    printf("\n[처음 → 끝]\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", *(arr + i));
    }
    printf("\n");

    // 뒤에서부터 처음까지 출력
    printf("\n[끝 → 처음]\n");
    for (int i = N - 1; i >= 0; i--) {
        printf("%d ", *(arr + i));
    }
    printf("\n");

    // 총합, 최대값, 최소값 계산
    int sum = 0;
    int max = *(arr + 0);
    int min = *(arr + 0);

    for (int i = 0; i < N; i++) {
        sum += *(arr + i);
        if (*(arr + i) > max) max = *(arr + i);
        if (*(arr + i) < min) min = *(arr + i);
    }

    printf("\n[통계]\n");
    printf("총합   : %d\n", sum);
    printf("최대값 : %d\n", max);
    printf("최소값 : %d\n", min);

    free(arr);
    return 0;
}
