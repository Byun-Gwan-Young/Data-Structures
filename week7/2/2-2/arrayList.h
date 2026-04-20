/*
 * arrayList.h
 * 과제(10)-2 희소행렬용 순차리스트
 *
 * [과제(9) 대비 변경]
 * - elementArrayList: int → {row, col, value} 구조체
 */

#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdio.h>
#include <stdlib.h>

/* ── 원소 타입: 희소행렬의 비영 원소 한 개 ── */
typedef struct elementArrayListType {
    int row;
    int col;
    int value;
} elementArrayList;

/* ── 순차리스트 ── */
typedef struct arrayListType {
    elementArrayList* data;
    int size;
    int capacity;
} arrayList;

/* 생성 / 소멸 */
extern arrayList*       createArrayList(int capacity);
extern void             destroyArrayList(arrayList* al);

/* 상태 조회 */
extern int              isEmptyArrayList(arrayList* al);
extern int              isFullArrayList(arrayList* al);
extern int              sizeArrayList(arrayList* al);

/* 핵심 연산 */
extern int              insertArrayList(arrayList* al, int pos, elementArrayList item);
extern elementArrayList deleteArrayList(arrayList* al, int pos);
extern int              replaceItemArrayList(arrayList* al, int pos, elementArrayList item);
extern elementArrayList getItemArrayList(arrayList* al, int pos);

/* 초기화 / 출력 */
extern int              initArrayList(arrayList* al);
extern void             printArrayList(arrayList* al);

#endif /* ARRAY_LIST_H */
