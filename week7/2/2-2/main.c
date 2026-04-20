/*
 * main.c
 * 과제(10)-2 희소행렬 전치 프로그램
 *
 * 1. 10×10 순차리스트 기반 희소행렬 생성
 * 2. 0이 아닌 원소 20개로 초기화
 * 3. 원본 희소행렬 출력 (리스트 형태 + 전체 행렬 형태)
 * 4. 전치행렬 생성 및 데이터 이동 횟수 출력
 * 5. 전치행렬 출력 (리스트 형태 + 전체 행렬 형태)
 */

#include <stdio.h>
#include <stdlib.h>

#include "sparseMatrix.h"

int main(void) {

    /* ── 1. 10×10 희소행렬 생성 ── */
    printf("==============================================\n");
    printf("  10×10 희소행렬 생성 (비영 원소 20개)\n");
    printf("==============================================\n");

    sparseMatrix* sm = createSparseMatrix(10, 10);
    if (sm == NULL) {
        printf("[오류] 희소행렬 생성 실패\n");
        return 1;
    }

    /*
     * ── 2. 비영 원소 20개 초기화 ──
     * 10×10 행렬에 골고루 배치하여 희소행렬 형성
     * addElementSparseMatrix(sm, row, col, value)
     */
    addElementSparseMatrix(sm, 0, 2,  5);
    addElementSparseMatrix(sm, 0, 7,  3);
    addElementSparseMatrix(sm, 1, 4,  8);
    addElementSparseMatrix(sm, 1, 9,  1);
    addElementSparseMatrix(sm, 2, 0,  7);
    addElementSparseMatrix(sm, 2, 6,  4);
    addElementSparseMatrix(sm, 3, 1,  2);
    addElementSparseMatrix(sm, 3, 5, 11);
    addElementSparseMatrix(sm, 4, 3,  6);
    addElementSparseMatrix(sm, 4, 8,  9);
    addElementSparseMatrix(sm, 5, 2, 13);
    addElementSparseMatrix(sm, 5, 7, 15);
    addElementSparseMatrix(sm, 6, 0, 12);
    addElementSparseMatrix(sm, 6, 4,  3);
    addElementSparseMatrix(sm, 7, 1,  7);
    addElementSparseMatrix(sm, 7, 9,  5);
    addElementSparseMatrix(sm, 8, 3, 10);
    addElementSparseMatrix(sm, 8, 6,  2);
    addElementSparseMatrix(sm, 9, 5,  8);
    addElementSparseMatrix(sm, 9, 8, 14);

    /* ── 3. 원본 희소행렬 출력 ── */
    printf("\n▶ 원본 희소행렬 (리스트 형태)\n");
    printSparseMatrix(sm);

    printf("\n▶ 원본 희소행렬 (행렬 형태)\n");
    printSparseMatrixFull(sm);

    /* ── 4. 전치행렬 생성 ── */
    printf("\n==============================================\n");
    printf("  전치행렬 생성\n");
    printf("==============================================\n");

    int moveCount = 0;
    sparseMatrix* smT = transposeSparseMatrix(sm, &moveCount);

    printf("  → 데이터 이동 횟수: %d\n", moveCount);

    /* ── 5. 전치행렬 출력 ── */
    printf("\n▶ 전치행렬 (리스트 형태)\n");
    printSparseMatrix(smT);

    printf("\n▶ 전치행렬 (행렬 형태)\n");
    printSparseMatrixFull(smT);

    /* ── 메모리 해제 ── */
    destroySparseMatrix(sm);
    destroySparseMatrix(smT);

    return 0;
}
