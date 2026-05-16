#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node* prev;
	struct node* next;
} Node;

typedef struct dLinkedList {
	Node head;
	int size;
} DLinkedList;

extern DLinkedList* createDLinkedList();
extern void destroyDLinkedList(DLinkedList* dl);

extern int isEmptyDLinkedList(DLinkedList* dl);
extern int sizeDLinkedList(DLinkedList* dl);

extern void insertFirstDLinkedList(DLinkedList* dl, int item);
extern void insertLastDLinkedList(DLinkedList* dl, int item);
extern void insertItemDLinkedList(DLinkedList* dl, Node* pre, int item);
extern void insertAtDLinkedList(DLinkedList* dl, int idx, int item);

extern int deleteFirstDLinkedList(DLinkedList* dl);
extern int deleteLastDLinkedList(DLinkedList* dl);
extern int deleteItemDLinkedList(DLinkedList* dl, int item);
extern int deleteAtDLinkedList(DLinkedList* dl, int idx);

extern int getItemDLinkedList(DLinkedList* dl, int pos);
extern void replaceItemDLinkedList(DLinkedList* dl, int pos, int item);
extern int nextItemDLinkedList(DLinkedList* dl, Node* pre);

extern void printDLinkedList(DLinkedList* dl);
