#include "LinkedList.h"

LinkedList* createLinkedList() {
	struct linkedList* r;
	r = (struct linkedList*)malloc(sizeof(struct linkedList));

	r->head = (struct nodeType*)NULL;
	r->size = 0;

	return r;
}

int destroyLinkedList(LinkedList* li) {
	struct nodeType* nptr, * mptr;
	for (nptr = li->head; nptr != NULL; nptr = mptr) {
		mptr = nptr->next;
		free(nptr);
	}

	free(li);

	return 1;
}

int isEmptyLinkedList(LinkedList* li) {
	return (li->size == 0);
}

int sizeLinkedList(LinkedList* li) {
	return li->size;
}

LinkedList* insertFirstLinkedList(LinkedList* li, int item) {
	NodeType* ptr = (NodeType*)malloc(sizeof(NodeType));
	ptr->data = item;

	ptr->next = li->head;
	li->head = ptr;
	li->size++;

	return li;
}

LinkedList* insertLastLinkedList(LinkedList* li, int item) {
	NodeType* nPtr = (NodeType*)malloc(sizeof(NodeType));
	nPtr->data = item;
	nPtr->next = NULL;

	if (li->head == NULL) {
		li->head = nPtr;
	}
	else {
		NodeType* ptr = li->head;

		while (ptr->next != NULL) {
			ptr = ptr->next;
		}

		ptr->next = nPtr;
	}

	li->size++;

	return li;
}

LinkedList* insertItemLinkedList(LinkedList* li, NodeType* pre, int item) {
	NodeType* nPtr = (NodeType*)malloc(sizeof(NodeType));
	nPtr->data = item;

	if (pre != NULL) {
		nPtr->next = pre->next;
		pre->next = nPtr;
	}
	else {
		nPtr->next = li->head;
		li->head = nPtr;
	}

	li->size++;

	return li;
}

LinkedList* insertAtLinkedList(LinkedList* li, int at, int item) {
	if (at < 0 || at > li->size) {
		return li;
	}

	if (at == 0) {
		insertFirstLinkedList(li, item);
		return li;
	}

	NodeType* nPtr = li->head;
	for (int i = 0; i < at - 1; i++) {
		nPtr = nPtr->next;
	}

	insertItemLinkedList(li, nPtr, item);

	return li;
}

int deleteFirstLinkedList(LinkedList* li) {
	if (li->size != 0) {
		NodeType* tPtr = li->head;
		li->head = tPtr->next;

		int temp = tPtr->data;
		free(tPtr);

		li->size--;
		return temp;
	}
	else {
		return 0;
	}
}

int deleteLastLinkedList(LinkedList* li) {
	NodeType* pre;
	NodeType* iPtr;

	pre = li->head;

	if (pre == NULL) {
		return 0;
	}

	iPtr = pre->next;

	if (iPtr == NULL) {
		li->head = NULL;

		int temp = pre->data;

		free(pre);
		li->size--;

		return temp;
	}
	else {
		while (iPtr->next != NULL) {
			pre = iPtr;
			iPtr = iPtr->next;
		}

		int temp = iPtr->data;

		pre->next = NULL;
		free(iPtr);
		li->size--;

		return temp;
	}
}

int deleteAtLinkedList(LinkedList* li, int at) {
	if (at >= 0 && at < li->size) {
		int data;

		if (at == 0) {
			NodeType* fPtr = li->head;
			data = fPtr->data;
			li->head = fPtr->next;
			free(fPtr);
		}
		else {
			NodeType* nPtr = li->head;

			for (int i = 0; i < at - 1; i++) {
				nPtr = nPtr->next;
			}

			NodeType* fPtr = nPtr->next;
			data = fPtr->data;
			nPtr->next = fPtr->next;
			free(fPtr);
		}

		li->size--;
		return data;
	}

	return 0;
}

int deleteItemLinkedList(LinkedList* li, int item) {
	NodeType* pre = NULL;
	NodeType* ptr = li->head;

	while (ptr != NULL && ptr->data != item) {
		pre = ptr;
		ptr = ptr->next;
	}

	if (ptr == NULL) {
		return 0;
	}

	if (pre == NULL) {
		li->head = ptr->next;
	}
	else {
		pre->next = ptr->next;
	}

	int data = ptr->data;
	free(ptr);
	li->size--;

	return data;
}

int getItemLinkedList(LinkedList* li, int pos) {
	if (pos < 0 || pos >= li->size) {
		return 0;
	}

	NodeType* ptr = li->head;
	for (int i = 0; i < pos; i++) {
		ptr = ptr->next;
	}

	return ptr->data;
}

int replaceItemLinkedList(LinkedList* li, int pos, int item) {
	if (pos < 0 || pos >= li->size) {
		return 0;
	}

	NodeType* ptr = li->head;
	for (int i = 0; i < pos; i++) {
		ptr = ptr->next;
	}

	ptr->data = item;

	return 1;
}

int nextItemLinkedList(LinkedList* li, NodeType* pre) {
	if (pre == NULL || pre->next == NULL) {
		return 0;
	}

	return pre->next->data;
}

int printLinkedList(LinkedList* li) {
	NodeType* current = li->head;
	printf("LinkedList:\n");
	printf("LinkedList size: %d\n", li->size);

	for (int i = 0; i < li->size; i++) {
		printf("[%d] data: %d\n", i, current->data);

		current = current->next;
	}

	return 1;
}
