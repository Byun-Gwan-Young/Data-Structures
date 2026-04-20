/*
 * main.c
 * 과제(10) - 양의 정수 전용 순차리스트 메뉴 프로그램
 *
 * 메뉴
 *  1. 삽입 (insert)  : 양의 정수 + 위치 입력 → 리스트에 추가
 *  2. 삭제 (delete)  : 위치 입력 → 해당 항목 삭제
 *  3. 변경 (replace) : 양의 정수 + 위치 입력 → 해당 위치 값 변경
 *  4. 출력 (print)   : 위치와 함께 리스트 출력
 *  5. 전체 삭제(clear): 모든 항목 삭제
 *  0. 종료
 */

#include <stdio.h>
#include <stdlib.h>

#include "arrayList.h"

/* 메뉴 출력 */
static void printMenu(void) {
    printf("\n==============================\n");
    printf("  양의 정수 순차리스트 메뉴\n");
    printf("==============================\n");
    printf("  1. 삽입 (insert)\n");
    printf("  2. 삭제 (delete)\n");
    printf("  3. 변경 (replace)\n");
    printf("  4. 출력 (print)\n");
    printf("  5. 전체 삭제 (clear)\n");
    printf("  0. 종료\n");
    printf("------------------------------\n");
    printf("  선택: ");
}

int main(void) {
    /* 초기 용량 4 (realloc 동작 확인 가능) */
    arrayList* al = createArrayList(4);
    if (al == NULL) {
        printf("[오류] 리스트 생성 실패\n");
        return 1;
    }

    int choice;
    int pos, item, result;

    while (1) {
        printMenu();
        if (scanf("%d", &choice) != 1) {
            /* 잘못된 입력 처리 */
            while (getchar() != '\n');
            printf("  [오류] 숫자를 입력하세요.\n");
            continue;
        }

        switch (choice) {
        /* ── 1. 삽입 ── */
        case 1:
            printf("  삽입할 양의 정수: ");
            scanf("%d", &item);
            printf("  삽입할 위치 (0 ~ %d): ", al->size);
            scanf("%d", &pos);

            result = insertArrayList(al, pos, item);
            if (result) {
                printf("  → %d 을(를) 위치 %d 에 삽입했습니다.\n", item, pos);
            }
            break;

        /* ── 2. 삭제 ── */
        case 2:
            if (isEmptyArrayList(al)) {
                printf("  [오류] 리스트가 비어 있습니다.\n");
                break;
            }
            printf("  삭제할 위치 (0 ~ %d): ", al->size - 1);
            scanf("%d", &pos);

            result = deleteArrayList(al, pos);
            if (result != -1) {
                printf("  → 위치 %d 의 값 %d 을(를) 삭제했습니다.\n", pos, result);
            }
            break;

        /* ── 3. 변경 ── */
        case 3:
            if (isEmptyArrayList(al)) {
                printf("  [오류] 리스트가 비어 있습니다.\n");
                break;
            }
            printf("  변경할 위치 (0 ~ %d): ", al->size - 1);
            scanf("%d", &pos);
            printf("  새로운 양의 정수: ");
            scanf("%d", &item);

            result = replaceItemArrayList(al, pos, item);
            if (result) {
                printf("  → 위치 %d 의 값을 %d (으)로 변경했습니다.\n", pos, item);
            }
            break;

        /* ── 4. 출력 ── */
        case 4:
            printf("\n  ── 순차리스트 출력 ──\n");
            printArrayList(al);
            break;

        /* ── 5. 전체 삭제 ── */
        case 5:
            clearArrayList(al);
            printf("  → 리스트의 모든 항목을 삭제했습니다.\n");
            break;

        /* ── 0. 종료 ── */
        case 0:
            printf("  프로그램을 종료합니다.\n");
            destroyArrayList(al);
            return 0;

        default:
            printf("  [오류] 0 ~ 5 사이의 번호를 입력하세요.\n");
            break;
        }
    }
}
