/*
* 학번: 202214314
* 이름: 이지현
* 실행환경: Mac
* 
* [4번 문제: Factorial Iteration의 큰 값 처리 시연]
* 이 프로그램은 factorial 반복(iteration) 구현에서 n값이 매우 커도
* 실행은 되지만 결과값이 오버플로우되어 정확하지 않음을 시연합니다.
* 반복문은 스택 오버플로우 없이 끝까지 실행되지만, 산술 오버플로우가 발생합니다.
*/

#include <stdio.h>

// [4번 문제] 반복(iteration) 방식으로 구현한 factorial 함수
// 이 함수는 스택 오버플로우는 발생하지 않지만, 산술 오버플로우는 발생함
unsigned long long factorial_iterative(int n) {
    unsigned long long result = 1;
    
    printf("[4번 문제] n=%d에 대한 factorial 계산 시작\n", n);
    
    // 1부터 n까지 모든 수를 곱함
    // unsigned long long 범위를 초과해도 루프는 계속 실행됨
    for (int i = 1; i <= n; i++) {
        result *= i;
        
        // 진행 상황을 보여주기 위해 일정 간격으로 중간 결과 출력
        if (i % 500 == 0 || i == n) {
            printf("i=%d 단계에서의 중간 결과: %llu\n", i, result);
        }
        
        // 오버플로우 발생 여부 확인
        // 이전 결과에 i를 곱했는데 값이 작아지면 오버플로우 발생
        if (result / i != result / i * i / i) {
            printf("i=%d에서 오버플로우 발생! 이후 결과값은 정확하지 않음\n", i);
        }
    }
    
    return result;
}

int main() {
    int n;
    
    printf("[4번 문제] Factorial Iteration의 큰 값 처리 시연\n\n");
    printf("factorial의 반복 버전은 n이 매우 커도 스택 오버플로우 없이 실행되지만,\n");
    printf("결과값이 자료형 범위를 초과하면 산술 오버플로우가 발생합니다.\n\n");
    
    printf("테스트할 n 값을 입력하세요 (권장: 5000): ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("양수를 입력해주세요.\n");
        return 1;
    }
    
    printf("\n반복 버전으로 factorial(%d) 계산 시작...\n\n", n);
    
    unsigned long long result = factorial_iterative(n);
    
    printf("\n계산 완료!\n");
    printf("factorial(%d)의 반복 계산 결과: %llu\n", n, result);
    printf("(주의: unsigned long long의 범위는 약 18자리 숫자까지만 정확합니다.)\n");
    printf("n이 20보다 크면 결과값은 오버플로우로 인해 정확하지 않습니다.\n");
    
    // 비교를 위해 작은 값의 factorial 정확한 결과 출력
    printf("\n비교: factorial(20)의 정확한 값은 2432902008176640000입니다.\n");
    
    return 0;
}