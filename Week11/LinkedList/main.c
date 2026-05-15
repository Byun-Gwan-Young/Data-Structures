#include "LinkedList.h"

void printMenu() {
	printf("\n========== 연결리스트 메뉴 ==========\n");
	printf("1. 맨 앞에 추가\n");
	printf("2. 맨 뒤에 추가\n");
	printf("3. 특정 위치에 추가\n");
	printf("4. 특정 위치 삭제\n");
	printf("5. 전체 목록 출력\n");
	printf("6. 리스트 크기 확인\n");
	printf("0. 종료\n");
	printf("=====================================\n");
	printf("선택: ");
}

int main() {
	LinkedList* myList = createLinkedList();
	int choice, item, pos;

	while (1) {
		printMenu();
		scanf("%d", &choice);

		if (choice == 0) {
			destroyLinkedList(myList);
			printf("프로그램을 종료합니다.\n");
			break;
		}
		else if (choice == 1) {
			printf("추가할 정수 입력: ");
			scanf("%d", &item);
			insertFirstLinkedList(myList, item);
			printf("맨 앞에 %d 추가 완료\n", item);
		}
		else if (choice == 2) {
			printf("추가할 정수 입력: ");
			scanf("%d", &item);
			insertLastLinkedList(myList, item);
			printf("맨 뒤에 %d 추가 완료\n", item);
		}
		else if (choice == 3) {
			printf("추가할 위치 입력(0 ~ %d): ", sizeLinkedList(myList));
			scanf("%d", &pos);

			if (pos < 0 || pos > sizeLinkedList(myList)) {
				printf("잘못된 위치입니다.\n");
				continue;
			}

			printf("추가할 정수 입력: ");
			scanf("%d", &item);
			insertAtLinkedList(myList, pos, item);
			printf("위치 %d에 %d 추가 완료\n", pos, item);
		}
		else if (choice == 4) {
			if (isEmptyLinkedList(myList) == 1) {
				printf("리스트가 비어있습니다.\n");
				continue;
			}

			printf("삭제할 위치 입력(0 ~ %d): ", sizeLinkedList(myList) - 1);
			scanf("%d", &pos);

			if (pos < 0 || pos >= sizeLinkedList(myList)) {
				printf("잘못된 위치입니다.\n");
				continue;
			}

			int data = deleteAtLinkedList(myList, pos);
			printf("위치 %d 삭제 완료, 값: %d\n", pos, data);
		}
		else if (choice == 5) {
			printLinkedList(myList);
		}
		else if (choice == 6) {
			printf("리스트 크기: %d\n", sizeLinkedList(myList));
		}
		else {
			printf("잘못된 메뉴입니다.\n");
		}
	}

	return 0;
}
