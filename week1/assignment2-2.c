#include <stdio.h>

int main() {
    char str[100];

    printf("입력: ");
    fgets(str, sizeof(str), stdin);

    printf("출력: ");
    for (int i = 0; str[i] != '\0'; i++) {
        // 알파벳인 경우에만 비트(32)를 뒤집습니다.
        if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) {
            // 2^5인 32와 XOR 연산 실행
            // 대문자, 소문자 구분해서 +32, -32를 할 수 있지만 XOR를 사용하면 코드 길이가 짧아지고 CPU의 효율을 높일 수 있다.
            // 아스키 코드 테이블에서 대문자와 소문자의 값 차이가 32 즉, 2^5 만큼 차이나는 것을 암 -> 2^5 비트 반전
            printf("%c", str[i] ^ 32); 
        } else {
            printf("%c", str[i]);
        }
    }

    return 0;
}
