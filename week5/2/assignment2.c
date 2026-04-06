#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;

    do {
        printf("홀수 N을 입력하세요: ");
        scanf("%d", &N);
        if (N % 2 == 0 || N < 1)
            printf("홀수만 입력 가능합니다.\n");
    } while (N % 2 == 0 || N < 1);

    /* 2차원 배열 동적 할당 */
    int **magic = (int **)malloc(sizeof(int *) * N);
    for (int i = 0; i < N; i++) {
        *(magic + i) = (int *)malloc(sizeof(int) * N);
        for (int j = 0; j < N; j++)
            *(*(magic + i) + j) = 0;
    }

    /*
     * 홀수 마방진 생성 - Siamese(de la Loubère) 방법
     *  1. 첫 번째 숫자(1)는 첫 행의 가운데 열에 배치
     *  2. 다음 숫자는 오른쪽 위 대각선 방향으로 이동
     *  3. 범위를 벗어나면 반대편으로 wrap-around
     *  4. 이미 채워진 칸이면 현재 위치에서 아래로 한 칸 이동
     */
    int row = 0;
    int col = N / 2;
    for (int num = 1; num <= N * N; num++) {
        *(*(magic + row) + col) = num;
        int next_row = (row - 1 + N) % N;
        int next_col = (col + 1) % N;
        if (*(*(magic + next_row) + next_col) != 0) {
            row = (row + 1) % N;
        } else {
            row = next_row;
            col = next_col;
        }
    }

    int magic_sum = N * (N * N + 1) / 2;
    printf("==============================\n");
    printf("   %d x %d 홀수 마방진\n", N, N);
    printf("==============================\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%4d", *(*(magic + i) + j));
        printf("\n");
    }
    printf("\n기대 합(모든 세트의 정답): %d\n", magic_sum);
    printf("\n==============================\n");
    printf("        합 검증\n");
    printf("==============================\n");

    /* 가로 */
    for (int i = 0; i < N; i++) {
        int sum = 0;
        for (int j = 0; j < N; j++) sum += *(*(magic + i) + j);
        printf("가로 %d행: %d %s\n", i + 1, sum, sum == magic_sum ? "OK" : "FAIL");
    }
    printf("\n");

    /* 세로 */
    for (int j = 0; j < N; j++) {
        int sum = 0;
        for (int i = 0; i < N; i++) sum += *(*(magic + i) + j);
        printf("세로 %d열: %d %s\n", j + 1, sum, sum == magic_sum ? "OK" : "FAIL");
    }
    printf("\n");

    /* 대각선 */
    int diag1 = 0, diag2 = 0;
    for (int i = 0; i < N; i++) {
        diag1 += *(*(magic + i) + i);
        diag2 += *(*(magic + i) + (N - 1 - i));
    }
    printf("대각선(↘): %d %s\n", diag1, diag1 == magic_sum ? "OK" : "FAIL");
    printf("대각선(↙): %d %s\n", diag2, diag2 == magic_sum ? "OK" : "FAIL");
    printf("==============================\n");

    /* 메모리 해제 */
    for (int i = 0; i < N; i++)
        free(*(magic + i));
    free(magic);

    return 0;
}
