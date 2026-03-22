#include <stdio.h>
#include <string.h>
#include "my_fraction.h"
#include "my_fraction.c" 

int main() {
    char str1[50], op, str2[50];

    // 입력: 2/5 + 2/4
    scanf("%s %c %s", str1, &op, str2);

    Fraction a = str_to_frac(str1);
    Fraction b = str_to_frac(str2);
    Fraction result;

    switch (op) {
        case '+': result = add_frac(a, b); break;
        case '-': result = sub_frac(a, b); break;
        case '*': result = mul_frac(a, b); break;
        case '/': result = div_frac(a, b); break;
        default:
            printf("오류: 잘못된 연산자입니다.\n");
            return 1;
    }

    print_frac(result);
    return 0;
}
