/*
 * 학번: 202214314
 * 이름: 이지현
 * 실행환경: Mac
 *
 * [문제 (3) 설명]
 * - 동적 배열(Dynamic Array)을 이용하여 스택을 구현할 때,
 *   배열의 용량(capacity)이 가득 차면 2배로 재할당(resize)합니다.
 * - 본 코드는 n을 2의 거듭제곱 형태(예: 2^3 ~ 2^12 등)로 증가시키면서,
 *   push 연산을 n번 반복했을 때 걸리는 전체 시간을 측정하여,
 *   배열이 2배로 늘어나는 시점(=재할당 시점)에서 수행 시간이
 *   다른 n 값들에 비해 증가하는지를 관찰할 수 있도록 설계되었습니다.
 *
 * [실험 아이디어]
 * 1) n을 2^3, 2^4, 2^5, ..., 2^12 등으로 순차적으로 설정.
 * 2) 초기 용량 1인 동적 배열 기반 스택(createStack(1))을 생성.
 * 3) push n번을 반복하며 총 걸린 시간을 clock() 함수를 통해 측정.
 *    - (end - start) * 1000 / CLOCKS_PER_SEC 로 밀리초(ms) 단위 변환
 * 4) 용량이 부족해질 때마다 2배로 확장(resize)되는 과정에서, 실제로 실행 시간이
 *    눈에 띄게 증가하는 순간이 있는지 관찰 (보고서에서 그래프나 표로 시각화).
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ===================================================== */
/*           동적 배열 기반 Stack (Dynamic Array)           */
/* ===================================================== */

// 동적 배열 기반 스택 구조체 정의 (capacity 가득 차면 2배로 증가)
typedef struct {
    int *arr;       // 실제 저장 공간
    int capacity;   // 현재 배열 용량
    int top;        // 스택의 크기(다음에 push될 인덱스)
} DynArrayStack;

// 스택 생성
DynArrayStack* createStack(int initialCapacity) {
    DynArrayStack* stack = (DynArrayStack*)malloc(sizeof(DynArrayStack));
    if (!stack) {
        printf("메모리 할당 오류 (DynArrayStack)\n");
        exit(1);
    }
    stack->arr = (int*)malloc(sizeof(int) * initialCapacity);
    if (!stack->arr) {
        printf("메모리 할당 오류 (arr)\n");
        free(stack);
        exit(1);
    }
    stack->capacity = initialCapacity;
    stack->top = 0;
    return stack;
}

// 스택 재할당: capacity를 2배로 확장
void resizeStack(DynArrayStack* stack) {
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
void push(DynArrayStack* stack, int value) {
    if (stack->top == stack->capacity) {
        resizeStack(stack);
    }
    stack->arr[stack->top++] = value;
}

// pop 1회
int pop(DynArrayStack* stack) {
    if (stack->top == 0) {
        return -1; // 언더플로우
    }
    return stack->arr[--stack->top];
}

// 스택 해제
void freeStack(DynArrayStack* stack) {
    if (stack) {
        if (stack->arr) free(stack->arr);
        free(stack);
    }
}

/* ===================================================== */
/*                    main 함수 테스트                      */
/* ===================================================== */

int main(void) {
    // n을 2의 거듭제곱 형태로 증가시키며 실험
    int testPowers[] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int numPowers = sizeof(testPowers) / sizeof(testPowers[0]);

    printf("[문제 3] Dynamic Array 스택: 2배 증가 시점 성능 측정\n");
    for (int i = 0; i < numPowers; i++) {
        int exponent = testPowers[i];
        int n = 1 << exponent;
        
        // 스택 생성
        DynArrayStack* stack = createStack(1);
        
        // 시간 측정 시작
        clock_t start = clock();
        
        // push n번
        for (int k = 0; k < n; k++) {
            // 예: 단순히 k를 push
            push(stack, k);
        }
        
        // 시간 측정 종료
        clock_t end = clock();
        double elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;

        printf("n = 2^%d = %d 일 때, push %d번 수행 -> 총 시간: %.4f ms\n",
            exponent, n, n, elapsed_ms);

        freeStack(stack);
    }

    return 0;
}