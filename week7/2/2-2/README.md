
# 과제(10)-2 : 순차리스트 기반 희소행렬 전치

---

## 📁 파일 구성

```
├── arrayList.h       # 순차리스트 타입 정의 및 함수 선언
├── arrayList.c       # 순차리스트 함수 구현 (버그 수정 포함)
├── sparseMatrix.h    # 희소행렬 구조체 정의 및 함수 선언
├── sparseMatrix.c    # 희소행렬 함수 구현
└── main.c            # 10×10 희소행렬 전치 실행 프로그램
```

---

## 🔨 컴파일 및 실행

```bash
gcc -o hw10_2 arrayList.c sparseMatrix.c main.c
./hw10_2
```

---

## 🏗️ 핵심 구조 설계 — 다단계 포인터 (가산점)

과제 명세에서 요구한 구조:
```
sparseMatrix
  ㄴ col
  ㄴ row
  ㄴ arrayList*
       ㄴ 과제(9)의 arrayList
```

실제 구현한 구조:
```c
// arrayList.h
typedef struct elementArrayListType {
    int row;    // 비영 원소의 행 위치
    int col;    // 비영 원소의 열 위치
    int value;  // 원소 값
} elementArrayList;

typedef struct arrayListType {
    elementArrayList* data;  // 비영 원소 배열 (3단계 포인터)
    int size;
    int capacity;
} arrayList;

// sparseMatrix.h
typedef struct sparseMatrixType {
    int row;         // 행렬의 행 수
    int col;         // 행렬의 열 수
    arrayList* al;   // 순차리스트 포인터 (2단계 포인터)
} sparseMatrix;
```

### 포인터 단계 구조

```
sparseMatrix*            ← 1단계: 희소행렬 포인터
    └─ arrayList* al     ← 2단계: 순차리스트 포인터
           └─ elementArrayList* data   ← 3단계: 원소 배열 포인터
                  └─ .row / .col / .value   ← 실제 데이터
```

실제 데이터 접근 코드:
```c
sm->al->data[i].value   // 포인터 3단계를 통해 도달
```

---

## 💡 희소행렬이란?

행렬에서 **0이 아닌 원소의 비율이 매우 낮은 행렬**을 희소행렬(Sparse Matrix)이라 한다.

10×10 행렬 = 원소 100개. 이 중 비영 원소가 20개라면 나머지 80개는 0.  
→ 0을 전부 저장하는 건 메모리 낭비이므로, **비영 원소만 (row, col, value)로 따로 저장**한다.

```
원본 행렬 100칸 저장 → 희소행렬 표현 시 20칸만 저장 (80% 절약)
```

---

## 🔄 전치행렬 알고리즘

전치행렬(Transpose)은 행과 열을 서로 바꾼 행렬이다. `A[i][j] → A[j][i]`

### 단순 전치 알고리즘 (구현한 방식)

```
열(col) 0부터 (maxCol-1)까지 순서대로:
    비영 원소 전체 리스트를 스캔:
        해당 열의 원소를 발견하면 row↔col 교환하여 결과에 삽입
```

이 방식의 장점: 결과 리스트가 자동으로 **행 우선(row-major) 순서**로 정렬됨.  
별도 정렬 과정 없이 올바른 순서로 전치행렬을 만들 수 있다.

---

## 📊 데이터 이동 횟수 설명

| 항목 | 값 | 의미 |
|---|---|---|
| 비영 원소 수 (nnz) | 20 | 리스트에 저장된 원소 개수 |
| 비교 횟수 | 200 | `10(열 수) × 20(nnz)` — 리스트를 총 10번 전체 스캔 |
| **데이터 이동 횟수** | **20** | 원소가 결과 리스트에 실제로 복사된 횟수 |

**데이터 이동 횟수 = nnz (비영 원소 수)**  
각 원소는 정확히 한 번 결과 배열에 복사되기 때문이다.

```c
if (e.col == c) {
    elementArrayList transposed = {e.col, e.row, e.value};
    insertArrayList(result->al, sizeArrayList(result->al), transposed);
    (*moveCount)++;  // ← 결과 배열에 쓸 때만 카운트
}
```

---

## 🐛 arrayList.c 버그 수정 내역

### 1. `insertArrayList()` — 루프 범위 오류

```c
// ❌ 수정 전: data[al->size + 1] 까지 접근 → 버퍼 오버플로우
for (int i = al->size; i >= pos; i--)

// ✅ 수정 후
for (int i = al->size - 1; i >= pos; i--)
```

### 2. `insertArrayList()` — 포화 상태 처리 누락

```c
// ✅ 수정 후: realloc으로 capacity 2배 확장
if (isFullArrayList(al)) {
    int newCapacity = al->capacity * 2;
    elementArrayList* newData = realloc(al->data, sizeof(elementArrayList) * newCapacity);
    if (newData == NULL) return 0;
    al->data = newData;
    al->capacity = newCapacity;
}
```

### 3. `initArrayList()` — 반환값 누락 (UB)

```c
// ✅ 수정 후: return 1; 추가
int initArrayList(arrayList* al) {
    ...
    return 1;
}
```

### 4. `deleteArrayList()` — 빈 오류 처리 블록

```c
// ❌ 수정 전: 오류 감지 후 아무것도 안 함, 이후 코드 계속 실행
if (pos < 0 || pos > al->size - 1) { }  // 빈 블록!

// ✅ 수정 후: 빈 구조체 반환으로 명시적 오류 처리
if (pos < 0 || pos > al->size - 1) {
    elementArrayList empty = {0, 0, 0};
    return empty;
}
```

---

## 📺 실행 결과 예시

```
==============================================
  10×10 희소행렬 생성 (비영 원소 20개)
==============================================

▶ 원본 희소행렬 (리스트 형태)
  [희소행렬] 10×10, 비영 원소 수: 20
  row   col   value
  -----------------
  0     2     5
  0     7     3
  ...

▶ 원본 희소행렬 (행렬 형태)
  [전체 행렬] 10×10
     0   0   5   0   0   0   0   3   0   0
     0   0   0   0   8   0   0   0   0   1
  ...

==============================================
  전치행렬 생성
==============================================
  [전치 완료] 비교 횟수: 200, 데이터 이동 횟수: 20
  → 데이터 이동 횟수: 20

▶ 전치행렬 (행렬 형태)
  [전체 행렬] 10×10
     0   0   7   0   0   0  12   0   0   0
     0   0   0   2   0   0   0   7   0   0
  ...
```

---

## 🔑 핵심 개념 요약

| 용어 | 설명 |
|---|---|
| 희소행렬 | 비영 원소 비율이 낮아 (row, col, value)만 따로 저장하는 행렬 |
| 전치행렬 | 행과 열을 서로 바꾼 행렬. A[i][j] → A[j][i] |
| 데이터 이동 횟수 | 원소가 결과 배열에 실제로 복사된 횟수 (= 비영 원소 수) |
| 다단계 포인터 | `sm→al→data[i]` 처럼 포인터를 여러 단계에 걸쳐 연결한 구조 |
| 행 우선 순서 | 결과를 row 순서대로 저장하기 위해 col 기준으로 반복 스캔 |
