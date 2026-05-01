#include <stdio.h>
#include <stdlib.h>

#include "arrayList.h"

arrayList* createArrayList(int size) {
    arrayList* al;
    al = (arrayList*)malloc(sizeof(arrayList));

    al->data = (elementArrayList*)malloc(sizeof(elementArrayList) * size);
    al->size = 0;
    al->capacity = size;

    return al;
}

void destroyArrayList(arrayList* al) {
    free(al->data);
    free(al);
}

int isEmptyArrayList(arrayList* al) {
    return (al->size == 0) ? 1 : 0;
}

int isFullArrayList(arrayList* al) {
    return (al->size == al->capacity) ? 1 : 0;
}

int sizeArrayList(arrayList* al) {
    return al->size;
}

/*
 * [버그 수정] 기존: i >= pos (마지막 원소가 한 칸 앞으로 덮어쓰기 후 다시 복사되는 문제)
 *           수정: i > pos  (pos 위치부터 뒤로 밀고, pos에 새 항목 삽입)
 */
int insertArrayList(arrayList* al, int pos, elementArrayList item) {
    if (pos < 0 || pos > al->size) {
        return 0;
    }
    if (isFullArrayList(al)) {
        /* capacity 초과 시 2배 확장 */
        int newCap = al->capacity * 2;
        elementArrayList* newData =
            (elementArrayList*)realloc(al->data, sizeof(elementArrayList) * newCap);
        if (!newData) return 0;
        al->data = newData;
        al->capacity = newCap;
    }

    /* [버그 수정] i >= pos → i > pos */
    for (int i = al->size; i > pos; i--) {
        al->data[i] = al->data[i - 1];
    }

    al->data[pos] = item;
    al->size++;

    return 1;
}

elementArrayList deleteArrayList(arrayList* al, int pos) {
    if (pos < 0 || pos > al->size - 1) {
        return (elementArrayList){ 0, 0 };
    }

    elementArrayList item = al->data[pos];

    for (int i = pos; i < al->size - 1; i++) {
        al->data[i] = al->data[i + 1];
    }

    al->size--;

    return item;
}

/* [버그 수정] 반환값(int) 없는 함수에 return 0 추가 */
int initArrayList(arrayList* al) {
    for (int i = al->size - 1; i >= 0; i--) {
        deleteArrayList(al, i);
    }
    return 1;
}

elementArrayList getItemArrayList(arrayList* al, int pos) {
    return al->data[pos];
}

int replaceItemArrayList(arrayList* al, int pos, elementArrayList item) {
    if (pos < 0 || pos > al->size - 1) {
        return 0;
    }

    al->data[pos] = item;

    return 1;
}

void printArrayList(arrayList* al) {
    printf("Array List: ");
    for (int i = 0; i < al->size; i++) {
        printf("(%d %d) ", al->data[i].coef, al->data[i].expo);
    }
    printf("\n");
}
