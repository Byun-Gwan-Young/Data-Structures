#include <stdio.h>
#include "my_math.h"
#include "my_math.c"

int main() {
    int a, b;
    
    if (scanf("%d %d", &a, &b) != 2) {
        printf("오류: 잘못된 입력입니다.\n");
        return 1;
    }

    printf("GCD: %d, LCM: %d\n", gcd(a, b), lcm(a, b));
    return 0;
}
