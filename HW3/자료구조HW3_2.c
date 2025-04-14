/*
 * 학번: 202214314
 * 이름: 이지현
 * 실행환경: Mac
 *
 * [문제 (2) 설명]
 * - 문제 (1)번 실험을 변경하여, dynamic array와 linked list에서
 *   push 1회, pop 1회 수행 시간의 time complexity를 측정할 수 있도록 실험을 설계합니다.
 * - 즉, '연산 단위(1회 push, 1회 pop)'의 평균 수행 시간을 구해,
 *   수업 시간에 배운 O(1) 등과 실제 성능을 비교합니다.
 * - 보고서에는 실험 설계와, 측정된 결과를 time complexity와 대조하여 결론을 제시합니다.
 *
 * [실험 아이디어]
 * 1) push 1회를 특정 횟수(N번)만큼 반복하여 전체 소요 시간을 측정.
 *    - 총 걸린 시간을 N으로 나누어 1회 push 평균 시간을 구함.
 * 2) pop 1회도 같은 방식으로 특정 횟수(N번) 반복하여 평균 수행 시간 측정.
 * 3) dynamic array 방식(stack)과 linked list 방식(stack)에 대해 각각 수행.
 * 4) N을 여러 값(예: 10,000 / 100,000 / 1,000,000)으로 변화시키며 측정하면,
 *    n 증가에 따른 시간 복잡도 경향도 관찰 가능.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ===================================================== */
/*           동적 배열 기반 Stack (Dynamic Array)           */
/* ===================================================== */

// 동적 배열 기반 스택 구조체 정의
typedef struct {
    int *arr;        // 실제 저장 공간
    int capacity;    // 배열 용량
    int top;         // 현재 스택 크기
} DynArrayStack;

// 스택 생성
DynArrayStack* createArrayStack(int initialCapacity) {
    DynArrayStack* stack = (DynArrayStack*)malloc(sizeof(DynArrayStack));
    if (!stack) {
        printf("메모리 할당 오류(DynArrayStack 구조체)\n");
        exit(1);
    }
    stack->arr = (int*)malloc(sizeof(int) * initialCapacity);
    if (!stack->arr) {
        printf("메모리 할당 오류(DynArrayStack 배열)\n");
        free(stack);
        exit(1);
    }
    stack->capacity = initialCapacity;
    stack->top = 0;
    return stack;
}

// 스택 재할당: capacity를 2배로 확장
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

// push 1회
void arrayPush(DynArrayStack* stack, int value) {
    if (stack->top == stack->capacity) {
        resizeArrayStack(stack);
    }
    stack->arr[stack->top++] = value;
}

// pop 1회
int arrayPop(DynArrayStack* stack) {
    if (stack->top == 0) {
        return -1;
    }
    return stack->arr[--stack->top];
}

// 동적 배열 스택 해제
void freeArrayStack(DynArrayStack* stack) {
    if (!stack) return;
    if (stack->arr) free(stack->arr);
    free(stack);
}

/* ===================================================== */
/*           연결 리스트 기반 Stack (Linked List)            */
/* ===================================================== */

// 연결 리스트 노드 정의
typedef struct ListNode {
    int data;
    struct ListNode* next;
} ListNode;

// push 1회 (맨 앞 삽입)
void listPush(ListNode** head, int value) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (!newNode) {
        printf("메모리 할당 오류(ListNode)\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = *head;
    *head = newNode;
}

// pop 1회 (맨 앞 삭제)
int listPop(ListNode** head) {
    if (*head == NULL) {
        return -1; // 언더플로우
    }
    ListNode* temp = *head;
    int value = temp->data;
    *head = temp->next;
    free(temp);
    return value;
}

// 연결 리스트 전체 해제
void freeListStack(ListNode** head) {
    while (*head) {
        ListNode* temp = *head;
        *head = temp->next;
        free(temp);
    }
}

/* ===================================================== */
/*                    main 함수 테스트                      */
/* ===================================================== */

int main(void) {
    int testCounts[] = {10000, 100000, 500000};
    int numTest = sizeof(testCounts) / sizeof(testCounts[0]);

    for (int i = 0; i < numTest; i++) {
        int N = testCounts[i];

        // ========== [문제 (2)] Dynamic Array 스택 테스트 ==========
        // 1) push 1회를 N번 반복 → 총 시간 / N = 1회 push 평균시간
        DynArrayStack* arrStack = createArrayStack(1);

        clock_t startPush = clock();
        for (int k = 0; k < N; k++) {
            arrayPush(arrStack, k);
        }
        clock_t endPush = clock();
        double totalPushTime = (double)(endPush - startPush) * 1000.0 / CLOCKS_PER_SEC;
        double avgPushTime = totalPushTime / N;

        // pop 1회를 N번 반복 → 총 시간 / N = 1회 pop 평균시간
        clock_t startPop = clock();
        for (int k = 0; k < N; k++) {
            arrayPop(arrStack);
        }
        clock_t endPop = clock();
        double totalPopTime = (double)(endPop - startPop) * 1000.0 / CLOCKS_PER_SEC;
        double avgPopTime = totalPopTime / N;

        // 출력
        printf("\n[문제 2] [Dynamic Array] N=%d\n", N);
        printf(" -> push 1회 평균: %.6f ms, pop 1회 평균: %.6f ms\n", avgPushTime, avgPopTime);

        freeArrayStack(arrStack);

        // ========== [문제 (2)] Linked List 스택 테스트 ==========
        // 1) push 1회를 N번 반복
        ListNode* listStack = NULL;

        clock_t startPush2 = clock();
        for (int k = 0; k < N; k++) {
            listPush(&listStack, k);
        }
        clock_t endPush2 = clock();
        double totalPushTime2 = (double)(endPush2 - startPush2) * 1000.0 / CLOCKS_PER_SEC;
        double avgPushTime2 = totalPushTime2 / N;

        // pop 1회를 N번 반복
        clock_t startPop2 = clock();
        for (int k = 0; k < N; k++) {
            listPop(&listStack);
        }
        clock_t endPop2 = clock();
        double totalPopTime2 = (double)(endPop2 - startPop2) * 1000.0 / CLOCKS_PER_SEC;
        double avgPopTime2 = totalPopTime2 / N;

        // 출력
        printf("[문제 2] [Linked List] N=%d\n", N);
        printf(" -> push 1회 평균: %.6f ms, pop 1회 평균: %.6f ms\n", avgPushTime2, avgPopTime2);

        freeListStack(&listStack);
    }

    return 0;
}