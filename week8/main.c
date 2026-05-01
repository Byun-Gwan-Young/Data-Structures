#include <stdio.h>
#include <stdlib.h>

#include "polynomial.h"

int main(void) {
    printf("========================================\n");
    printf("       다항식 덧셈 및 곱셈 계산기\n");
    printf("========================================\n\n");

    /* ── 다항식 입력 ── */
    printf("[첫 번째 다항식]\n");
    polynomial* p1 = inputPolynomial();
    printf("입력된 p1: ");
    printPolynomial(p1);
    printf("\n");

    printf("[두 번째 다항식]\n");
    polynomial* p2 = inputPolynomial();
    printf("입력된 p2: ");
    printPolynomial(p2);
    printf("\n");

    /* ── 덧셈 ── */
    printf("========================================\n");
    printf("[덧셈 결과: p1 + p2]\n");
    polynomial* pAdd = addPolynomial(p1, p2);
    printPolynomial(pAdd);
    printf("\n");

    /* ── 곱셈 ── */
    printf("========================================\n");
    printf("[곱셈 결과: p1 * p2]\n");
    polynomial* pMul = multiplyPolynomial(p1, p2);
    printPolynomial(pMul);
    printf("\n");

    /* ── 메모리 해제 ── */
    destroyArrayList(p1);
    destroyArrayList(p2);
    destroyArrayList(pAdd);
    destroyArrayList(pMul);

    return 0;
}
