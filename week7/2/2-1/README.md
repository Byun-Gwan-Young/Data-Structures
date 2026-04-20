
# 과제(10)-1 : 양의 정수 전용 순차리스트

## ✅ 과제 조건 충족 여부

| 번호 | 요구사항 | 충족 여부 | 구현 위치 |
|:---:|---|:---:|---|
| - | 과제(9) ArrayList 코드 기반 | ✅ | 전체 구조 동일 유지 |
| - | 양의 정수 전용 순차리스트 | ✅ | `isPositiveInt()` 검사 |
| 1 | 양의 정수 + 위치 입력 → 삽입 (insert) | ✅ | `main.c` case 1 |
| 2 | 위치 입력 → 삭제 (delete) | ✅ | `main.c` case 2 |
| 3 | 양의 정수 + 위치 입력 → 변경 (replace) | ✅ | `main.c` case 3 |
| 4 | 위치와 함께 프린트 (print) | ✅ | `main.c` case 4 |
| 5 | 모든 값 삭제 (clear) | ✅ | `main.c` case 5 |
| - | 기존 오류 개선 | ✅ | 아래 오류 수정 참고 |

---

## 📁 파일 구성

```
├── arrayList.h   # 순차리스트 타입 정의 및 함수 선언
├── arrayList.c   # 순차리스트 함수 구현
└── main.c        # 메뉴 기반 실행 프로그램
```

---

## 🔨 컴파일 및 실행

```bash
gcc -o hw10_1 arrayList.c main.c
./hw10_1
```

---

## 🐛 과제(9) 버그 수정 내역

### 1. `insertArrayList()` — 루프 범위 오류 (버퍼 오버플로우)

```c
// ❌ 수정 전
for (int i = al->size; i >= pos; i--)

// ✅ 수정 후
for (int i = al->size - 1; i >= pos; i--)
```

**이유:**  
배열을 뒤에서부터 한 칸씩 민다. `i = al->size`에서 시작하면
`data[al->size + 1]`에 쓰게 되는데, 포화 직전(`size == capacity - 1`)일 때
`data[capacity]`는 할당 범위 밖이라 **버퍼 오버플로우** 발생.

---

### 2. `insertArrayList()` — 포화 상태에서 삽입 시 오버플로우

```c
// ❌ 수정 전: 포화 상태에서도 그냥 삽입 시도 → 배열 범위 초과

// ✅ 수정 후: realloc으로 capacity 2배 확장
if (isFullArrayList(al)) {
    int newCapacity = al->capacity * 2;
    elementArrayList* newData = realloc(al->data, sizeof(elementArrayList) * newCapacity);
    if (newData == NULL) return 0;
    al->data     = newData;
    al->capacity = newCapacity;
}
```

---

### 3. `initArrayList()` — 반환값 누락 (미정의 동작, UB)

```c
// ❌ 수정 전: 반환형이 int인데 return 문 없음 → Undefined Behavior
int initArrayList(arrayList* al) { ... }

// ✅ 수정 후
int initArrayList(arrayList* al) {
    ...
    return 1;
}
```

---

## ✨ 과제(10)에서 새로 추가한 것들

### 1. `isPositiveInt()` — 양의 정수 검사 함수

```c
int isPositiveInt(elementArrayList item) {
    return (item > 0) ? 1 : 0;
}
```

`insertArrayList()`와 `replaceItemArrayList()` 호출 시 먼저 이 함수로 검사한다.  
0이나 음수를 입력하면 오류 메시지를 출력하고 삽입/변경을 거부한다.

---

### 2. `printArrayList()` — 위치와 함께 출력

```c
// 출력 예시
크기: 3 / 용량: 4
[0] 10
[1] 20
[2] 30
```

---

### 3. `clearArrayList()` — 전체 삭제 (메뉴 5번)

```c
int clearArrayList(arrayList* al) {
    return initArrayList(al);
}
```

`initArrayList()`의 래퍼 함수.  
`initArrayList()`는 과제(9) 호환을 위해 유지하고, 메뉴 5번에서는 의미가 명확한 `clearArrayList()`를 호출한다.

---

### 4. `deleteArrayList()` 오류 반환값 변경

- **수정 전:** 오류 시 `0` 반환  
- **수정 후:** 오류 시 `-1` 반환  

**이유:** 이 리스트는 양의 정수만 저장하므로 `0`은 절대 정상 값으로 들어올 수 없다.  
하지만 오류 반환값도 `0`이면 "삭제 성공인데 값이 0" vs "삭제 실패"를 구분할 수 없다.  
`-1`로 변경하면 음수도 정상 값이 아니므로 명확하게 오류를 구분할 수 있다.

---

## 📺 실행 화면 예시

```
==============================
  양의 정수 순차리스트 메뉴
==============================
  1. 삽입 (insert)
  2. 삭제 (delete)
  3. 변경 (replace)
  4. 출력 (print)
  5. 전체 삭제 (clear)
  0. 종료
------------------------------
  선택: 1
  삽입할 양의 정수: 10
  삽입할 위치 (0 ~ 0): 0
  → 10 을(를) 위치 0 에 삽입했습니다.

  선택: 4
  ── 순차리스트 출력 ──
  크기: 1 / 용량: 4
  [0] 10

  선택: 1
  삽입할 양의 정수: -5
  [오류] 양의 정수만 삽입할 수 있습니다. (입력값: -5)
```

---

## 🔑 핵심 개념 요약

| 용어 | 설명 |
|---|---|
| 순차리스트 (ArrayList) | 배열 기반 선형 자료구조. 인덱스로 O(1) 접근 가능 |
| 삽입 시 이동 | pos 뒤의 원소를 모두 한 칸씩 뒤로 밀어야 함 → 최악 O(n) |
| 삭제 시 이동 | pos 뒤의 원소를 모두 한 칸씩 앞으로 당겨야 함 → 최악 O(n) |
| realloc | 기존 메모리를 새 크기로 재할당. 실패 시 NULL 반환, 원본은 유지됨 |
| capacity vs size | capacity = 배열 총 크기, size = 실제 저장된 원소 수 |
