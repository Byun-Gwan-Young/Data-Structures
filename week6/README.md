과제(7) - 구조체 배열

과제 제출 관련 안내 공지사항을 꼭 확인하세요.



1) 배열

- 숫자 N을 입력받아 동적 할당으로 크기가 N인 학생 구조체 배열을 생성한다.

- 학생 구조체 배열에는 이름(문자열), 학번(1~N), 성적(1~100) 필드가 존재한다.

- 학생의 이름은 아래 참고 학생 이름에서 무작위로 사용, 학번은 순서대로 증가, 성적은 무작위 범위 내 숫자를 사용하여 학생 배열을 생성한다.

- 이름 리스트는 파일 입출력으로 받아온다.

- 최처점 학생의 정보, 최고점 학생의 정보, 평균 점수를 출력한다.

- 이때 모든 배열 접근 연산은 인덱스 연산자(arr[idx])만을 사용한다.

 

2) 포인터

- 위와 같은 과제에서, 모든 배열 접근 연산을 포인터 연산자(*(arr + idx))를 통해 진행한다.



+ 참고 사항
- 과제의 기본 점수는 세부 과제 한 항목당 5점입니다.
- 과제 제출 방법 세부 안내에서 0점 처리로 안내된 조항 및 잘못된/늦은 과제 제출의 정정은 불가합니다.
- 과제 제출 시 과제에 포함된 모든 *.md 파일과 *.h, *.c 파일의 링크를 전부 과제 제출란에 입력하여야 합니다.





#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>



int main()

{

    FILE* fp;



    fp = fopen("C:\\Users\\user\\Desktop\\name_list.txt", "r");



    if (fp == NULL) {

        printf("Fail to open\n");

        return 0;

    }



    char file_buff[50];

    while (fgets(file_buff, sizeof(file_buff), fp) != NULL) {

        printf("%s", file_buff);

        memset(file_buff, 0, sizeof(file_buff));

    }



    fclose(fp);



    return 0;

}
