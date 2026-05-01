
# 다항식 계산기 (Polynomial Calculator)

순차 리스트(Array List) 자료구조를 기반으로 다항식의 **덧셈**과 **곱셈**을 구현한 프로젝트입니다.

수의 범위가 int형이므로 큰 수를 계산하고 싶으면 int -> long long 으로 코드 수정 후 사용하시면 됩니다.

---

## 목차

1. [프로젝트 구조](#프로젝트-구조)
2. [자료구조 설계](#자료구조-설계)
3. [주요 알고리즘](#주요-알고리즘)
4. [버그 수정 내역](#버그-수정-내역)
5. [빌드 및 실행](#빌드-및-실행)
6. [입출력 예시](#입출력-예시)
7. [시간복잡도 분석](#시간복잡도-분석)

---

## 프로젝트 구조

```
.
├── arrayList.h      # 순차 리스트 구조체 및 함수 선언
├── arrayList.c      # 순차 리스트 구현
├── polynomial.h     # 다항식 함수 선언
├── polynomial.c     # 다항식 덧셈 · 곱셈 · 입력 · 출력 구현
├── main.c           # 프로그램 진입점
└── README.md
```

### 파일 의존 관계

```
main.c
  └── polynomial.h / polynomial.c
        └── arrayList.h / arrayList.c
```

`polynomial`은 `arrayList`를 **typedef로 재사용**하는 방식으로 설계되어,  
별도의 새로운 구조체 없이 기존 순차 리스트 인프라를 그대로 활용합니다.

---

## 자료구조 설계

### 핵심 구조체

```c
/* arrayList.h */

typedef struct ElementType {
    int coef;   /* 계수 (coefficient) */
    int expo;   /* 지수 (exponent)    */
} elementType;

typedef struct arrayListType {
    elementArrayList* data;   /* 동적 배열 */
    int size;                 /* 현재 원소 수 */
    int capacity;             /* 할당된 최대 크기 */
} arrayList;

/* polynomial.h */
typedef arrayList polynomial;  /* polynomial은 arrayList의 별칭 */
```

### 다항식 저장 방식

각 항(term)을 `(coef, expo)` 쌍으로 저장하며, 배열 내에서 **지수 내림차순**으로 정렬 유지합니다.

```
3X² + 2X + 1  →  [(3,2), (2,1), (1,0)]
4X³ + 5       →  [(4,3), (5,0)]
```

정렬을 유지하며 삽입하면 덧셈·곱셈 시 순차 탐색만으로 처리가 가능하여 불필요한 정렬 비용을 줄일 수 있습니다.

---

## 주요 알고리즘

### 1. 정렬 삽입 — `addItemPolynomial`

새 항을 삽입할 때 항상 **지수 내림차순 위치**를 찾아 삽입합니다.  
같은 지수가 이미 존재하면 계수를 합산하고, 합산 결과가 0이 되면 해당 항을 제거합니다.

```c
for (i = 0; i < sizeArrayList(po); i++) {
    if (po->data[i].expo < item.expo) break;  /* 삽입 위치 발견 */
}

if (po->data[i].expo == item.expo) {
    po->data[i].coef += item.coef;            /* 계수 합산 */
    if (po->data[i].coef == 0)
        deleteArrayList(po, i);               /* 0이면 제거 */
} else {
    insertArrayList(po, i, item);             /* 새 항 삽입 */
}
```

### 2. 다항식 덧셈 — `addPolynomial`

두 다항식이 모두 **지수 내림차순 정렬** 상태임을 이용한 **병합(Merge) 방식**입니다.  
두 포인터 `i`, `j`를 동시에 진행하며 O(n+m) 시간에 처리합니다.

```
p1: [4X³][3X²][2X][1]
p2:      [5X²]    [6]

i→ 4X³  :  p1 지수(3) > p2 지수(2)  →  결과에 4X³ 추가, i++
i→ 3X²  :  p1 지수(2) = p2 지수(2)  →  계수 합산 8X², i++, j++
i→ 2X   :  p1 지수(1) > p2 지수(0)  →  결과에 2X  추가, i++
i→ 1    :  p1 지수(0) = p2 지수(0)  →  계수 합산 7,   i++, j++
```

루프 종료 후 **남은 항을 모두 결과에 추가**하는 처리가 필수입니다(기존 코드의 버그 지점).

```c
while (i < sizeArrayList(p1)) { addItemPolynomial(r, p1->data[i++]); }
while (j < sizeArrayList(p2)) { addItemPolynomial(r, p2->data[j++]); }
```

### 3. 다항식 곱셈 — `multiplyPolynomial`

분배법칙을 직접 구현합니다. p1의 모든 항과 p2의 모든 항을 **이중 반복**으로 곱한 후,  
`addItemPolynomial`의 정렬 삽입 + 계수 합산 기능을 활용해 결과를 누적합니다.

```
(3X² + 2X + 1) × (4X³ + 5)

= 3X²·4X³ + 3X²·5 + 2X·4X³ + 2X·5 + 1·4X³ + 1·5
= 12X⁵ + 15X² + 8X⁴ + 10X + 4X³ + 5
= 12X⁵ + 8X⁴ + 4X³ + 15X² + 10X + 5
```

```c
for (int i = 0; i < sizeArrayList(p1); i++) {
    for (int j = 0; j < sizeArrayList(p2); j++) {
        elementType term = {
            p1->data[i].coef * p2->data[j].coef,
            p1->data[i].expo + p2->data[j].expo
        };
        addItemPolynomial(r, term);  /* 동일 지수면 내부에서 자동 합산 */
    }
}
```

### 4. 다항식 입력 파싱 — `inputPolynomial`

`3X^2+2X^1+1X^0` 형식의 문자열을 직접 파싱합니다.

```
"3X^2+2X^1+1X^0"
  │   │   │
  │   │   └─ coef=1, expo=0  →  (1, 0)
  │   └───── coef=2, expo=1  →  (2, 1)
  └───────── coef=3, expo=2  →  (3, 2)
```

`isdigit()`으로 숫자 토큰을 읽고, `X` · `^` 문자로 지수부를 구분합니다.

---

## 버그 수정 내역

### 1. `insertArrayList` — 원소 이동 방향 오류

```c
/* 수정 전: pos 위치 원소가 자기 자신을 덮어쓰는 문제 */
for (int i = al->size; i >= pos; i--)
    al->data[i + 1] = al->data[i];  /* i == pos 일 때 data[pos+1] = data[pos] 후 data[pos] = item이 아닌 위치 오류 */

/* 수정 후 */
for (int i = al->size; i > pos; i--)
    al->data[i] = al->data[i - 1];
```

### 2. `insertArrayList` — capacity 초과 시 메모리 오버플로우

원래 코드는 배열이 가득 찼을 때 아무 처리 없이 범위 밖 메모리에 쓰기를 시도합니다.  
`realloc`으로 capacity를 2배 확장하여 해결했습니다.

```c
if (isFullArrayList(al)) {
    int newCap = al->capacity * 2;
    al->data = realloc(al->data, sizeof(elementArrayList) * newCap);
    al->capacity = newCap;
}
```

### 3. `initArrayList` — 반환값 누락 (UB)

`int` 반환 함수인데 `return`이 없어 미정의 동작(Undefined Behavior)이 발생합니다.

```c
/* 수정 후 */
int initArrayList(arrayList* al) {
    for (int i = al->size - 1; i >= 0; i--)
        deleteArrayList(al, i);
    return 1;
}
```

### 4. `addItemPolynomial` — 정렬 삽입 비교 방향 오류

지수 내림차순 유지를 위해 `<=` 비교가 `<`가 되어야 합니다.  
`<=`를 사용하면 동일 지수 항이 합산되지 않고 뒤에 별도 삽입됩니다.

```c
/* 수정 전 */
if (po->data[i].expo <= item.expo) break;

/* 수정 후: 같은 지수는 break 하지 않고 합산 분기로 처리 */
if (po->data[i].expo < item.expo) break;
```

### 5. `addPolynomial` — 나머지 항 처리 누락

두 포인터 방식에서 한쪽 배열이 먼저 소진되면 나머지를 결과에 추가해야 합니다.

```c
/* 수정 전: 나머지 항 누락 */
/* 수정 후 */
while (i < sizeArrayList(p1)) addItemPolynomial(r, p1->data[i++]);
while (j < sizeArrayList(p2)) addItemPolynomial(r, p2->data[j++]);
```

---

## 빌드 및 실행

### 컴파일

```bash
gcc -Wall -o poly main.c arrayList.c polynomial.c
```

| 옵션 | 설명 |
|------|------|
| `-Wall` | 모든 경고 활성화 |
| `-o poly` | 출력 파일명 지정 |

### 실행

```bash
./poly
```

---

## 입출력 예시

```
========================================
       다항식 덧셈 및 곱셈 계산기
========================================

[첫 번째 다항식]
다항식 입력 (예: 3X^2+2X^1+1X^0): 3X^2+2X^1+1X^0
입력된 p1: Polynomial: 3X^2+2X+1

[두 번째 다항식]
다항식 입력 (예: 3X^2+2X^1+1X^0): 4X^3+5X^0
입력된 p2: Polynomial: 4X^3+5

========================================
[덧셈 결과: p1 + p2]
Polynomial: 4X^3+3X^2+2X+6

========================================
[곱셈 결과: p1 * p2]
Polynomial: 12X^5+8X^4+4X^3+15X^2+10X+5
```

---

## 시간복잡도 분석

| 연산 | 시간복잡도 | 설명 |
|------|-----------|------|
| `insertArrayList` | O(n) | 원소 이동 |
| `deleteArrayList` | O(n) | 원소 이동 |
| `addItemPolynomial` | O(n) | 삽입 위치 탐색 + 이동 |
| `addPolynomial` | O(n + m) | 두 포인터 병합 |
| `multiplyPolynomial` | O(n·m·(n+m)) | 이중 루프 × 삽입 비용 |

> **곱셈 최적화 여지**: 결과 항을 임시 배열에 모은 후 한 번에 정렬(merge sort)하면  
> O(n·m·log(n·m))으로 개선 가능합니다.
