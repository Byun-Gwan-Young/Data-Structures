#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "polynomial.h"

polynomial* createPolynomial(int capacity) {
    polynomial* po = (polynomial*)createArrayList(capacity);
    return po;
}

/*
 * 내림차순(expo 큰 것이 앞)으로 정렬 삽입.
 * [버그 수정] 기존: expo <= item.expo → 올바른 내림차순 삽입 위치를 못 찾는 문제
 *           수정: expo < item.expo  (같은 지수는 계수 합산, 큰 지수가 앞에 오도록)
 */
polynomial* addItemPolynomial(polynomial* po, elementType item) {
    int n = sizeArrayList(po);
    int i;

    /* 삽입 위치 탐색: 지수 내림차순 유지 */
    for (i = 0; i < n; i++) {
        if (po->data[i].expo == item.expo) {
            /* 같은 지수 발견 → 계수 합산 */
            po->data[i].coef += item.coef;
            if (po->data[i].coef == 0) {
                deleteArrayList(po, i);
            }
            return po;
        }
        if (po->data[i].expo < item.expo) {
            /* 현재 항보다 지수가 크므로 앞에 삽입 */
            break;
        }
    }
    /* 삽입 위치 i (맨 뒤 포함) */
    insertArrayList(po, i, item);
    return po;
}

/*
 * 다항식 덧셈.
 * [버그 수정] 기존: while 루프 종료 후 남은 항 처리 누락
 *           수정: 두 개의 while 루프로 나머지 항 모두 처리
 */
polynomial* addPolynomial(polynomial* p1, polynomial* p2) {
    polynomial* r = createPolynomial(sizeArrayList(p1) + sizeArrayList(p2));

    int i = 0, j = 0;

    while (i < sizeArrayList(p1) && j < sizeArrayList(p2)) {
        if (p1->data[i].expo > p2->data[j].expo) {
            addItemPolynomial(r, p1->data[i]);
            i++;
        } else if (p1->data[i].expo < p2->data[j].expo) {
            addItemPolynomial(r, p2->data[j]);
            j++;
        } else {
            int sumCoef = p1->data[i].coef + p2->data[j].coef;
            if (sumCoef != 0) {
                addItemPolynomial(r, (elementType){ sumCoef, p1->data[i].expo });
            }
            i++;
            j++;
        }
    }

    /* [버그 수정] 남은 p1 항 처리 */
    while (i < sizeArrayList(p1)) {
        addItemPolynomial(r, p1->data[i]);
        i++;
    }

    /* [버그 수정] 남은 p2 항 처리 */
    while (j < sizeArrayList(p2)) {
        addItemPolynomial(r, p2->data[j]);
        j++;
    }

    return r;
}

/*
 * 다항식 곱셈.
 * p1의 각 항과 p2의 각 항을 곱한 뒤 addItemPolynomial로 결과 다항식에 삽입.
 * 같은 지수끼리는 addItemPolynomial 내부에서 자동으로 계수가 합산됨.
 */
polynomial* multiplyPolynomial(polynomial* p1, polynomial* p2) {
    int maxSize = sizeArrayList(p1) * sizeArrayList(p2);
    if (maxSize == 0) {
        return createPolynomial(1);
    }

    polynomial* r = createPolynomial(maxSize);

    for (int i = 0; i < sizeArrayList(p1); i++) {
        for (int j = 0; j < sizeArrayList(p2); j++) {
            elementType term;
            term.coef = p1->data[i].coef * p2->data[j].coef;
            term.expo = p1->data[i].expo + p2->data[j].expo;
            addItemPolynomial(r, term);
        }
    }

    return r;
}

/*
 * 사용자로부터 다항식을 입력받는 함수.
 * 입력 형식: 3X^2+2X^1+1X^0
 * 음수 계수는 지원하지 않음 (과제 요구사항 기준).
 */
polynomial* inputPolynomial(void) {
    char buf[1024];
    printf("다항식 입력 (예: 3X^2+2X^1+1X^0): ");
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        return createPolynomial(10);
    }

    /* 개행 제거 */
    buf[strcspn(buf, "\n")] = '\0';

    polynomial* po = createPolynomial(50);
    char* ptr = buf;

    while (*ptr != '\0') {
        int coef = 0, expo = 0;
        int hasCoef = 0; /* 계수가 명시적으로 적혔는지 여부 */

        /* 계수 파싱 */
        while (isdigit((unsigned char)*ptr)) {
            coef = coef * 10 + (*ptr - '0');
            ptr++;
            hasCoef = 1;
        }

        /* 'X' 확인 */
        if (*ptr == 'X' || *ptr == 'x') {
            /* [버그 수정] 계수 없는 X → 계수 1로 처리 (예: X^2, X) */
            if (!hasCoef) coef = 1;
            ptr++; /* 'X' 건너뜀 */

            if (*ptr == '^') {
                ptr++; /* '^' 건너뜀 */
                /* 지수 파싱 */
                while (isdigit((unsigned char)*ptr)) {
                    expo = expo * 10 + (*ptr - '0');
                    ptr++;
                }
            } else {
                expo = 1; /* X^1 생략 형태 */
            }
        } else {
            expo = 0; /* 상수항 */
        }

        /* [버그 수정] coef != 0 조건 제거: 계수 0인 항만 제외, 정상 항은 모두 삽입 */
        if (hasCoef || coef == 1) {
            addItemPolynomial(po, (elementType){ coef, expo });
        }

        /* '+' 건너뜀 */
        if (*ptr == '+') {
            ptr++;
        }
    }

    return po;
}

void printPolynomial(polynomial* po) {
    if (sizeArrayList(po) == 0) {
        printf("Polynomial: 0\n");
        return;
    }

    printf("Polynomial: ");
    for (int i = 0; i < sizeArrayList(po); i++) {
        int coef = po->data[i].coef;
        int expo = po->data[i].expo;

        if (i > 0 && coef > 0) printf("+");

        if (expo == 0) {
            printf("%d", coef);
        } else if (expo == 1) {
            printf("%dX", coef);
        } else {
            printf("%dX^%d", coef, expo);
        }
    }
    printf("\n");
}
