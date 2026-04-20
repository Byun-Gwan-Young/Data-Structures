/*
 * arrayList.h
 * 과제(10) - 양의 정수 전용 순차리스트
 *
 * [과제(9) 대비 변경 사항]
 * 1. 양의 정수 유효성 검사 함수 isPositiveInt() 추가
 * 2. printArrayList() → 위치(인덱스)와 함께 출력하도록 개선
 * 3. clearArrayList() 추가 (모든 항목 삭제)
 */

#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef int elementArrayList;

typedef struct arrayListType {
    elementArrayList* data;
    int size;
    int capacity;
} arrayList;

/* 생성 / 소멸 */
extern arrayList* createArrayList(int size);
extern void       destroyArrayList(arrayList* al);

/* 상태 조회 */
extern int isEmptyArrayList(arrayList* al);
extern int isFullArrayList(arrayList* al);
extern int sizeArrayList(arrayList* al);

/* 유효성 검사 */
extern int isPositiveInt(elementArrayList item); /* 양의 정수 여부 */

/* 핵심 연산 */
extern int             insertArrayList(arrayList* al, int pos, elementArrayList item);
extern elementArrayList deleteArrayList(arrayList* al, int pos);
extern int             replaceItemArrayList(arrayList* al, int pos, elementArrayList item);
extern elementArrayList getItemArrayList(arrayList* al, int pos);

/* 초기화 */
extern int initArrayList(arrayList* al);   /* 과제(9) 호환 유지 */
extern int clearArrayList(arrayList* al);  /* 메뉴 5번 전용 (initArrayList 래퍼) */

/* 출력 */
extern void printArrayList(arrayList* al); /* 위치 + 값 함께 출력 */

#endif /* ARRAY_LIST_H */
