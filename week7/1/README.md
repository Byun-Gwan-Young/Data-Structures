
# ArrayList (순차 리스트)

배열 기반 순차 리스트 구현 및 `realloc`을 이용한 동적 크기 확장

---

## 파일 구조

```
├── arrayList.h   # 구조체 및 함수 선언
├── arrayList.c   # 함수 구현
└── main.c        # 테스트 코드
```

---

## 실행 방법

VSCode 내장 터미널(`Ctrl + ~`)을 열고 아래 명령어를 입력한다.

**맥/리눅스**
```bash
gcc main.c arrayList.c -o main && ./main
```

**윈도우**
```bash
gcc main.c arrayList.c -o main.exe && main.exe
```

---

## 코드 설명

### arrayList.h
- `elementArrayList` : 리스트에 저장할 데이터 타입 (`int`)
- `arrayList` 구조체
  - `data` : 데이터를 저장하는 배열 (동적 할당)
  - `size` : 현재 저장된 데이터 수
  - `capacity` : 배열의 최대 용량

### arrayList.c

| 함수 | 설명 |
|---|---|
| `createArrayList(size)` | 초기 용량 `size`로 리스트 생성 |
| `destroyArrayList(al)` | 리스트 메모리 해제 |
| `isEmptyArrayList(al)` | 리스트가 비어있으면 1, 아니면 0 반환 |
| `isFullArrayList(al)` | 리스트가 가득 찼으면 1, 아니면 0 반환 |
| `sizeArrayList(al)` | 현재 저장된 데이터 수 반환 |
| `insertArrayList(al, pos, item)` | `pos` 위치에 `item` 삽입 |
| `deleteArrayList(al, pos)` | `pos` 위치의 데이터 삭제 후 반환 |
| `initArrayList(al)` | 리스트의 모든 데이터 삭제 |
| `getItemArrayList(al, pos)` | `pos` 위치의 데이터 반환 |
| `replaceItemArrayList(al, pos, item)` | `pos` 위치의 데이터를 `item`으로 교체 |
| `printArrayList(al)` | 리스트의 모든 데이터 출력 |

---

## realloc을 이용한 동적 크기 확장 (과제 핵심)

배열 기반 리스트는 `capacity`가 꽉 차면 더 이상 삽입이 불가능한 **포화 상태(Full)** 가 된다.  
`insertArrayList()` 에서 포화 상태가 감지되면 `realloc`으로 배열 크기를 **2배로 자동 확장**하여 이를 해결한다.

```c
if (isFullArrayList(al)) {
    int newCapacity = al->capacity * 2;
    elementArrayList* newData = (elementArrayList*)realloc(
        al->data, sizeof(elementArrayList) * newCapacity);
    if (newData == NULL) {
        return 0;  // 메모리 할당 실패
    }
    al->data = newData;
    al->capacity = newCapacity;
}
```

---

## 버그 수정 내역

1. **`insertArrayList()` 루프 범위 오류 (버퍼 오버플로우)**
   - 수정 전: `for (int i = al->size; i >= pos; i--)`
   - 수정 후: `for (int i = al->size - 1; i >= pos; i--)`
   - `i = al->size`에서 시작하면 포화 직전에 `data[capacity]` 범위 밖을 접근

2. **`initArrayList()` 반환값 누락 (미정의 동작)**
   - 반환형이 `int`인데 `return` 문이 없어 미정의 동작(UB) 발생
   - `return 1;` 추가로 수정
