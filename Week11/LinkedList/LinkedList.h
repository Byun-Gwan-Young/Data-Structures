#include <stdio.h>
#include <stdlib.h>

typedef struct nodeType {
	int data;
	struct nodeType* next;
} NodeType;

typedef struct linkedList {
	struct nodeType* head;
	int size;
} LinkedList;

extern LinkedList* createLinkedList();
extern int destroyLinkedList(LinkedList* li);
extern int isEmptyLinkedList(LinkedList* li);
extern int sizeLinkedList(LinkedList* li);
extern LinkedList* insertFirstLinkedList(LinkedList* li, int item);
extern LinkedList* insertLastLinkedList(LinkedList* li, int item);
extern LinkedList* insertItemLinkedList(LinkedList* li, NodeType* pre, int item);
extern LinkedList* insertAtLinkedList(LinkedList* li, int at, int item);
extern int deleteFirstLinkedList(LinkedList* li);
extern int deleteLastLinkedList(LinkedList* li);
extern int deleteAtLinkedList(LinkedList* li, int at);
extern int printLinkedList(LinkedList* li);
