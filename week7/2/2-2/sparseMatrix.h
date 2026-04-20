/*
 * sparseMatrix.h
 * 과제(10)-2 희소행렬
 *
 * ────────────────────────────────────────────────────────
 * [구조 설계 - 다단계 포인터 (가산점)]
 *
 *   sparseMatrix*         ← 1단계 포인터
 *      ├─ row  (int)
 *      ├─ col  (int)
 *      └─ al   (arrayList*)   ← 2단계 포인터
 *                ├─ size, capacity
 *                └─ data (elementArrayList*)  ← 3단계 포인터
 *                            ├─ row
 *                            ├─ col
 *                            └─ value
 *
 *   접근 예시: sm->al->data[i].value
 *   포인터 3단계로 실제 데이터에 도달
 * ────────────────────────────────────────────────────────
 */

#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <stdio.h>
#include <stdlib.h>

#include "arrayList.h"

/* ── 희소행렬 구조체: arrayList를 포인터로 포함 (다단계 포인터 구조) ── */
typedef struct sparseMatrixType {
    int row;         /* 행렬의 행 수 */
    int col;         /* 행렬의 열 수 */
    arrayList* al;   /* 비영 원소를 저장하는 순차리스트 (포인터) */
} sparseMatrix;

/* 생성 / 소멸 */
extern sparseMatrix* createSparseMatrix(int row, int col);
extern void          destroySparseMatrix(sparseMatrix* sm);

/* 원소 추가 */
extern int           addElementSparseMatrix(sparseMatrix* sm, int row, int col, int value);

/* 출력 */
extern void          printSparseMatrix(sparseMatrix* sm);
extern void          printSparseMatrixFull(sparseMatrix* sm);  /* 전체 행렬 형태로 출력 */

/* 전치행렬 (데이터 이동 횟수 반환) */
extern sparseMatrix* transposeSparseMatrix(sparseMatrix* sm, int* moveCount);

#endif /* SPARSE_MATRIX_H */
