/*
 * [기존 과제 + 추가적인 오류 수정 내용]
 *
 * 1. insertArrayList() - 루프 범위 오류 (버퍼 오버플로우)
 *    - 수정 전: for (int i = al->size; i >= pos; i--)
 *    - 수정 후: for (int i = al->size - 1; i >= pos; i--)
 *    - 이유: i = al->size에서 시작하면 data[al->size + 1]에 쓰게 되는데,
 *            포화 직전(size == capacity - 1)일 때 data[capacity]는
 *            할당 범위 밖이므로 버퍼 오버플로우 발생
 *
 * 2. initArrayList() - 반환값 누락 (미정의 동작, UB)
 *    - 수정 전: 반환형이 int인데 return 문 없음
 *    - 수정 후: return 1; 추가
 *    - 이유: return 문이 없으면 미정의 동작(Undefined Behavior)으로
 *            컴파일러에 따라 예측 불가능한 결과가 발생할 수 있음
 *
 * 3. insertArrayList() - realloc을 이용한 포화 상태 해결 (과제 요구사항)
 *    - 포화 상태(size == capacity)일 때 realloc으로 capacity를 2배로 확장
 *    - realloc 실패(NULL 반환) 시 0을 반환하여 실패 처리
 */

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

	if (isFullArrayList(al)) {
		int newCapacity = al->capacity * 2;
		elementArrayList* newData = (elementArrayList*)realloc(
			al->data, sizeof(elementArrayList) * newCapacity);
		if (newData == NULL) {
			return 0;
		}
		al->data = newData;
		al->capacity = newCapacity;
	}

	for (int i = al->size - 1; i >= pos; i--) {
		al->data[i + 1] = al->data[i];
	}

	al->data[pos] = item;
	al->size++;

	return 1;
}

elementArrayList deleteArrayList(
	arrayList* al, int pos) {
	if (pos < 0 || pos > al->size - 1) {
		return 0;
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
	return 1;
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
	printf("순차 리스트: ");

	for (int i = 0; i < al->size; i++) {
		printf("%d ", al->data[i]);
	}
}
