/*
 * 학번: 202214314
 * 이름: 이지현
 * 실행환경: Mac
 * 
 * [1번 문제: 배열과 연결 리스트 성능 비교]
 * 이 프로그램은 수업 시간에 배운 배열(Array)과 단일 연결 리스트(Singly Linked List)의 성능을 비교합니다:
 * 1. 배열과 연결 리스트의 접근 시간 비교
 * 2. 연결 리스트의 경우, 첫 번째 element의 index를 1로 가정하고 C 스타일 코드와는 달리 0으로 가정
 * 3. C 프로그램에 대한 시간 측정은 첨부된 예제 프로그램을 참고하여 작성하고, 수행시간의 경우 millisecond 단위로 표시
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 
 #define REP_COUNT 1000
 
 // [1번 문제] 단일 연결 리스트의 노드 구조체 정의
 typedef struct ListNode {
     int data;
     struct ListNode *next;
 } ListNode;
 
 // [1번 문제] 새 노드 생성 함수
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
 
 // [1번 문제] 연결 리스트 끝에 노드 추가 함수
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
     
     // 마지막 노드 다음에 새 노드 추가
     current->next = newNode;
 }
 
 // [1번 문제] 연결 리스트 메모리 해제 함수
 void freeLinkedList(ListNode** head) {
     ListNode* current = *head;
     ListNode* next;
     
     while (current != NULL) {
         next = current->next;
         free(current);
         current = next;
     }
     
     *head = NULL;
 }
 
 // [1번 문제] 배열 접근 시간 측정 함수
 void measureArrayAccess(int size) {
     // 배열 생성
     int* arr = (int*)malloc(size * sizeof(int));
     if (arr == NULL) {
         printf("메모리 할당 오류\n");
         return;
     }
     
     // 배열 초기화
     for (int i = 0; i < size; i++) {
         arr[i] = i;
     }
     
     // 접근 시간 측정 시작
     volatile int sum = 0;
     clock_t start = clock();
     
     for (int rep = 0; rep < REP_COUNT; rep++) {
         for (int i = 0; i < size; i++) {
             sum += arr[i];
         }
     }
     
     clock_t end = clock();
     
     // 밀리초 단위로 변환하여 결과 출력
     printf("[1번 문제] 배열 접근 시간 (%d개 요소, %d회 반복): %d 밀리초\n", 
            size, REP_COUNT, (int)((end - start) * 1000 / CLOCKS_PER_SEC));
     
     free(arr);
 }
 
 // [1번 문제] 연결 리스트 접근 시간 측정 함수 (첫 번째 요소 인덱스를 1로 가정)
 void measureLinkedListAccess(int size) {
     // 연결 리스트 생성
     ListNode* head = NULL;
     
     // 연결 리스트 초기화
     for (int i = 0; i < size; i++) {
         insertAtEnd(&head, i);
     }
     
     // 접근 시간 측정 시작
     volatile int sum = 0;
     clock_t start = clock();
     
     for (int rep = 0; rep < REP_COUNT; rep++) {
         ListNode* current = head;
         while (current != NULL) {
             sum += current->data;
             current = current->next;
         }
     }
     
     clock_t end = clock();
     
     // 밀리초 단위로 변환하여 결과 출력
     printf("[1번 문제] 연결 리스트 접근 시간 (%d개 요소, %d회 반복): %d 밀리초\n", 
            size, REP_COUNT, (int)((end - start) * 1000 / CLOCKS_PER_SEC));
     
     freeLinkedList(&head);
 }
 
 // [1번 문제] 예제 프로그램 실행
 void runExampleProgram() {
     clock_t start;
     clock_t end;
     unsigned long long i;
     
     start = clock();
     /* 시간을 측정하고자 하는 코드 시작 */
     for (i = 0; i < 1000000000; i++);
     /* 시간을 측정하고자 하는 코드 끝 */
     end = clock();
     
     printf("[1번 문제] 예제 프로그램 실행 시간: %d 밀리초\n", (int)((end - start) * 1000 / CLOCKS_PER_SEC));
 }
 
 int main() {
     printf("===============================================\n");
     printf("[1번 문제] 배열과 연결 리스트 성능 비교\n");
     printf("===============================================\n\n");
     
     // 다양한 크기로 테스트
     int sizes[] = {10000, 100000, 1000000};
     
     for (int i = 0; i < 3; i++) {
         int size = sizes[i];
         
         // 접근 시간 측정
         measureArrayAccess(size);
         measureLinkedListAccess(size);
         
         printf("\n");
     }
     
     // 예제 프로그램 실행
     printf("[1번 문제] 예제 프로그램 실행:\n");
     runExampleProgram();
     
     return 0;
 }