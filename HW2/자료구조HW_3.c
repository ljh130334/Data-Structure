/*
 * 학번: 202214314
 * 이름: 이지현
 * 실행환경: Mac
 *
 * [1-(2)번 문제: Array vs Linked List Random Access (Read)]
 *
 * <문제 설명>
 * 1) Array:
 *    - 크기가 100,000인 배열을 준비하고 0 ~ 99,999로 초기화
 *    - 100,000번 반복하면서 매번 랜덤 인덱스를 생성(index = rand() % size)하여
 *      그 위치에 있는 데이터를 sum에 누적
 *    - 전체 걸린 시간을 밀리초 단위로 측정
 *
 * 2) Linked List:
 *    - 단일 연결 리스트를 0 ~ 99,999로 초기화 (100,000개 노드)
 *    - 100,000번 반복하면서 매번 랜덤 인덱스를 생성(index = rand() % size)하고,
 *      해당 인덱스까지 순차적으로 이동하여 노드의 data를 sum에 누적
 *    - 전체 걸린 시간을 밀리초 단위로 측정
 *
 * 주의: Visual Studio 환경에서 rand()의 범위가 작을 경우, 
 *       index = (int)((double)rand() / RAND_MAX * (size - 1)) 와 같이 처리 가능
 *       여기서는 간단히 rand() % size로 구현
 *
 * 시간 측정은 clock() 함수를 사용하며,
 * (end - start) * 1000 / CLOCKS_PER_SEC 로 밀리초 단위로 변환합니다.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 
 // --------------------------------------------------------
 // 전역 상수 정의
 // --------------------------------------------------------
 #define SIZE 100000     // 배열 또는 연결 리스트의 크기
 #define NUM_ACCESS 100000 // 랜덤 접근 횟수 (100,000번)
 
 // --------------------------------------------------------
 // 연결 리스트 (Linked List) 관련 함수들
 // --------------------------------------------------------
 typedef struct ListNode {
     int data;
     struct ListNode* next;
 } ListNode;
 
 // 새 노드를 생성하는 함수
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
 
 // 연결 리스트의 끝에 노드를 추가하는 함수
 void insertAtEnd(ListNode** head, int data) {
     ListNode* newNode = createNode(data);
     
     if (*head == NULL) {
         *head = newNode;
         return;
     }
     
     ListNode* current = *head;
     while (current->next != NULL) {
         current = current->next;
     }
     current->next = newNode;
 }
 
 // 연결 리스트의 메모리를 해제하는 함수
 void freeLinkedList(ListNode** head) {
     ListNode* current = *head;
     while (current != NULL) {
         ListNode* temp = current;
         current = current->next;
         free(temp);
     }
     *head = NULL;
 }
 
 // --------------------------------------------------------
 // 배열 (Array) 랜덤 접근 측정 함수
 // --------------------------------------------------------
 void measureArrayRandomAccess() {
     // 배열 생성 및 초기화
     int* arr = (int*)malloc(SIZE * sizeof(int));
     if (arr == NULL) {
         printf("메모리 할당 오류\n");
         exit(1);
     }
     for (int i = 0; i < SIZE; i++) {
         arr[i] = i;
     }
     
     // 랜덤 시드 설정(매번 실행 시 다른 결과를 원한다면 time(NULL) 등 사용)
     srand((unsigned int)time(NULL));
     
     // 랜덤 접근 시간 측정
     long long sum = 0;  // 누적 합(오버플로 방지 위해 long long 사용)
     clock_t start = clock();
     
     for (int i = 0; i < NUM_ACCESS; i++) {
         int index = rand() % SIZE; // 0 ~ (SIZE-1)
         sum += arr[index];
     }
     
     clock_t end = clock();
     int elapsed_ms = (int)((end - start) * 1000 / CLOCKS_PER_SEC);
     
     printf("[1-(2)번 문제] Array 랜덤 접근 (100,000번) 수행 시간: %d 밀리초\n", elapsed_ms);
     
     // sum 변수를 사용하지 않으면 최적화될 수 있으므로, 최적화 방지용 출력(옵션)
     // printf("sum = %lld\n", sum);
     
     free(arr);
 }
 
 // --------------------------------------------------------
 // 연결 리스트 (Linked List) 랜덤 접근 측정 함수
 // --------------------------------------------------------
 void measureLinkedListRandomAccess() {
     // 연결 리스트 생성 (노드 100,000개)
     ListNode* head = NULL;
     for (int i = 0; i < SIZE; i++) {
         insertAtEnd(&head, i);
     }
     
     srand((unsigned int)time(NULL)); // 랜덤 시드 설정
     
     // 랜덤 접근 시간 측정
     long long sum = 0;
     clock_t start = clock();
     
     for (int i = 0; i < NUM_ACCESS; i++) {
         int index = rand() % SIZE; // 0 ~ (SIZE-1)
         
         // index 번째 노드를 찾기 위해 순차적으로 이동
         ListNode* current = head;
         for (int j = 0; j < index; j++) {
             current = current->next;
         }
         sum += current->data;
     }
     
     clock_t end = clock();
     int elapsed_ms = (int)((end - start) * 1000 / CLOCKS_PER_SEC);
     
     printf("[1-(2)번 문제] Linked List 랜덤 접근 (100,000번) 수행 시간: %d 밀리초\n", elapsed_ms);
     
     freeLinkedList(&head);
 }
 
 // --------------------------------------------------------
 // main 함수
 // --------------------------------------------------------
 int main() {
     printf("===============================================\n");
     printf("[1-(2)번 문제] Array vs Linked List Random Access\n");
     printf("===============================================\n\n");
     
     // Array 랜덤 접근 시간 측정
     measureArrayRandomAccess();
     
     // Linked List 랜덤 접근 시간 측정
     measureLinkedListRandomAccess();
     
     return 0;
 }