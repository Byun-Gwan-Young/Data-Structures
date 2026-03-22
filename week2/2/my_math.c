#include <stdlib.h>
#include "my_math.h"

int gcd(int a, int b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int lcm(int a, int b) {
    if (a == 0 || b == 0) return 0;
    return abs(a) / gcd(a, b) * abs(b);
    // a * b / gcd 순서로 하면 a * b 가 int 범위 초과할 수 있음
    // a / gcd * b 순서로 하면 먼저 나눠서 숫자를 줄인 후 곱함
    // gcd는 항상 a의 약수이므로 a / gcd 는 나머지 없이 나누어 떨어짐
}
