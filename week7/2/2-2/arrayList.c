/*
 * arrayList.c
 * 과제(10)-2 희소행렬용 순차리스트 구현
 *
 * ────────────────────────────────────────────────────────
 * [버그 수정 내역]
 *
 * 1. insertArrayList() - 루프 범위 오류 (버퍼 오버플로우)
 *    - 수정 전: for (int i = al->size; i >= pos; i--)
 *    - 수정 후: for (int i = al->size - 1; i >= pos; i--)
 *    - 이유: i = al->size 에서 data[al->size+1] 에 쓰게 되어
 *            포화 직전일 때 할당 범위 밖 접근 발생
 *
 * 2. insertArrayList() - 포화 상태 처리 누락
 *    - 수정 전: 포화 상태에서도 삽입 시도 → 버퍼 오버플로우
 *    - 수정 후: realloc 으로 capacity 2배 확장
 *
 * 3. initArrayList() - 반환값 누락 (미정의 동작, UB)
 *    - 수정 전: return 문 없음
 *    - 수정 후: return 1; 추가
 *
 * 4. deleteArrayList() - 오류 처리 블록 비어 있음
 *    - 수정 전: if (pos < 0 || ...) { } ← 빈 블록, 이후 계속 실행
 *    - 수정 후: 빈 elementArrayList 반환으로 명시적 오류 처리
 * ────────────────────────────────────────────────────────
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arrayList.h"

/* ─── 생성 / 소멸 ─── */

arrayList* createArrayList(int capacity) {
    arrayList* al = (arrayList*)malloc(sizeof(arrayList));
    if (al == NULL) return NULL;

    al->data = (elementArrayList*)malloc(sizeof(elementArrayList) * capacity);
    if (al->data == NULL) { free(al); return NULL; }

    al->size     = 0;
    al->capacity = capacity;
    return al;
}

void destroyArrayList(arrayList* al) {
    if (al == NULL) return;
    free(al->data);
    free(al);
}

/* ─── 상태 조회 ─── */

int isEmptyArrayList(arrayList* al) {
    return (al->size == 0) ? 1 : 0;
}

int isFullArrayList(arrayList* al) {
    return (al->size == al->capacity) ? 1 : 0;
}

int sizeArrayList(arrayList* al) {
    return al->size;
}

/* ─── 핵심 연산 ─── */

/*
 * insertArrayList()
 * [수정 1] 루프를 size-1 부터 시작 (버퍼 오버플로우 방지)
 * [수정 2] 포화 시 realloc 으로 capacity 2배 확장
 */
int insertArrayList(arrayList* al, int pos, elementArrayList item) {
    if (pos < 0 || pos > al->size) return 0;

    /* [수정 2] 포화 시 동적 확장 */
    if (isFullArrayList(al)) {
        int newCapacity = al->capacity * 2;
        elementArrayList* newData = (elementArrayList*)realloc(
            al->data, sizeof(elementArrayList) * newCapacity);
        if (newData == NULL) return 0;
        al->data     = newData;
        al->capacity = newCapacity;
    }

    /* [수정 1] i = size-1 부터 시작 */
    for (int i = al->size - 1; i >= pos; i--) {
        al->data[i + 1] = al->data[i];
    }

    al->data[pos] = item;
    al->size++;
    return 1;
}

/*
 * deleteArrayList()
 * [수정 4] 범위 오류 시 빈 구조체 반환 (빈 블록 제거)
 */
elementArrayList deleteArrayList(arrayList* al, int pos) {
    elementArrayList empty = {0, 0, 0};

    if (pos < 0 || pos > al->size - 1) {
        return empty; /* [수정 4] 명시적 오류 반환 */
    }

    elementArrayList item = al->data[pos];

    for (int i = pos; i < al->size - 1; i++) {
        al->data[i] = al->data[i + 1];
    }

    al->size--;
    return item;
}

elementArrayList getItemArrayList(arrayList* al, int pos) {
    return al->data[pos];
}

int replaceItemArrayList(arrayList* al, int pos, elementArrayList item) {
    if (pos < 0 || pos > al->size - 1) return 0;
    al->data[pos] = item;
    return 1;
}

/*
 * initArrayList()
 * [수정 3] return 1; 추가 (UB 방지)
 */
int initArrayList(arrayList* al) {
    for (int i = al->size - 1; i >= 0; i--) {
        deleteArrayList(al, i);
    }
    return 1; /* [수정 3] */
}

/* ─── 출력 ─── */

void printArrayList(arrayList* al) {
    printf("  capacity: %d, size: %d\n", al->capacity, al->size);
    for (int i = 0; i < al->size; i++) {
        printf("  [%d] (row=%d, col=%d, value=%d)\n",
               i,
               al->data[i].row,
               al->data[i].col,
               al->data[i].value);
    }
}
