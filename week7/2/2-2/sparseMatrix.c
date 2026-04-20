/*
 * sparseMatrix.c
 * 과제(10)-2 희소행렬 구현
 *
 * ────────────────────────────────────────────────────────
 * [전치행렬 알고리즘 및 데이터 이동 횟수]
 *
 *  단순 전치 알고리즘:
 *   - 열(col) 0 부터 (maxCol-1) 까지 순서대로,
 *     비영 원소 리스트를 전체 스캔하며 해당 열의 원소를 결과에 삽입
 *   - 이 과정에서 원소가 결과 배열에 복사될 때마다 이동 횟수 +1
 *   - 총 이동 횟수 = 비영 원소 개수 (nnz)
 *     (각 원소는 정확히 한 번 결과 리스트에 복사됨)
 *   - 총 비교 횟수 = maxCol × nnz (참고용으로 함께 출력)
 *
 * [다단계 포인터 접근]
 *   sm            : sparseMatrix*          (1단계)
 *   sm->al        : arrayList*             (2단계)
 *   sm->al->data  : elementArrayList*      (3단계)
 *   sm->al->data[i].value                  (실제 데이터)
 * ────────────────────────────────────────────────────────
 */

#include <stdio.h>
#include <stdlib.h>

#include "sparseMatrix.h"

/* ─── 생성 / 소멸 ─── */

/*
 * createSparseMatrix()
 * sparseMatrix 구조체를 할당하고 내부 arrayList 를 초기화한다.
 * 다단계 포인터: sparseMatrix* → arrayList* → elementArrayList*
 */
sparseMatrix* createSparseMatrix(int row, int col) {
    sparseMatrix* sm = (sparseMatrix*)malloc(sizeof(sparseMatrix));
    if (sm == NULL) return NULL;

    sm->row = row;
    sm->col = col;
    sm->al  = createArrayList(row * col); /* 2단계 포인터 초기화 */

    if (sm->al == NULL) {
        free(sm);
        return NULL;
    }

    return sm;
}

void destroySparseMatrix(sparseMatrix* sm) {
    if (sm == NULL) return;
    destroyArrayList(sm->al); /* 2단계 포인터 해제 */
    free(sm);
}

/* ─── 원소 추가 ─── */

/*
 * addElementSparseMatrix()
 * 비영 원소 (row, col, value) 를 순차리스트 맨 뒤에 추가한다.
 */
int addElementSparseMatrix(sparseMatrix* sm, int row, int col, int value) {
    if (row < 0 || row >= sm->row || col < 0 || col >= sm->col) {
        printf("  [오류] 범위를 벗어난 위치입니다. (row=%d, col=%d)\n", row, col);
        return 0;
    }
    if (value == 0) {
        printf("  [오류] 0은 희소행렬에 저장하지 않습니다.\n");
        return 0;
    }

    elementArrayList elem = {row, col, value};
    /* sm->al->data 까지 3단계 포인터를 통해 삽입 */
    return insertArrayList(sm->al, sizeArrayList(sm->al), elem);
}

/* ─── 출력 ─── */

/*
 * printSparseMatrix()
 * 비영 원소 리스트 형태로 출력: (row, col, value) 나열
 */
void printSparseMatrix(sparseMatrix* sm) {
    printf("  [희소행렬] %d×%d, 비영 원소 수: %d\n",
           sm->row, sm->col, sizeArrayList(sm->al));
    printf("  %-5s %-5s %-8s\n", "row", "col", "value");
    printf("  -----------------\n");

    /* sm->al->data[i] : 3단계 포인터 접근 */
    for (int i = 0; i < sizeArrayList(sm->al); i++) {
        elementArrayList e = getItemArrayList(sm->al, i);
        printf("  %-5d %-5d %-8d\n", e.row, e.col, e.value);
    }
}

/*
 * printSparseMatrixFull()
 * 전체 행렬 형태(격자)로 출력
 */
void printSparseMatrixFull(sparseMatrix* sm) {
    /* 임시 2차원 배열에 비영 원소 배치 */
    int** grid = (int**)calloc(sm->row, sizeof(int*));
    for (int i = 0; i < sm->row; i++) {
        grid[i] = (int*)calloc(sm->col, sizeof(int));
    }

    for (int k = 0; k < sizeArrayList(sm->al); k++) {
        elementArrayList e = getItemArrayList(sm->al, k);
        grid[e.row][e.col] = e.value;
    }

    printf("  [전체 행렬] %d×%d\n", sm->row, sm->col);
    for (int i = 0; i < sm->row; i++) {
        printf("  ");
        for (int j = 0; j < sm->col; j++) {
            printf("%4d", grid[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < sm->row; i++) free(grid[i]);
    free(grid);
}

/* ─── 전치행렬 ─── */

/*
 * transposeSparseMatrix()
 *
 * [단순 전치 알고리즘]
 *  열(col) 0 ~ (sm->col - 1) 순서로 비영 원소 리스트를 반복 스캔.
 *  해당 열의 원소를 발견하면 row↔col 을 교환하여 결과 리스트에 삽입.
 *
 * [데이터 이동 횟수]
 *  원소가 결과 리스트에 복사(삽입)될 때마다 moveCount 를 1 증가.
 *  최종 moveCount == 비영 원소 개수(nnz).
 *  (비교 횟수 = sm->col × nnz, 이동 횟수와 별도로 출력)
 *
 * 반환: 전치행렬 sparseMatrix* (호출자가 destroySparseMatrix 로 해제)
 *       moveCount: 데이터 이동 횟수를 기록하는 포인터
 */
sparseMatrix* transposeSparseMatrix(sparseMatrix* sm, int* moveCount) {
    /* 전치행렬: row↔col 교환 */
    sparseMatrix* result = createSparseMatrix(sm->col, sm->row);
    if (result == NULL) return NULL;

    int nnz       = sizeArrayList(sm->al);
    int compareCount = 0;
    *moveCount    = 0;

    /*
     * 열(col) 순서로 스캔하여 전치행렬의 행(row) 순서를 맞춤.
     * 이렇게 하면 별도 정렬 없이 결과가 행 우선 순서(row-major)로 저장됨.
     */
    for (int c = 0; c < sm->col; c++) {
        for (int k = 0; k < nnz; k++) {
            /* sm->al->data[k] : 3단계 포인터 접근 */
            elementArrayList e = getItemArrayList(sm->al, k);
            compareCount++;

            if (e.col == c) {
                /* row ↔ col 교환하여 삽입 */
                elementArrayList transposed = {e.col, e.row, e.value};
                insertArrayList(result->al,
                                sizeArrayList(result->al),
                                transposed);
                (*moveCount)++; /* 데이터 이동 1회 */
            }
        }
    }

    printf("  [전치 완료] 비교 횟수: %d, 데이터 이동 횟수: %d\n",
           compareCount, *moveCount);

    return result;
}
