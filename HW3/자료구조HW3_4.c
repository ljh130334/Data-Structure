/*
 * 학번: 202214314
 * 이름: 이지현
 * 실행환경: Mac
 *
 * [문제 (4) 설명]
 * - (1)번 실험과 비교: 이번에는 push 1번, pop 1번을 교대로
 *   (a) 100번, (b) 200번, ..., (n) ~1,000만 번 수행하여 실행 시간을 비교합니다.
 * - 즉, 'push(1) → pop(1) → push(2) → pop(2) → ... → push(n) → pop(n)' 식으로
 *   i=1부터 i=n까지 반복하면서 전체 소요 시간을 clock()으로 측정한 뒤,
 *   (end - start) * 1000 / CLOCKS_PER_SEC 로 밀리초(ms) 단위로 변환하여 출력합니다.
 * - 동적 배열(Dynamic Array)과 연결 리스트(Linked List)로 각각 구현된 스택에 대해
 *   동일한 실험을 수행하고, (1)번 문제와도 결과를 비교하여 결론을 제시할 수 있습니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ===================================================== */
/*           동적 배열 기반 Stack (Dynamic Array)           */
/* ===================================================== */

// 동적 배열 기반 스택 구조체 정의 (초기 용량을 1로 시작)
typedef struct {
    int *arr;        // 데이터를 저장할 배열 포인터
    int capacity;    // 현재 배열의 용량
    int top;         // 스택의 크기(다음에 push될 인덱스)
} DynArrayStack;

// 스택 생성: 초기 용량을 인자로 받아 생성
DynArrayStack* createArrayStack(int initialCapacity) {
    DynArrayStack* stack = (DynArrayStack*)malloc(sizeof(DynArrayStack));
    if (!stack) {
        printf("메모리 할당 오류 (stack 구조체)\n");
        exit(1);
    }
    stack->arr = (int*)malloc(sizeof(int) * initialCapacity);
    if (!stack->arr) {
        printf("메모리 할당 오류 (stack 배열)\n");
        free(stack);
        exit(1);
    }
    stack->capacity = initialCapacity;
    stack->top = 0;
    return stack;
}

// 스택 용량 재할당
void resizeArrayStack(DynArrayStack* stack) {
    int newCapacity = stack->capacity * 2;
    int* newArr = (int*)realloc(stack->arr, sizeof(int) * newCapacity);
    if (!newArr) {
        printf("realloc 오류\n");
        free(stack->arr);
        free(stack);
        exit(1);
    }
    stack->arr = newArr;
    stack->capacity = newCapacity;
}

// push 연산: 스택이 가득 찼으면 확장 후 요소 추가
void arrayPush(DynArrayStack* stack, int value) {
    if (stack->top == stack->capacity) {
        resizeArrayStack(stack);
    }
    stack->arr[stack->top++] = value;
}

// pop 연산: 스택이 비었으면 -1 리턴, 아니면 top 요소 반환
int arrayPop(DynArrayStack* stack) {
    if (stack->top == 0)
        return -1;
    return stack->arr[--stack->top];
}

// 스택 메모리 해제
void freeArrayStack(DynArrayStack* stack) {
    if (stack) {
        if (stack->arr)
            free(stack->arr);
        free(stack);
    }
}

/* ===================================================== */
/*           연결 리스트 기반 Stack (Linked List)            */
/* ===================================================== */

// 연결 리스트 노드 정의
typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

// push 연산: 새로운 노드를 생성하여 list의 앞에 삽입
void listPush(ListNode** head, int value) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (!newNode) {
        printf("메모리 할당 오류 (ListNode)\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = *head;
    *head = newNode;
}

// pop 연산: list의 head를 제거하고, 해당 데이터를 반환
int listPop(ListNode** head) {
    if (*head == NULL)
        return -1;
    ListNode* temp = *head;
    int value = temp->data;
    *head = temp->next;
    free(temp);
    return value;
}

// 연결 리스트 전체 해제
void freeListStack(ListNode** head) {
    while (*head != NULL) {
        ListNode* temp = *head;
        *head = temp->next;
        free(temp);
    }
}

/* ===================================================== */
/*                    main 함수 (문제 4)                   */
/* ===================================================== */

int main(void) {
    int testCases[] = {100, 200, 300, 400, 500};
    int numCases = sizeof(testCases) / sizeof(testCases[0]);
    
    int i, j;

    printf("[문제 4] ==== Dynamic Array Stack: push/pop 교대 실험 ====\n");
    for (i = 0; i < numCases; i++) {
        int n = testCases[i];
        // 초기 용량 1로 동적 배열 스택 생성
        DynArrayStack* arrStack = createArrayStack(1);

        clock_t start = clock();

        // push(1), pop(1), push(2), pop(2), ..., push(n), pop(n)
        // 각 i에 대해 push i번 + pop i번
        for (int x = 1; x <= n; x++) {
            // push x번
            for (j = 0; j < x; j++) {
                arrayPush(arrStack, j);
            }
            // pop x번
            for (j = 0; j < x; j++) {
                arrayPop(arrStack);
            }
        }

        clock_t end = clock();
        double elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;

        // 계산된 총 연산 횟수 = 2 * (1 + 2 + ... + n) = n*(n+1)
        printf("[Dynamic Array] n=%d번까지 (push x + pop x 교대), 총 실행 시간: %.2f ms\n", n, elapsed_ms);
        
        freeArrayStack(arrStack);
    }

    printf("\n[문제 4] ==== Linked List Stack: push/pop 교대 실험 ====\n");
    for (i = 0; i < numCases; i++) {
        int n = testCases[i];
        ListNode* listStack = NULL;

        clock_t start = clock();

        // push(1), pop(1), push(2), pop(2), ..., push(n), pop(n)
        for (int x = 1; x <= n; x++) {
            // push x번
            for (j = 0; j < x; j++) {
                listPush(&listStack, j);
            }
            // pop x번
            for (j = 0; j < x; j++) {
                listPop(&listStack);
            }
        }

        clock_t end = clock();
        double elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;

        printf("[Linked List] n=%d번까지 (push x + pop x 교대), 총 실행 시간: %.2f ms\n", n, elapsed_ms);

        freeListStack(&listStack);
    }

    return 0;
}