#include <stdio.h>
#include <stdlib.h>

#include "DLinkedList.h"

int main() {
	DLinkedList* myList = createDLinkedList();
	int menu, value, idx;

	while (1) {
		printf("\n===== 메뉴 =====\n");
		printf("1. 맨 앞에 추가\n");
		printf("2. 맨 뒤에 추가\n");
		printf("3. 특정 위치에 추가\n");
		printf("4. 특정 위치 삭제\n");
		printf("5. 전체 목록 출력\n");
		printf("6. 리스트 크기 확인\n");
		printf("0. 종료\n");
		printf("선택: ");
		scanf("%d", &menu);

		if (menu == 0) {
			destroyDLinkedList(myList);
			printf("프로그램을 종료합니다.\n");
			break;
		}
		else if (menu == 1) {
			printf("정수 입력: ");
			scanf("%d", &value);
			insertFirstDLinkedList(myList, value);
		}
		else if (menu == 2) {
			printf("정수 입력: ");
			scanf("%d", &value);
			insertLastDLinkedList(myList, value);
		}
		else if (menu == 3) {
			printf("위치 입력: ");
			scanf("%d", &idx);
			printf("정수 입력: ");
			scanf("%d", &value);
			insertAtDLinkedList(myList, idx, value);
		}
		else if (menu == 4) {
			printf("위치 입력: ");
			scanf("%d", &idx);
			int deleted = deleteAtDLinkedList(myList, idx);
			if (deleted != -1) {
				printf("삭제된 값: %d\n", deleted);
			}
		}
		else if (menu == 5) {
			printDLinkedList(myList);
		}
		else if (menu == 6) {
			printf("리스트 크기: %d\n", sizeDLinkedList(myList));
		}
		else {
			printf("잘못된 입력입니다.\n");
		}
	}

	return 0;
}
