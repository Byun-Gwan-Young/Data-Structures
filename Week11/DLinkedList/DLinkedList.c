#include "DLinkedList.h"

DLinkedList* createDLinkedList() {
	DLinkedList* temp;
	temp = (DLinkedList*)malloc(sizeof(DLinkedList));
	temp->head.prev = &(temp->head);
	temp->head.next = &(temp->head);
	temp->size = 0;

	return temp;
}

void destroyDLinkedList(DLinkedList* dl) {
	while (dl->size != 0) {
		deleteFirstDLinkedList(dl);
	}

	free(dl);
}

void insertFirstDLinkedList(DLinkedList* dl, int item) {
	Node* nPtr = (Node*)malloc(sizeof(Node));
	nPtr->data = item;

	nPtr->prev = &(dl->head);
	nPtr->next = dl->head.next;
	dl->head.next = nPtr;
	nPtr->next->prev = nPtr;

	dl->size++;
}

void insertLastDLinkedList(DLinkedList* dl, int item) {
	Node* nPtr = (Node*)malloc(sizeof(Node));
	nPtr->data = item;

	nPtr->prev = dl->head.prev;
	nPtr->next = &(dl->head);
	nPtr->prev->next = nPtr;
	nPtr->next->prev = nPtr;

	dl->size++;
}

void insertItemDLinkedList(DLinkedList* dl, Node* pre, int item) {
	if (pre == NULL) {
		printf("잘못된 위치입니다.\n");
		return;
	}

	Node* nPtr = (Node*)malloc(sizeof(Node));
	nPtr->data = item;

	nPtr->prev = pre;
	nPtr->next = pre->next;
	pre->next->prev = nPtr;
	pre->next = nPtr;

	dl->size++;
}

void insertAtDLinkedList(DLinkedList* dl, int idx, int item) {
	if (idx < 0 || idx > dl->size) {
		printf("잘못된 위치입니다.\n");
		return;
	}

	if (idx == 0) {
		insertFirstDLinkedList(dl, item);
		return;
	}
	if (idx == dl->size) {
		insertLastDLinkedList(dl, item);
		return;
	}

	Node* cur = dl->head.next;
	for (int i = 0; i < idx; i++) {
		cur = cur->next;
	}

	Node* nPtr = (Node*)malloc(sizeof(Node));
	nPtr->data = item;

	nPtr->prev = cur->prev;
	nPtr->next = cur;
	cur->prev->next = nPtr;
	cur->prev = nPtr;

	dl->size++;
}

int deleteFirstDLinkedList(DLinkedList* dl) {
	if (dl->size == 0) {
		printf("리스트가 비어있습니다.\n");
		return -1;
	}

	Node* temp = dl->head.next;
	int data = temp->data;

	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;

	dl->size--;
	free(temp);

	return data;
}

int deleteLastDLinkedList(DLinkedList* dl) {
	if (dl->size == 0) {
		printf("리스트가 비어있습니다.\n");
		return -1;
	}

	Node* temp = dl->head.prev;
	int data = temp->data;

	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;

	dl->size--;
	free(temp);

	return data;
}

int deleteAtDLinkedList(DLinkedList* dl, int idx) {
	if (idx < 0 || idx >= dl->size) {
		printf("잘못된 위치입니다.\n");
		return -1;
	}

	Node* cur = dl->head.next;
	for (int i = 0; i < idx; i++) {
		cur = cur->next;
	}

	int data = cur->data;
	cur->prev->next = cur->next;
	cur->next->prev = cur->prev;

	dl->size--;
	free(cur);

	return data;
}

int deleteItemDLinkedList(DLinkedList* dl, int item) {
	if (dl->size == 0) {
		printf("리스트가 비어있습니다.\n");
		return -1;
	}

	Node* cur = dl->head.next;
	while (cur != &(dl->head)) {
		if (cur->data == item) {
			int data = cur->data;
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			dl->size--;
			free(cur);
			return data;
		}
		cur = cur->next;
	}

	printf("값을 찾을 수 없습니다.\n");
	return -1;
}

int getItemDLinkedList(DLinkedList* dl, int pos) {
	if (pos < 0 || pos >= dl->size) {
		printf("잘못된 위치입니다.\n");
		return -1;
	}

	Node* cur = dl->head.next;
	for (int i = 0; i < pos; i++) {
		cur = cur->next;
	}

	return cur->data;
}

void replaceItemDLinkedList(DLinkedList* dl, int pos, int item) {
	if (pos < 0 || pos >= dl->size) {
		printf("잘못된 위치입니다.\n");
		return;
	}

	Node* cur = dl->head.next;
	for (int i = 0; i < pos; i++) {
		cur = cur->next;
	}

	cur->data = item;
}

int nextItemDLinkedList(DLinkedList* dl, Node* pre) {
	if (pre == NULL || pre->next == &(dl->head)) {
		return -1;
	}
	return pre->next->data;
}

void printDLinkedList(DLinkedList* dl) {
	printf("리스트 출력\n");
	printf("크기: %d\n", dl->size);

	if (dl->size == 0) {
		return;
	}

	Node* start = dl->head.next;

	for (int i = 0; i < dl->size; i++) {
		printf("[%d] %d\n", i, start->data);
		start = start->next;
	}
}

int isEmptyDLinkedList(DLinkedList* dl) {
	if (dl->size == 0) {
		return 1;
	}
	return 0;
}

int sizeDLinkedList(DLinkedList* dl) {
	return dl->size;
}
