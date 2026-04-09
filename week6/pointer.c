#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME 50
#define MAX_NAMES 100

typedef struct {
    char name[MAX_NAME];
    int id;
    int score;
} Student;

int main()
{
    FILE* fp;
    char name_list[MAX_NAMES][MAX_NAME];
    int name_count = 0;
    char file_buff[MAX_NAME];
    int N, i;
    Student* students;
    int min_idx, max_idx;
    double sum;

    /* 이름 리스트 파일 입출력 */
    fp = fopen("name_list.txt", "r");
    if (fp == NULL) {
        printf("Fail to open\n");
        return 0;
    }

    while (fgets(file_buff, sizeof(file_buff), fp) != NULL && name_count < MAX_NAMES) {
        *(file_buff + strcspn(file_buff, "\r\n")) = '\0';  /* 개행 제거 */
        strcpy(*(name_list + name_count), file_buff);
        name_count++;
    }
    fclose(fp);

    /* N 입력 및 동적 할당 */
    printf("Enter N: ");
    scanf("%d", &N);

    students = (Student*)malloc(sizeof(Student) * N);
    if (students == NULL) {
        printf("Memory allocation failed\n");
        return 0;
    }

    /* 학생 배열 생성 (포인터 연산자 사용) */
    srand((unsigned int)time(NULL));
    for (i = 0; i < N; i++) {
        strcpy((*(students + i)).name, *(name_list + rand() % name_count));
        (*(students + i)).id = i + 1;
        (*(students + i)).score = rand() % 100 + 1;
    }

    /* 학생 배열 전체 출력 (포인터 연산자 사용) */
    printf("\n===== Student List =====\n");
    printf("%-4s %-25s %s\n", "ID", "Name", "Score");
    printf("-----------------------------------\n");
    for (i = 0; i < N; i++) {
        printf("%-4d %-25s %d\n", (*(students + i)).id, (*(students + i)).name, (*(students + i)).score);
    }

    /* 최저점, 최고점, 평균 계산 (포인터 연산자 사용) */
    min_idx = 0;
    max_idx = 0;
    sum = 0.0;
    for (i = 0; i < N; i++) {
        sum += (*(students + i)).score;
        if ((*(students + i)).score < (*(students + min_idx)).score)
            min_idx = i;
        if ((*(students + i)).score > (*(students + max_idx)).score)
            max_idx = i;
    }

    /* 결과 출력 */
    printf("\n===== Result =====\n");
    printf("Lowest  : Name = %s, ID = %d, Score = %d\n",
        (*(students + min_idx)).name, (*(students + min_idx)).id, (*(students + min_idx)).score);
    printf("Highest : Name = %s, ID = %d, Score = %d\n",
        (*(students + max_idx)).name, (*(students + max_idx)).id, (*(students + max_idx)).score);
    printf("Average : %.2f\n", sum / N);

    free(students);
    return 0;
}
