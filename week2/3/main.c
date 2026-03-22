#include <stdio.h>
#include "my_fraction.h"
#include "my_fraction.c"

int main(int c, char** v) {
    // 인자 개수 확인 (프로그램명 + 가로 + 세로 = 3개)
    if (c != 3) {
        printf("오류: 인자가 부족합니다.\n");
        printf("사용법: .\\program 가로 세로\n");
        printf("예시: .\\program 3/7 4/9\n");
        return 1;
    }

    Fraction width  = str_to_frac(v[1]);  // 가로
    Fraction height = str_to_frac(v[2]);  // 세로

    // 둘레 = 2 * (가로 + 세로)
    Fraction two = {2, 1};
    Fraction perimeter = mul_frac(two, add_frac(width, height));

    // 넓이 = 가로 * 세로
    Fraction area = mul_frac(width, height);

    printf("Perimeter: ");
    print_frac(perimeter);
    printf("Area: ");
    print_frac(area);

    return 0;
}         
