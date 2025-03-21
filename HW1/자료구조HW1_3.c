/*
* 학번: 202214314
* 이름: 이지현
* 실행환경: Mac
* 
* [3번 문제: Factorial Recursion의 Stack Overflow 시연]
* 이 프로그램은 factorial 재귀 구현에서 n값이 커질 때 발생하는
* stack overflow 현상을 시연합니다.
* 입력 값이 커짐에 따라 재귀 호출 깊이가 깊어지고,
* 결국 스택 메모리 한계를 초과하여 런타임 에러가 발생합니다.
*/

#include <stdio.h>

// [3번 문제] 재귀(recursion) 방식으로 구현한 factorial 함수
// 의도적으로 unsigned long long 대신 long long을 사용해 오버플로우 발생 가능
long long factorial_recursive(int n) {
    // 스택 오버플로우 발생 여부를 표시하기 위한 변수 (실제 스택에 메모리 추가)
    char stack_usage[1000]; // 스택 사용량을 늘리기 위한 큰 지역 배열
    
    // 현재 n 값 출력 (깊은 재귀 호출을 확인하기 위해)
    printf("Calculating factorial for n = %d\n", n);
    
    // 배열 초기화 (스택 메모리 사용)
    for (int i = 0; i < 1000 && i < n; i++) {
        stack_usage[i] = i % 256;
    }
    
    // base case: 0 또는 1의 팩토리얼은 1이다
    if (n == 0 || n == 1) {
        return 1;
    }
    // recursive step: n! = n * (n-1)!
    else {
        return n * factorial_recursive(n - 1);
    }
}

// [3번 문제] 반복(iteration) 방식으로 구현한 factorial 함수
// 이 함수는 비교를 위해 포함되었으며, 스택 오버플로우가 발생하지 않음
unsigned long long factorial_iterative(int n) {
    unsigned long long result = 1;
    
    for (int i = 1; i <= n && i <= 20; i++) { // 20으로 제한하여 오버플로우 방지
        result *= i;
    }
    
    return result;
}

int main() {
    int n;
    
    printf("[3번 문제] Factorial Recursion의 Stack Overflow 시연\n\n");
    printf("factorial 재귀 버전에서 n값이 증가함에 따라 스택 오버플로우가 발생합니다.\n");
    printf("일반적으로 n이 특정 값(컴퓨터 환경에 따라 다름) 이상이면 런타임 에러가 발생합니다.\n\n");
    
    printf("테스트할 n 값을 입력하세요 (1000 이상 권장): ");
    scanf("%d", &n);
    
    printf("\n[주의] n=%d에 대한 factorial 재귀 계산을 시작합니다.\n", n);
    printf("값이 매우 크면 스택 오버플로우로 인해 프로그램이 종료될 수 있습니다.\n\n");
    
    printf("재귀 호출 시작...\n");
    
    // 스택 오버플로우 발생 가능성 경고
    if (n > 1000) {
        printf("경고: n=%d는 매우 큰 값으로, 스택 오버플로우가 발생할 가능성이 높습니다.\n", n);
    }
    
    // 스택 오버플로우를 포착하기 위한 try-catch 구문 대신
    // C에서는 실행 중에 에러가 발생하면 프로그램이 종료됨
    long long result = factorial_recursive(n);
    
    // 이 부분은 스택 오버플로우가 발생하지 않았을 경우에만 실행됨
    printf("\n스택 오버플로우 없이 계산 완료!\n");
    printf("factorial(%d)의 결과는 %lld입니다.\n", n, result);
    
    // 값이 20!보다 크면 오버플로우 경고 표시
    if (n > 20) {
        printf("factorial(%d)의 결과가 표시되지만, long long 자료형의 범위를 초과하여 정확하지 않습니다.\n", n);
        printf("long long의 오버플로우로 인해 결과값 %lld는 실제 %d!의 정확한 값이 아닙니다.\n", result, n);
    }
    
    printf("\n비교: 반복 버전은 스택 오버플로우가 발생하지 않습니다.\n");
    printf("factorial_iterative(20) = %llu (20!까지만 정확히 계산)\n", factorial_iterative(20));
    
    return 0;
}