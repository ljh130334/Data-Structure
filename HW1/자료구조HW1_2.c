/*
* 학번: 202214314
* 이름: 이지현
* 실행환경: Mac
* 
* [2번 문제: 피보나치 수열 프로그램 구현]
* 이 프로그램은 피보나치 수열 계산을 두 가지 방식으로 구현합니다:
* 1. 재귀(recursion) 방식 구현
* 2. 반복(iteration) 방식 구현
* 
* 입력값(1~10)에 대한 각 방식의 계산 결과를 출력합니다.
*/

#include <stdio.h>

// [2번 문제] 재귀(recursion) 방식으로 구현한 피보나치 수열 함수
// F(n) = F(n-1) + F(n-2) (n > 2일 때)
// F(1) = 1, F(2) = 1 (base case)
long long fibonacci_recursive(int n) {
    // base case: 첫 번째와 두 번째 피보나치 수는 1
    if (n <= 0) {
        return 0;
    } else if (n == 1 || n == 2) {
        return 1;
    }
    // recursive step: F(n) = F(n-1) + F(n-2)
    else {
        return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
    }
}

// [2번 문제] 반복(iteration) 방식으로 구현한 피보나치 수열 함수
// 반복문을 사용하여 피보나치 수열의 n번째 항을 계산
long long fibonacci_iterative(int n) {
    if (n <= 0) {
        return 0;
    } else if (n == 1 || n == 2) {
        return 1;
    }
    
    long long fib_prev = 1;    // F(1) = 1
    long long fib_curr = 1;    // F(2) = 1
    long long fib_next;
    
    // 3번째 항부터 n번째 항까지 계산
    for (int i = 3; i <= n; i++) {
        fib_next = fib_curr + fib_prev;  // F(i) = F(i-1) + F(i-2)
        fib_prev = fib_curr;             // 다음 단계를 위해 값을 갱신
        fib_curr = fib_next;
    }
    
    return fib_curr;
}

int main() {
    int n;
    
    // 사용자로부터 n 값 입력 받기
    printf("피보나치 수열의 항 개수 n 값을 입력하세요 (1~10): ");
    scanf("%d", &n);
    
    // 입력값 검증
    if (n < 1 || n > 10) {
        printf("입력 범위는 1부터 10까지입니다.\n");
        return 1;
    }
    
    printf("\n--- [2번 문제] 1부터 %d까지의 피보나치 수열 계산 결과 ---\n", n);
    printf("%-5s %-20s %20s\n", "n", "Recursive Version", "Iterative Version");
    printf("---------------------------------------------------\n");
    
    // 1부터 n까지 피보나치 수열 계산 결과 출력
    for (int i = 1; i <= n; i++) {
        // 2번 문제 출력: i번째 피보나치 수 (재귀 및 반복 버전)
        long long recursive_result = fibonacci_recursive(i);
        long long iterative_result = fibonacci_iterative(i);
        printf("%-5d %-20lld %20lld\n", i, recursive_result, iterative_result);
    }
    
    return 0;
}