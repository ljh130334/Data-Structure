/*
 * 학번: 202214314
 * 이름: 이지현
 * 실행환경: Mac
 * 
 * [1번 문제: 배열과 연결 리스트 성능 비교]
 *
 * <문제 설명>
 * 1) 배열(Array)과 단일 연결 리스트(Singly Linked List)의 접근 시간을 비교합니다.
 *    - 배열: 모든 요소를 순차 접근하여 누적된 시간을 측정합니다.
 *    - 연결 리스트: 첫 번째 요소의 인덱스를 1로 가정하고 순차 접근하며 누적된 시간을 측정합니다.
 * 2) 시간 측정은 clock() 함수를 사용하며, (end - start) * 1000 / CLOCKS_PER_SEC 로 밀리초 단위로 변환합니다.
 * 3) 각 데이터 구조에 대해 다양한 크기(예: 10,000, 100,000, 1,000,000)의 데이터를 사용하여 접근 시간을 측정합니다.
 * 4) REP_COUNT(1000회) 만큼 반복하여 전체 수행 시간을 측정합니다.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 
 #define REP_COUNT 1000
 
 // --------------------------------------------------------
 // 연결 리스트 (Linked List) 관련 함수들
 // --------------------------------------------------------
 
 // 단일 연결 리스트의 노드 구조체 정의
 typedef struct ListNode {
     int data;
     struct ListNode* next;
 } ListNode;
 
 // 새로운 노드를 생성하는 함수
 ListNode* createNode(int data) {
     ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
     if (newNode == NULL) {
         printf("메모리 할당 오류\n");
         exit(1);
     }
     newNode->data = data;
     newNode->next = NULL;
     return newNode;
 }
 
 // 연결 리스트의 마지막에 노드를 추가하는 함수 (O(n) 삽입)
 void insertAtEnd(ListNode** head, int data) {
     ListNode* newNode = createNode(data);
     
     // 리스트가 비어있는 경우
     if (*head == NULL) {
         *head = newNode;
         return;
     }
     
     // 마지막 노드 찾기
     ListNode* current = *head;
     while (current->next != NULL) {
         current = current->next;
     }
     
     // 마지막 노드의 다음에 새 노드 추가
     current->next = newNode;
 }
 
 // 연결 리스트의 메모리를 해제하는 함수
 void freeLinkedList(ListNode** head) {
     ListNode* current = *head;
     ListNode* nextNode;
     while (current != NULL) {
         nextNode = current->next;
         free(current);
         current = nextNode;
     }
     *head = NULL;
 }
 
 // --------------------------------------------------------
 // 배열(Array) 관련 함수들
 // --------------------------------------------------------
 
 // 배열의 모든 요소에 순차 접근하여 시간을 측정하는 함수
 // 배열을 초기화한 후 REP_COUNT 만큼 반복하며 접근 시간을 측정합니다.
 void measureArrayAccess(int size) {
     // 배열 생성 및 초기화
     int* arr = (int*)malloc(size * sizeof(int));
     if (arr == NULL) {
         printf("메모리 할당 오류\n");
         exit(1);
     }
     for (int i = 0; i < size; i++) {
         arr[i] = i;
     }
     
     // 접근 시간 측정 시작 (최적화 방지를 위해 volatile 사용)
     volatile int sum = 0;
     clock_t start = clock();
     
     for (int rep = 0; rep < REP_COUNT; rep++) {
         for (int i = 0; i < size; i++) {
             sum += arr[i];
         }
     }
     
     clock_t end = clock();
     int elapsed_ms = (int)((end - start) * 1000 / CLOCKS_PER_SEC);
     
     // 결과 출력
     printf("[1번 문제] 배열 접근 시간 (%d개 요소, %d회 반복): %d 밀리초\n",
            size, REP_COUNT, elapsed_ms);
     
     free(arr);
 }
 
 // --------------------------------------------------------
 // 연결 리스트 접근 시간 측정을 위한 함수
 // --------------------------------------------------------
 
 // 연결 리스트를 생성하고 REP_COUNT 만큼 반복하여 모든 노드를 순차 접근하며 시간을 측정합니다.
 // 연결 리스트의 첫 번째 요소의 인덱스는 1로 가정합니다.
 void measureLinkedListAccess(int size) {
     // 연결 리스트 생성 및 초기화
     ListNode* head = NULL;
     for (int i = 0; i < size; i++) {
         insertAtEnd(&head, i);
     }
     
     // 접근 시간 측정 시작
     volatile int sum = 0;
     clock_t start = clock();
     
     for (int rep = 0; rep < REP_COUNT; rep++) {
         ListNode* current = head;
         int index = 1; // 첫 번째 요소의 인덱스를 1로 가정
         while (current != NULL) {
             sum += current->data;
             current = current->next;
             index++;
         }
     }
     
     clock_t end = clock();
     int elapsed_ms = (int)((end - start) * 1000 / CLOCKS_PER_SEC);
     
     // 결과 출력
     printf("[1번 문제] 연결 리스트 접근 시간 (%d개 요소, %d회 반복): %d 밀리초\n",
            size, REP_COUNT, elapsed_ms);
     
     freeLinkedList(&head);
 }
 
 // --------------------------------------------------------
 // 예제 프로그램 실행 함수
 // --------------------------------------------------------
 
 // 1,000,000,000번의 반복문 실행 시간을 측정하는 예제 코드
 void runExampleProgram() {
     clock_t start, end;
     unsigned long long i;
     
     start = clock();
     /* 시간을 측정하고자 하는 코드 시작 */
     for (i = 0; i < 1000000000ULL; i++);
     /* 시간을 측정하고자 하는 코드 끝 */
     end = clock();
     
     int elapsed_ms = (int)((end - start) * 1000 / CLOCKS_PER_SEC);
     printf("[1번 문제] 예제 프로그램 실행 시간: %d 밀리초\n", elapsed_ms);
 }
 
 // --------------------------------------------------------
 // main 함수
 // --------------------------------------------------------
 int main() {
     printf("===============================================\n");
     printf("[1번 문제] 배열과 연결 리스트 성능 비교\n");
     printf("===============================================\n\n");
     
     // 테스트할 데이터 크기 배열
     int sizes[] = {10000, 100000, 1000000};
     int numSizes = sizeof(sizes) / sizeof(sizes[0]);
     
     // 각 크기에 대해 배열 및 연결 리스트 접근 시간 측정
     for (int i = 0; i < numSizes; i++) {
         int size = sizes[i];
         
         // 배열 접근 시간 측정
         measureArrayAccess(size);
         
         // 연결 리스트 접근 시간 측정
         measureLinkedListAccess(size);
         
         printf("\n");
     }
     
     // 예제 프로그램 실행 시간 측정
     printf("[1번 문제] 예제 프로그램 실행:\n");
     runExampleProgram();
     
     return 0;
 }