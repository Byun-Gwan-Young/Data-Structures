#include <stdio.h>
#include <stdlib.h>

#include "arrayList.h"

int main() {
	arrayList* myArrayList;
	myArrayList = createArrayList(100);

	if (sizeArrayList(myArrayList) == 0) {
		printf("Create ok\n");
	}

	// Insert test
	insertArrayList(myArrayList, 0, 10); // 최초 삽입
	insertArrayList(myArrayList, 1, 20);
	insertArrayList(myArrayList, 2, 30);
	insertArrayList(myArrayList, 0, 5);

	printArrayList(myArrayList);

	// Delete test
	deleteArrayList(myArrayList, 0);
	deleteArrayList(myArrayList, 1);
	deleteArrayList(myArrayList, 2);

	printArrayList(myArrayList);

	// realloc test: capacity(3)짜리 리스트를 만들어 포화 상태 유발
	printf("\n\n--- realloc test ---\n");
	arrayList* smallList;
	smallList = createArrayList(3);

	printf("초기 capacity: %d\n", smallList->capacity);

	insertArrayList(smallList, 0, 10);
	insertArrayList(smallList, 1, 20);
	insertArrayList(smallList, 2, 30);

	printf("포화 상태 여부: %s\n", isFullArrayList(smallList) ? "Full" : "Not Full");
	printf("4번째 데이터 삽입 시도 (realloc 발생)\n");

	insertArrayList(smallList, 3, 40); // realloc 발생

	printf("realloc 후 capacity: %d\n", smallList->capacity);

	printArrayList(smallList);
	printf("\n");

	destroyArrayList(smallList);
	destroyArrayList(myArrayList);
}
