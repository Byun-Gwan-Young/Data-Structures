#include <stdio.h>
#include <stdlib.h>

#include "arrayList.h"

arrayList* createArrayList(int size) {
	arrayList* al;
	al = (arrayList*)malloc(sizeof(arrayList));

	al->data = (elementArrayList*)malloc(
		sizeof(elementArrayList) * size);
	al->size = 0;
	al->capacity = size;

	return al;
}

void destroyArrayList(arrayList* al) {
	free(al->data);
	free(al);
}

int isEmptyArrayList(arrayList* al) {
	if (al->size == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

int isFullArrayList(arrayList* al) {
	if (al->size == al->capacity) {
		return 1;
	}
	else {
		return 0;
	}
}

int sizeArrayList(arrayList* al) {
	return al->size;
}

int insertArrayList(arrayList* al,
	int pos, elementArrayList item) {
	if (pos < 0 || pos > al->size) {
		return 0;
	}

	// [수정] 꽉 찼을 때 삽입 방지
	if (isFullArrayList(al)) {
		return 0;
	}

	// [수정] i = al->size - 1 에서 시작 (기존 al->size 는 out-of-bounds)
	for (int i = al->size - 1; i >= pos; i--) {
		al->data[i + 1] = al->data[i];
	}

	al->data[pos] = item;
	al->size++;

	return 1;
}

elementArrayList deleteArrayList(
	arrayList* al, int pos) {
	// [수정] 빈 블록 → 빈 element 반환으로 처리
	if (pos < 0 || pos > al->size - 1) {
		elementArrayList empty = {0, 0, 0};
		return empty;
	}

	elementArrayList item = al->data[pos];

	for (int i = pos; i < al->size - 1; i++) {
		al->data[i] = al->data[i + 1];
	}

	al->size--;

	return item;
}

int initArrayList(arrayList* al) {
	for (int i = al->size - 1; i >= 0; i--) {
		deleteArrayList(al, i);
	}
	return 1; // [수정] return 문 추가
}

elementArrayList getItemArrayList(
	arrayList* al, int pos) {
	return al->data[pos];
}

int replaceItemArrayList(arrayList* al,
	int pos, elementArrayList item) {
	if (pos < 0 || pos > al->size - 1) {
		return 0;
	}

	al->data[pos] = item;

	return 1;
}

void printArrayList(arrayList* al) {
	printf("현재 배열 리스트: ");

	printf("Cap: %d, size: %d\n", al->capacity, al->size);

	for (int i = 0; i < al->size; i++) {
		printf("(%d %d %d) ", al->data[i].row,
			al->data[i].col, al->data[i].value);
	}
	printf("\n");
}
