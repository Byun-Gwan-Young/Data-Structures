#ifndef MY_FRACTION_H
#define MY_FRACTION_H

// 분수 자료형
typedef struct {
    int numerator;   // 분자
    int denominator; // 분모
} Fraction;

Fraction reduce(Fraction f);                  // 기약분수 변환
Fraction add_frac(Fraction a, Fraction b);    // 덧셈
Fraction sub_frac(Fraction a, Fraction b);    // 뺄셈
Fraction mul_frac(Fraction a, Fraction b);    // 곱셈
Fraction div_frac(Fraction a, Fraction b);    // 나눗셈
Fraction str_to_frac(const char* str);        // 문자열 → 분수
void print_frac(Fraction f);                  // 분수 출력

#endif
