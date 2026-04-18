
# SparseMatrix - 오류 수정 내용

## 개요

수업 시간(2025.04.16)에 작성한 희소행렬(Sparse Matrix) 구현 코드에서 발견된 버그를 수정한 버전입니다.  
ArrayList를 기반으로 희소행렬을 표현하며, 행렬 출력 및 덧셈 기능을 제공합니다.

---

## 파일 구조

```
SparseMatrix/
├── arrayList.h       # ArrayList 구조체 및 함수 선언
├── arrayList.c       # ArrayList 구현 (수정됨)
├── sparseMatrix.h    # SparseMatrix 구조체 및 함수 선언
├── sparseMatrix.c    # SparseMatrix 구현 (수정됨)
└── main.c            # 테스트 코드
```

---

## 발견된 오류 및 수정 내용

### ❗ [오류 1] `sparseMatrix.c` — `addSparseMatrix` 루프 범위 오류 (핵심 크래시 원인)

**증상:** 수업 시간에 `add 완료` 출력 전 프로그램이 비정상 종료됨 (Segmentation Fault)

**원인:**
```c
// ❌ 수정 전: <= 로 인해 size=3일 때 인덱스 3(존재하지 않음)까지 접근
for (int i = 0; i <= sizeArrayList(sm1); i++)
for (j = 0; j <= sizeArrayList(sm2); j++)
```

`getItemArrayList()`는 범위 검사를 하지 않기 때문에, 존재하지 않는 메모리를 읽어 런타임 크래시 발생.

**수정:**
```c
// ✅ 수정 후: < 로 변경하여 유효 인덱스(0 ~ size-1)만 접근
for (int i = 0; i < sizeArrayList(sm1); i++)
for (j = 0; j < sizeArrayList(sm2); j++)
```

---

### ❗ [오류 2] `sparseMatrix.c` — `addSparseMatrix` 논리 오류 (sm2 단독 원소 누락)

**증상:** 행렬 덧셈 결과에 sm2에만 있는 원소가 포함되지 않음

**원인:**
기존 코드는 sm1을 기준으로만 순회하며, sm2에만 존재하는 원소를 결과에 추가하는 로직이 없었음.

**수정:**
```c
// ✅ sm1 루프 완료 후, sm2에만 있는 원소를 별도로 결과에 추가
for (int j = 0; j < sizeArrayList(sm2); j++) {
    elementArrayList nonZeroOfSM2 = getItemArrayList(sm2, j);
    int found = 0;
    for (int i = 0; i < sizeArrayList(sm1); i++) {
        elementArrayList nonZeroOfSM1 = getItemArrayList(sm1, i);
        if (nonZeroOfSM1.row == nonZeroOfSM2.row &&
            nonZeroOfSM1.col == nonZeroOfSM2.col) {
            found = 1;
            break;
        }
    }
    if (!found) {
        insertArrayList(smResult, sizeArrayList(smResult), nonZeroOfSM2);
    }
}
```

---

### ⚠️ [오류 3] `arrayList.c` — `insertArrayList` 루프 off-by-one

**원인:**
```c
// ❌ 수정 전: i = al->size 에서 시작 → data[size+1] 에 쓰기 (out-of-bounds)
for (int i = al->size; i >= pos; i--) {
    al->data[i + 1] = al->data[i];
}
```

**수정:**
```c
// ✅ 수정 후: i = al->size - 1 에서 시작
for (int i = al->size - 1; i >= pos; i--) {
    al->data[i + 1] = al->data[i];
}
```

---

### ⚠️ [오류 4] `arrayList.c` — `insertArrayList` 용량 초과 체크 누락

**수정:**
```c
// ✅ 삽입 전 꽉 찼는지 확인
if (isFullArrayList(al)) {
    return 0;
}
```

---

### ⚠️ [오류 5] `arrayList.c` — `deleteArrayList` 에러 처리 누락

**원인:** 잘못된 pos가 입력되어도 빈 블록으로 처리하고 진행함

**수정:**
```c
// ✅ 빈 element를 반환하도록 수정
if (pos < 0 || pos > al->size - 1) {
    elementArrayList empty = {0, 0, 0};
    return empty;
}
```

---

### ⚠️ [오류 6] return 문 누락 (3곳)

반환형이 `int`인 함수들에 `return` 문이 없어 undefined behavior 발생 가능.

| 함수 | 파일 |
|---|---|
| `initArrayList()` | arrayList.c |
| `addElementSparseMatrix()` | sparseMatrix.c |
| `printSparseMatrix()` | sparseMatrix.c |

모두 `return 1;` 추가로 수정.

---

## 컴파일 및 실행 방법

```bash
gcc -o sparseMatrix main.c arrayList.c sparseMatrix.c
./sparseMatrix
```

## 예상 출력

```
희소행렬입니다
Cap: 25, size: 3
(2 1 10) (3 3 15) (4 1 3)
희소행렬입니다
Cap: 25, size: 3
(2 1 10) (3 4 15) (4 1 3)
add 완료
희소행렬입니다
Cap: 100, size: 4
(2 1 20) (3 3 15) (4 1 6) (3 4 15)
print 완료
```
