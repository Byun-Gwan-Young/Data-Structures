# LinkedList - deleteAtLinkedList 버그 수정

## 수정 내용

### 1. 루프 범위 오류 수정

**수정 전**
```c
for (int i = 0; i < at; i++) {
    nPtr = nPtr->next;
}
```

**수정 후**
```c
for (int i = 0; i < at - 1; i++) {
    nPtr = nPtr->next;
}
```

**이유:**  
`else` 블록에서 노드를 삭제하려면 `nPtr`이 삭제할 노드의 **이전 노드**를 가리켜야 한다.  
기존 코드는 루프가 `at`번 돌아 `nPtr`이 삭제할 노드 자체로 이동했기 때문에, `nPtr->next`가 잘못된 노드를 가리켜 오류(Segmentation Fault)가 발생했다.  
`at - 1`번 루프로 수정하여 `nPtr`이 삭제 대상의 이전 노드에서 멈추도록 했다.

---

### 2. size 갱신 누락 수정

**수정 전**  
노드 삭제 후 `li->size` 갱신 없음

**수정 후**
```c
li->size--;
```

**이유:**  
`printLinkedList`는 `li->size`를 기준으로 반복하기 때문에, 노드를 삭제한 뒤 `size`를 줄이지 않으면 이미 해제된 메모리에 접근하게 된다.

---

### 3. 반환값 누락 수정

**수정 전**  
`return` 문 없음

**수정 후**
```c
return li;
```

**이유:**  
함수 반환형이 `LinkedList*`인데 `return`이 없으면 오류(undefined behavior)가 발생한다.
