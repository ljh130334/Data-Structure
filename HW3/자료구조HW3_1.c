/*
 * 학번: 202214314
 * 이름: 이지현
 * 실행환경: Mac
 *
 * [과제 설명]
 * - 수업 시간에 배운 stack을 dynamic array 방식과 linked list 방식으로 각각 구현합니다.
 * - Dynamic array 방식의 경우, 초기 용량을 1로 시작하고, 스택이 가득 차면 용량을 2배로 재할당하는 방식을 사용합니다.
 * - Linked list 방식의 경우, 노드를 동적 할당하여 push/pop 연산을 구현합니다.
 *
 * [실험 조건]
 * 1) 단계별로 push와 pop 연산 횟수를 증가시키며 테스트합니다.
 *    예를 들어, 첫 단계는 push 100번 + pop 100번, 그 다음 단계는 push 200번 + pop 200번, 
 *    이후 push 300번/pop 300번, ... 이런 식으로 진행합니다.
 * 2) 각 단계별로 전체 push/pop 연산에 걸린 시간을 clock() 함수를 이용하여 측정하고,
 *    (end - start) * 1000 / CLOCKS_PER_SEC 로 밀리초(ms) 단위로 변환해 출력합니다.
 *
 * [구현 및 제출]
 * - 이 파일에서는 Dynamic Array 방식과 Linked List 방식의 두 가지 stack 구현을 모두 포함하였습니다.
 * - main() 함수에서는 각각의 방식에 대해 테스트를 진행한 후, 수행 시간 결과를 출력합니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ===================================================== */
/*              동적 배열 기반 Stack (Dynamic Array)              */
/* ===================================================== */

// 동적 배열 기반 스택 구조체 정의 (초기 용량을 1로 시작)
typedef struct {
    int *arr;        // 데이터를 저장할 배열 포인터
    int capacity;    // 현재 배열의 용량
    int top;         // 다음에 push 될 인덱스 (현재 스택 크기)
} DynArrayStack;

// 스택 생성: 초기 용량을 인자로 받아 생성 (문제 요구: 초기 용량 = 1)
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

// 스택 용량 재할당 (현재 capacity의 2배로 확장)
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
        return -1; // 언더플로우 처리
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
/*               연결 리스트 기반 Stack (Linked List)             */
/* ===================================================== */

// 연결 리스트 노드 정의
typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

// 연결 리스트 기반 스택은 단순히 head 포인터를 사용하며, 맨 앞에 push/pop하는 방식으로 구현

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
        return -1; // 언더플로우 처리
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
/*                    main 함수 테스트                        */
/* ===================================================== */

int main(void) {
    // 테스트할 push/pop 횟수를 단계적으로 늘릴 배열
    int testCases[] = {100, 200, 300, 400, 500};
    int numCases = sizeof(testCases) / sizeof(testCases[0]);
    int i, j;
    
    printf("[문제 1] ==== Dynamic Array Stack 테스트 ====\n");
    for (i = 0; i < numCases; i++) {
        int n = testCases[i];
        // 초기 용량 1로 스택 생성 (과제 요구 사항)
        DynArrayStack* arrStack = createArrayStack(1);
        
        clock_t start = clock();
        // push n번
        for (j = 0; j < n; j++) {
            arrayPush(arrStack, j);
        }
        // pop n번
        for (j = 0; j < n; j++) {
            arrayPop(arrStack);
        }
        clock_t end = clock();
        double elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
        
        printf("[Dynamic Array Stack] push %d번 + pop %d번 -> 실행 시간: %.2f ms\n", n, n, elapsed_ms);
        freeArrayStack(arrStack);
    }
    
    printf("\n[문제 1] ==== Linked List Stack 테스트 ====\n");
    for (i = 0; i < numCases; i++) {
        int n = testCases[i];
        // 연결 리스트 스택의 head를 NULL로 초기화
        ListNode* listStack = NULL;
        
        clock_t start = clock();
        // push n번: 맨 앞 삽입
        for (j = 0; j < n; j++) {
            listPush(&listStack, j);
        }
        // pop n번
        for (j = 0; j < n; j++) {
            listPop(&listStack);
        }
        clock_t end = clock();
        double elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
        
        printf("[Linked List Stack] push %d번 + pop %d번 -> 실행 시간: %.2f ms\n", n, n, elapsed_ms);
        freeListStack(&listStack);
    }
    
    return 0;
}