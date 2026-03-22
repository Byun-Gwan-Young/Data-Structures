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
    return abs(a) / gcd(a, b) * abs(b);  // 오버플로우 방지
}
