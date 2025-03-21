/*
* 학번: 202214314
* 이름: 이지현
* 실행환경: Mac
* 
* [1번 문제: factorial 프로그램 구현]
* 이 프로그램은 수업 시간에 배운 factorial 계산을 두 가지 방식으로 구현합니다:
* 1. 재귀(recursion) 방식 구현
* 2. 반복(iteration) 방식 구현
* 
* 입력값(1~10)에 대한 각 방식의 계산 결과를 출력합니다.
*/

#include <stdio.h>

// [1번 문제] 재귀(recursion) 방식으로 구현한 factorial 함수
// n! = n * (n-1)! (n > 1일 때)
// 0! = 1! = 1 (base case)
long long factorial_recursive(int n) {
    // base case: 0 또는 1의 팩토리얼은 1이다
    if (n == 0 || n == 1) {
        return 1;
    }
    // recursive step: n! = n * (n-1)!
    else {
        return n * factorial_recursive(n - 1);
    }
}

// [1번 문제] 반복(iteration) 방식으로 구현한 factorial 함수
// 반복문을 사용하여 n!을 계산
long long factorial_iterative(int n) {
    long long result = 1; // 결과를 저장할 변수 (1로 초기화)
    
    // n부터 1까지 곱셈을 반복
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    
    return result;
}

int main() {
    int n;
    
    // 사용자로부터 n 값 입력 받기
    printf("팩토리얼을 계산할 n 값을 입력하세요 (1~10): ");
    scanf("%d", &n);
    
    // 입력값 검증
    if (n < 1 || n > 10) {
        printf("입력 범위는 1부터 10까지입니다.\n");
        return 1;
    }
    
    printf("\n--- [1번 문제] 1부터 %d까지의 팩토리얼 계산 결과 ---\n", n);
    printf("%-5s %-20s %20s\n", "n", "Recursive Version", "Iterative Version");
    printf("---------------------------------------------------\n");
    
    // 1부터 n까지 factorial 계산 결과 출력
    for (int i = 1; i <= n; i++) {
        long long recursive_result = factorial_recursive(i);
        long long iterative_result = factorial_iterative(i);
        
        // 1번 문제 출력: i의 팩토리얼 값 (재귀 및 반복 버전)
        printf("%-5d %-20lld %20lld\n", i, recursive_result, iterative_result);
    }
    
    return 0;
}