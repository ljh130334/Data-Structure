/*
* 학번: 202214314
* 이름: 이지현
* 실행환경: Mac
* 
* [5번 문제: 프로그램 실행 시 메모리 구성과 스택 영역 분석]
* 이 프로그램은 C 프로그램의 메모리 구성을 설명하고
* 스택 영역의 크기를 테스트하여 3번 문제의 스택 오버플로우 현상과 연결시킵니다.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 전역 변수 (Data 영역에 저장)
int global_variable = 100;
char global_array[1000] = "이것은 전역 배열입니다.";

// 상수 데이터 (Code 영역에 저장)
const char* constant_string = "이것은 상수 문자열입니다.";

// 재귀 함수 - 스택 영역 테스트용
int recursion_test(int depth, int max_depth, int stack_size) {
    // 스택에 할당되는 지역 변수
    char local_array[stack_size]; // 의도적으로 큰 배열 선언
    
    // 지역 변수 초기화 (메모리 사용 표시)
    memset(local_array, 'A', stack_size - 1);
    local_array[stack_size - 1] = '\0';
    
    // 현재 깊이 출력
    printf("재귀 깊이: %d, 스택 메모리 사용: %d 바이트\n", depth, depth * stack_size);
    
    // 종료 조건
    if (depth >= max_depth) {
        printf("최대 재귀 깊이 %d에 도달했습니다. 정상 종료합니다.\n", max_depth);
        return depth;
    }
    
    // 재귀 호출
    return recursion_test(depth + 1, max_depth, stack_size);
}

// 동적 메모리 할당 함수 - Heap 영역 테스트용
void heap_test(int size) {
    // Heap 영역에 메모리 할당
    char* dynamic_memory = (char*)malloc(size);
    
    if (dynamic_memory != NULL) {
        printf("Heap에 %d 바이트 메모리 할당 성공\n", size);
        
        // 할당된 메모리 사용
        memset(dynamic_memory, 'B', size - 1);
        dynamic_memory[size - 1] = '\0';
        
        // 첫 10바이트만 출력
        printf("Heap 메모리 내용(첫 10바이트): %.10s...\n", dynamic_memory);
        
        // 메모리 해제
        free(dynamic_memory);
        printf("Heap 메모리 해제 완료\n");
    } else {
        printf("Heap에 %d 바이트 메모리 할당 실패\n", size);
    }
}

int main() {
    // 지역 변수 (Stack 영역에 저장)
    int local_variable = 200;
    char local_array[100] = "이것은 지역 배열입니다.";
    
    printf("[5번 문제] 프로그램의 메모리 구성 분석\n\n");
    
    // 1. 프로그램 메모리 공간 설명
    printf("===== 프로그램 메모리 공간 설명 =====\n");
    printf("1. Code 영역: 프로그램의 실행 코드와 상수가 저장됩니다.\n");
    printf("   - 상수 문자열: \"%s\"\n", constant_string);
    printf("   - 이 영역은 읽기 전용이며 프로그램 실행 중 변경되지 않습니다.\n\n");
    
    printf("2. Data 영역: 전역 변수와 정적 변수가 저장됩니다.\n");
    printf("   - 전역 변수: global_variable = %d\n", global_variable);
    printf("   - 전역 배열: \"%s\"\n", global_array);
    printf("   - 이 영역은 프로그램 시작 시 할당되고 종료 시 해제됩니다.\n\n");
    
    printf("3. Heap 영역: 동적으로 할당된 메모리가 저장됩니다.\n");
    printf("   - malloc, calloc, realloc 등으로 할당한 메모리가 여기에 저장됩니다.\n");
    printf("   - 프로그래머가 직접 할당하고 해제해야 합니다.\n");
    heap_test(1024); // Heap 영역 테스트
    printf("\n");
    
    printf("4. Stack 영역: 함수 호출 정보와 지역 변수가 저장됩니다.\n");
    printf("   - 지역 변수: local_variable = %d\n", local_variable);
    printf("   - 지역 배열: \"%s\"\n", local_array);
    printf("   - 함수 호출 시마다 스택 프레임이 쌓이고 함수 종료 시 제거됩니다.\n");
    printf("   - 재귀 함수에서 스택이 과도하게 쌓이면 스택 오버플로우가 발생합니다.\n\n");
    
    // 2. Stack 영역 크기 테스트
    printf("===== Stack 영역 크기 테스트 =====\n");
    printf("스택의 크기는 운영체제와 컴파일러 설정에 따라 다릅니다.\n");
    printf("일반적으로 Windows에서는 1MB, Linux에서는 8MB 정도입니다.\n");
    printf("Visual Studio Code에서 디버그 모드와 릴리즈 모드의 차이점:\n");
    printf("  - 디버그 모드: 디버깅 정보가 추가되어 스택 사용량이 더 많습니다.\n");
    printf("  - 릴리즈 모드: 최적화되어 스택 사용량이 적습니다.\n\n");
    
    // 스택 테스트 - 작은 크기로 시작
    int stack_size = 1000; // 각 함수 호출마다 1KB 사용
    int max_depth = 10;    // 초기 테스트는 10번 정도의 깊이로 제한
    
    printf("스택 테스트 시작 (각 호출마다 %dB 사용, 최대 깊이: %d)\n", stack_size, max_depth);
    int reached_depth = recursion_test(1, max_depth, stack_size);
    printf("도달한 재귀 깊이: %d, 총 스택 사용 추정: %d 바이트\n\n", reached_depth, reached_depth * stack_size);
    
    printf("===== 3번 문제와의 연관성 =====\n");
    printf("3번 문제에서 factorial 재귀 버전이 큰 n에서 스택 오버플로우가 발생하는 이유:\n");
    printf("1. 각 재귀 호출마다 스택에 새로운 스택 프레임이 생성됩니다.\n");
    printf("2. 스택 프레임에는 매개변수, 반환 주소, 지역 변수 등이 저장됩니다.\n");
    printf("3. 3번 문제에서는 의도적으로 큰 지역 배열(char stack_usage[1000])을 선언하여\n");
    printf("   스택 사용량을 증가시켰습니다.\n");
    printf("4. n이 매우 큰 경우, 재귀 깊이가 깊어져 스택 메모리가 고갈되고\n");
    printf("   'segmentation fault'가 발생합니다.\n\n");
    
    printf("Visual Studio Code에서 디버그 모드와 릴리즈 모드의 차이:\n");
    printf("1. 디버그 모드에서는 스택 프레임에 디버깅 정보가 추가되어 더 많은 메모리를 사용합니다.\n");
    printf("2. 릴리즈 모드에서는 컴파일러 최적화로 인해 불필요한 변수가 제거되고,\n");
    printf("   일부 재귀 호출이 꼬리 재귀 최적화를 통해 제거될 수 있습니다.\n");
    printf("3. 따라서 같은 코드라도 디버그 모드에서는 더 일찍 스택 오버플로우가 발생하고,\n");
    printf("   릴리즈 모드에서는 더 많은 재귀 깊이를 처리할 수 있습니다.\n");
    
    return 0;
}