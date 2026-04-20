/*
 * arrayList.c
 * 과제(10) - 양의 정수 전용 순차리스트
 *
 * ────────────────────────────────────────────────────────
 * [과제(9) 버그 수정 내역 유지]
 *
 * 1. insertArrayList() - 루프 범위 오류 (버퍼 오버플로우)
 *    - 수정 전: for (int i = al->size; i >= pos; i--)
 *    - 수정 후: for (int i = al->size - 1; i >= pos; i--)
 *    - 이유: i = al->size에서 시작하면 포화 직전(size == capacity-1)일 때
 *            data[capacity] 는 할당 범위 밖이므로 버퍼 오버플로우 발생
 *
 * 2. initArrayList() - 반환값 누락 (미정의 동작, UB)
 *    - 수정 전: 반환형이 int인데 return 문 없음
 *    - 수정 후: return 1; 추가
 *
 * 3. insertArrayList() - realloc으로 포화 상태 해결
 *    - 포화(size == capacity)일 때 capacity를 2배로 확장
 *    - realloc 실패 시 0 반환
 *
 * ────────────────────────────────────────────────────────
 * [과제(10) 추가·변경 사항]
 *
 * 4. isPositiveInt() 추가
 *    - item <= 0 이면 0 반환 → insert/replace 에서 양의 정수만 허용
 *
 * 5. insertArrayList() / replaceItemArrayList() - 양의 정수 검사 추가
 *    - isPositiveInt() 실패 시 즉시 0 반환
 *
 * 6. printArrayList() - 위치(인덱스)와 값을 함께 출력하도록 변경
 *    - 형식: [위치] 값
 *
 * 7. clearArrayList() 추가
 *    - initArrayList() 를 호출하는 래퍼 함수
 *    - 메뉴 5번 "모든 값 삭제" 전용
 * ────────────────────────────────────────────────────────
 */

#include <stdio.h>
#include <stdlib.h>

#include "arrayList.h"

/* ──────────────────────────── 생성 / 소멸 ──────────────────────────── */

arrayList* createArrayList(int size) {
    arrayList* al = (arrayList*)malloc(sizeof(arrayList));
    if (al == NULL) return NULL;

    al->data = (elementArrayList*)malloc(sizeof(elementArrayList) * size);
    if (al->data == NULL) {
        free(al);
        return NULL;
    }

    al->size     = 0;
    al->capacity = size;
    return al;
}

void destroyArrayList(arrayList* al) {
    if (al == NULL) return;
    free(al->data);
    free(al);
}

/* ──────────────────────────── 상태 조회 ────────────────────────────── */

int isEmptyArrayList(arrayList* al) {
    return (al->size == 0) ? 1 : 0;
}

int isFullArrayList(arrayList* al) {
    return (al->size == al->capacity) ? 1 : 0;
}

int sizeArrayList(arrayList* al) {
    return al->size;
}

/* ──────────────────────────── 유효성 검사 ──────────────────────────── */

/*
 * isPositiveInt()
 * 양의 정수(1 이상)인지 확인한다.
 * 반환: 양의 정수면 1, 아니면 0
 */
int isPositiveInt(elementArrayList item) {
    return (item > 0) ? 1 : 0;
}

/* ──────────────────────────── 핵심 연산 ────────────────────────────── */

/*
 * insertArrayList()
 * pos 위치에 item 을 삽입한다.
 * - item 이 양의 정수가 아니면 0 반환 (과제(10) 추가)
 * - 포화 시 capacity 2배 realloc
 * 반환: 성공 1, 실패 0
 */
int insertArrayList(arrayList* al, int pos, elementArrayList item) {
    /* 양의 정수 검사 (과제(10)) */
    if (!isPositiveInt(item)) {
        printf("  [오류] 양의 정수만 삽입할 수 있습니다. (입력값: %d)\n", item);
        return 0;
    }

    /* 위치 유효성 검사 */
    if (pos < 0 || pos > al->size) {
        printf("  [오류] 유효하지 않은 위치입니다. (입력위치: %d, 허용범위: 0~%d)\n",
               pos, al->size);
        return 0;
    }

    /* 포화 시 동적 확장 */
    if (isFullArrayList(al)) {
        int newCapacity = al->capacity * 2;
        elementArrayList* newData = (elementArrayList*)realloc(
            al->data, sizeof(elementArrayList) * newCapacity);
        if (newData == NULL) {
            printf("  [오류] 메모리 재할당 실패\n");
            return 0;
        }
        al->data     = newData;
        al->capacity = newCapacity;
    }

    /* 삽입 위치 뒤의 데이터를 한 칸씩 뒤로 이동 */
    for (int i = al->size - 1; i >= pos; i--) {
        al->data[i + 1] = al->data[i];
    }

    al->data[pos] = item;
    al->size++;
    return 1;
}

/*
 * deleteArrayList()
 * pos 위치의 항목을 삭제하고 반환한다.
 * 반환: 삭제된 값, 실패 시 -1
 */
elementArrayList deleteArrayList(arrayList* al, int pos) {
    if (pos < 0 || pos > al->size - 1) {
        printf("  [오류] 유효하지 않은 위치입니다. (입력위치: %d, 허용범위: 0~%d)\n",
               pos, al->size - 1);
        return -1;   /* 양의 정수 리스트이므로 -1 은 오류 구분 가능 */
    }

    elementArrayList item = al->data[pos];

    for (int i = pos; i < al->size - 1; i++) {
        al->data[i] = al->data[i + 1];
    }

    al->size--;
    return item;
}

/*
 * replaceItemArrayList()
 * pos 위치의 값을 item 으로 교체한다.
 * - item 이 양의 정수가 아니면 0 반환 (과제(10) 추가)
 * 반환: 성공 1, 실패 0
 */
int replaceItemArrayList(arrayList* al, int pos, elementArrayList item) {
    /* 양의 정수 검사 (과제(10)) */
    if (!isPositiveInt(item)) {
        printf("  [오류] 양의 정수만 입력할 수 있습니다. (입력값: %d)\n", item);
        return 0;
    }

    if (pos < 0 || pos > al->size - 1) {
        printf("  [오류] 유효하지 않은 위치입니다. (입력위치: %d, 허용범위: 0~%d)\n",
               pos, al->size - 1);
        return 0;
    }

    al->data[pos] = item;
    return 1;
}

/*
 * getItemArrayList()
 * pos 위치의 값을 반환한다.
 */
elementArrayList getItemArrayList(arrayList* al, int pos) {
    return al->data[pos];
}

/* ──────────────────────────── 초기화 ───────────────────────────────── */

/*
 * initArrayList()
 * 리스트의 모든 항목을 삭제한다. (과제(9) 호환 유지)
 * 반환: 항상 1
 */
int initArrayList(arrayList* al) {
    for (int i = al->size - 1; i >= 0; i--) {
        deleteArrayList(al, i);
    }
    return 1;
}

/*
 * clearArrayList()
 * 메뉴 5번 전용: initArrayList() 의 래퍼 함수
 * 반환: 항상 1
 */
int clearArrayList(arrayList* al) {
    return initArrayList(al);
}

/* ──────────────────────────── 출력 ─────────────────────────────────── */

/*
 * printArrayList()
 * 리스트를 위치(인덱스)와 함께 출력한다. (과제(10) 변경)
 * 형식 예시:
 *   크기: 3 / 용량: 8
 *   [0] 10
 *   [1] 20
 *   [2] 30
 */
void printArrayList(arrayList* al) {
    printf("  크기: %d / 용량: %d\n", al->size, al->capacity);

    if (isEmptyArrayList(al)) {
        printf("  (리스트가 비어 있습니다)\n");
        return;
    }

    for (int i = 0; i < al->size; i++) {
        printf("  [%d] %d\n", i, al->data[i]);
    }
}
