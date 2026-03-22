#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_fraction.h"

// 최대공약수 (유클리드 호제법)
static int gcd(int a, int b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// 기약분수 변환
Fraction reduce(Fraction f) {
    if (f.denominator == 0) {
        printf("오류: 분모가 0입니다.\n");
        exit(1);
    }
    if (f.denominator < 0) {
        f.numerator = -f.numerator;
        f.denominator = -f.denominator;
    }
    int g = gcd(abs(f.numerator), f.denominator);
    f.numerator /= g;
    f.denominator /= g;
    return f;
}

// 덧셈
Fraction add_frac(Fraction a, Fraction b) {
    Fraction result;
    result.numerator = a.numerator * b.denominator + b.numerator * a.denominator;
    result.denominator = a.denominator * b.denominator;
    return reduce(result);
}

// 뺄셈
Fraction sub_frac(Fraction a, Fraction b) {
    Fraction result;
    result.numerator = a.numerator * b.denominator - b.numerator * a.denominator;
    result.denominator = a.denominator * b.denominator;
    return reduce(result);
}

// 곱셈
Fraction mul_frac(Fraction a, Fraction b) {
    Fraction result;
    result.numerator = a.numerator * b.numerator;
    result.denominator = a.denominator * b.denominator;
    return reduce(result);
}

// 나눗셈
Fraction div_frac(Fraction a, Fraction b) {
    if (b.numerator == 0) {
        printf("오류: 0으로 나눌 수 없습니다.\n");
        exit(1);
    }
    Fraction result;
    result.numerator = a.numerator * b.denominator;
    result.denominator = a.denominator * b.numerator;
    return reduce(result);
}

// "A/B" 문자열 → 분수
Fraction str_to_frac(const char* str) {
    Fraction f;

    if (sscanf(str, "%d/%d", &f.numerator, &f.denominator) == 2) {
        // A/B 형태
        if (f.denominator == 0) {
            printf("오류: 분모가 0입니다.\n");
            exit(1);
        }
    } else {
        // 정수 or 소수 형태
        double d;
        if (sscanf(str, "%lf", &d) == 1) {
            int denominator = 1;
            double temp = d;
            int count = 0;
            double frac_part = temp - (int)temp;
            if (frac_part < 0) frac_part = -frac_part;
            while (frac_part > 1e-9 && count < 10) {
                temp *= 10;
                denominator *= 10;
                count++;
                frac_part = temp - (int)temp;
                if (frac_part < 0) frac_part = -frac_part;
            }
            f.numerator = (int)(d * denominator);
            f.denominator = denominator;
        } else {
            printf("오류: 잘못된 입력입니다.\n");
            exit(1);
        }
    }

    return reduce(f);
}

// 분수 출력 (분모가 1이면 정수로 출력)
void print_frac(Fraction f) {
    if (f.denominator == 1)
        printf("%d\n", f.numerator);
    else
        printf("%d/%d\n", f.numerator, f.denominator);
}
